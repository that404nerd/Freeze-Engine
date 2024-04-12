#pragma once

#include <GL/glew.h>

#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"
#include "core/Core.h"

#include <memory>

namespace Freeze {

  class RenderCommands
  {
  public:
    static void SetRenderColor(const glm::vec4& color);
    static void RenderClear();
  };

  // Batch Rendering
  class Renderer2D {
  public:
    Renderer2D() = default;

    static void StartBatch();
    static void NextBatch();
    static void Flush(); // Ensure that all the rendering operations are executed
    static void EndBatch();

    static void InitRenderer();

    // Quad
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

    // Triangle
    static void DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

    static void ShutdownRenderer();
    ~Renderer2D() {};
  };

};
