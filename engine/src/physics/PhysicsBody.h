#pragma once

#include <box2d/box2d.h>

#include <vector>
#include <string>

#include "renderer/Renderer2D.h"
#include "core/Core.h"
#include "InitPhysics.h"

#include "event/KeyboardInput.h"

/* 
   Collision is kinda bad when too many objects are drawn at the same time (like 100,000 1x1 or 2x2 quads at max). If you are trying to test with sizes 
   more than that (like say 10x10 or 5x5) then, i am wondering why? Not like we are going to do that thing in an actual game. The physics for quads 
   is the only thing that i tested and confirmed that works. This API needs a lot of rework.

   This took a lot of time especially with this custom 2D rendering. Right now the bodies work no matter which camera resolution. Unless you
   wanna take it to the extreme. I generally keep it small because we already have camera movement (yea i know it sucks but it works). If
   you want to extend it more than that of the example sandbox's camera then it's is pretty much upto you. That doesn't mean you can't extend it a little more.
   But generally speaking it's fine and making it larger pretty much means that the objects are lot bigger and things are going to be really slow.
   Yes, this obviously requires some optimisation, but that's for future me. This is of course not a 3D engine, so I am not going to care much about it.
*/

namespace Freeze {

    namespace Physics {

        class PhysicsBody {
        public:
            virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions) = 0;
            virtual void RenderBody(const glm::vec4& color) = 0; // TODO: This is temporary, in the future the rendering needs can be done as wish in the sandbox
            virtual ~PhysicsBody() {}
        };

        class DynamicBody : public PhysicsBody {
        private:
            struct DynamicBodyData {
                b2BodyDef BodyDef;
                b2Body* Body;
                b2FixtureDef FixtureDef;
                b2PolygonShape Shape;
                std::string BodyID;
                ShapeRenderer* RendShape = new ShapeRenderer();

                b2Vec2 Positions = { 0.0f, 0.0f };
                b2Vec2 Size = { 0.0f, 0.0f };
            };

            std::vector<DynamicBodyData*> m_BodyData;
            DynamicBodyData* m_Current = nullptr;

            float m_Friction;
            float m_Density;
            float m_Restitution;

        public:
            DynamicBody();
            void CreateBody(const b2Vec2& size, const b2Vec2& positions) override;
            void RenderBody(const glm::vec4& color) override;

            void MoveBody(const b2Vec2& position);

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
            StaticBody();
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
                std::string BodyID;

                b2Vec2 Positions;
                b2Vec2 Size;
            };

            std::vector<StaticBodyData*> m_BodyData;

        };

    }

}