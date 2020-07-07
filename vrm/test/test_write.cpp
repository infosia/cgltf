#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#include "../../cgltf_write.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>

int main(int argc, char** argv)
{
	if (argc < 2)
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

	result = cgltf_write_file(&options, "out.gltf", data0);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to write file\n");
		return result;
	}
	cgltf_data* data1 = NULL;
	result = cgltf_parse_file(&options, "out.gltf", &data1);
	if (result != cgltf_result_success)
	{
		printf("[FAILED] failed to parse written file\n");
		return result;
	}
	if (data0->vrm.humanoid.humanBones_count != data1->vrm.humanoid.humanBones_count) {
		printf("[FAILED] failed to test vrm humanBones\n");
		return -1;
	}

	if (data0->vrm.humanoid.humanBones_count != data1->vrm.humanoid.humanBones_count) {
		printf("[FAILED] failed to test vrm humanBones\n");
		return -1;
	}

	if (data0->vrm.materialProperties_count != data1->vrm.materialProperties_count) {
		printf("[FAILED] failed to test vrm materialProperties\n expected: %zd, actual %zd", data0->vrm.materialProperties_count, data1->vrm.materialProperties_count);
		return -1;
	}

	printf("[OK] all tests passed\n");
	cgltf_free(data1);
	cgltf_free(data0);
	return cgltf_result_success;
}
