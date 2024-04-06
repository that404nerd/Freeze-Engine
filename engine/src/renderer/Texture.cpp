#include "Texture.h"

namespace Freeze
{
    Texture::Texture()
    {
    }

    void Texture::GenerateTexture(int nTextures, const std::string& filepath, GLint format)
    {
        stbi_set_flip_vertically_on_load(1);
        glGenTextures(nTextures, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        // Set the texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_ImageData = stbi_load(filepath.c_str(), &m_TextureWidth, &m_TextureHeight, &m_NTextureChannels, 0);
        if (m_ImageData)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, format, m_TextureWidth, m_TextureHeight, 0, format, GL_UNSIGNED_BYTE, m_ImageData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            FZ_ERROR("Failed to load texture {}", stbi_failure_reason());
        }
    }

    void Texture::BindTexture(int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void Texture::UnbindTexture() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        stbi_image_free(m_ImageData);
    }
};
