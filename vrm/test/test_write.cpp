#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#include "../../cgltf_write.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("[FAILED] too few arguments\n");
		return -1;
	}

	cgltf_options options = {};
	cgltf_data* data0 = NULL;
	cgltf_result result = cgltf_parse_file(&options, argv[1], &data0);

	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to parse file\n");
		return cgltf_result_success;
	}

	result = cgltf_write_file(&options, argv[2], data0);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to write file\n");
		return result;
	}
	cgltf_data* data1 = NULL;
	result = cgltf_parse_file(&options, argv[2], &data1);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to parse %s\n", argv[2]);
		return result;
	}

	if (data0->vrm.exporterVersion && strncmp(data0->vrm.exporterVersion, data1->vrm.exporterVersion , strlen(data0->vrm.exporterVersion)) != 0) {
		printf("[FAILED] failed to test vrm exporterVersion: %s, actual %s\n", data0->vrm.exporterVersion, data1->vrm.exporterVersion);
		return -1;
	}

	if (data0->vrm.meta.title && strncmp(data0->vrm.meta.title, data1->vrm.meta.title , strlen(data0->vrm.meta.title)) != 0) {
		printf("[FAILED] failed to test vrm meta.title: %s, actual %s\n", data0->vrm.meta.title, data1->vrm.meta.title);
		return -1;
	}

	if (data1->vrm.humanoid.humanBones_count == 0 || data0->vrm.humanoid.humanBones_count != data1->vrm.humanoid.humanBones_count) {
		printf("[FAILED] failed to test vrm humanoid.humanBones_count expected: %zd, actual %zd\n", data0->vrm.humanoid.humanBones_count, data1->vrm.humanoid.humanBones_count);
		return -1;
	}

	if (data0->vrm.firstPerson.firstPersonBone != data1->vrm.firstPerson.firstPersonBone) {
		printf("[FAILED] failed to test vrm firstPerson.firstPersonBone expected: %d, actual %d\n", data0->vrm.firstPerson.firstPersonBone, data1->vrm.firstPerson.firstPersonBone);
		return -1;
	}

	if (data0->vrm.blendShapeMaster.blendShapeGroups_count != data1->vrm.blendShapeMaster.blendShapeGroups_count) {
		printf("[FAILED] failed to test vrm blendShapeMaster.blendShapeGroups_count expected: %zd, actual %zd\n", data0->vrm.blendShapeMaster.blendShapeGroups_count, data1->vrm.blendShapeMaster.blendShapeGroups_count);
		return -1;
	}

	if (data0->vrm.secondaryAnimation.boneGroups_count != data1->vrm.secondaryAnimation.boneGroups_count) {
		printf("[FAILED] failed to test vrm secondaryAnimation.boneGroups_count expected: %zd, actual %zd\n", data0->vrm.secondaryAnimation.boneGroups_count, data1->vrm.secondaryAnimation.boneGroups_count);
		return -1;
	}

	if (data1->vrm.materialProperties_count == 0 || data0->vrm.materialProperties_count != data1->vrm.materialProperties_count) {
		printf("[FAILED] failed to test vrm materialProperties expected: %zd, actual %zd\n", data0->vrm.materialProperties_count, data1->vrm.materialProperties_count);
		return -1;
	}

	printf("[OK] all tests passed\n");
	cgltf_free(data1);
	cgltf_free(data0);
	return cgltf_result_success;
}
