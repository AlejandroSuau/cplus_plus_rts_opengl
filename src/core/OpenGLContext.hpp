#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>

class OpenGLContext {
public:
    OpenGLContext(int width, int height, const char* title);
    ~OpenGLContext();

    GLFWwindow* GetWindow() const;

private:
    OpenGLContext(const OpenGLContext&) = delete;
    OpenGLContext& operator=(const OpenGLContext&) = delete;
    OpenGLContext(OpenGLContext&&) = delete;
    OpenGLContext& operator=(OpenGLContext&&) = delete;

    GLFWwindow* window_;
};
