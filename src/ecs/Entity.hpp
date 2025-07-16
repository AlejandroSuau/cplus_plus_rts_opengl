#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>

class Component;

class Entity {
public:
    Entity() = default;

    template<typename T, typename... Args>
    void AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        std::type_index index(typeid(T));
        components_[index] = std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    std::shared_ptr<T> GetComponent() {
        std::type_index index(typeid(T));
        auto it = components_.find(index);
        if (it == components_.end()) {
            return nullptr;
        }

        return std::static_pointer_cast<T>(it->second);
    }

    template<typename T>
    bool HasComponent() const {
        return components_.count(std::type_index(typeid(T))) > 0;
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components_ {};
};
