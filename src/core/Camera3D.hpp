#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera3D {
public:
    Camera3D(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspect_ratio) const;

    void ProcessKeyboard(char direction, float delta_time);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch = true);

    glm::vec3 GetPosition() const;

private:
    void UpdateCameraVectors();

    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;
    
    float yaw_;
    float pitch_;

    float movement_speed_ = 5.f;
    float mouse_sensitivity_ = 0.1f;
    float fov_ = 45.0f; // Field of view in degrees
};
