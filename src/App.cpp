#include "App.hpp"

#include "core/InputManager.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace {
const float kFixedTimeStep = 0.016666f; // In Seconds
}
std::vector<float> orthoPlaneVertices = {
    -1.f, -1.f, 0.f,  0.f, 0.f,  0.f, 0.f, 1.f,
     1.f, -1.f, 0.f,  1.f, 0.f,  0.f, 0.f, 1.f,
     1.f,  1.f, 0.f,  1.f, 1.f,  0.f, 0.f, 1.f,
    -1.f,  1.f, 0.f,  0.f, 1.f,  0.f, 0.f, 1.f
};

std::vector<unsigned int> planeIndices = {
    0, 1, 2,  // Primer triángulo
    2, 3, 0   // Segundo triángulo
};

// Quad simple con posición (x, y, z) + texcoords (u, v)
std::vector<float> quadVertices = {
    // Positions        // TexCoords
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // Bottom Left
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // Bottom Right
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // Top Right
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // Top Left
};

std::vector<unsigned int> quadIndices = {
    0, 1, 2,  // First Triangle
    2, 3, 0   // Second Triangle
};

App::App() 
    : context_(std::make_unique<OpenGLContext>(800, 600, "RTS Game"))
    , input_manager_(std::make_unique<InputManager>(context_->GetWindow()))
    , fps_camera_(std::make_unique<Camera3D>(glm::vec3(3.f, 3.f, 3.f), glm::vec3(0,1,0), -135.f, -35.f))
    , ortho_camera_(std::make_unique<Camera2D>(-4.f, 4.f, -3.f, 3.f))
    , shader_(ResourceManager::LoadShader("shader1", "assets/shaders/basic.vert", "assets/shaders/basic.frag"))
    , mesh_(std::make_shared<Mesh>(orthoPlaneVertices, planeIndices))
    , model_(ResourceManager::LoadModel("sphere", "assets/models/sphere.obj"))
    , texture_(ResourceManager::LoadTexture("texture1", "assets/images/StoneWall_Texture.png")) {
    Init();
}

void App::Init() {
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(context_->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void App::Run() {
    GLFWwindow* window = context_->GetWindow();

    float last_frame = static_cast<float>(glfwGetTime());
    float accumulator = 0.f;

    while (!glfwWindowShouldClose(window)) {
        float current_frame = static_cast<float>(glfwGetTime());
        float delta_time = (current_frame - last_frame);
        last_frame = current_frame;

        glfwPollEvents();
        HandleEvents();

        accumulator += delta_time;
        while (accumulator >= kFixedTimeStep) {
            Update(kFixedTimeStep);
            accumulator -= kFixedTimeStep;
        }

        Render();
        glfwSwapBuffers(window);
    }
}

void App::Update(float dt) {
    if (camera_mode_ == CameraMode::FPS_3D) {
        if (input_manager_->IsKeyPressed(GLFW_KEY_W)) fps_camera_->ProcessKeyboard('W', dt);
        if (input_manager_->IsKeyPressed(GLFW_KEY_S)) fps_camera_->ProcessKeyboard('S', dt);
        if (input_manager_->IsKeyPressed(GLFW_KEY_A)) fps_camera_->ProcessKeyboard('A', dt);
        if (input_manager_->IsKeyPressed(GLFW_KEY_D)) fps_camera_->ProcessKeyboard('D', dt);
    
        glm::vec2 mouse_delta = input_manager_->GetMouseDelta();
        fps_camera_->ProcessMouseMovement(mouse_delta.x, -mouse_delta.y);
        input_manager_->ResetMouseDelta();
    } else if (camera_mode_ == CameraMode::ORTHO_2D) {
        glm::vec2 move(0.f);
        if (input_manager_->IsKeyPressed(GLFW_KEY_W)) move.y += 1.f;
        if (input_manager_->IsKeyPressed(GLFW_KEY_S)) move.y -= 1.f;
        if (input_manager_->IsKeyPressed(GLFW_KEY_A)) move.x -= 1.f;
        if (input_manager_->IsKeyPressed(GLFW_KEY_D)) move.x += 1.f;
        if (glm::length(move) > 0.f)
            ortho_camera_->Move(move * dt * 5.f); // Velocidad ajustable
        
        if (input_manager_->IsKeyPressed(GLFW_KEY_Q)) ortho_camera_->Zoom(1.0f + dt);
        if (input_manager_->IsKeyPressed(GLFW_KEY_E)) ortho_camera_->Zoom(1.0f - dt);
    }
}

void App::HandleEvents() {
    static bool last_tab = false;
    bool current_tab = input_manager_->IsKeyPressed(GLFW_KEY_TAB);
    if (current_tab && !last_tab) {
        if (camera_mode_ == CameraMode::FPS_3D)
            camera_mode_ = CameraMode::ORTHO_2D;
        else
            camera_mode_ = CameraMode::FPS_3D;
    }
    last_tab = current_tab;
    
    if (input_manager_->IsKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(context_->GetWindow(), true);
        return;
    }
}


void App::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection, view;
    if (camera_mode_ == CameraMode::FPS_3D) {
        projection = fps_camera_->GetProjectionMatrix(800.f / 600.f);
        view = fps_camera_->GetViewMatrix();
    } else {
        projection = ortho_camera_->GetProjectionMatrix();
        view = ortho_camera_->GetViewMatrix();
    }

    renderer_.DrawMesh(
        *mesh_,
        *shader_,
        *texture_,
        projection * view * glm::mat4(1.f)
    );

    // 2. Render esfera/cubo encima
    /*{
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.5f, 0.f));
        model = glm::scale(model, glm::vec3(0.3f));
        glm::mat4 MVP = projection * view * model;
        shader_->SetMat4("MVP", MVP);
        model_->Draw():
    }*/
}