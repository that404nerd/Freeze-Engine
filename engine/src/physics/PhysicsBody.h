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
      virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions) = 0;
      virtual void RenderBody(const glm::vec4& color) = 0; // TODO: This is temporary, in the future the rendering needs can be done as wish in the sandbox
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
        ShapeRenderer* RendShape = new ShapeRenderer();

        std::string BodyID;
        b2Vec2 Positions = { 0.0f, 0.0f };
        b2Vec2 Size = { 0.0f, 0.0f };
      };

      std::vector<DynamicBodyData*> m_BodyData;
      DynamicBodyData* m_Current = nullptr;

      float m_Friction;
      float m_Density;
      float m_Restitution;

      std::string m_BodyID;
      
      BODY_DIRECTION m_DefDirection;
      BODY_DIRECTION m_CurrentDirection;

    public:
      DynamicBody(const std::string& bodyID);
      void CreateBody(const b2Vec2& size, const b2Vec2& positions) override;
      void RenderBody(const glm::vec4& color) override;

      void MoveBody(const b2Vec2& force, BODY_DIRECTION direction);

    public:
      void SetFriction(float friction) { m_Friction = friction; }
      void SetDensity(float density) { m_Density = density; }
      void SetRestitution(float restitution) { m_Restitution = restitution; }

      float GetFriction() const { return m_Friction; }
      float GetDensity() const { return m_Density; }
      float GetRestitution() const { return m_Restitution; } 

      DynamicBodyData* GetBodyData();

      ~DynamicBody();
    };

    class StaticBody : public PhysicsBody {
    public:
      StaticBody(const std::string& bodyID);
      void CreateBody(const b2Vec2& size, const b2Vec2& positions) override;
      void RenderBody(const glm::vec4& color) override;
      ~StaticBody();

    private:
      struct StaticBodyData {
        b2BodyDef BodyDef;
        b2Body* Body;
        b2FixtureDef FixtureDef;
        b2PolygonShape Shape;
        ShapeRenderer* RendShape = new ShapeRenderer();
        std::string BodyID; // Only for debugging

        b2Vec2 Positions;
        b2Vec2 Size;
      };

      std::vector<StaticBodyData*> m_BodyData;
      StaticBodyData* m_Current = nullptr;
      std::string m_BodyID;
    };

    }

}
