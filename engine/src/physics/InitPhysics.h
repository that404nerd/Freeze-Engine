#pragma once

#include <GL/glew.h>
#include <box2d/box2d.h>

#include <imgui.h>
#include <memory>

#include "core/Core.h"
#include "Box2DDebugRenderer.h"
#include "renderer/Buffer.h"
#include "renderer/Renderer2D.h"

namespace Freeze
{
    namespace Physics {
        namespace PhysicsModule
        {
            inline b2World* m_PhysicsWorld = nullptr;
            inline Box2DDebugRenderer* m_DebugRenderer;

            inline void InitPhysicsWorld()
            {
                FZ_INFO("Physics API Initialised");

                b2Vec2 gravity(0.0f, -9.8f);

                if(m_PhysicsWorld == nullptr)
                    m_PhysicsWorld = new b2World(gravity);
                else
                    FZ_ASSERT("Physics intialised again!");

                m_DebugRenderer = new Box2DDebugRenderer(b2Draw::e_shapeBit);
                m_PhysicsWorld->SetDebugDraw(m_DebugRenderer);
            }

            inline void UpdatePhysicsWorld(float dt)
            {
                m_PhysicsWorld->Step(1.0f / 60.0f, 9, 4);

                // m_PhysicsWorld->DebugDraw();
            }

            inline b2World* GetPhysicsWorld() { return m_PhysicsWorld; }

            inline void DestroyPhysicsWorld()
            {
                delete m_DebugRenderer;
                m_PhysicsWorld->SetDebugDraw(nullptr);
                m_PhysicsWorld->ClearForces();

                delete m_PhysicsWorld;
            }
        };
    };
};
