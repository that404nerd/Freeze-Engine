#pragma once

#include <GL/glew.h>

#include "Window.h"
#include "../../../sandbox/src/Sandbox.h"
#include "renderer/Renderer2D.h"
#include "physics/InitPhysics.h"
#include "AudioSystem.h"
#include "imgui/ImGuiContext.h"
#include "renderer/Buffer.h"

#include "Core.h"

#include <memory>

namespace Freeze
{
    // Callback functions
    class Application
    {
    public:
        void OnInit(uint32_t width, uint32_t height, const std::string& title);
        static void OnEvent(Event& e);
        void Run();

        static void OnResize(WindowResizeEvent& event);

        virtual ~Application();

    private:
        bool InitGLEW();
    private:
        inline static std::shared_ptr<Sandbox> m_Sandbox;
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<Renderer2D> m_Renderer2D;
        std::shared_ptr<ImGuiContext> m_ImGuiContext;

    };
};
