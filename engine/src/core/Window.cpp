#include "Window.h"

namespace Freeze
{
    GLFWwindow *Window::m_Window;
    uint32_t Window::m_Width;
    uint32_t Window::m_Height;
    bool Window::m_IsWindowClosed = false;

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
        m_IsWindowClosed = false;

        if (m_Window == nullptr)
        {
            FZ_ERROR("Window failed to initialise");
            FZ_EXIT();
            return false;
        }

        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        return true;
    }
    
    void Window::InitCallbacks()
    {
      glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		  {
        WindowDataFn* data = static_cast<WindowDataFn*>(glfwGetWindowUserPointer(window));
        m_Width = width;
        m_Height = height;

        if (data && data->callbackFn) {
          WindowResizeEvent event(m_Width, m_Height);
          data->callbackFn(event);
        }
		  });

      glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
      {
          WindowDataFn* data = static_cast<WindowDataFn*>(glfwGetWindowUserPointer(window));

          m_IsWindowClosed = true;

          if(data && data->callbackFn)
          {
              WindowCloseEvent event;
              data->callbackFn(event);
          }
      });
    }  

    void Window::CreateWindowContext()
    {
        glfwMakeContextCurrent(m_Window);
    }

    void Window::DestroyWindow()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
};
