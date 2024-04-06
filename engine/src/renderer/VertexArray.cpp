#include "VertexArray.h"

namespace Freeze
{
    void VertexArray::AddVertexArray(int nVao)
    {
        m_NVertexArrays = nVao;
        glGenVertexArrays(nVao, &m_VertexArrayID);
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
        glDeleteVertexArrays(m_NVertexArrays, &m_VertexArrayID);
    }
};