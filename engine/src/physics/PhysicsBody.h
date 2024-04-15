#pragma once

#include <box2d/box2d.h>

#include <vector>
#include <string>

#include "renderer/Renderer2D.h"
#include "core/Core.h"
#include "InitPhysics.h"

namespace Freeze {

    namespace Physics {

        class PhysicsBody {
        public:
            virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions) = 0;
            virtual void RenderBody(const glm::vec4& color) = 0; // TODO: This is temporary, in the future the rendering needs can be done as wish in the sandbox
            virtual void DeleteBody() = 0;
            virtual ~PhysicsBody() {}
        };

        class DynamicBody : public PhysicsBody {
        public:
            DynamicBody();
            void CreateBody(const b2Vec2& size, const b2Vec2& positions) override;
            void RenderBody(const glm::vec4& color) override;
            void DeleteBody() override;

            void SetFriction(float friction) { m_Friction = friction; }
            void SetDensity(float density) { m_Density = density; }
            void SetRestitution(float restitution) { m_Restitution = restitution; }

            float GetFriction() const { return m_Friction; }
            float GetDensity() const { return m_Density; }
            float GetRestitution() const { return m_Restitution; } 

            ~DynamicBody();

        private:
            struct DynamicBodyData {
                b2BodyDef BodyDef;
                b2Body* Body;
                b2FixtureDef FixtureDef;
                b2PolygonShape Shape;
                std::string BodyID;

                b2Vec2 Positions = { 0.0f, 0.0f };
                b2Vec2 Size = { 0.0f, 0.0f };

                DynamicBodyData* next;
            };

            DynamicBodyData* m_Head = nullptr;
            float m_Friction;
            float m_Density;
            float m_Restitution;
        };

        class StaticBody : public PhysicsBody {
        public:
            StaticBody();
            void CreateBody(const b2Vec2& size, const b2Vec2& positions) override;
            void RenderBody(const glm::vec4& color) override;
            void DeleteBody() override;
            ~StaticBody();

        private:
            struct StaticBodyData {
                b2BodyDef BodyDef;
                b2Body* Body;
                b2FixtureDef FixtureDef;
                b2PolygonShape Shape;
                std::string BodyID;

                b2Vec2 Positions;
                b2Vec2 Size;
            };

            StaticBodyData* m_StaticBodyData;
            static std::vector<b2Body*> m_StaticBodies;
        };

    }

}