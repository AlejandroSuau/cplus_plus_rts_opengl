#include "App.hpp"

#include "core/InputManager.hpp"

#include "glm/gtc/matrix_transform.hpp"

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
    glm::mat4 view = glm::mat4(1.f);
    glm::mat4 projection = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
    glm::mat4 MVP = projection * view * model;

    shader_->SetMat4("MVP", MVP);
    texture_->Bind(0);
    shader_->SetInt("texture1", 0);

    mesh_->Draw();
}

void App::Run() {
    GLFWwindow* window = context_->GetWindow();
    while (!glfwWindowShouldClose(window)) {
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::HandleEvents() {

}
