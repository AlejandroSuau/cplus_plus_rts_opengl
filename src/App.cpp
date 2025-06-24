#include "App.hpp"

#include "core/InputManager.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace {
const float kFixedTimeStep = 0.016666f; // In Seconds
}

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
    , camera_(std::make_unique<Camera2D>(-1.f, 1.f, -1.f, 1.f))
    , shader_(std::make_unique<ShaderProgram>("assets/shaders/basic.vert", "assets/shaders/basic.frag"))
    , mesh_(std::make_unique<Mesh>(quadVertices, quadIndices))
    , texture_(std::make_unique<Texture2D>("assets/images/StoneWall_Texture.png")) {}

void App::Init() {
}

void App::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->Use();

    // Simple MVP: identity (no camera)
    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 MVP = camera_->GetProjectionMatrix() * camera_->GetViewMatrix() * model;

    shader_->SetMat4("MVP", MVP);
    texture_->Bind(0);
    shader_->SetInt("texture1", 0);

    mesh_->Draw();
}

void App::Run() {
    GLFWwindow* window = context_->GetWindow();

    float last_frame = static_cast<float>(glfwGetTime());
    float accumulator = 0.f;

    while (!glfwWindowShouldClose(window)) {
        float current_frame = static_cast<float>(glfwGetTime());
        float delta_time = (current_frame - last_frame);
        last_frame = current_frame;

        accumulator += delta_time;
        while (accumulator >= kFixedTimeStep) {
            Update(kFixedTimeStep);
            accumulator -= kFixedTimeStep;
        }

        HandleEvents();
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::Update(float dt) {
    
}

void App::HandleEvents() {
    float camera_speed = .1f;
    if (input_manager_->IsKeyPressed(GLFW_KEY_W)) camera_->Move({0.f, camera_speed});
    if (input_manager_->IsKeyPressed(GLFW_KEY_S)) camera_->Move({0.f, -camera_speed});
    if (input_manager_->IsKeyPressed(GLFW_KEY_A)) camera_->Move({-camera_speed, 0.f});
    if (input_manager_->IsKeyPressed(GLFW_KEY_D)) camera_->Move({camera_speed, 0.f});
}
