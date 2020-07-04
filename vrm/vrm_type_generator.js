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

	free_def.push('static void ' + typename + '_free(const struct cgltf_memory_options* memory, ' + typename + '* data) {');

	structs_def.push('typedef struct ' + typename + ' {')

	Object.keys(json.properties).forEach(name => {
		const type = json.properties[name].type;
		const ref  = json.properties[name]['$ref'];
		const primitive = selectType(type);
		if (type == 'string') {
			const enums = json.properties[name]['enum'];
			if (enums && Array.isArray(enums)) {
				const enumname = typename + '_' + name;
				enums_def.push('typedef enum ' + enumname + ' {');
				enum_selector_def.push('static cgltf_bool select_' + enumname + '(const char* name, ' + enumname + '* out) {');

				enum_selector_def.push(indent + 'if (strlen(name) == 0) {');
				enum_selector_def.push(indent + indent + 'return 0;');
				enums.forEach(value => {
					const enumvalue = enumname + '_' + value;
					enums_def.push(indent + enumvalue + ',');
					enum_selector_def.push(indent + '} else if (strncmp(name, "' + value + '", ' + value.length + ') == 0) {');
					enum_selector_def.push(indent + indent + '*out = ' + enumvalue + ';');
					enum_selector_def.push(indent + indent + 'return 1;');
				});
				enum_selector_def.push(indent + '}');
				enum_selector_def.push(indent + indent + 'return 0;');

				enums_def.push('} ' + enumname + ';')
				enums_def.push('');
				enum_selector_def.push('}');
				enum_selector_def.push('');
			} else {
				structs_def.push(indent + 'char* ' + name + ';');
				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + ');');
			}
		} else if (primitive) {
			structs_def.push(indent + primitive + ' ' + name + ';');
		} else if (type == 'object') {
			if (vec3(json.properties[name])) {
				structs_def.push(indent + 'cgltf_float* ' + name + '; // [x, y, z]');
				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + ');');
			} else if (name == 'floatProperties' || name == 'textureProperties' || name == 'keywordMap') {
				const property_type = selectType(name);
				structs_def.push(indent + 'char** ' + name + '_keys;');
				structs_def.push(indent + property_type + '* ' + name + '_values;');
				structs_def.push(indent + 'cgltf_size ' + name + '_count;');

				free_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				free_def.push(indent + indent + 'memory->free(memory->user_data, data->' + name + '_keys[i]);');
				free_def.push(indent + '}');

				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_keys);');
				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_values);');

			} else if (name == 'vectorProperties' || name == 'tagMap') {
				const property_type = selectType(name);
				structs_def.push(indent + 'char** ' + name + '_keys;');
				structs_def.push(indent + property_type + '* ' + name + '_values;');
				structs_def.push(indent + 'cgltf_size ' + name + '_count;');

				free_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				free_def.push(indent + indent + 'memory->free(memory->user_data, data->' + name + '_keys[i]);');
				free_def.push(indent + indent + 'memory->free(memory->user_data, data->' + name + '_values[i]);');
				free_def.push(indent + '}');

				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_keys);');
				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_values);');

			} else {
				throw new Error('Unknown type: ' + json.type + ' for ' + name + ' in ' + file);
			}
		} else if (type == 'array') {
			const items = json.properties[name].items;
			if (items) {
				const refs  = items['$ref'];
				const primitives = selectType(items.type);
				if (refs) {
					structs_def.push(indent + prefix + sanitize(refs) + '* ' + name + ';');
					free_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent + indent + prefix + sanitize(refs) + '_free(memory, &data->'  + name + '[i]);');
					free_def.push(indent + '}');
				} else if (primitives) {
					structs_def.push(indent + primitives + '* ' + name + ';');
				} else if (items.type == 'object') {
					let member_type = typename + '_' + name;
					structs_def.push(indent + member_type + '* ' + name + ';');
					dependencies_def.push(parse(items, file, typename, name));
					free_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent + indent + member_type + '_free(memory, &data->'  + name + '[i]);');
					free_def.push(indent + '}');
				} else {
					throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
				}
				structs_def.push(indent + 'cgltf_size ' + name + '_count;');
				free_def.push(indent + 'memory->free(memory->user_data, data->' + name + ');');
			} else {
				throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
			}
		} else if (ref) {
			structs_def.push(indent + prefix + sanitize(ref) + ' ' + name + ';');
			free_def.push(indent + prefix + sanitize(ref) + '_free(memory, &data->'  + name + ');');
		} else {
			throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
		}
	});

	structs_def.push('} ' + typename + ';');
	structs_def.push('');

	// mark unused variables in case there's nothing to output
	if (free_def.length == 1) {
		free_def.push(indent + '(void)memory;');
		free_def.push(indent + '(void)data;');
	}

	free_def.push('}');

	return {enums:enums_def, structs:structs_def, dependencies:dependencies_def, free: free_def, enum_selector:enum_selector_def};
}

fs.readdir(basepath, (err, files) => {
    if (err) throw err;

	console.log(fs.readFileSync(path.join(__dirname, 'vrm_types_header.txt'), 'utf8'));

   	let structs_def = [];
	let enums_def   = [];
	let dependencies_def = [];
	let free_def = [];
	let enum_selector_def = [];

    files.filter(file => /.*\.json$/.test(file)).forEach(file => {
		const json = JSON.parse(fs.readFileSync(path.join(basepath, file), 'utf8'));
		const defs = parse(json, file);

		if (defs.enums) enums_def = enums_def.concat(defs.enums);
		if (defs.dependencies) dependencies_def = dependencies_def.concat(defs.dependencies);
		if (defs.structs) structs_def = structs_def.concat(defs.structs);
		if (defs.free) free_def = free_def.concat(defs.free);
		if (defs.enum_selector) enum_selector_def = enum_selector_def.concat(defs.enum_selector);
    });

    console.log(enums_def.join('\n'));
    dependencies_def.forEach(deps => {
	    console.log(deps.enums.join('\n'));
	    console.log(deps.structs.join('\n'));
	    if (deps.free) free_def = deps.free.concat(free_def);
		if (deps.enum_selector) enum_selector_def = enum_selector_def.concat(deps.enum_selector);
    });
    console.log(structs_def.join('\n'));
    console.log(free_def.join('\n'));
	console.log(enum_selector_def.join('\n'));

	console.log(fs.readFileSync(path.join(__dirname, 'vrm_types_footer.txt'), 'utf8'));
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
