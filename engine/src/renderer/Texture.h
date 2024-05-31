#pragma once

#include <GL/glew.h>
#include "stb/stb_image.h"
#include "core/Core.h"

#include <string>

namespace Freeze
{
  class Texture
  {
  public:
    Texture();

    void CreateTexture();
    void LoadTextureFile(const std::string& filepath);
      
    void BindTexture(int slot = 0) const;
    void UnbindTexture() const;

    uint32_t GetTextureID() { return m_TextureID; }
    
    ~Texture();

  private:
    uint32_t m_TextureID, m_FBTexID;
    uint8_t* m_ImageData = nullptr;
    int m_TextureWidth, m_TextureHeight, m_NTextureChannels;

    std::string m_FilePath;
  };
};
