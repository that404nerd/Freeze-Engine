#pragma once

#include <GL/glew.h>
#include "stb/stb_image.h"
#include "core/Core.h"

#include "Shader.h"

#include <string>

namespace Freeze
{
  class Texture
  {
  public:
    Texture();

    void CreateTexture();
    void LoadTextureFile(const std::string& filepath);
      
    void Update();

    void BindTexture(int slot = 0) const;
    void UnbindTexture() const;
    
    ~Texture();

  private:
    uint32_t m_TextureID;
    uint8_t* m_ImageData = nullptr;
    int m_TextureWidth, m_TextureHeight, m_NTextureChannels;

    std::string m_FilePath;

    std::shared_ptr<Shader> m_TextureShader = std::make_shared<Shader>();
  };
};
