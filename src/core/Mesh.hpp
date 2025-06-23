#pragma once

#include <glad/glad.h>

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices,
        unsigned int stride = 5); // stride: pos(3) + text(2) = 5 by default
    ~Mesh();

    void Draw() const;

private:
    GLuint VAO_, VBO_, EBO_;
    GLsizei index_count_;
};