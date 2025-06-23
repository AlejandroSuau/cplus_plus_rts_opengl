#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>

#include "core/OpenGLContext.hpp"
#include "core/ShaderProgram.hpp"
#include "core/InputManager.hpp"

#include "core/Mesh.hpp"
#include "core/Texture2D.hpp"

#include <memory>

class App {
public:
    App();
    void Run();

private:
    std::unique_ptr<OpenGLContext> context_;
    std::unique_ptr<InputManager> input_manager_;
    std::unique_ptr<ShaderProgram> shader_;
    bool is_running_;

    std::unique_ptr<Mesh> mesh_;
    std::unique_ptr<Texture2D> texture_;

    void Init();
    void Update(float dt);
    void Render();
    void HandleEvents();
};
