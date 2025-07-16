#include "core/ResourceManager.hpp"

#include "render/ShaderProgram.hpp"
#include "render/Texture2D.hpp"
#include "core/ObjModel.hpp"

std::unordered_map<std::string, std::shared_ptr<Texture2D>> ResourceManager::textures_ {};
std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> ResourceManager::shaders_ {};
std::unordered_map<std::string, std::shared_ptr<ObjModel>> ResourceManager::models_ {};

void ResourceManager::Init() {}

void ResourceManager::Clear() {
    shaders_.clear();
    textures_.clear();
    models_.clear();
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& name, const std::string& path) {
    auto texture = std::make_shared<Texture2D>(path);
    textures_[name] = texture;
    return texture;
}

std::shared_ptr<ShaderProgram> ResourceManager::LoadShader(const std::string& name, const std::string& vertex_path, const std::string& fragment_path) {
    auto shader = std::make_shared<ShaderProgram>(vertex_path, fragment_path);
    shaders_[name] = shader;
    return shader;
}

std::shared_ptr<ObjModel> ResourceManager::LoadModel(const std::string& name, const std::string& path) {
    auto model = std::make_shared<ObjModel>(path);
    models_[name] = model;
    return model;
}

std::shared_ptr<Texture2D> ResourceManager::GetTexture(const std::string& name) {
    return textures_.at(name);
}

std::shared_ptr<ShaderProgram> ResourceManager::GetShader(const std::string& name) {
    return shaders_.at(name);
}

std::shared_ptr<ObjModel> ResourceManager::GetModel(const std::string& name) {
    return models_.at(name);
}