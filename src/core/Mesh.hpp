#pragma once

#include <glad/glad.h>

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices,
         unsigned int stride = 8); // stride = 8 for 3 pos + 3 normal + 2 uv
    ~Mesh();

    void Draw() const;

private:
    GLuint VAO_, VBO_, EBO_;
    GLsizei index_count_;
};