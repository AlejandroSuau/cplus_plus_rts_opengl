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
    , camera_(std::make_unique<Camera3D>(glm::vec3(3.f, 3.f, 3.f), glm::vec3(0,1,0), -135.f, -35.f))
    , shader_(std::make_unique<ShaderProgram>("assets/shaders/basic.vert", "assets/shaders/basic.frag"))
    , mesh_(std::make_unique<Mesh>(quadVertices, quadIndices))
    , model_(std::make_unique<ObjModel>("assets/models/cube.obj"))
    , texture_(std::make_unique<Texture2D>("assets/images/StoneWall_Texture.png")) {
    Init();
}

void App::Init() {
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
    if (input_manager_->IsKeyPressed(GLFW_KEY_W)) camera_->ProcessKeyboard('W', dt);
    if (input_manager_->IsKeyPressed(GLFW_KEY_S)) camera_->ProcessKeyboard('S', dt);
    if (input_manager_->IsKeyPressed(GLFW_KEY_A)) camera_->ProcessKeyboard('A', dt);
    if (input_manager_->IsKeyPressed(GLFW_KEY_D)) camera_->ProcessKeyboard('D', dt);

    glm::vec2 mouse_delta = input_manager_->GetMouseDelta();
    camera_->ProcessMouseMovement(mouse_delta.x, -mouse_delta.y);
    input_manager_->ResetMouseDelta();
}

void App::HandleEvents() {
    if (input_manager_->IsKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(context_->GetWindow(), true);
        return;
    }
}


void App::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->Use();

    glm::mat4 projection = camera_->GetProjectionMatrix(800.f / 600.f);
    glm::mat4 view = camera_->GetViewMatrix();
    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 MVP = projection * view * model;
    shader_->SetMat4("MVP", MVP);

    texture_->Bind(0);
    shader_->SetInt("texture1", 0);
    
    model_->Draw();
}