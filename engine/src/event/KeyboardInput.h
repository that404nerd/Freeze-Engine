#pragma once

#include "core/Window.h"

#include <GLFW/glfw3.h>

namespace Freeze {
    class KeyboardInput {
    public:
        KeyboardInput() = default;

        static bool IsKeyPressed(int scancode);
        static bool IsKeyRepeated(int scancode);

        ~KeyboardInput();
    };
};