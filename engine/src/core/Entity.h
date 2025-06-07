/*
  This is the best choice rather than making my own entity system. I will just add all the components
  required for most of my needs here. Should be better. Tried writing my own but it was a mess.
  This is built as a singleton because i want a single entity manager for the whole engine. Creating 
  multiple of them for say Physics, Renderer2D stuff, AI Components is just a mess anyways.
*/

#pragma once

#include "entt/entt.hpp"
#include "box2d/box2d.h"
#include <glm/glm.hpp>

namespace Freeze {

  struct PhysicsComponent
  {
    b2Vec2 Positions = { 0.0f, 0.0f };
    b2Vec2 Size = { 0.0f, 0.0f };
    float Rotation = 0.0f;
    
    float Density = 0.5f, Friction = 0.3f, Restitution = 0.0f; // These are the default values of the properties.
    glm::vec4 Color; // Temporary
    b2Body* RuntimeBody;
  };

  struct PhysicsBodyData 
  {
    b2BodyDef BodyDef;
    b2Body* Body;
    b2FixtureDef FixtureDef;
    b2PolygonShape Shape;

    std::string BodyID;
    entt::entity PhysicsEntity = entt::null; 
    bool isCollided = false;
    b2Body* CollidedWith = nullptr;
  };
  
  class EntityManager {

  public:
    
    static EntityManager& GetEntityManagerInstance() 
    {
      static EntityManager entityManager;
      return entityManager; 
    }

    entt::registry& GetRegistry() { return m_Registry; }
    entt::entity& GetCurrentEntity() { return m_CurrentEntity; }

    entt::entity& CreateEntity()
    {
      m_CurrentEntity = m_Registry.create(); 
      return m_CurrentEntity;
    }

    template <typename T, typename... Args>
    T& AddComponent(const entt::entity& entity, Args&&... args)
    {
      m_CurrentEntity = entity;
      auto& componentProperty = m_Registry.emplace<T>(m_CurrentEntity, std::forward<Args>(args)...);

      return componentProperty;
    }

    void DestroyEntity(const entt::entity& entity)
    {
      if(m_Registry.valid(entity))
        m_Registry.destroy(entity);
    }

    void RemoveAllEntities() { m_Registry.clear(); }

    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
  
  private:
    EntityManager() = default;
    ~EntityManager() = default;

    entt::registry m_Registry;
    entt::entity m_CurrentEntity;
    std::string m_ComponentTag;
  };

};
