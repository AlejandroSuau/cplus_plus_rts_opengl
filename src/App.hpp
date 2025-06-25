#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>

#include "core/OpenGLContext.hpp"
#include "core/ShaderProgram.hpp"
#include "core/InputManager.hpp"
#include "core/Camera2D.hpp"
#include "core/Camera3D.hpp"
#include "core/Mesh.hpp"
#include "core/Texture2D.hpp"
#include "core/ObjModel.hpp"

#include <memory>

enum class CameraMode {
    FPS_3D,
    ORTHO_2D
};

class App {
public:
    App();
    void Run();

private:
    std::unique_ptr<OpenGLContext> context_;
    std::unique_ptr<InputManager> input_manager_;
    std::unique_ptr<Camera3D> fps_camera_;
    std::unique_ptr<Camera2D> ortho_camera_;
    std::unique_ptr<ShaderProgram> shader_;
    bool is_running_{true};
    CameraMode camera_mode_{CameraMode::ORTHO_2D};

    std::unique_ptr<Mesh> mesh_;
    std::unique_ptr<ObjModel> model_;
    std::unique_ptr<Texture2D> texture_;

    void Init();
    void Update(float dt);
    void Render();
    void HandleEvents();
};
