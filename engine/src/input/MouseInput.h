#pragma once

#include <GLFW/glfw3.h>

#include <array>

namespace Freeze
{
    class MouseInput
    {
    public:
        MouseInput();

        static bool IsMousePressed(GLFWwindow* window, int scancode);
        static void HideCursor(GLFWwindow* window, bool setCursorStatus);

        static std::pair<double, double> GetMouseCoords(GLFWwindow *window);

        ~MouseInput();

    private:
        float m_X, m_Y;
    };
};