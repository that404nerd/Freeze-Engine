#pragma once

#include "core/Window.h"

#include <array>

namespace Freeze
{
    class MouseInput
    {
    public:
        MouseInput();

        static bool IsMousePressed(int scancode);
        static void HideCursor(bool setCursorStatus);

        static std::pair<double, double> GetMouseCoords();

        ~MouseInput();

    private:
        float m_X, m_Y;
    };
};