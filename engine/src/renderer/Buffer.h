#pragma once

#include <GL/glew.h>

#include "core/Core.h"

#include <cstdint>

namespace Freeze {
    class VertexBuffer 
    {
    public:
        VertexBuffer() = default;

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
        IndexBuffer() = default;

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
        VertexArray() = default;

        void AddVertexArray();

        void BindVertexArray() const;
        void UnbindVertexArray() const;

        uint32_t GetVertexArrayID() { return m_VertexArrayID; }

        ~VertexArray();

    private:
        uint32_t m_VertexArrayID;
    };
};
