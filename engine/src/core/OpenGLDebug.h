#pragma once

#include <GL/glew.h>

#include "Core.h"

namespace Freeze
{
    inline void glDebugOutput(GLenum source,
                       GLenum type,
                       uint32_t id,
                       GLenum severity,
                       GLsizei length,
                       const char *message,
                       const void *userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        FZ_ERROR("Debug message ({}): {}", id, message);

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            FZ_ERROR("Source: API");
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            FZ_ERROR("Source: Window System");
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            FZ_ERROR("Source: Shader Compiler");
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            FZ_ERROR("Source: Third Party");
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            FZ_ERROR("Source: Application");
            break;
        case GL_DEBUG_SOURCE_OTHER:
            FZ_ERROR("Source: Other");
            break;
        }

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            FZ_ERROR("Severity: high");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            FZ_ERROR("Severity: medium");
            break;
        case GL_DEBUG_SEVERITY_LOW:
            FZ_ERROR("Severity: low");
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            FZ_ERROR("Severity: notification");
            break;
        }
    }

    inline void EnableOpenGLDebug()
    {
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }
};