/**
 * vrm_type_generator - generate C11 structs and enums from VRM specification
 *
 * Distributed under the MIT License, see notice at the end of this file.
 *
 */
"use strict"

const supportedVersions = ['0.0', '1.0'];

const fs = require('fs');
const path = require('path');
const basepath = path.join(__dirname, 'schema');
const prefix   = 'cgltf_';
const indent   = '\t';
const indent1  = indent;
const indent2  = indent + indent1;
const indent3  = indent + indent2;
const indent4  = indent + indent3;
const indent5  = indent + indent4;

function sanitize(str) {
	return str.replace(/^\d+\./, '').toLowerCase().replace(/\./g, '_').replace(/_schema_json$/g, '');
}

function sanitizeVersion(str) {
	return str.replace(/\./g, '_');
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

function selectWriteFunc(type) {
	if (type == 'string') return 'cgltf_write_strprop';
	if (type == 'integer' || type == 'cgltf_int')    return 'cgltf_write_intprop_strict';
	if (type == 'number'  || type == 'cgltf_float')  return 'cgltf_write_floatprop_strict';
	if (type == 'boolean' || type == 'cgltf_bool')   return 'cgltf_write_boolprop_strict';
	return type;
}

function vec3(items) {
	return (items.properties && items.properties.x && items.properties.y && items.properties.z
		&& items.properties.x.type == 'number' && items.properties.y.type == 'number' && items.properties.z.type == 'number');
}

function parse(json, file, version, rootType, subType) {
	if (json.type != 'object') {
		throw new Error('Unknown type: ' + json.type + ' in ' + file);
	}

	const suffix = '_v' + sanitizeVersion(version);
	const title = sanitize(file);
	const typename = rootType ? (rootType.replace(suffix, '') + '_' + subType + suffix) : (prefix + title + suffix);

	let structs_def = [];
	let enums_def   = [];
	let dependencies_def = [];
	let free_def = [];
	let enum_selector_def = [];
	let enum_to_str_def = [];
	let parse_def = [];
	let write_def = [];

	free_def.push('static void ' + typename + '_free(const struct cgltf_memory_options* memory, ' + typename + '* data) {');
	parse_def.push('static int cgltf_parse_json_' + typename.replace('cgltf_', '') + '(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, ' + typename +'* out_data) {');
	parse_def.push(indent1 + '(void)options;');
	parse_def.push(indent1 + 'if (tokens[i].type == JSMN_OBJECT) {');
	parse_def.push(indent2 + 'int size = tokens[i].size; ++i;');
	parse_def.push(indent2 + 'for (int j = 0; j < size; ++j) {');
	parse_def.push(indent3 + 'if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {');
	parse_def.push(indent4 + 'continue;');

	structs_def.push('typedef struct ' + typename + ' {')

	write_def.push('static void cgltf_write_' + typename.replace('cgltf_', '') + '(cgltf_write_context* context, const ' + typename + '* data) {');
	write_def.push(indent1 + 'cgltf_write_line(context, "{");');

	Object.keys(json.properties).forEach(name => {
		const type = json.properties[name].type;
		const ref  = json.properties[name]['$ref'];
		const primitive = selectType(type);
		const allOf = json.properties[name].allOf;

		if (type == 'string') {
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');
			const enums = json.properties[name]['enum'];
			if (enums && Array.isArray(enums)) {
				const enumname = typename.replace(suffix, '') + '_' + name + suffix;
				enums_def.push('typedef enum ' + enumname + ' {');
				enum_selector_def.push('static cgltf_bool select_' + enumname + '(const char* name, ' + enumname + '* out) {');

				enum_to_str_def.push('static const char* ' + enumname + '_to_str(const ' + enumname + ' in) {');
				enum_to_str_def.push(indent1 + 'switch (in) {');	

				enum_selector_def.push(indent1 + 'if (strlen(name) == 0) {');
				enum_selector_def.push(indent2 + 'return 0;');
				enums.forEach(value => {
					const enumvalue = enumname + '_' + value;
					enums_def.push(indent1 + enumvalue + ',');
					enum_selector_def.push(indent1 + '} else if (strlen(name) == ' + value.length + ' && strncmp(name, "' + value + '", ' + value.length + ') == 0) {');
					enum_selector_def.push(indent2 + '*out = ' + enumvalue + ';');
					enum_selector_def.push(indent2 + 'return 1;');

					enum_to_str_def.push(indent2 + 'case ' + enumvalue + ': return "' + value + '";');
				});
				enum_selector_def.push(indent1 + '}');
				enum_selector_def.push(indent1 + 'return 0;');

				enums_def.push('} ' + enumname + ';\n')
				enum_selector_def.push('}\n');

				enum_to_str_def.push(indent2 + 'default: return "";');	
				enum_to_str_def.push(indent1 + '}');	
				enum_to_str_def.push('}\n');

				structs_def.push(indent1 + enumname + ' ' + name + ';');
				parse_def.push(indent4 + 'char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);');
				parse_def.push(indent4 + 'i = select_' + enumname + '(enum_key, &out_data->' + name + ') ? i : -1;');

				write_def.push(indent1 + 'cgltf_write_strprop(context, "' + name + '", ' + enumname + '_to_str(data->' + name + '));');
			} else {
				structs_def.push(indent1 + 'char* ' + name + ';');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');
				parse_def.push(indent4 + 'i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->' + name + ');');
				write_def.push(indent1 + 'cgltf_write_strprop(context, "' + name + '", data->' + name + ');');
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
			write_def.push(indent1 + selectWriteFunc(type) + '(context, "' + name + '", data->' + name + ');');
		} else if (!ref && type == 'object') {
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');

			if (vec3(json.properties[name])) {
				structs_def.push(indent1 + 'cgltf_float* ' + name + '; // [x, y, z]');
				structs_def.push(indent1 + 'cgltf_size ' + name + '_count;');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');
				parse_def.push(indent4 + 'i = cgltf_parse_json_vec3(options, tokens, i + 1, json_chunk, &out_data->' + name + ', &out_data->' + name + '_count);');
				write_def.push(indent1 + 'if (data->' + name + '_count > 0) {');

				write_def.push(indent2 + 'cgltf_write_line(context, "\\"' + name + '\\": {");');
				write_def.push(indent2 + 'cgltf_write_floatprop_strict(context, "x", data->' + name + '[0]);');
				write_def.push(indent2 + 'cgltf_write_floatprop_strict(context, "y", data->' + name + '[1]);');
				write_def.push(indent2 + 'cgltf_write_floatprop_strict(context, "z", data->' + name + '[2]);');
				write_def.push(indent2 + 'cgltf_write_line(context, "}");');
				write_def.push(indent1 + '}');
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

				parse_def.push(indent5 + 'i = cgltf_parse_json_' + property_type.replace('cgltf_', '') + '_properties(options, tokens, i + 1, json_chunk, &out_data->' + name + '_keys, &out_data->' + name + '_values, &out_data->' + name + '_count);');

				write_def.push(indent1 + 'cgltf_write_line(context, "\\"' + name + '\\": {");');
				write_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				write_def.push(indent2 + selectWriteFunc(property_type) + '(context, data->' + name + '_keys[i], data->' + name + '_values[i]);');
				write_def.push(indent1 + '}');
				write_def.push(indent1 + 'cgltf_write_line(context, "}");');
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

				write_def.push(indent1 + 'cgltf_write_line(context, "\\"' + name + '\\": {");');
				write_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				if (name == 'vectorProperties') {
					structs_def.push(indent1 + 'cgltf_size* ' + name + '_floats_size;');
					free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + '_floats_size);');
					parse_def.push(indent5 + 'i = cgltf_parse_json_floats_properties(options, tokens, i + 1, json_chunk, &out_data->' + name + '_keys, &out_data->' + name + '_values, &out_data->' + name + '_floats_size, &out_data->' + name + '_count);');

					write_def.push(indent2 + 'cgltf_write_floatarrayprop(context, data->' + name + '_keys[i], data->' + name + '_values[i], data->' + name + '_floats_size[i]);');

				} else {
					parse_def.push(indent5 + 'i = cgltf_parse_json_chars_properties(options, tokens, i + 1, json_chunk, &out_data->' + name + '_keys, &out_data->' + name + '_values, &out_data->' + name + '_count);');
					write_def.push(indent2 + 'cgltf_write_strprop(context, data->' + name + '_keys[i], data->' + name + '_values[i]);');
				}

				write_def.push(indent1 + '}');
				write_def.push(indent1 + 'cgltf_write_line(context, "}");');
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
					const refname = sanitize(refs) + suffix;
					structs_def.push(indent1 + prefix + refname + '* ' + name + ';');
					free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent2 + prefix + refname + '_free(memory, &data->'  + name + '[i]);');
					free_def.push(indent1 + '}');
					parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(' + prefix + refname + '), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
					parse_def.push(indent4 + 'if (i < 0) return i;');
					parse_def.push(indent4 + 'for (cgltf_size k = 0; k < out_data->' + name + '_count; k++) {');
					parse_def.push(indent5 + 'i = cgltf_parse_json_' + refname + '(options, tokens, i, json_chunk, out_data->' + name + ' + k);');
					parse_def.push(indent4 + '}');

					write_def.push(indent1 + 'cgltf_write_line(context, "\\"' + name + '\\": [");');
					write_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; ++i) {');
					write_def.push(indent2 + 'cgltf_write_' + refname + '(context, data->' + name + ' + i);');
					write_def.push(indent1 + '}');
					write_def.push(indent1 + 'cgltf_write_line(context, "]");');

				} else if (primitives) {
					structs_def.push(indent1 + primitives + '* ' + name + ';');
					if (items.type == 'number') {
						parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
						parse_def.push(indent4 + 'if (i < 0) return i;');
						parse_def.push(indent4 + 'i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->' + name + ', (int)out_data->' + name + '_count);');
						write_def.push(indent1 + 'cgltf_write_floatarrayprop(context, "' + name + '", data->' + name + ', data->' + name + '_count);');
					} else if (items.type == 'integer') {
						parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_int), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
						parse_def.push(indent4 + 'if (i < 0) return i;');
						parse_def.push(indent4 + 'i = cgltf_parse_json_int_array(tokens, i - 1, json_chunk, out_data->' + name + ', (int)out_data->' + name + '_count);');
						write_def.push(indent1 + 'cgltf_write_intarrayprop(context, "' + name + '", data->' + name + ', data->' + name + '_count);');
					} else {
						throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
					}
				} else if (items.type == 'object') {
					let member_type = typename.replace(suffix, '') + '_' + name + suffix;
					let member_func = member_type.replace('cgltf_', '');
					structs_def.push(indent1 + member_type + '* ' + name + ';');
					dependencies_def.push(parse(items, file, version, typename, name));
					free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent2 + member_type + '_free(memory, &data->'  + name + '[i]);');
					free_def.push(indent1 + '}');
					parse_def.push(indent4 + 'i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(' + member_type + '), (void**)&out_data->' + name + ', &out_data->' + name + '_count);');
					parse_def.push(indent4 + 'if (i < 0) return i;');
					parse_def.push(indent4 + 'for (cgltf_size k = 0; k < out_data->' + name + '_count; k++) {');
					parse_def.push(indent5 + 'i = cgltf_parse_json_' + member_func + '(options, tokens, i, json_chunk, out_data->' + name + ' + k);');
					parse_def.push(indent4 + '}');

					write_def.push(indent1 + 'cgltf_write_line(context, "\\"' + name + '\\": [");');
					write_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; ++i) {');
					write_def.push(indent2 + 'cgltf_write_' + member_func + '(context, data->' + name + ' + i);');
					write_def.push(indent1 + '}');
					write_def.push(indent1 + 'cgltf_write_line(context, "]");');

				} else if (items.type == 'string') {
					structs_def.push(indent1 + 'char** ' + name + ';');
					free_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					free_def.push(indent2 + 'memory->free(memory->user_data, &data->'  + name + '[i]);');
					free_def.push(indent1 + '}');

					parse_def.push(indent4 + 'i = cgltf_parse_json_string_array(options, tokens, i + 1, json_chunk, &out_data->' + name + ', &out_data->' + name + '_count);');

					write_def.push(indent1 + 'cgltf_write_line(context, "\\"' + name + '\\": [");');
					write_def.push(indent1 + 'for (cgltf_size i = 0; i < data->' + name + '_count; ++i) {');
					write_def.push(indent2 + 'cgltf_write_strprop(context, "' + name + '", data->' + name + ' + i);');
					write_def.push(indent1 + '}');
					write_def.push(indent1 + 'cgltf_write_line(context, "]");');

				} else {
					throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
				}
				structs_def.push(indent1 + 'cgltf_size ' + name + '_count;');
				free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');

			} else {
				throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
			}
		} else if (ref) {
			const refname = sanitize(ref) + suffix;
			structs_def.push(indent1 + prefix + refname + ' ' + name + ';');
			free_def.push(indent1 + prefix + refname + '_free(memory, &data->'  + name + ');');
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');
			parse_def.push(indent4 + 'i = cgltf_parse_json_' + refname + '(options, tokens, i + 1, json_chunk, &out_data->' + name + ');');

			write_def.push(indent1 + 'cgltf_write_line(context, "\\"' + name + '\\": ");');
			write_def.push(indent1 + 'cgltf_write_' + refname + '(context, &data->' + name + ');');
		} else if (allOf) {
			// Note: Currently this only assumes glTF id which is string (See glTFid.schema.json)
			structs_def.push(indent1 + 'char* ' + name + ';');
			free_def.push(indent1 + 'memory->free(memory->user_data, data->' + name + ');');
			parse_def.push(indent3 + '} else if (cgltf_json_strcmp(tokens + i, json_chunk, "' + name + '") == 0) {');
			parse_def.push(indent4 + 'i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->' + name + ');');
			write_def.push(indent1 + 'cgltf_write_strprop(context, "' + name + '", data->' + name + ');');
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

	write_def.push(indent1 + 'cgltf_write_line(context, "}");');
	write_def.push('}');

	return {enums:enums_def, structs:structs_def, dependencies:dependencies_def,
			 free: free_def, enum_selector:enum_selector_def, enum_to_str:enum_to_str_def,
			 parse: parse_def, write: write_def};
}

supportedVersions.forEach(scheme_version => {
	const scheme_dir = path.join(basepath, scheme_version);
	fs.readdir(scheme_dir, (err, files) => {
		if (err) throw err;

		const suffix = 'v' + sanitizeVersion(scheme_version);

		let typesStream = fs.createWriteStream(path.join(__dirname, 'vrm_types.' + suffix + '.h'), 'utf8');
		let typesImplStream = fs.createWriteStream(path.join(__dirname, 'vrm_types.' + suffix + '.inl'), 'utf8');
		let writeImplStream = fs.createWriteStream(path.join(__dirname, 'vrm_write.' + suffix + '.inl'), 'utf8');

		let header = fs.readFileSync(path.join(__dirname, 'vrm_types_header.txt'), 'utf8').toString();
		typesStream.write(header.replace(/_VERSION_/g, '_' + suffix.toUpperCase() + '_'), 'utf8');

		let structs_def = [];
		let enums_def   = [];
		let dependencies_def = [];
		let free_def = [];
		let enum_selector_def = [];
		let enum_to_str_def = [];
		let parse_def = [];
		let write_def = [];

		files.filter(file => /.*\.json$/.test(file)).forEach(file => {
			const json = JSON.parse(fs.readFileSync(path.join(scheme_dir, file), 'utf8'));
			const defs = parse(json, file, scheme_version);

			if (defs.enums) enums_def = enums_def.concat(defs.enums);
			if (defs.dependencies) dependencies_def = dependencies_def.concat(defs.dependencies);
			if (defs.structs) structs_def = structs_def.concat(defs.structs);
			if (defs.free) free_def = free_def.concat(defs.free);
			if (defs.enum_selector) enum_selector_def = enum_selector_def.concat(defs.enum_selector);
			if (defs.enum_to_str) enum_to_str_def = enum_to_str_def.concat(defs.enum_to_str);
			if (defs.parse) parse_def = parse_def.concat(defs.parse);
			if (defs.write) write_def = write_def.concat(defs.write);
		});

		typesStream.write(enums_def.join('\n'));
		dependencies_def.forEach(deps => {
			typesStream.write(deps.enums.join('\n'));
			typesStream.write(deps.structs.join('\n'));
			if (deps.free) free_def = deps.free.concat(free_def);
			if (deps.enum_selector) enum_selector_def = enum_selector_def.concat(deps.enum_selector);
			if (deps.enum_to_str) enum_to_str_def = enum_to_str_def.concat(deps.enum_to_str);
			if (deps.parse) parse_def = deps.parse.concat(parse_def);
			if (deps.write) write_def = deps.write.concat(write_def);
		});
		typesStream.write(structs_def.join('\n'));
		typesImplStream.write(free_def.join('\n'));
		typesImplStream.write(enum_selector_def.join('\n'));
		typesImplStream.write(parse_def.join('\n'));
		writeImplStream.write(enum_to_str_def.join('\n'));
		writeImplStream.write(write_def.join('\n'));

		let footer = fs.readFileSync(path.join(__dirname, 'vrm_types_footer.txt'), 'utf8').toString();
		typesStream.write(footer.replace(/_VERSION_/g, '_' + suffix.toUpperCase() + '_'), 'utf8');

		typesStream.write('\n');
		typesImplStream.write('\n');
		writeImplStream.write('\n');

		typesStream.end();
		typesImplStream.end();
		writeImplStream.end();
	});

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
