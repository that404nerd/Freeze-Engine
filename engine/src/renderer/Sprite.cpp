#include "Sprite.h"

// TODO: Integrate into the 2D Renderer

namespace Freeze {
  Sprite::Sprite(std::shared_ptr<Shader> shader)
    :m_Shader(shader)
  {
    InitRendererData();
  }

  // This is a private function that initialises the sprite data required for rendering! DON'T MODIFY THIS!
  void Sprite::InitRendererData()
  {
    // The positions will be the xy coordinates and the texture coordinates are wz (x, y, w, z -> vec4)
    float spriteVertices[] = {
      // Positions (x, y)     // Texture Coordinates (z, w)
      0.0f, 1.0f,             0.0f, 1.0f,
      1.0f, 0.0f,             1.0f, 0.0f,
      0.0f, 0.0f,             0.0f, 0.0f,

      0.0f, 1.0f,             0.0f, 1.0f,
      1.0f, 1.0f,             1.0f, 1.0f,
      1.0f, 0.0f,             1.0f, 0.0f
    };

    m_VertexArray->AddVertexArray();
    m_VertexArray->BindVertexArray();

    m_VertexBuffer->AddVertexBuffer(spriteVertices, sizeof(spriteVertices));
    m_VertexBuffer->BindVertexBuffer();

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 16, (void*)0);
    glEnableVertexAttribArray(0);
  }

  void Sprite::DrawSprite(std::shared_ptr<Texture> texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color)
  {
    // Enable blending otherwise the resultant sprite will be a mess!
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_Shader->UseShader();
    /* First scale, then rotate and then translate. (SRT)
       This is the advised order of transforming an object.

       But when it comes to multiplying matrices in the shader we need to reverse the order to the following:
       Translation, rotation, scaling (TRS)

       The origin of rotation is at the top-left of the quad, which produces undesirable results. What we want to do is move the origin of rotation to the center of the quad so the quad neatly rotates around this origin, instead of rotating around the top-left of the quad. We solve this by translating the quad by half its size first, so its center is at coordinate (0,0) before rotating.
    */

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f)); // first translate using the given position vector parameter
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // translate again but now the size.x and size.y (with 0.5f)

    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // now rotate using the angle specified and in the z (x, y rotation is going to give weird results!)

    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // rotate again but using the value of -0.5f.

    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f)); // scale the texture using the size specified and the z-axis is default as usual.

    m_Shader->SetMatrix4fv(m_Shader->GetUniformLocation("a_ModelMatrix"), modelMatrix);
    m_Shader->SetVector3f(m_Shader->GetUniformLocation("spriteColor"), color);

    texture->BindTexture(); // bind the texture (the texture will be passed when using the function)
    m_VertexArray->BindVertexArray(); // bind the vertex array
    glDrawArrays(GL_TRIANGLES, 0, 6);  // Draw it. (We don't really have any index buffer setup and likely we won't so this is fine)
  }

  Sprite::~Sprite()
  {
    m_Shader->DeleteShaders();
  }
};
