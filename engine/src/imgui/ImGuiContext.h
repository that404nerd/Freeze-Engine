#pragma once

#include <GLFW/glfw3.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "core/Core.h"

namespace Freeze
{
    class ImGuiContext
    {
    public:
        ImGuiContext() = default;

        void CreateImGuiContext(GLFWwindow* window)
        {
            FZ_INFO("ImGui Version: {}", IMGUI_VERSION); // Check the version
            ImGui::CreateContext();                           // Create the ImGui Context

            ImGuiIO& io = ImGui::GetIO();                         // Main configuration and I/O between your application and ImGui
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 420");

            ImGui::StyleColorsDark();
        }

        void UpdateImGui()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void RenderImGui()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        ~ImGuiContext()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    };
};