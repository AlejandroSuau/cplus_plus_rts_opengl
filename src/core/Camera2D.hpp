#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
public:
    Camera2D(float left, float right, float bottom, float top);

    void SetPosition(const glm::vec2& position);
    void SetZoom(float zoom);

    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;

    void Move(const glm::vec2& delta);
    void Zoom(float factor);

private:
    glm::vec2 position_;
    float zoom_;

    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
    
    void UpdateViewMatrix();
};
