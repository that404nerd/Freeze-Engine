#pragma once

#include <GL/glew.h>
#include "../core/Core.h"

namespace Freeze
{
    class VertexArray
    {
    public:
        VertexArray() = default;

        void AddVertexArray(int nVao);

        void BindVertexArray() const;
        void UnbindVertexArray() const;

        ~VertexArray();

    private:
        uint32_t m_VertexArrayID;
        int m_NVertexArrays;
    };
};