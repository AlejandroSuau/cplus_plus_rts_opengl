#pragma once

#include "ecs/component/Component.hpp"

#include <glm/glm.hpp>

class TransformComponent : public Component {
public:
    constexpr TransformComponent() = default;
    constexpr TransformComponent(const glm::vec3& pos)
        : position(pos) {}

    glm::vec3 position{0.f};
    glm::vec3 scale{1.f};
    glm::vec3 rotation{0.f};

};
