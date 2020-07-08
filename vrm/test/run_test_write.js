"use strict"

const fs = require('fs');
const path = require('path');
const basepath = path.join(__dirname, 'models');
const { spawnSync } = require('child_process');

const exe = path.join(__dirname, 'build', 'Debug', 'test_write.exe');

let failed_count = 0;
let tested_count = 0;

let json_failed_count = 0;
let json_tested_count = 0;

fs.readdir(basepath, (err, files) => {
	if (err) throw err;

	files.filter(file => /.*\.vrm$/.test(file)).forEach(file => {
		const vrm = path.join(basepath, file);
		const p = spawnSync(exe, [vrm], {cwd: __dirname});

		process.stdout.write(p.stdout);
		const code = p.status;
		if (code != 0) failed_count++;
		tested_count++;
	});

	console.log((failed_count == 0 ? '[OK] ' : '[FAILED] ') + `${tested_count} tested, ${failed_count} errors`);

	if (failed_count == 0) {
		fs.readdir(basepath, (err, files) => {
			files.filter(file => /.*\.in.json$/.test(file)).forEach(file => {
				const json = path.join(basepath, file);
				const p2 = spawnSync('node', ['vrm_format_check.js', json, json.replace('.in.', '.out.')], {cwd: __dirname});

				process.stdout.write(p2.stdout);
				process.stderr.write(p2.stderr);
				const code = p2.status;
				if (code != 0) json_failed_count++;
				json_tested_count++;
			});
			console.log((json_failed_count == 0 ? '[OK] ' : '[FAILED] ') + `${json_tested_count} tested, ${json_failed_count} errors`);
		});
	}
});


