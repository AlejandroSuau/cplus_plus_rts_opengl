#pragma once

class ISystem {
public:
    virtual ~System() = default;
    virtual void Update(float dt) = 0;
};
