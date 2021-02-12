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
#include <sstream>
#include <string>
#include <unordered_map>

#define CGLTF_IMPLEMENTATION
#define CGLTF_WRITE_IMPLEMENTATION
#define CGLTF_VRM_v0_0
#define CGLTF_VRM_v0_0_IMPLEMENTATION

#include "../../cgltf_write.h"
#include "CLI11.hpp"
#include "json11.hpp"

#include "math.inl"

#define RETURN_WITH_ERROR(MSG, DATA)             \
    std::cout << "[ERROR] " << MSG << std::endl; \
    cgltf_free(DATA);                            \
    return 1;

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

    accessor->max[0] = -FLT_MAX;
    accessor->max[2] = -FLT_MAX;
    accessor->min[0] = FLT_MAX;
    accessor->min[2] = FLT_MAX;

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
    std::ifstream in_json_st(in_json, std::ios::in | std::ios::binary);
    std::ifstream in_bin_st(in_bin, std::ios::in | std::ios::binary);
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

static tm_vec3_t inverse_bind_translation(const cgltf_node* node)
{
    tm_vec3_t bind = { node->translation[0], node->translation[1], node->translation[2] };
    cgltf_node* parent = node->parent;
    while (parent != nullptr) {
        bind.x += parent->translation[0];
        bind.y += parent->translation[1];
        bind.z += parent->translation[2];
        parent = parent->parent;
    }
    return bind;
}

static void transform_apply(cgltf_node* node, const tm_mat44_t* parent_matrix)
{
    const tm_vec3_t pos = { node->translation[0], node->translation[1], node->translation[2] };
    const tm_vec3_t scale = { node->scale[0], node->scale[1], node->scale[2] };
    const tm_vec4_t rot = { node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3] };

    tm_vec3_t pos_unused, scale_unused;
    tm_vec4_t rot_parent;
    tm_mat44_to_translation_quaternion_scale(&pos_unused, &rot_parent, &scale_unused, parent_matrix);

    tm_vec3_t newpos = tm_quaternion_rotate_vec3(rot_parent, pos);

    tm_mat44_t self, bind_matrix;
    tm_mat44_from_translation_quaternion_scale(&self, pos, rot, scale);
    tm_mat44_mul(&bind_matrix, &self, parent_matrix);

    node->translation[0] = -newpos.x;
    node->translation[1] = newpos.y;
    node->translation[2] = -newpos.z;
    node->rotation[0] = 0;
    node->rotation[1] = 0;
    node->rotation[2] = 0;
    node->rotation[3] = 1;
    node->scale[0] = 1;
    node->scale[1] = 1;
    node->scale[2] = 1;

    for (cgltf_size i = 0; i < node->children_count; i++) {
        transform_apply(node->children[i], &bind_matrix);
    }
}

static char* alloc_chars(const char* str) {
    const auto length = strlen(str);
    if (length == 0) {
        return (char*)calloc(1, 1);
    }
    auto dst = (char*)calloc(length + 1, 1);
    if (dst > 0)
        strncpy(dst, str, length);    

    return dst;
}

static void ensure_defaults(cgltf_data* data) {
    data->has_vrm_v0_0 = true;

    const auto vrm = &data->vrm_v0_0;
    const auto meta = &vrm->meta;

    vrm->exporterVersion = alloc_chars("cgltf+VRM 1.9");
    vrm->specVersion = alloc_chars("0.0");

    meta->title = alloc_chars("");
    meta->author = alloc_chars("");
    meta->version = alloc_chars("");
    meta->contactInformation = alloc_chars("");
    meta->reference = alloc_chars("");
}

static bool update_bone_mapping(std::string file, cgltf_data* data)
{
    std::ifstream f(file, std::ios::in);
    if (f.fail()) {
        std::cout << "[ERROR] failed to read bone mapping file " << file << std::endl;
        return false;
    }

    std::ostringstream ss;
    ss << f.rdbuf();
    std::string content = ss.str();

    std::string parse_error;
    const auto json = json11::Json::parse(content, parse_error);

    if (!parse_error.empty()) {
        std::cout << "[ERROR] failed to parse bone mapping file " << file << std::endl;
        std::cout << parse_error << std::endl;
        return false;
    }

    const auto vrm = &data->vrm_v0_0.humanoid;
    const auto bones = json.object_items();

    if (bones.size() == 0) {
        std::cout << "[ERROR] no bone mapping found in " << file << std::endl;
        return false;
    }

    vrm->humanBones_count = bones.size();
    vrm->humanBones = (cgltf_vrm_humanoid_bone_v0_0*)malloc(sizeof(cgltf_vrm_humanoid_bone_v0_0) * bones.size());

    std::unordered_map<std::string, cgltf_int> node_names;
    for (cgltf_size i = 0; i < data->nodes_count; ++i) {
        const auto node = &data->nodes[i];
        if (node->name != nullptr && strlen(node->name) > 0) {
            std::string name = node->name;
            node_names.emplace(name, static_cast<cgltf_int>(i));
        }
    }

    cgltf_size i = 0;
    for (const auto bone : bones) {

        if (!bone.second.is_string()) {
            std::cout << "[ERROR] bone mapping is not a string. index=" << i << std::endl;
            return false;            
        }

        auto dst = &vrm->humanBones[i];

        // defaults
        dst->axisLength = 0;
        dst->useDefaultValues = true;
        dst->center_count = 1;
        dst->min_count = 1;
        dst->max_count = 1;
        dst->node = 0;

        dst->center = (cgltf_float*)calloc(3, sizeof(cgltf_float));
        dst->max = (cgltf_float*)calloc(3, sizeof(cgltf_float));
        dst->min = (cgltf_float*)calloc(3, sizeof(cgltf_float));

        const auto found = node_names.find(bone.second.string_value());
        if (found != node_names.end()) {
            dst->node = found->second;
            select_cgltf_vrm_humanoid_bone_bone_v0_0(bone.first.c_str(), &dst->bone);
        }

        i++;
    }

    return true;
}

int main(int argc, char** argv)
{
    CLI::App app { "glb2vrm: Convert glTF binary (.glb) to VRM" };

    std::string input;
    app.add_option("-i,--input", input, "input glTF binary (.glb) file name");

    std::string bones_mapping_file;
    app.add_option("-b,--bone", bones_mapping_file, "bone to VRM humanBones mapping (JSON)");

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
    std::set<cgltf_accessor*> accessor_coord_done;
    for (cgltf_size i = 0; i < data->meshes_count; ++i) {
        const auto mesh = &data->meshes[i];

        if (mesh->name != nullptr) {
            std::cout << "[INFO] Processing " << mesh->name << std::endl;
        }

        for (cgltf_size j = 0; j < mesh->primitives_count; ++j) {
            const auto primitive = &mesh->primitives[j];

            for (cgltf_size k = 0; k < primitive->attributes_count; ++k) {
                const auto attr = &primitive->attributes[k];
                const auto accessor = attr->data;

                if (accessor_coord_done.count(accessor) > 0) {
                    continue;
                }
                if (attr->type == cgltf_attribute_type_position) {
                    std::cout << "[INFO] " << accessor->count << " vertices" << std::endl;
                    vrm_vec3_convert_coord(accessor);
                } else if (attr->type == cgltf_attribute_type_normal) {
                    std::cout << "[INFO] " << accessor->count << " normals" << std::endl;
                    vrm_vec3_convert_coord(accessor);
                }
                accessor_coord_done.emplace(accessor);
            }

            for (cgltf_size k = 0; k < primitive->targets_count; ++k) {
                const auto target = &primitive->targets[k];
                for (cgltf_size a = 0; a < target->attributes_count; ++a) {
                    const auto attr = &target->attributes[a];
                    const auto accessor = attr->data;
                    if (accessor_coord_done.count(accessor) > 0) {
                        continue;
                    }
                    if (attr->type == cgltf_attribute_type_position) {
                        std::cout << "[INFO] " << accessor->count << " morph vertices" << std::endl;
                        vrm_vec3_convert_coord(accessor);
                    } else if (attr->type == cgltf_attribute_type_normal) {
                        std::cout << "[INFO] " << accessor->count << " morph normals" << std::endl;
                        vrm_vec3_convert_coord(accessor);
                    }
                    accessor_coord_done.emplace(accessor);
                }
            }
        }
    }

    const auto identity = tm_mat44_identity();
    for (cgltf_size i = 0; i < data->scenes_count; ++i) {
        const auto scene = &data->scenes[i];
        for (cgltf_size j = 0; j < scene->nodes_count; ++j) {
            transform_apply(scene->nodes[j], identity);
        }
    }

    std::set<cgltf_accessor*> skin_done;
    for (cgltf_size i = 0; i < data->skins_count; ++i) {
        const auto skin = &data->skins[i];
        const auto accessor = skin->inverse_bind_matrices;

        if (skin_done.count(accessor) > 0) {
            continue;
        }
        skin_done.emplace(accessor);

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

    if (!bones_mapping_file.empty()) {
        update_bone_mapping(bones_mapping_file, data);
    }

    ensure_defaults(data);

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
