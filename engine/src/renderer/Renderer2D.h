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
  protected:
    inline static glm::mat4 m_TransformMatrix;
  };

  class ShapeRenderer : public Renderer2D {
  public:

    // Quad
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
    void DrawTexturedQuad(const std::string& filepath, const glm::vec2& position, const glm::vec2& size);

    // Triangle
    void DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
  };

};
