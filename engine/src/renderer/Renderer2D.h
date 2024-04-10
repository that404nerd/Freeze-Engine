#pragma once

#include <GL/glew.h>

#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
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

  class FreezeQuad {
  private:
    struct QuadRendererData
    {
      std::shared_ptr<Freeze::VertexBuffer> m_VertexBuffer = std::make_shared<Freeze::VertexBuffer>();
      std::shared_ptr<Freeze::ElementBuffer> m_ElementBuffer = std::make_shared<Freeze::ElementBuffer>();
      std::shared_ptr<Freeze::VertexArray> m_VertexArray = std::make_shared<Freeze::VertexArray>();
      std::shared_ptr<Freeze::Shader> m_RendererShader = std::make_shared<Freeze::Shader>();

      float* m_QuadCoords;
      uint32_t* m_QuadIndices;
    };

  public:
    FreezeQuad();

    void CreateQuad(float width, float height, const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void RenderQuad(const glm::mat4& projectionMatrix, const glm::vec2& positions, const glm::vec4& color);

    glm::vec2 GetQuadPositions() { return m_Positions; }

    ~FreezeQuad();

  private:
    QuadRendererData* m_QuadRendererData;
    glm::vec2 m_Positions;
  };

  class FreezeTriangle
  {
  private:
    struct TriangleRendererData
    {
      std::shared_ptr<Freeze::VertexBuffer> m_VertexBuffer = std::make_shared<Freeze::VertexBuffer>();
      std::shared_ptr<Freeze::ElementBuffer> m_ElementBuffer = std::make_shared<Freeze::ElementBuffer>();
      std::shared_ptr<Freeze::VertexArray> m_VertexArray = std::make_shared<Freeze::VertexArray>();
      std::shared_ptr<Freeze::Shader> m_RendererShader = std::make_shared<Freeze::Shader>();

      float* m_TriangleCoords;
    };

  public:
    FreezeTriangle();

    void CreateTriangle(float width, float height, const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void RenderTriangle(const glm::mat4& projectionMatrix, const glm::vec2& positions, const glm::vec4& color);

    ~FreezeTriangle();

  private:
    TriangleRendererData* m_TriangleRendererData;
  };

}; // namespace Freeze
