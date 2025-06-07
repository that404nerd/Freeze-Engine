#pragma once

#include <box2d/box2d.h>
#include "entt/entt.hpp"

#include <memory>
#include <vector>
#include <string>

#include "renderer/Renderer2D.h"
#include "core/Core.h"
#include "InitPhysics.h"
#include "./core/Entity.h"

namespace Freeze {
  namespace Physics {
    
    // Interface for other physics body types
    class PhysicsBody {
    public:

      virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color) = 0;
      
      std::shared_ptr<PhysicsBodyData> GetPhysicsBodyDataInst() { return m_PhysicsBodyData; }
      entt::entity& GetPhysicsEntity() { return m_PhysicsBodyData->PhysicsEntity; }

      virtual ~PhysicsBody() {};
    private:
      std::shared_ptr<PhysicsBodyData> m_PhysicsBodyData = std::make_shared<PhysicsBodyData>();
    };

    class DynamicBody : public PhysicsBody {

    public:
      DynamicBody(const std::string& bodyID) { GetPhysicsBodyDataInst()->BodyID = bodyID; };
      void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color={ 1.0f, 1.0f, 1.0f, 1.0f }) override;

    public:
      void SetFriction(float friction);
      void SetDensity(float density);
      void SetRestitution(float restitution); 

      float GetFriction() const;
      float GetDensity() const;
      float GetRestitution() const;

      b2Body* GetBody() { return GetPhysicsBodyDataInst()->Body; }

      ~DynamicBody() {};
    };

    class StaticBody : public PhysicsBody {
    public:

      StaticBody(const std::string& bodyID) { GetPhysicsBodyDataInst()->BodyID = bodyID; };
      void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation=0.0f, glm::vec4 color={ 1.0f, 1.0f, 1.0f, 1.0f }) override;
      ~StaticBody() {};

    public:
      b2Body* GetBody() { return GetPhysicsBodyDataInst()->Body; }
    };
  };
};
