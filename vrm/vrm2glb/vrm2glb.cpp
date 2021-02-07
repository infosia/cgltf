#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#define CGLTF_VRM_v0_0
#define CGLTF_VRM_v0_0_IMPLEMENTATION

#include "../../cgltf_write.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>

static inline void f3_min(cgltf_float* a, cgltf_float* b, cgltf_float* out)
{
    out[0] = a[0] < b[0] ? a[0] : b[0];
    out[1] = a[1] < b[1] ? a[1] : b[1];
    out[2] = a[2] < b[2] ? a[2] : b[2];
}

static inline void f3_max(cgltf_float* a, cgltf_float* b, cgltf_float* out)
{
    out[0] = a[0] > b[0] ? a[0] : b[0];
    out[1] = a[1] > b[1] ? a[1] : b[1];
    out[2] = a[2] > b[2] ? a[2] : b[2];
}

static void vrm_vec3_convert_coord(cgltf_accessor* accessor)
{
    uint8_t* buffer_data = (uint8_t*)accessor->buffer_view->buffer->data + accessor->buffer_view->offset + accessor->offset;

    for (cgltf_size i = 0; i < accessor->count; ++i) {
        cgltf_float* element = (cgltf_float*)(buffer_data + (accessor->stride * i));
        element[0] = -element[0];
        element[2] = -element[2];

        f3_max(element, accessor->max, accessor->max);
        f3_min(element, accessor->min, accessor->min);
    }
}

static void write_bin(cgltf_data* data, std::string output)
{
    std::ofstream fout;
    fout.open(output.c_str(), std::ios::out | std::ios::binary);

    for (cgltf_size i = 0; i < data->buffers_count; i++) {
        cgltf_buffer* buffer = &data->buffers[i];

        fout.write(reinterpret_cast<const char*>(&buffer->size), 4);
        fout.write(reinterpret_cast<const char*>(&GlbMagicBinChunk), 4);
        fout.write(reinterpret_cast<const char*>(buffer->data), buffer->size);
    }

    fout.close();
}

static void write(std::string output, std::string in_json, std::string in_bin)
{
    std::ifstream in_json_st(in_json, std::ios::binary);
    std::ifstream in_bin_st(in_bin, std::ios::binary);
    std::ofstream out_st(output, std::ios::trunc | std::ios::binary);

    in_json_st.seekg(0, std::ios::end);
    uint32_t json_size = (uint32_t)in_json_st.tellg();
    in_json_st.seekg(0, std::ios::beg);

    in_bin_st.seekg(0, std::ios::end);
    uint32_t bin_size = (uint32_t)in_bin_st.tellg();
    in_bin_st.seekg(0, std::ios::beg);

    uint32_t total_size = GlbHeaderSize + GlbChunkHeaderSize + json_size + bin_size;

    out_st.write(reinterpret_cast<const char*>(&GlbMagic), 4);
    out_st.write(reinterpret_cast<const char*>(&GlbVersion), 4);
    out_st.write(reinterpret_cast<const char*>(&total_size), 4);

    out_st.write(reinterpret_cast<const char*>(&json_size), 4);
    out_st.write(reinterpret_cast<const char*>(&GlbMagicJsonChunk), 4);

    out_st << in_json_st.rdbuf();
    out_st << in_bin_st.rdbuf();

    out_st.close();
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("[FAILED] too few arguments\n");
        printf("[INFO] Usage: vrm2glb input.vrm\n");
        return -1;
    }

    std::string input = argv[1];

    cgltf_options options = {};
    cgltf_data* data = NULL;
    cgltf_result result = cgltf_parse_file(&options, input.c_str(), &data);

    if (result != cgltf_result_success) {
        std::cout << "[FAILED] failed to parse file " << input << std::endl;
        return result;
    }

    result = cgltf_load_buffers(&options, data, input.c_str());

    if (result != cgltf_result_success) {
        std::cout << "[FAILED] failed to load buffers from " << input << std::endl;
        cgltf_free(data);
        return result;
    }

    std::set<cgltf_size> buffer_view_done;
    std::cout << "[INFO] Converting " << input << std::endl;
    for (cgltf_size i = 0; i < data->meshes_count; ++i) {
        const auto mesh = &data->meshes[i];

        if (mesh->name != nullptr) {
            std::cout << "[INFO] Processing " << mesh->name << std::endl;
        }

        for (cgltf_size j = 0; j < mesh->primitives_count; ++j) {
            const auto primitive = &mesh->primitives[j];

            for (cgltf_size k = 0; k < primitive->attributes_count; ++k) {
                const auto* attr = &primitive->attributes[k];
                const auto accessor = attr->data;
                const auto data_index = accessor->buffer_view_index;

                if (buffer_view_done.count(data_index) > 0) {
                    continue;
                }

                if (attr->type == cgltf_attribute_type_position) {
                    std::cout << "[INFO] " << data_index << ", " << accessor->count << " vertices" << std::endl;
                    vrm_vec3_convert_coord(accessor);
                    buffer_view_done.emplace(data_index);
                } else if (attr->type == cgltf_attribute_type_normal) {
                    std::cout << "[INFO] " << data_index << ", " << accessor->count << " normals" << std::endl;
                    vrm_vec3_convert_coord(accessor);
                    buffer_view_done.emplace(data_index);
                }
            }
        }
    }

    for (cgltf_size i = 0; i < data->nodes_count; ++i) {
        const auto node = &data->nodes[i];
        if (node->has_translation) {
            node->translation[0] = -node->translation[0];
            node->translation[2] = -node->translation[2];
        }
    }

    for (cgltf_size i = 0; i < data->skins_count; ++i) {
        const auto skin = &data->skins[i];
        const auto accessor = skin->inverse_bind_matrices;
        uint8_t* buffer_data = (uint8_t*)accessor->buffer_view->buffer->data + accessor->buffer_view->offset;
        cgltf_float* element = (cgltf_float*)(buffer_data + accessor->offset + accessor->stride * i);

        element[12] = -element[12];
        element[14] = -element[14];
    }

    std::string output = input + ".glb";
    std::string out_json = input + ".json";
    std::string out_bin = input + ".bin";

    cgltf_write_file(&options, out_json.c_str(), data);

    write_bin(data, out_bin);
    write(output, out_json, out_bin);

    cgltf_free(data);

    std::cout << "[INFO] Successfully converted to " << output << std::endl;

    return cgltf_result_success;
}
