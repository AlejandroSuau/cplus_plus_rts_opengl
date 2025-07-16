#pragma once

#include "render/ShaderProgram.hpp"
#include "render/Mesh.hpp"
#include "render/Texture2D.hpp"

#include <glm/glm.hpp>

class Renderer {
public:
    Renderer() = default;

    void DrawMesh(
        const Mesh& mesh,
        const ShaderProgram& shader,
        const Texture2D& texture,
        const glm::mat4& MVP
    ) const;
};
