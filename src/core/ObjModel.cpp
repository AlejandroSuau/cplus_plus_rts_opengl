#include "core/ObjModel.hpp"

#include "tiny_obj_loader.h"

#include <vector>
#include <iostream>
#include <stdexcept>

ObjModel::ObjModel(const std::string& path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if (!warn.empty()) std::cout << "[WARN]: " << warn << std::endl;
    if (!err.empty()) std::cerr << "[ERROR]: " << err << std::endl;

    if (!ret) throw std::runtime_error("Failed to load OBJ file");

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    for (const auto& shape: shapes) {
        for (const auto& index : shape.mesh.indices) {
            float vx = attrib.vertices[3 * index.vertex_index + 0];
            float vy = attrib.vertices[3 * index.vertex_index + 1];
            float vz = attrib.vertices[3 * index.vertex_index + 2];
            vertices.push_back(vx);
            vertices.push_back(vy);
            vertices.push_back(vz);
            
            float nx = 0.f, ny = 0.f, nz = 0.f;
            if (!attrib.normals.empty() && index.normal_index >= 0) {
                nx = attrib.normals[3 * index.normal_index + 0];
                ny = attrib.normals[3 * index.normal_index + 1];
                nz = attrib.normals[3 * index.normal_index + 2];
            }
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);

            // UV (si existen)
            if (!attrib.texcoords.empty() && index.texcoord_index >= 0) {
                float tx = attrib.texcoords[2 * index.texcoord_index + 0];
                float ty = attrib.texcoords[2 * index.texcoord_index + 1];
                vertices.push_back(tx);
                vertices.push_back(ty);
            } else {
                vertices.push_back(0.0f); // UV dummy
                vertices.push_back(0.0f);
            }

            indices.push_back(indices.size());
        }
    }

    mesh_ = std::make_unique<Mesh>(vertices, indices);
}

void ObjModel::Draw() const {
    mesh_->Draw();
}
