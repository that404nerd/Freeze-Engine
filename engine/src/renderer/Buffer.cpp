#include "Buffer.h"
#include "renderer/Shader.h"

namespace Freeze
{

  /////////////////////////////////// Vertex Buffer //////////////////////////////////////////////

  void VertexBuffer::AddVertexBuffer(const void *data, uint32_t size)
  {
    glGenBuffers(1, &m_VertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjectID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    if (data == nullptr)
    {
      FZ_ERROR("Vertex Buffer: No Data/Invalid Data Provided");
      FZ_EXIT();
    }
  }

  // Override function for dynamic geometry
  void VertexBuffer::AddVertexBuffer(uint32_t size, GLenum drawType)
  {
    glGenBuffers(1, &m_VertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjectID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, drawType); // Set data -> nullptr
  }

  void VertexBuffer::SetVertexBufferData(const void* data, uint32_t size)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjectID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); // Not for allocating memory but for writing into it
  }

  void VertexBuffer::BindVertexBuffer() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjectID);
  }

  void VertexBuffer::UnbindVertexBuffer() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  VertexBuffer::~VertexBuffer()
  {
    glDeleteBuffers(1, &m_VertexBufferObjectID);
  }

  ///////////////////////////////// Element Buffer /////////////////////////////////////////

  void IndexBuffer::AddIndexBuffer(uint32_t *data, uint32_t size, GLenum drawType)
  {
    glGenBuffers(1, &m_IndexBufferObjectID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObjectID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawType);

    if (data == nullptr)
    {
      FZ_ERROR("Element Buffer: No Data/Invalid Data Provided");
      FZ_EXIT();
    }

  }

  void IndexBuffer::BindIndexBuffer() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObjectID);
  }

  void IndexBuffer::UnbindIndexBuffer() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  IndexBuffer::~IndexBuffer()
  {
    glDeleteBuffers(1, &m_IndexBufferObjectID);
  }

  ///////////////////////////////// Vertex Array /////////////////////////////////////////
  void VertexArray::AddVertexArray()
  {
    glGenVertexArrays(1, &m_VertexArrayID);
  }

  void VertexArray::BindVertexArray() const
  {
    glBindVertexArray(m_VertexArrayID);
  }

  void VertexArray::UnbindVertexArray() const
  {
    glBindVertexArray(0);
  }

  VertexArray::~VertexArray()
  {
    glDeleteVertexArrays(1, &m_VertexArrayID);
  }

  ///////////////////////////////// FrameBuffers //////////////////////////////////////////
  void Framebuffer::CreateFrameBuffer(uint32_t width, uint32_t height)
  {
    glGenFramebuffers(1, &m_fbID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbID);

    glGenTextures(1, &m_TexAttachment);
    glBindTexture(GL_TEXTURE_2D, m_TexAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexAttachment, 0);

    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        FZ_WARN("Framebuffer not complete: {}", status);
    } else { FZ_INFO("Framebuffer created!"); }


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  const void Framebuffer::BindFrameBuffer() const { glBindFramebuffer(GL_FRAMEBUFFER, m_fbID); }
  const void Framebuffer::UnbindFrameBuffer() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
  const uint32_t Framebuffer::GetFrameBufferTexture() const { return m_TexAttachment; }

  Framebuffer::~Framebuffer()
  {
    glDeleteFramebuffers(1, &m_fbID);  
    glDeleteTextures(1, &m_TexAttachment);
  }

};
