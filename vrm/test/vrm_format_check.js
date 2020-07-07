"use strict"

const fs = require('fs');
const path = require('path');

if (process.argv.length < 4) {
	console.log('[FAILED] Too few arguments');
	console.log('Usage: node vrm_format_check.js in.json out.json');
	return;
}

var args = process.argv.slice(2);

const before = JSON.parse(fs.readFileSync(path.join(__dirname, args[0]), 'utf8'));
const after  = JSON.parse(fs.readFileSync(path.join(__dirname, args[1]), 'utf8'));

let count = 0, failed = 0;

function almostEquals(a, b) {
	if (a === b) return true;
	let aa = parseFloat(a.toFixed(7));
	let bb = parseFloat(b.toFixed(7));
	if (aa < bb + 0.000001 && aa > bb - 0.000001) return true;
	return false;
}

var traverse = function(o1, o2, fn) {
	for (var i in o1) {
		let type = typeof(o1[i]);
		if (type != 'object') {
			count++;
			if (type == 'number' ? !almostEquals(o1[i], o2[i]) : (o1[i] != o2[i])) {
				failed++;
				console.log('----------');
				console.log('Checking ' + JSON.stringify(o1) + ' => ' + JSON.stringify(o2));
				console.log('Expected: ' + JSON.stringify(o1[i]));
				console.log('Found: ' + JSON.stringify(o2[i]));
			}
		}

		if (o1[i] !== null && typeof(o1[i])=='object') {
			traverse(o1[i], o2[i], fn);
		}
	}
}

traverse(before.extensions.VRM, after.extensions.VRM);

console.log('----------');
console.log((failed == 0 ? '[OK] ' : '[FAILED] ') + count + ' checked, ' + failed + ' errors');
