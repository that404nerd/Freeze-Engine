#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <memory>

#include "core/OpenGLDebug.h"

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
    std::shared_ptr<World> m_World = std::make_shared<World>();

    bool m_OpenImGuiWindow = true;
};
