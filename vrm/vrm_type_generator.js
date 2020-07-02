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
	let func_def = [];

	func_def.push('static void ' + typename + '_free(const struct cgltf_memory_options* memory, ' + typename + '* data) {');

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
				enums.forEach(value => {
					enums_def.push(indent + enumname + '_' + value + ',');
				});
				enums_def.push('} ' + enumname + ';')
				enums_def.push('');
			} else {
				structs_def.push(indent + 'char* ' + name + ';');
				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + ');');
			}
		} else if (primitive) {
			structs_def.push(indent + primitive + ' ' + name + ';');
		} else if (type == 'object') {
			if (vec3(json.properties[name])) {
				structs_def.push(indent + 'cgltf_float* ' + name + '; // [x, y, z]');
				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + ');');
			} else if (name == 'floatProperties' || name == 'textureProperties' || name == 'keywordMap') {
				const property_type = selectType(name);
				structs_def.push(indent + 'char** ' + name + '_keys;');
				structs_def.push(indent + property_type + '* ' + name + '_values;');
				structs_def.push(indent + 'cgltf_size ' + name + '_count;');

				func_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				func_def.push(indent + indent + 'memory->free(memory->user_data, data->' + name + '_keys[i]);');
				func_def.push(indent + '}');

				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_keys);');
				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_values);');

			} else if (name == 'vectorProperties' || name == 'tagMap') {
				const property_type = selectType(name);
				structs_def.push(indent + 'char** ' + name + '_keys;');
				structs_def.push(indent + property_type + '* ' + name + '_values;');
				structs_def.push(indent + 'cgltf_size ' + name + '_count;');

				func_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
				func_def.push(indent + indent + 'memory->free(memory->user_data, data->' + name + '_keys[i]);');
				func_def.push(indent + indent + 'memory->free(memory->user_data, data->' + name + '_values[i]);');
				func_def.push(indent + '}');

				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_keys);');
				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + '_values);');

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
					func_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					func_def.push(indent + indent + prefix + sanitize(refs) + '_free(memory, &data->'  + name + '[i]);');
					func_def.push(indent + '}');
				} else if (primitives) {
					structs_def.push(indent + primitives + '* ' + name + ';');
				} else if (items.type == 'object') {
					let member_type = typename + '_' + name;
					structs_def.push(indent + member_type + '* ' + name + ';');
					dependencies_def.push(parse(items, file, typename, name));
					func_def.push(indent + 'for (cgltf_size i = 0; i < data->' + name + '_count; i++) {');
					func_def.push(indent + indent + member_type + '_free(memory, &data->'  + name + '[i]);');
					func_def.push(indent + '}');
				} else {
					throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
				}
				structs_def.push(indent + 'cgltf_size ' + name + '_count;');
				func_def.push(indent + 'memory->free(memory->user_data, data->' + name + ');');
			} else {
				throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
			}
		} else if (ref) {
			structs_def.push(indent + prefix + sanitize(ref) + ' ' + name + ';');
			func_def.push(indent + prefix + sanitize(ref) + '_free(memory, &data->'  + name + ');');
		} else {
			throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
		}
	});

	structs_def.push('} ' + typename + ';');
	structs_def.push('');

	// mark unused variables in case there's nothing to output
	if (func_def.length == 1) {
		func_def.push(indent + '(void)memory;');
		func_def.push(indent + '(void)data;');
	}

	func_def.push('}');

	return {enums:enums_def, structs:structs_def, dependencies:dependencies_def, func: func_def};
}

fs.readdir(basepath, (err, files) => {
    if (err) throw err;

   	let structs_def = [];
	let enums_def   = [];
	let dependencies_def = [];
	let func_def = [];

    files.filter(file => /.*\.json$/.test(file)).forEach(file => {
		const json = JSON.parse(fs.readFileSync(path.join(basepath, file), 'utf8'));
		const defs = parse(json, file);

		if (defs.enums) enums_def = enums_def.concat(defs.enums);
		if (defs.dependencies) dependencies_def = dependencies_def.concat(defs.dependencies);
		if (defs.structs) structs_def = structs_def.concat(defs.structs);
		if (defs.func) func_def = func_def.concat(defs.func);
    });

    console.log(enums_def.join('\n'));
    dependencies_def.forEach(deps => {
	    console.log(deps.enums.join('\n'));
	    console.log(deps.structs.join('\n'));
	    if (deps.func) func_def = deps.func.concat(func_def);
    });
    console.log(structs_def.join('\n'));
    console.log(func_def.join('\n'));
});



