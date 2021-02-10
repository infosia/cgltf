/* glb2vrm is distributed under MIT license:
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
#include <emmintrin.h>

#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#define CGLTF_VRM_v0_0
#define CGLTF_VRM_v0_0_IMPLEMENTATION

#include "../../cgltf_write.h"
#include "CLI11.hpp"

#define RETURN_WITH_ERROR(MSG, DATA)             \
    std::cout << "[ERROR] " << MSG << std::endl; \
    cgltf_free(DATA);                            \
    return 1;

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct vec4 {
    float x, y, z, w;
} vec4;

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


static inline vec4 quaternion_mul(vec4 lhs, vec4 rhs)
{
    const vec4 res = {
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
        lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
    };
    return res;
}

static inline vec4 quaternion_inverse(vec4 q)
{
    const vec4 res = {
        -q.x,
        -q.y,
        -q.z,
        q.w,
    };
    return res;
}

static inline vec3 quaternion_rotate_vec3(vec4 q, vec3 v)
{
    const vec4 v4 = { v.x, v.y, v.z };
    const vec4 q_inv = quaternion_inverse(q);
    const vec4 v4_rot = quaternion_mul(q, quaternion_mul(v4, q_inv));
    const vec3 res = {
        v4_rot.x,
        v4_rot.y,
        v4_rot.z,
    };
    return res;
}

static void write_bin(cgltf_data* data, std::string output)
{
    std::ofstream fout;
    fout.open(output.c_str(), std::ios::out | std::ios::binary);

    for (cgltf_size i = 0; i < data->buffers_count; ++i) {
        cgltf_buffer* buffer = &data->buffers[i];

        cgltf_size aligned_size = (buffer->size + 3) & ~3;
        cgltf_size align = aligned_size - buffer->size;

        fout.write(reinterpret_cast<const char*>(&aligned_size), 4);
        fout.write(reinterpret_cast<const char*>(&GlbMagicBinChunk), 4);
        fout.write(reinterpret_cast<const char*>(buffer->data), buffer->size);

        for (uint32_t j = 0; j < align; ++j) {
            fout.write(" ", 1);
        }
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

    uint32_t aligned_json_size = (json_size + 3) & ~3;
    uint32_t json_align = aligned_json_size - json_size;

    in_bin_st.seekg(0, std::ios::end);
    uint32_t bin_size = (uint32_t)in_bin_st.tellg();
    in_bin_st.seekg(0, std::ios::beg);

    uint32_t total_size = GlbHeaderSize + GlbChunkHeaderSize + aligned_json_size + bin_size;

    out_st.write(reinterpret_cast<const char*>(&GlbMagic), 4);
    out_st.write(reinterpret_cast<const char*>(&GlbVersion), 4);
    out_st.write(reinterpret_cast<const char*>(&total_size), 4);

    out_st.write(reinterpret_cast<const char*>(&aligned_json_size), 4);
    out_st.write(reinterpret_cast<const char*>(&GlbMagicJsonChunk), 4);

    out_st << in_json_st.rdbuf();
    for (uint32_t i = 0; i < json_align; ++i) {
        out_st << ' ';
    }
    out_st << in_bin_st.rdbuf();

    out_st.close();
}

static vec3 inverse_bind_translation(const cgltf_node* node) {
    vec3 bind = { node->translation[0], node->translation[1], node->translation[2] };
    cgltf_node* parent = node->parent;
    while(parent != nullptr) {
        bind.x += parent->translation[0];
        bind.y += parent->translation[1];
        bind.z += parent->translation[2];
        parent = parent->parent;
    }
    return bind;
}

int main(int argc, char** argv)
{
    CLI::App app { "glb2vrm: Convert VRM to valid glTF binary (.glb)" };

    std::string input;
    app.add_option("-i,--input", input, "input VRM file name");

    CLI11_PARSE(app, argc, argv);

    cgltf_options options = {};
    cgltf_data* data = NULL;
    cgltf_result result = cgltf_parse_file(&options, input.c_str(), &data);

    if (result != cgltf_result_success) {
        std::cout << "[ERROR] failed to parse file " << input << std::endl;
        return result;
    }

    result = cgltf_load_buffers(&options, data, input.c_str());

    if (result != cgltf_result_success) {
        RETURN_WITH_ERROR("failed to load buffers. Exiting.", data)
    }

    std::cout << "[INFO] Converting " << input << std::endl;
    for (cgltf_size i = 0; i < data->nodes_count; ++i) {
        const auto node = &data->nodes[i];
        vec3 pos = { node->translation[0] * node->scale[0], node->translation[1] * node->scale[1], node->translation[2] * node->scale[2] };
        vec4 rot = { node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3] };
        vec3 newpos = quaternion_rotate_vec3(rot, pos);

        node->translation[0] = newpos.x;
        node->translation[1] = newpos.y;
        node->translation[2] = newpos.z;
        node->rotation[0] = 0;
        node->rotation[1] = 0;
        node->rotation[2] = 0;
        node->rotation[3] = 1;
        node->scale[0] = 1;
        node->scale[1] = 1;
        node->scale[2] = 1;
    }

    std::set<cgltf_accessor*> accessor_done;
    for (cgltf_size i = 0; i < data->skins_count; ++i) {
        const auto skin = &data->skins[i];
        const auto accessor = skin->inverse_bind_matrices;

        if (accessor_done.count(accessor) > 0) {
            continue;
        }
        accessor_done.emplace(accessor);

        uint8_t* buffer_data = (uint8_t*)accessor->buffer_view->buffer->data + accessor->buffer_view->offset + accessor->offset;

        accessor->max[12] = -FLT_MAX;
        accessor->max[14] = -FLT_MAX;
        accessor->min[12] = FLT_MAX;
        accessor->min[14] = FLT_MAX;

        for (cgltf_size j = 0; j < skin->joints_count; ++j) {
            cgltf_node* node = skin->joints[j];
            cgltf_float* inverse_bind_matrix = (cgltf_float*)(buffer_data + accessor->stride * j);

            const auto inverse_translation = inverse_bind_translation(node);

            inverse_bind_matrix[0] = 1.f;
            inverse_bind_matrix[1] = 0.f;
            inverse_bind_matrix[2] = 0.f;
            inverse_bind_matrix[3] = 0.f;
            inverse_bind_matrix[4] = 0.f;
            inverse_bind_matrix[5] = 1.f;
            inverse_bind_matrix[6] = 0.f;
            inverse_bind_matrix[7] = 0.f;
            inverse_bind_matrix[8] = 0.f;
            inverse_bind_matrix[9] = 0.f;
            inverse_bind_matrix[10] = 1.f;
            inverse_bind_matrix[11] = 0.f;
            inverse_bind_matrix[12] = -inverse_translation.x;
            inverse_bind_matrix[13] = -inverse_translation.y;
            inverse_bind_matrix[14] = -inverse_translation.z;
            inverse_bind_matrix[15] = 1.f;

            f3_max(inverse_bind_matrix + 12, accessor->max + 12, accessor->max + 12);
            f3_min(inverse_bind_matrix + 12, accessor->min + 12, accessor->min + 12);
        }
    }

    result = cgltf_validate(data);

    if (result != cgltf_result_success) {
        std::cout << "[WARN] Invalid glTF data: " << result << std::endl;
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
