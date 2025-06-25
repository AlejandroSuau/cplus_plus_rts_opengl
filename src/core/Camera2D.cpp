#include "core/Camera2D.hpp"

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D(float left, float right, float bottom, float top) 
    : position_(0.f, 0.f)
    , zoom_(1.f) {
    projection_matrix_ = glm::ortho(left, right, bottom, top);
    UpdateViewMatrix();
}

void Camera2D::SetPosition(const glm::vec2& position) {
    position_ = position;
    UpdateViewMatrix();
}

void Camera2D::SetZoom(float zoom) {
    zoom_ = zoom;
    UpdateViewMatrix();
}

const glm::mat4& Camera2D::GetViewMatrix() const {
    return view_matrix_;
}

const glm::mat4& Camera2D::GetProjectionMatrix() const {
    return projection_matrix_;
}

void Camera2D::Move(const glm::vec2& delta) {
    position_ += delta;
    UpdateViewMatrix();
}

void Camera2D::Zoom(float factor) {
    zoom_ *= factor;
    zoom_ = glm::clamp(zoom_, 0.1f, 10.0f); // para que no se vuelva loca
    UpdateViewMatrix();
}
    
void Camera2D::UpdateViewMatrix() {
    view_matrix_ = glm::mat4(1.f);
    view_matrix_ = glm::translate(view_matrix_, glm::vec3(-position_, 0.f));
    view_matrix_ = glm::scale(view_matrix_, glm::vec3(zoom_, zoom_, 1.f));
}
