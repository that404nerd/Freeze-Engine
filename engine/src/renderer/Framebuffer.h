#pragma once

#include <GL/glew.h>

namespace Freeze {
  class Framebuffer {
  public:
    Framebuffer();

    ~Framebuffer();
  private:
    uint32_t m_fbID;
  };
}
