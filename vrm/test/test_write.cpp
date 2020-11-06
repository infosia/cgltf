#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#define CGLTF_VRM_v0_0
#define CGLTF_VRM_v0_0_IMPLEMENTATION

#include "../../cgltf_write.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>

static void concat(char* dest, const char* base, const char* str) {
	strcpy(dest, base);
	strcat(dest + strlen(base), str);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("[FAILED] too few arguments\n");
		printf("[INFO] Usage: test_write input.vrm\n");
		return -1;
	}

	cgltf_options options = {};
	cgltf_data* data0 = NULL;
	cgltf_result result = cgltf_parse_file(&options, argv[1], &data0);

	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to parse file %s\n", argv[1]);
		return cgltf_result_success;
	}

	const char* in_suffix = ".in.json";
	cgltf_size in_json_size = strlen(argv[1]) + strlen(in_suffix) + 1;;
	char* in_json = (char*)CGLTF_MALLOC(in_json_size);
	concat(in_json, argv[1], in_suffix);
	result = cgltf_write_json(&options, in_json, data0);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to write json %s\n", in_json);
		return result;
	}
	CGLTF_FREE(in_json);

	const char* out_suffix = ".out.json";
	cgltf_size out_json_size = strlen(argv[1]) + strlen(out_suffix) + 1;;
	char* out_json = (char*)CGLTF_MALLOC(out_json_size);
	concat(out_json, argv[1], out_suffix);
	result = cgltf_write_file(&options, out_json, data0);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to write file %s\n", out_json);
		return result;
	}
	cgltf_data* data1 = NULL;
	result = cgltf_parse_file(&options, out_json, &data1);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to parse %s\n", out_json);
		return result;
	}
	CGLTF_FREE(out_json);

	if (data0->vrm_v0_0.exporterVersion && strncmp(data0->vrm_v0_0.exporterVersion, data1->vrm_v0_0.exporterVersion , strlen(data0->vrm_v0_0.exporterVersion)) != 0) {
		printf("[FAILED] failed to test vrm exporterVersion: %s, actual %s\n", data0->vrm_v0_0.exporterVersion, data1->vrm_v0_0.exporterVersion);
		return -1;
	}

	if (data0->vrm_v0_0.meta.title && strncmp(data0->vrm_v0_0.meta.title, data1->vrm_v0_0.meta.title , strlen(data0->vrm_v0_0.meta.title)) != 0) {
		printf("[FAILED] failed to test vrm meta.title: %s, actual %s\n", data0->vrm_v0_0.meta.title, data1->vrm_v0_0.meta.title);
		return -1;
	}

	if (data1->vrm_v0_0.humanoid.humanBones_count == 0 || data0->vrm_v0_0.humanoid.humanBones_count != data1->vrm_v0_0.humanoid.humanBones_count) {
		printf("[FAILED] failed to test vrm humanoid.humanBones_count expected: %zd, actual %zd\n", data0->vrm_v0_0.humanoid.humanBones_count, data1->vrm_v0_0.humanoid.humanBones_count);
		return -1;
	}

	if (data0->vrm_v0_0.firstPerson.firstPersonBone != data1->vrm_v0_0.firstPerson.firstPersonBone) {
		printf("[FAILED] failed to test vrm firstPerson.firstPersonBone expected: %d, actual %d\n", data0->vrm_v0_0.firstPerson.firstPersonBone, data1->vrm_v0_0.firstPerson.firstPersonBone);
		return -1;
	}

	if (data0->vrm_v0_0.blendShapeMaster.blendShapeGroups_count != data1->vrm_v0_0.blendShapeMaster.blendShapeGroups_count) {
		printf("[FAILED] failed to test vrm blendShapeMaster.blendShapeGroups_count expected: %zd, actual %zd\n", data0->vrm_v0_0.blendShapeMaster.blendShapeGroups_count, data1->vrm_v0_0.blendShapeMaster.blendShapeGroups_count);
		return -1;
	}

	if (data0->vrm_v0_0.secondaryAnimation.boneGroups_count != data1->vrm_v0_0.secondaryAnimation.boneGroups_count) {
		printf("[FAILED] failed to test vrm secondaryAnimation.boneGroups_count expected: %zd, actual %zd\n", data0->vrm_v0_0.secondaryAnimation.boneGroups_count, data1->vrm_v0_0.secondaryAnimation.boneGroups_count);
		return -1;
	}

	if (data1->vrm_v0_0.materialProperties_count == 0 || data0->vrm_v0_0.materialProperties_count != data1->vrm_v0_0.materialProperties_count) {
		printf("[FAILED] failed to test vrm materialProperties expected: %zd, actual %zd\n", data0->vrm_v0_0.materialProperties_count, data1->vrm_v0_0.materialProperties_count);
		return -1;
	}

	printf("[OK] all tests passed\n");
	cgltf_free(data1);
	cgltf_free(data0);
	return cgltf_result_success;
}
