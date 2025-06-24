#include "core/Mesh.hpp"

Mesh::Mesh(
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    unsigned int stride)
    : index_count_(static_cast<GLsizei>(indices.size())) {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // 3 pos + 3 normal + 2 uv = 8 floats por vértice
    // Layout: [x y z] + [nx ny nz] + [u v]

    // Position (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // UV (vec2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
    glDeleteVertexArrays(1, &VAO_);
}

void Mesh::Draw() const {
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
