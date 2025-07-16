#pragma once

#include "ecs/Entity.hpp"

#include <vector>
#include <memory>

class Scene {
public:
    Entity& CreateEntity() {
        entities_.emplace_back(std::make_unique<Entity>());
        return *entities_.back();
    }

    const std::vector<std::unique_ptr<Entity>>& GetEntities() const {
        return entities_;
    }

private:
    std::vector<std::unique_ptr<Entity>> entities_;
};
