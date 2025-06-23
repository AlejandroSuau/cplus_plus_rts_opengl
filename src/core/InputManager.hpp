#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <unordered_map>

class InputManager {
public:
    InputManager(GLFWwindow* window);

    bool IsKeyPressed(int key) const;
    bool IsButtonPressed(int button) const;
    glm::vec2 GetMousePosition() const;
    glm::vec2 GetMouseDelta() const;

private:
    void KeyCallback(int key, int scancode, int action, int mods);
    void MouseButtonCallback(int button, int action, int mods);
    void CursorPositionCallback(double xpos, double ypos); 

    GLFWwindow* window_;
    std::unordered_map<int, bool> key_states_;
    std::unordered_map<int, bool> mouse_buttons_;
    glm::vec2 mouse_position_;
    glm::vec2 mouse_delta_;
    glm::vec2 last_mouse_position_;

    static void KeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallbackDispatch(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallbackDispatch(GLFWwindow* window, double xpos, double ypos);
};
