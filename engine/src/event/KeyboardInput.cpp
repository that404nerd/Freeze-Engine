#include "KeyboardInput.h"

namespace Freeze {

  bool KeyboardInput::IsKeyPressed(int scancode) 
  {
    if (glfwGetKey(Window::GetWindowInstance(), scancode) == GLFW_PRESS) 
    {
      return true;
    }

    return false;
  }

  bool KeyboardInput::IsKeyRepeated(int scancode) 
  {
    if (glfwGetKey(Window::GetWindowInstance(), scancode) == GLFW_REPEAT) 
    {
      return true;
    }

    return false;
  }

  KeyboardInput::~KeyboardInput() {}
}; 