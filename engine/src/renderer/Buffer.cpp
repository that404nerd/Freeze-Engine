#include "Buffer.h"
#include "core/Core.h"

namespace Freeze
{

  /////////////////////////////////// Vertex Buffer //////////////////////////////////////////////

  void VertexBuffer::AddVertexBuffer(float *data, uint32_t size,
                                     GLenum drawType)
  {
    glGenBuffers(1, &m_VertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjectID);
    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);

    if (data == nullptr)
    {
      FZ_ERROR(
          "Vertex Buffer: No Data/Invalid Data Provided");
      FZ_EXIT();
    }
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

  ///////////////////////////////// Element Buffer
  /////////////////////////////////////////

  void ElementBuffer::AddElementBuffer(uint32_t *data,
                                       uint32_t size, GLenum drawType)
  {
    glGenBuffers(1, &m_ElementBufferObjectID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferObjectID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawType);

    if (data == nullptr)
    {
      FZ_ERROR(
          "Element Buffer: No Data/Invalid Data Provided");
      FZ_EXIT();
    }

  }

  void ElementBuffer::BindElementBuffer() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferObjectID);
  }

  void ElementBuffer::UnbindElementBuffer() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  ElementBuffer::~ElementBuffer()
  {
    glDeleteBuffers(1, &m_ElementBufferObjectID);
  }
};
