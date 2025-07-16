#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class ShaderProgram;
class Texture2D;
class ObjModel;

class ResourceManager {
public:
    static void Init();
    static void Clear();

    static std::shared_ptr<Texture2D> LoadTexture(const std::string& name, const std::string& path);
    static std::shared_ptr<ShaderProgram> LoadShader(const std::string& name, const std::string& vertex_path, const std::string& fragment_path);
    static std::shared_ptr<ObjModel> LoadModel(const std::string& name, const std::string& path);

    static std::shared_ptr<Texture2D> GetTexture(const std::string& name);
    static std::shared_ptr<ShaderProgram> GetShader(const std::string& name);
    static std::shared_ptr<ObjModel> GetModel(const std::string& name);

private:
    static std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures_;
    static std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shaders_;
    static std::unordered_map<std::string, std::shared_ptr<ObjModel>> models_;

    ResourceManager() = default; // Prevent instantiation
    ~ResourceManager() = default; // Prevent deletion
};
