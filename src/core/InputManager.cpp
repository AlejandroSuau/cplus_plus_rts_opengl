#include "core/InputManager.hpp"

InputManager::InputManager(GLFWwindow* window) 
    : window_(window)
    , mouse_position_(0.f, 0.f)
    , mouse_delta_(0.f, 0.f)
    , last_mouse_position_(0.f, 0.f) {
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, KeyCallbackDispatch);
    glfwSetMouseButtonCallback(window, MouseButtonCallbackDispatch);
    glfwSetCursorPosCallback(window, CursorPositionCallbackDispatch);
}

bool InputManager::IsKeyPressed(int key) const {
    auto it = key_states_.find(key);
    return (it != key_states_.cend() && it->second);
}

bool InputManager::IsButtonPressed(int button) const {
    auto it = mouse_buttons_.find(button);
    return (it != mouse_buttons_.cend() && it->second);
}

glm::vec2 InputManager::GetMousePosition() const{
    return mouse_position_;
}

glm::vec2 InputManager::GetMouseDelta() const{
    return mouse_delta_;
}

void InputManager::KeyCallback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        key_states_[key] = true;
    } else if (action == GLFW_RELEASE) {
        key_states_[key] = false;
    }
}

void InputManager::MouseButtonCallback(int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        mouse_buttons_[button] = true;
    } else if (action == GLFW_RELEASE) {
        mouse_buttons_[button] = false;
    }
}

void InputManager::CursorPositionCallback(double xpos, double ypos) {
    mouse_position_ = glm::vec2(xpos, ypos);
    mouse_delta_ = mouse_position_ - last_mouse_position_;
    last_mouse_position_ = mouse_position_;
}

void InputManager::KeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (input) input->KeyCallback(key, scancode, action, mods);
}

void InputManager::MouseButtonCallbackDispatch(GLFWwindow* window, int button, int action, int mods) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (input) input->MouseButtonCallback(button, action, mods);
}

void InputManager::CursorPositionCallbackDispatch(GLFWwindow* window, double xpos, double ypos) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (input) input->CursorPositionCallback(xpos, ypos);
}

