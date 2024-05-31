#pragma once

#include <GL/glew.h>

#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"
#include "core/Core.h"
#include "Texture.h"

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
    static void InitRenderer();

    static void StartBatch();
    static void NextBatch();
    static void Flush(); // Ensure that all the rendering operations are executed
    static void EndBatch();

    static void ShutdownRenderer();
    ~Renderer2D() {};
  public:
    // Quad
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
    static void DrawTexturedQuad(const std::string& filepath, const glm::vec2& position, const glm::vec2& size);

    // Triangle
    static void DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

    // Points
    static void DrawPoint(const glm::vec2& position, const glm::vec4& color); // glVertex2f kinda implementation
    
    // Lines
    static void SetLineWidth(float width);
    static void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color); // Default size (1.0f)
  private:
    inline static float m_Width;
  };
};
