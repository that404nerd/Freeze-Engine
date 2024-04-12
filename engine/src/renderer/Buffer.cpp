#include "Buffer.h"

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
};
