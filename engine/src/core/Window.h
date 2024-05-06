#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Core.h"
#include "event/WindowEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"

#include <string>
#include <memory>

namespace Freeze
{
    using EventCallbackFn = std::function<void(Event&)>;
    class Window
    {
    public:
      Window();

      bool CreateWindow(uint32_t width, uint32_t height, const std::string &title);
      void CreateWindowContext();
      
      void InitCallbacks();

      static GLFWwindow *GetWindowInstance() { return m_Window; }

      static uint32_t GetWindowWidth() { return m_Width; }
      static uint32_t GetWindowHeight() { return m_Height; }

      bool IsWindowClosed() { return m_IsWindowClosed; }

      void SetEventCallbackFunction(const EventCallbackFn& callback) { m_WindowData.callbackFn = callback; } // Use to call OnEvent in Application.cpp

      static void DestroyWindow();

    private:
      static GLFWwindow* m_Window;
      static uint32_t m_Width, m_Height;

      struct WindowDataFn {
          EventCallbackFn callbackFn;
      };

      WindowDataFn m_WindowData;
      static bool m_IsWindowClosed;
    };
};
