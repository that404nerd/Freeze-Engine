#pragma once

#include <GL/glew.h>

#include "core/Core.h"
#include "renderer/Texture.h"

#include <cstdint>

namespace Freeze {
    class VertexBuffer 
    {
    public:
      void AddVertexBuffer(const void* data, uint32_t size);
      void AddVertexBuffer(uint32_t size, GLenum drawType);

      void SetVertexBufferData(const void* data, uint32_t size);

      void BindVertexBuffer() const;
      void UnbindVertexBuffer() const;

      ~VertexBuffer();
    private:
       uint32_t m_VertexBufferObjectID;
    };

    class IndexBuffer
    {
    public:
      
      void AddIndexBuffer(uint32_t* data, uint32_t size, GLenum drawType);

      void BindIndexBuffer() const;
      void UnbindIndexBuffer() const;

      ~IndexBuffer();
    private:
      uint32_t m_IndexBufferObjectID;
    };

    class VertexArray
    {
    public:
      void AddVertexArray();

      void BindVertexArray() const;
      void UnbindVertexArray() const;

      uint32_t GetVertexArrayID() { return m_VertexArrayID; }

      ~VertexArray();

    private:
      uint32_t m_VertexArrayID;
    };

    class Framebuffer {
    public:
      void CreateFrameBuffer(uint32_t width, uint32_t height);
   
      const void BindFrameBuffer() const;
      const void UnbindFrameBuffer() const;
      const uint32_t GetFrameBufferTexture() const;

      ~Framebuffer();
    private:
      uint32_t m_fbID, m_TexAttachment, m_RBO;
      uint32_t m_Width, m_Height;
    };

};
