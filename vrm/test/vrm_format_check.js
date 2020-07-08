/**
 * vrm_format_check - Compare JSON values for input and output
 *
 * Distributed under the MIT License, see notice at the end of this file.
 *
 */

"use strict"

const fs = require('fs');
const path = require('path');

if (process.argv.length < 4) {
	console.log('[FAILED] Too few arguments');
	console.log('[INFO] Usage: node vrm_format_check.js in.json out.json');
	return;
}

var args = process.argv.slice(2);

const before = JSON.parse(fs.readFileSync(args[0], 'utf8'));
const after  = JSON.parse(fs.readFileSync(args[1], 'utf8'));

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

/* vrm_format_check is distributed under MIT license:
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
