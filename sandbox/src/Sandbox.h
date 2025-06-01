#pragma once

#include "core/OpenGLDebug.h"
#include "event/Event.h"

////////// Sandbox Includes /////////////
#include "World.h"

class Sandbox
{
public:
    Sandbox();

    void OnInit();
    void OnImGui();
    void OnEvent(Freeze::Event& event);
    void OnUpdate(float dt);

    ~Sandbox();

private:
    std::shared_ptr<Freeze::Texture> m_Texture = std::make_shared<Freeze::Texture>();

    std::unique_ptr<World> m_World = std::make_unique<World>();

    bool m_OpenImGuiWindow = true;
};
