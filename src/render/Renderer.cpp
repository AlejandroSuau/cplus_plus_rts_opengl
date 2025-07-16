#include "render/Renderer.hpp"

#include <glad/glad.h>

void Renderer::DrawMesh(
    const Mesh& mesh,
    const ShaderProgram& shader,
    const Texture2D& texture,
    const glm::mat4& MVP
) const {
    shader.Use();
    shader.SetMat4("MVP", MVP);
    
    texture.Bind(0);
    shader.SetInt("texture1", 0);

    mesh.Draw();
}