#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertex_path, const std::string& fragment_path);
    ~ShaderProgram();

    void Use() const;
    GLuint GetID() const;

    void SetInt(const std::string& name, int value) const;
    void SetMat4(const std::string& name, const glm::mat4& matrix) const;

private:
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;
    ShaderProgram& operator=(ShaderProgram&&) = delete;

    GLuint id_;
    std::string LoadFile(const std::string& file_path);
    GLuint CompileShader(GLenum type, const std::string& source);
};
