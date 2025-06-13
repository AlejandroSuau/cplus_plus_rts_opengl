#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>

#include "core/OpenGLContext.hpp"
#include "core/ShaderProgram.hpp"

#include <memory>

class App {
public:
    App();
    void Run();

private:
    std::unique_ptr<OpenGLContext> context_;
    std::unique_ptr<ShaderProgram> shader_;
    unsigned int VAO_, VBO_;
    bool is_running_;

    void Init();
    void Update(float dt);
    void Render();
    void HandleEvents();
};
