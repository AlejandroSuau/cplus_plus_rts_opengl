#include "core/Camera3D.hpp"

Camera3D::Camera3D(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
    : position_(position)
    , world_up_(up)
    , yaw_(yaw)
    , pitch_(pitch) {
    UpdateCameraVectors();
}

glm::mat4 Camera3D::GetViewMatrix() const {
    return glm::lookAt(position_, position_ + front_, up_);
}

glm::mat4 Camera3D::GetProjectionMatrix(float aspect_ratio) const {
    return glm::perspective(glm::radians(fov_), aspect_ratio, 0.1f, 100.f);
}

void Camera3D::ProcessKeyboard(char direction, float delta_time) {
    float velocity = movement_speed_ * delta_time;
    if (direction == 'W') position_ += front_ * velocity;
    if (direction == 'S') position_ -= front_ * velocity;
    if (direction == 'A') position_ -= right_ * velocity;
    if (direction == 'D') position_ += right_ * velocity;
 }

void Camera3D::ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch) {
    xoffset *= mouse_sensitivity_;
    yoffset *= mouse_sensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    if (constrain_pitch) {
        if (pitch_ > 89.f) pitch_ = 89.f;
        if (pitch_ < -89.f) pitch_ = -89.f;
    }

    UpdateCameraVectors();
}

glm::vec3 Camera3D::GetPosition() const {
    return position_;
}
    
void Camera3D::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);

    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
}
