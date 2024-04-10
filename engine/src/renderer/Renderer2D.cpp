#include "Renderer2D.h"

namespace Freeze {

  void RenderCommands::SetRenderColor(const glm::vec4& color)
  {
      glClearColor(color.r, color.g, color.b, color.a);
  }

  void RenderCommands::RenderClear()
  {
      glClear(GL_COLOR_BUFFER_BIT);
  }

  ///////////////////////// Quad Rendering //////////////////////////////////

  FreezeQuad::FreezeQuad()
  {
  }

  void FreezeQuad::CreateQuad(float width, float height, const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
    
    // TODO: Change the coordinates to be dynamic. Must work for any camera positions. 

   
    }

  void FreezeQuad::RenderQuad(const glm::mat4& projectionMatrix, const glm::vec2& positions, const glm::vec4& color) 
  {
    
  }

  FreezeQuad::~FreezeQuad()
  {
    
  }

  ///////////////////////// Triangle Rendering ///////////////////////////////

  FreezeTriangle::FreezeTriangle()
  {
  }

  void FreezeTriangle::CreateTriangle(float width, float height, const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
  {
    // TODO: Change the coordinates to be dynamic. Must work for any camera positions. 

    
  }

  void FreezeTriangle::RenderTriangle(const glm::mat4& projectionMatrix, const glm::vec2& positions, const glm::vec4& color) 
  {
   
  }

  FreezeTriangle::~FreezeTriangle() {
  }

};  // namespace Freeze
