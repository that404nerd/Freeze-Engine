#include "MouseInput.h"

namespace Freeze
{
    MouseInput::MouseInput()
    {
    }

    bool MouseInput::IsMousePressed(GLFWwindow* window, int scancode)
    {
        if(glfwGetMouseButton(window, scancode) == GLFW_PRESS) 
        {
            return true;
        }

        return false;
    }

    void MouseInput::HideCursor(GLFWwindow* window, bool setCursorStatus)
    {
        if(setCursorStatus)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    std::pair<double, double> MouseInput::GetMouseCoords(GLFWwindow *window)
    {
        std::pair<double, double> mousePos;
        glfwGetCursorPos(window, &mousePos.first, &mousePos.second);

        return mousePos;
    }

    MouseInput::~MouseInput()
    {
    }
};