#include "MouseInput.h"

namespace Freeze
{
    MouseInput::MouseInput()
    {
    }

    bool MouseInput::IsMousePressed(GLFWwindow* window, int scancode)
    {
        if(glfwGetMouseButton(Window::GetWindowInstance(), scancode) == GLFW_PRESS) 
        {
            return true;
        }

        return false;
    }

    void MouseInput::HideCursor(GLFWwindow* window, bool setCursorStatus)
    {
        if(setCursorStatus)
        {
            glfwSetInputMode(Window::GetWindowInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    std::pair<double, double> MouseInput::GetMouseCoords(GLFWwindow *window)
    {
        std::pair<double, double> mousePos;
        glfwGetCursorPos(Window::GetWindowInstance(), &mousePos.first, &mousePos.second);

        return mousePos;
    }

    MouseInput::~MouseInput()
    {
    }
};