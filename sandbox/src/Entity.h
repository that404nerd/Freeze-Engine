#pragma once

#include <string>

#include <glm/glm.hpp>

class Entity {
public:
    Entity(const std::string& id) : m_EntityID(id) 
    {
    }

    const std::string& PrintEntityName() { return m_EntityID; }

    virtual void CreateEntity() = 0;
    virtual void RenderEntity(float dt) = 0;

    virtual ~Entity() = default;
private:
    const std::string m_EntityID;
};
