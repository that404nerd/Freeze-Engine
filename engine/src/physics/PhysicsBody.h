#pragma once

#include <box2d/box2d.h>

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
    public:
      virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation) = 0;
      virtual ~PhysicsBody() {}
    };

    class DynamicBody : public PhysicsBody {

    public:
      enum class BODY_DIRECTION {
        LEFT, RIGHT, TOP, DOWN, NONE
      };

    private:
      struct DynamicBodyData {
        b2BodyDef BodyDef;
        b2Body* Body;
        b2FixtureDef FixtureDef;
        b2PolygonShape Shape;

        std::string BodyID;
        b2Vec2 Positions = { 0.0f, 0.0f };
        b2Vec2 Size = { 0.0f, 0.0f };
        float Rotation = 0.0f;
      };

      std::vector<std::shared_ptr<DynamicBodyData>> m_BodyData;
      std::shared_ptr<DynamicBodyData> m_Current;

      float m_Friction;
      float m_Density;
      float m_Restitution;

      std::string m_BodyID;
      
      BODY_DIRECTION m_DefDirection;
      BODY_DIRECTION m_CurrentDirection;

    public:
      DynamicBody(const std::string& bodyID);
      void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation) override;

      void MoveBody(const b2Vec2& force, BODY_DIRECTION direction);

    public:
      void SetFriction(float friction) { m_Friction = friction; }
      void SetDensity(float density) { m_Density = density; }
      void SetRestitution(float restitution) { m_Restitution = restitution; }

      float GetFriction() const { return m_Friction; }
      float GetDensity() const { return m_Density; }
      float GetRestitution() const { return m_Restitution; } 

      std::shared_ptr<DynamicBodyData> GetBodyData() { return m_Current; };
      b2Body* GetBody() { return m_Current->Body; }

      ~DynamicBody();
    };

    class StaticBody : public PhysicsBody {
    public:
      StaticBody(const std::string& bodyID);
      void CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation=0.0f) override;
      ~StaticBody();

    private:
      struct StaticBodyData {
        b2BodyDef BodyDef;
        b2Body* Body;
        b2FixtureDef FixtureDef;
        b2PolygonShape Shape;
        std::string BodyID; // Only for debugging

        b2Vec2 Positions = { 0.0f, 0.0f };
        b2Vec2 Size = { 0.0f, 0.0f };
        float Rotation = 0.0f;
      };

      std::vector<std::shared_ptr<StaticBodyData>> m_BodyData;
      std::shared_ptr<StaticBodyData> m_Current;

      std::string m_BodyID;
    public:
      std::shared_ptr<StaticBodyData> GetBodyData() { return m_Current; }
      b2Body* GetBody() { return m_Current->Body; }
    };
  };
};
