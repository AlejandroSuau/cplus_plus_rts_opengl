#pragma once

#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>

#include "core/ResourceManager.hpp"

#include "core/OpenGLContext.hpp"
#include "core/InputManager.hpp"
#include "core/Camera2D.hpp"
#include "core/ObjModel.hpp"
#include "core/Camera3D.hpp"

#include "render/ShaderProgram.hpp"
#include "render/Renderer.hpp"
#include "render/Mesh.hpp"
#include "render/Texture2D.hpp"

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
    bool is_running_{true};
    CameraMode camera_mode_{CameraMode::ORTHO_2D};

    std::shared_ptr<ShaderProgram> shader_;
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<ObjModel> model_;
    std::shared_ptr<Texture2D> texture_;

    Renderer renderer_;

    void Init();
    void Update(float dt);
    void Render();
    void HandleEvents();
};
