#pragma once

#include <GL/glew.h>

// GLM Math Libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/Core.h"
#include "glm/fwd.hpp"

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>

namespace Freeze
{
    class Shader
    {
    public:
        Shader();

        void LoadShaders(const std::string& vertexShader, const std::string& fragmentShader);
        void LoadShadersFromFiles(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

        void UseShader();
        void UnbindShader();

        uint32_t getShaderProgramID() { return m_ShaderProgramID; }

        uint32_t GetUniformLocation(const std::string& uniformName) const;
        void SetMatrix4fv(uint32_t loc, const glm::mat4& matrix);
        void SetVector2f(uint32_t loc, const glm::vec2& vector);
        void SetVector3f(uint32_t loc, const glm::vec3& vector);
        void SetVector4f(uint32_t loc, const glm::vec4& vector);
        void SetInteger(uint32_t loc, int index);

        ~Shader();

    private:
        uint32_t m_ShaderProgramID;
        uint32_t m_VertexShader, m_FragmentShader;
        mutable uint32_t m_GetUniformLocation;
        std::string m_UniformLocation;
    };
};