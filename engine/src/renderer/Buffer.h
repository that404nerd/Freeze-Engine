#pragma once

#include <GL/glew.h>

#include "../core/Core.h"

#include <cstdint>

namespace Freeze {
    class VertexBuffer 
    {
    public:
        VertexBuffer() = default;

        void AddVertexBuffer(float* data, uint32_t size, GLenum drawType);

        void BindVertexBuffer() const;
        void UnbindVertexBuffer() const;

        ~VertexBuffer();
    private:
        uint32_t m_VertexBufferObjectID;
    };

    class ElementBuffer
    {
    public:
        ElementBuffer() = default;

        void AddElementBuffer(uint32_t* data, uint32_t size, GLenum drawType);

        void BindElementBuffer() const;
        void UnbindElementBuffer() const;

        ~ElementBuffer();
    private:
        uint32_t m_ElementBufferObjectID;
    };
};
