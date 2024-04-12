#pragma once

#include <box2d/box2d.h>

#include <vector>
#include <string>

#include "renderer/Renderer2D.h"
#include "InitPhysics.h"

namespace Freeze {

    namespace Physics {
        
        class PhysicsBody {
        public:
            virtual void CreateBody(const b2Vec2& size, const b2Vec2& positions) = 0;
            virtual void RenderBody(const glm::vec4& color) = 0;
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

                b2Vec2 Positions;
                b2Vec2 Size;
            };

            DynamicBodyData* m_BodyData = nullptr;
            float m_Friction;
            float m_Density;
            float m_Restitution;

            static std::vector<DynamicBodyData*> m_DynamicBodies;
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
            };

            StaticBodyData* m_BodyData;
            b2Vec2 m_Size;
            b2Vec2 m_Positions;
            static std::vector<StaticBodyData*> m_StaticBodies;
        };

    }

}
