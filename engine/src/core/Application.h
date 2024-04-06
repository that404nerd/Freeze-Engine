#pragma once

#include <GL/glew.h>

#include "Window.h"
#include "../../../sandbox/src/Sandbox.h"
#include "renderer/Renderer2D.h"
#include "physics/InitPhysics.h"
#include "imgui/ImGuiContext.h"

#include "Core.h"

#include <memory>

namespace Freeze
{
    // Callback functions
    inline void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    inline void process_input(GLFWwindow* window);

    class Application
    {
    public:
        void OnInit(uint32_t width, uint32_t height, const std::string& title);
        void OnEvent();
        void Run();

        void SetEngineViewport();

        virtual ~Application();

    private:
        bool InitGLEW();

    private:
        std::shared_ptr<Sandbox> m_Sandbox;
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<ImGuiContext> m_ImGuiContext;
    };
};
