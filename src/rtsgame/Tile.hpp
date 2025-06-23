#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

enum class ETileType {
    GRASS,
    WATER
};

inline static const std::unordered_map<ETileType, glm::vec3> kTileTypeColorMap {
    {ETileType::GRASS, glm::vec3{0.2f, 0.8f, 0.2f}},
    {ETileType::WATER, glm::vec3{0.2f, 0.4f, 0.8f}}
};

glm::vec3 FromTileTypeToColor(ETileType tile_type) {
    auto it = kTileTypeColorMap.find(tile_type);
    if (it == kTileTypeColorMap.cend()) {
        assert(false && "TileType has no color defined!");
        return {0.f, 0.f, 0.f};
    }

    return it->second;
}

struct Tile {
    ETileType type;
    glm::vec3 position;
};

