#pragma once

// External includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Engine files
#include "Core.h"

// STD Library Includes
#include <string>
#include <memory>

namespace Freeze
{
    class Window
    {
    public:
        Window();

        bool CreateWindow(uint32_t width, uint32_t height, const std::string &title);
        void CreateWindowContext();
        GLFWwindow *GetWindowInstance() { return m_Window; }

        uint32_t GetWindowWidth() { return m_Width; }
        uint32_t GetWindowHeight() { return m_Height; }

        ~Window();
    private:
        static GLFWwindow *m_Window;
        uint32_t m_Width, m_Height;
    };
};