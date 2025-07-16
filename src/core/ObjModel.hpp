#pragma once

#include "render/Mesh.hpp"

#include <string>

class ObjModel {
public:
    ObjModel(const std::string& path);
    
    void Draw() const;

private:
    std::unique_ptr<Mesh> mesh_;
};
