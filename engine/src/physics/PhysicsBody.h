#pragma once

#include <box2d/box2d.h>

#include <vector>
#include <string>

#include "renderer/Renderer2D.h"
#include "core/Core.h"
#include "InitPhysics.h"

// TODO: Optimise this!

namespace Freeze {

    namespace Physics {

        inline float MetersPerPixelFactor = 32.0f;

        inline float PixelToMeter(const float value) { return (value * (1.0f / MetersPerPixelFactor)); }
        inline b2Vec2 PixelToMeter(const b2Vec2& vector) { return b2Vec2(PixelToMeter(vector.x), PixelToMeter(vector.y)); }

        inline float MeterToPixel(const float value) { return (value * MetersPerPixelFactor); }
        inline b2Vec2 MeterToPixel(const b2Vec2& vector) { return b2Vec2(MeterToPixel(vector.x), MeterToPixel(vector.y)); }

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

                StaticBodyData* next;
            };

            StaticBodyData* m_Head = nullptr;
        };

    }

}