#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"

#include <glm/glm.hpp>
#include <memory>

namespace Freeze {
  class Sprite {
  public:
    // @param shader Shader that should be passed which is responsible for rendering the actual sprite
    Sprite(std::shared_ptr<Shader> shader);

    // @param texture The actual texture that needs to be modified
    // @param position Position of the texture. Requires position only in the x, y direction so position is a glm::vec2
    // @param size Can be zoomed or can be really small based on the orthographic projection specified using the Freeze::Camera API's constructor
    // @param rotation Rotate the sprite with the specified value
    // @param color Color of the sprite
    void DrawSprite(std::shared_ptr<Texture> texture, glm::vec2 position, glm::vec2 size, float rotation,
                      glm::vec3 color = glm::vec3(1.0f));

    ~Sprite();
  private:
    void InitRendererData();
  private:
    std::shared_ptr<Freeze::VertexBuffer> m_VertexBuffer = std::make_shared<Freeze::VertexBuffer>();
    std::shared_ptr<Freeze::VertexArray> m_VertexArray = std::make_shared<Freeze::VertexArray>();

    std::shared_ptr<Shader> m_Shader = std::make_shared<Shader>();
  };
};
