#include "core/OpenGLContext.hpp"

#include <stdexcept>

OpenGLContext::OpenGLContext(int width, int height, const char* title) {
    if (!glfwInit()) throw std::runtime_error("GLFW init failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window_) throw std::runtime_error("GLFW window creation failed!");

    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("GLAD init failed!");
}

OpenGLContext::~OpenGLContext() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

GLFWwindow* OpenGLContext::GetWindow() const {
    return window_;
}
