#pragma once

#include "systems/ISystem.hpp"
#include "ecs/component/TransformComponent.hpp"

class RenderSystem : public ISystem {
public:
    RenderSystem(Scene& scene, Renderer& renderer)
        : scene_(scene), renderer_(renderer) {}
    
    void Update(float dt) override {
        for (const auto& entity : scene_.GetEntities()) {
            auto transform = entity->GetComponent<TransformComponent>();
        }
    }

private:
    Scene& scene_;
    Renderer& renderer_;
};
