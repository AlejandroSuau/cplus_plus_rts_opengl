#include "App.hpp"

App::App() 
    : context_(std::make_unique<OpenGLContext>(800, 600, "RTS Game"))
    , shader_(std::make_unique<ShaderProgram>("assets/shaders/basic.vert", "assets/shaders/basic.frag")) {
    Init();
}

void App::Init() {
    float vertices[] {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void App::Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_->Use();
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
