#pragma once

#include <box2d/box2d.h>
#include "entt/entt.hpp"

#include <memory>
#include <vector>
#include <string>

#include "renderer/Renderer2D.h"
#include "core/Core.h"
#include "InitPhysics.h"
#include "event/KeyboardInput.h"
#include "./core/Entity.h"

namespace Freeze {
  namespace Physics {
    
    // Interface for other physics body types
    class PhysicsBody {
    private:

      struct PhysicsBodyData {
        b2BodyDef BodyDef;
        b2Body* Body;
        b2FixtureDef FixtureDef;
        b2PolygonShape Shape;

        std::string BodyID;

        entt::entity PhysicsEntity = entt::null;
      };

    public:
      virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color) = 0;
      
      std::shared_ptr<PhysicsBodyData> GetPhysicsBodyDataInst() { return m_PhysicsBodyData; }

      virtual ~PhysicsBody() {};
    protected:
      std::shared_ptr<PhysicsBodyData> m_PhysicsBodyData = std::make_shared<PhysicsBodyData>();
    };

    class DynamicBody : public PhysicsBody {

    private:
      float m_Friction;
      float m_Density;
      float m_Restitution;

      std::string m_BodyID;

    public:
      DynamicBody(const std::string& bodyID);
      void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color={ 1.0f, 1.0f, 1.0f, 1.0f }) override;

    public:
      // void SetFriction(float friction) { m_PhysicsBodyData->PhysicsBodyComponent.Friction = friction; }
      // void SetDensity(float density) { m_PhysicsBodyData->PhysicsBodyComponent.Density = density; }
      // void SetRestitution(float restitution) { m_PhysicsBodyData->PhysicsBodyComponent.Restitution = restitution; }
      //
      // float GetFriction() const { return m_PhysicsBodyData->PhysicsBodyComponent.Friction; }
      // float GetDensity() const { return m_PhysicsBodyData->PhysicsBodyComponent.Density; }
      // float GetRestitution() const { return m_PhysicsBodyData->PhysicsBodyComponent.Restitution; }
      
      

      b2Body* GetBody() { return GetPhysicsBodyDataInst()->Body; }

      ~DynamicBody();
    };

    class StaticBody : public PhysicsBody {
    public:
      StaticBody(const std::string& bodyID);
      void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation=0.0f, glm::vec4 color={ 1.0f, 1.0f, 1.0f, 1.0f }) override;
      ~StaticBody();

    private:
      std::string m_BodyID;
    public:
      b2Body* GetBody() { return GetPhysicsBodyDataInst()->Body; }
    };
  };
};
