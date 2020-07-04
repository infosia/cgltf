/**
 * vrm_type_generator - generate C11 structs and enums from VRM specification
 *
 * Distributed under the MIT License, see notice at the end of this file.
 *
 */
"use strict"

const fs = require('fs');
const path = require('path');
const basepath = path.join(__dirname, 'scheme');
const prefix   = 'cgltf_';
const indent   = '\t';
const indent1  = indent;
const indent2  = indent + indent1;
const indent3  = indent + indent2;
const indent4  = indent + indent3;
const indent5  = indent + indent4;

function sanitize(str) {
	return str.toLowerCase().replace(/\./g, '_').replace(/_schema_json$/g, '');
}

function selectType(type) {
	if (type == 'integer') return 'cgltf_int';
	if (type == 'number')  return 'cgltf_float';
	if (type == 'boolean') return 'cgltf_bool';
	if (type == 'textureProperties') return 'cgltf_int';
	if (type == 'floatProperties') return 'cgltf_float';
	if (type == 'keywordMap') return 'cgltf_bool';
	if (type == 'vectorProperties') return 'cgltf_float*';
	if (type == 'tagMap') return 'char*';
	return undefined;
}

function selectPrimitiveParser(type) {
	if (type == 'integer') return 'cgltf_json_to_int';
	if (type == 'number')  return 'cgltf_json_to_float';
	if (type == 'boolean') return 'cgltf_json_to_bool';
	return undefined;
}

function vec3(items) {
	return (items.properties && items.properties.x && items.properties.y && items.properties.z
		&& items.properties.x.type == 'number' && items.properties.y.type == 'number' && items.properties.z.type == 'number');
}

function parse(json, file, rootType, subType) {
	if (json.type != 'object') {
		throw new Error('Unknown type: ' + json.type + ' in ' + file);
	}

	const typename = rootType ? (rootType + '_' + subType) : (prefix + sanitize(json.title));

	let structs_def = [];
	let enums_def   = [];
	let dependencies_def = [];
	let free_def = [];
	let enum_selector_def = [];
	let parse_def = [];

	free_def.push('static void ' + typename + '_free(const struct cgltf_memory_options* memory, ' + typename + '* data) {');
	parse_def.push('static int cgltf_parse_json_' + typename.replace('cgltf_', '') + '(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, ' + typename +'* out_data) {');
	parse_def.push(indent1 + '(void)out_data; (void)json_chunk; (void)options;');
	parse_def.push(indent1 + 'if (tokens[i].type == JSMN_OBJECT) {');
	parse_def.push(indent2 + 'int size = tokens[i].size; ++i;');
	parse_def.push(indent2 + 'for (int j = 0; j < size; ++j) {');
	parse_def.push(indent3 + 'if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {');
	parse_def.push(indent4 + 'continue;');

	structs_def.push('typedef struct ' + typename + ' {')

	Object.keys(json.properties).forEach(name => {
		const type = json.properties[name].type;
		const ref  = json.properties[name]['$ref'];
		const primitive = selectType(type);
		if (type == 'string') {
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');
			const enums = json.properties[name]['enum'];
			if (enums && Array.isArray(enums)) {
				const enumname = typename + '_' + name;
				enums_def.push('typedef enum ' + enumname + ' {');
				enum_selector_def.push('static cgltf_bool select_' + enumname + '(const char* name, ' + enumname + '* out) {');

				enum_selector_def.push(indent1 + 'if (strlen(name) == 0) {');
				enum_selector_def.push(indent2 + 'return 0;');
				enums.forEach(value => {
					const enumvalue = enumname + '_' + value;
					enums_def.push(indent1 + enumvalue + ',');
					enum_selector_def.push(indent1 + '} else if (strncmp(name, "' + value + '", ' + value.length + ') == 0) {');
					enum_selector_def.push(indent2 + '*out = ' + enumvalue + ';');
					enum_selector_def.push(indent2 + 'return 1;');
				});
				enum_selector_def.push(indent1 + '}');
				enum_selector_def.push(indent1 + 'return 0;');

				enums_def.push('} ' + enumname + ';')
				enums_def.push('');
				enum_selector_def.push('}');
				enum_selector_def.push('');

				structs_def.push(indent1 + enumname + ' ' + name + ';');
				parse_def.push(indent4 + 'char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);');
				parse_def.push(indent4 + 'i = select_' + enumname + '(enum_key, &out_data->' + name + ') ? i : -1;');
			} else {
				structs_def.push(indent1 + 'char* ' + name + ';');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');
				parse_def.push(indent4 + 'i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->' + name + ');');
			}
		} else if (primitive) {
			structs_def.push(indent1 + primitive + ' ' + name + ';');
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');
			let prim_parser = selectPrimitiveParser(type);
			if (prim_parser) {
				parse_def.push(indent4 + '++i; out_data->' + name + ' = ' + prim_parser + '(tokens + i, json_chunk); ++i;');
			} else {
				throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
			}
		} else if (type == 'object') {
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');

			if (vec3(json.properties[name])) {
				structs_def.push(indent1 + 'cgltf_float* ' + name + '; // [x, y, z]');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');

				parse_def.push(indent4 + 'i = cgltf_parse_json_vec3(options, tokens, i + 1, json_chunk, out_data->' + name + ');');

			} else if (name == 'floatProperties' || name == 'textureProperties' || name == 'keywordMap') {
				const property_type = selectType(name);
				structs_def.push(indent1 + 'char** ' + name + '_keys;');
				structs_def.push(indent1 + property_type + '* ' + name + '_values;');
				structs_def.push(indent1 + 'cgltf_size ' + name + '_count;');

				free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				free_def.push(indent2 + 'memory->free(memory->user_data, data->' + name + '_keys[i]);');
				free_def.push(indent1 + '}');

				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + '_keys);');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + '_values);');

				parse_def.push(indent5 + 'i = cgltf_skip_json(tokens, i + 1);// TODO');
			} else if (name == 'vectorProperties' || name == 'tagMap') {
				const property_type = selectType(name);
				structs_def.push(indent1 + 'char** ' + name + '_keys;');
				structs_def.push(indent1 + property_type + '* ' + name + '_values;');
				structs_def.push(indent1 + 'cgltf_size ' + name + '_count;');

				free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				free_def.push(indent2 + 'memory->free(memory->user_data, data->' + name + '_keys[i]);');
				free_def.push(indent2 + 'memory->free(memory->user_data, data->' + name + '_values[i]);');
				free_def.push(indent1 + '}');

				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + '_keys);');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + '_values);');

				parse_def.push(indent5 + 'i = cgltf_skip_json(tokens, i + 1);// TODO');
			} else {
				throw new Error('Unknown type: ' + json.type + ' for ' + name + ' in ' + file);
			}
		} else if (type == 'array') {
			const items = json.properties[name].items;
			if (items) {
				parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');

				const refs  = items['$ref'];
				const primitives = selectType(items.type);
				if (refs) {
					const refname = sanitize(refs);
					structs_def.push(indent1 + prefix + refname + '* ' + name + ';');
					free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent2 + prefix + refname + '_free(memory, &data->'  + name + '[i]);');
					free_def.push(indent1 + '}');
					parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(' + prefix + refname + '), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
					parse_def.push(indent4 + 'if (i < 0) return i;');
					parse_def.push(indent4 + 'for (cgltf_int k = 0; k < out_data->' + name + '_count; k++) {');
					parse_def.push(indent5 + 'i = cgltf_parse_json_' + refname + '(options, tokens, i, json_chunk, out_data->' + name + ' + k);');
					parse_def.push(indent4 + '}');
				} else if (primitives) {
					structs_def.push(indent1 + primitives + '* ' + name + ';');
					if (items.type == 'number') {
						parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
						parse_def.push(indent4 + 'if (i < 0) return i;');
						parse_def.push(indent4 + 'i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->' + name + ', (int)out_data->' + name + '_count);');
					} else if (items.type == 'integer') {
						parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_int), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
						parse_def.push(indent4 + 'if (i < 0) return i;');
						parse_def.push(indent4 + 'i = cgltf_parse_json_int_array(tokens, i - 1, json_chunk, out_data->' + name + ', (int)out_data->' + name + '_count);');
					} else {
						throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
					}
				} else if (items.type == 'object') {
					let member_type = typename + '_' + name;
					structs_def.push(indent1 + member_type + '* ' + name + ';');
					dependencies_def.push(parse(items, file, typename, name));
					free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent2 + member_type + '_free(memory, &data->'  + name + '[i]);');
					free_def.push(indent1 + '}');
					parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(' + member_type + '), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
					parse_def.push(indent4 + 'if (i < 0) return i;');
					parse_def.push(indent4 + 'for (cgltf_int k = 0; k < out_data->' + name + '_count; k++) {');
					parse_def.push(indent5 + 'i = cgltf_parse_json_' + member_type.replace('cgltf_', '') + '(options, tokens, i, json_chunk, out_data->' + name + ' + k);');
					parse_def.push(indent4 + '}');
				} else {
					throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
				}
				structs_def.push(indent1 + 'cgltf_size ' + name + '_count;');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');
			} else {
				throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
			}
		} else if (ref) {
			const refname = sanitize(ref);
			structs_def.push(indent1 + prefix + refname + ' ' + name + ';');
			free_def.push(indent1 + prefix + refname + '_free(memory, &data->'  + name + ');');
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');
			parse_def.push(indent4 + 'i = cgltf_parse_json_' + refname + '(options, tokens, i + 1, json_chunk, &out_data->' + name + ');');
		} else {
			throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
		}
	});

	structs_def.push('} ' + typename + ';');
	structs_def.push('');

	// mark unused variables in case there's nothing to output
	if (free_def.length == 1) {
		free_def.push(indent1 + '(void)memory;');
		free_def.push(indent1 + '(void)data;');
	}

	free_def.push('}');
	free_def.push('');

	parse_def.push(indent3 + '} else {');
	parse_def.push(indent4 + 'i = cgltf_skip_json(tokens, i + 1);');
	parse_def.push(indent3 +'}');
	parse_def.push(indent3 + 'if (i < 0) return i;');
	parse_def.push(indent2 + '}');
	parse_def.push(indent1 + '} else {');
	parse_def.push(indent2 + 'i = cgltf_skip_json(tokens, i + 1);');
	parse_def.push(indent1 + '}');
	parse_def.push(indent1 + 'return i;');

	parse_def.push('}');

	return {enums:enums_def, structs:structs_def, dependencies:dependencies_def,
			 free: free_def, enum_selector:enum_selector_def, parse: parse_def};
}

fs.readdir(basepath, (err, files) => {
    if (err) throw err;

    let typesStream = fs.createWriteStream(path.join(__dirname, 'vrm_types.h'), 'utf8');
    let inlStream   = fs.createWriteStream(path.join(__dirname, 'vrm_types.inl'), 'utf8');

	typesStream.write(fs.readFileSync(path.join(__dirname, 'vrm_types_header.txt'), 'utf8'));

   	let structs_def = [];
	let enums_def   = [];
	let dependencies_def = [];
	let free_def = [];
	let enum_selector_def = [];
	let parse_def = [];

    files.filter(file => /.*\.json$/.test(file)).forEach(file => {
		const json = JSON.parse(fs.readFileSync(path.join(basepath, file), 'utf8'));
		const defs = parse(json, file);

		if (defs.enums) enums_def = enums_def.concat(defs.enums);
		if (defs.dependencies) dependencies_def = dependencies_def.concat(defs.dependencies);
		if (defs.structs) structs_def = structs_def.concat(defs.structs);
		if (defs.free) free_def = free_def.concat(defs.free);
		if (defs.enum_selector) enum_selector_def = enum_selector_def.concat(defs.enum_selector);
		if (defs.parse) parse_def = parse_def.concat(defs.parse);
    });

    typesStream.write(enums_def.join('\n'));
    dependencies_def.forEach(deps => {
	    typesStream.write(deps.enums.join('\n'));
	    typesStream.write(deps.structs.join('\n'));
	    if (deps.free) free_def = deps.free.concat(free_def);
		if (deps.enum_selector) enum_selector_def = enum_selector_def.concat(deps.enum_selector);
	    if (deps.parse) parse_def = deps.parse.concat(parse_def);
    });
    typesStream.write(structs_def.join('\n'));
    inlStream.write(free_def.join('\n'));
	inlStream.write(enum_selector_def.join('\n'));
	inlStream.write(parse_def.join('\n'));

	typesStream.write(fs.readFileSync(path.join(__dirname, 'vrm_types_footer.txt'), 'utf8'));

	typesStream.close();
	inlStream.close();
});

/* vrm_type_generator is distributed under MIT license:
 *
 * Copyright (c) 2020 Kota Iguchi

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
