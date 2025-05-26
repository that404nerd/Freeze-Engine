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
      };

    public:
      virtual b2Body* CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation) = 0;
      
      std::shared_ptr<PhysicsBodyData> GetPhysicsBodyDataInst() { return m_PhysicsBodyData; }
      virtual ~PhysicsBody() {};
    protected:
      std::shared_ptr<PhysicsBodyData> m_PhysicsBodyData = std::make_shared<PhysicsBodyData>();
    };

    class DynamicBody : public PhysicsBody {

    // public:
      // enum class BODY_DIRECTION {
      //   LEFT, RIGHT, TOP, DOWN, NONE
      // };

    private:
      float m_Friction;
      float m_Density;
      float m_Restitution;

      std::string m_BodyID;
      //
      // BODY_DIRECTION m_DefDirection;
      // BODY_DIRECTION m_CurrentDirection;

    public:
      DynamicBody(const std::string& bodyID);
      b2Body* CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation) override;

      // void MoveBody(const b2Vec2& force, BODY_DIRECTION direction);

    public:
      void SetFriction(float friction) { m_Friction = friction; }
      void SetDensity(float density) { m_Density = density; }
      void SetRestitution(float restitution) { m_Restitution = restitution; }

      float GetFriction() const { return m_Friction; }
      float GetDensity() const { return m_Density; }
      float GetRestitution() const { return m_Restitution; } 

      b2Body* GetBody() { return GetPhysicsBodyDataInst()->Body; }

      ~DynamicBody();
    };

    class StaticBody : public PhysicsBody {
    public:
      StaticBody(const std::string& bodyID);
      b2Body* CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation=0.0f) override;
      ~StaticBody();

    private:
      std::string m_BodyID;
    public:
      b2Body* GetBody() { return GetPhysicsBodyDataInst()->Body; }
    };
  };
};
