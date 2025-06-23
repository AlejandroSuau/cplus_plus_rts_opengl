#pragma once

#include <glad/glad.h>

#include <string>

class Texture2D {
public:
    Texture2D(const std::string& path);
    ~Texture2D();

    void Bind(unsigned int unit = 0) const;

private:
    GLuint id_;
    int width_, height_, channels_;
};