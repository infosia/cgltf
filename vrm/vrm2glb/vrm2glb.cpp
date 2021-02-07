/* vrm2glb is distributed under MIT license:
 *
 * Copyright (c) 2021 Kota Iguchi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#define CGLTF_VRM_v0_0
#define CGLTF_VRM_v0_0_IMPLEMENTATION

#include "../../cgltf_write.h"
#include "CLI11.hpp"

static void f3_min(cgltf_float* a, cgltf_float* b, cgltf_float* out)
{
    out[0] = a[0] < b[0] ? a[0] : b[0];
    out[1] = a[1] < b[1] ? a[1] : b[1];
    out[2] = a[2] < b[2] ? a[2] : b[2];
}

static void f3_max(cgltf_float* a, cgltf_float* b, cgltf_float* out)
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

    uint32_t json_align = json_size % 4;
    json_size += json_align;

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
    for (uint32_t i = 0; i < json_align; ++i) {
        out_st << ' ';
    }
    out_st << in_bin_st.rdbuf();

    out_st.close();
}

int main(int argc, char** argv)
{
    CLI::App app { "vrm2glb: Convert VRM to valid glTF binary (.glb)" };

    std::string input;
    app.add_option("-i,--input", input, "input VRM file name");

    bool strip = false;
    app.add_flag("-s,--strip", strip, "strip VRM extension");

    CLI11_PARSE(app, argc, argv);

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

    std::set<cgltf_accessor*> accessor_done;
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

                if (accessor_done.count(accessor) > 0) {
                    continue;
                }
                if (attr->type == cgltf_attribute_type_position) {
                    std::cout << "[INFO] " << accessor->count << " vertices" << std::endl;
                    vrm_vec3_convert_coord(accessor);
                } else if (attr->type == cgltf_attribute_type_normal) {
                    std::cout << "[INFO] " << accessor->count << " normals" << std::endl;
                    vrm_vec3_convert_coord(accessor);
                }
                accessor_done.emplace(accessor);
            }

            for (cgltf_size k = 0; k < primitive->targets_count; ++k) {
                const auto target = &primitive->targets[k];
                for (cgltf_size a = 0; a < target->attributes_count; ++a) {
                    const auto attr = &target->attributes[a];
                    const auto accessor = attr->data;
                    if (accessor_done.count(accessor) > 0) {
                        continue;
                    }
                    if (attr->type == cgltf_attribute_type_position) {
                        std::cout << "[INFO] " << accessor->count << " morph vertices" << std::endl;
                        vrm_vec3_convert_coord(accessor);
                    } else if (attr->type == cgltf_attribute_type_normal) {
                        std::cout << "[INFO] " << accessor->count << " morph normals" << std::endl;
                        vrm_vec3_convert_coord(accessor);
                    }
                    accessor_done.emplace(accessor);
                }
            }
        }
    }

    for (cgltf_size i = 0; i < data->skins_count; ++i) {
        const auto skin = &data->skins[i];
        const auto accessor = skin->inverse_bind_matrices;
        uint8_t* buffer_data = (uint8_t*)accessor->buffer_view->buffer->data + accessor->buffer_view->offset + accessor->offset;

        for (cgltf_size j = 0; j < skin->joints_count; ++j) {
            cgltf_float* element = (cgltf_float*)(buffer_data + accessor->stride * j);

            element[12] = -element[12];
            element[14] = -element[14];
        }
    }

    for (cgltf_size i = 0; i < data->nodes_count; ++i) {
        const auto node = &data->nodes[i];
        if (node->has_translation) {
            node->translation[0] = -node->translation[0];
            node->translation[2] = -node->translation[2];
        }
    }

    result = cgltf_validate(data);

    if (result != cgltf_result_success) {
        std::cout << "[WARN] Invalid glTF data: " << result << std::endl;
    }

    if (strip) {
        data->has_vrm_v0_0 = false;
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
