#include "core/ShaderProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

ShaderProgram::ShaderProgram(
    const std::string& vertex_path,
    const std::string& fragment_path) {

    std::string vertex_code = LoadFile(vertex_path);
    std::string fragment_code = LoadFile(fragment_path);

    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertex_code);
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragment_code);

    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);

    GLint success;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(id_, 512, nullptr, info_log);
        throw std::runtime_error(std::string("Shader link failed: ") + info_log);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id_);
}

void ShaderProgram::Use() const {
    glUseProgram(id_);
}

GLuint ShaderProgram::GetID() const {
    return id_;
}

void ShaderProgram::SetInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string ShaderProgram::LoadFile(const std::string& file_path) {
    std::ifstream file(file_path);
    std::stringstream buffer;
    if (!file) {
        throw std::runtime_error("Failed to load shader: " + file_path);
    }

    buffer << file.rdbuf();
    return buffer.str();
}

GLuint ShaderProgram::CompileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* code = source.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(id_, 512, nullptr, info_log);
        throw std::runtime_error(std::string("Shader compile failed: ") + info_log);
    }
    
    return shader;
}
