#include "KeyboardInput.h"

namespace Freeze {
KeyboardInput::KeyboardInput() {}

bool KeyboardInput::IsKeyPressed(GLFWwindow *window, int scancode) {
  if (glfwGetKey(window, scancode) == GLFW_PRESS) {
    return true;
  }

  return false;
}

bool KeyboardInput::IsKeyRepeated(GLFWwindow *window, int scancode) {
  if (glfwGetKey(window, scancode) == GLFW_REPEAT) {
    return true;
  }

  return false;
}

KeyboardInput::~KeyboardInput() {}
};  // namespace Freeze
