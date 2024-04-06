#include "Window.h"
#include "Core.h"

namespace Freeze
{
    GLFWwindow *Window::m_Window;

    Window::Window()
    {
    }

    bool Window::CreateWindow(uint32_t width, uint32_t height, const std::string &title)
    {
        glfwInit();

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        m_Width = width;
        m_Height = height;

        if (m_Window == nullptr)
        {
            FZ_ERROR("Window failed to initialise");
            FZ_EXIT();
            return false;
        }

        return true;
    }

    void Window::CreateWindowContext()
    {
        glfwMakeContextCurrent(m_Window);
    }

    Window::~Window()
    {
        glfwTerminate();
    }
};