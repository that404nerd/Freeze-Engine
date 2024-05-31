#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <memory>

#include "core/OpenGLDebug.h"
#include "event/Event.h"
#include "renderer/Buffer.h"
#include "renderer/Camera.h"
#include "renderer/Renderer2D.h"
#include "core/Window.h"

#include "physics/PhysicsBody.h"

class Sandbox
{
public:
    Sandbox();

    void OnInit();
    void OnImGui();
    void OnEvent(Freeze::Event& event);
    void OnUpdate(float dt);

    bool Status() { return showColliders; }

    ~Sandbox();

private:
    std::shared_ptr<Freeze::Physics::DynamicBody> m_Body = std::make_shared<Freeze::Physics::DynamicBody>("Body1");
    std::shared_ptr<Freeze::Physics::StaticBody> m_PlatformBody = std::make_shared<Freeze::Physics::StaticBody>("Body2");

    std::shared_ptr<Freeze::Camera> m_Camera = std::make_shared<Freeze::Camera>();

    bool showColliders = false;

    bool m_OpenImGuiWindow = true;
};
