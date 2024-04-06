#include "Shader.h"

namespace Freeze
{
    Shader::Shader()
    {
    }


    void Shader::LoadShaders(const std::string& vertexShader, const std::string& fragmentShader)
    {
        const GLchar* vertexSource = vertexShader.c_str();
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
        glCompileShader(m_VertexShader);

        int resultVertex;
        char infoVertex[1024];
        glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &resultVertex);

        if (!resultVertex)
        {
            glGetShaderInfoLog(m_VertexShader, 1024, nullptr, infoVertex);
            spdlog::error("Failed to compile vertex shader {}", infoVertex);
        }

        const GLchar* fragmentSource = fragmentShader.c_str();
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(m_FragmentShader);

        int resultFragment;
        char infoFragment[1024];
        glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &resultFragment);

        if (!resultFragment)
        {
            glGetShaderInfoLog(m_FragmentShader, 1024, nullptr, infoFragment);
            spdlog::error("Failed to compile fragment shader {} ", infoFragment);
        }

        m_ShaderProgramID = glCreateProgram();
        glAttachShader(m_ShaderProgramID, m_VertexShader);
        glAttachShader(m_ShaderProgramID, m_FragmentShader);
        glLinkProgram(m_ShaderProgramID);
    }

    void Shader::LoadShadersFromFiles(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexShaderFile);
            fShaderFile.open(fragmentShaderFile);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            FZ_INFO("Shader file failed to read! {}", e.what());
        }

        const GLchar* vertexSource = vertexCode.c_str();
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
        glCompileShader(m_VertexShader);

        int resultVertex;
        char infoVertex[1024];
        glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &resultVertex);

        if (!resultVertex)
        {
            glGetShaderInfoLog(m_VertexShader, 1024, nullptr, infoVertex);
            spdlog::error("Failed to compile vertex shader {}", infoVertex);
        }

        const GLchar* fragmentSource = fragmentCode.c_str();
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(m_FragmentShader);

        int resultFragment;
        char infoFragment[1024];
        glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &resultFragment);

        if (!resultFragment)
        {
            glGetShaderInfoLog(m_FragmentShader, 1024, nullptr, infoFragment);
            spdlog::error("Failed to compile fragment shader {} ", infoFragment);
        }

        m_ShaderProgramID = glCreateProgram();
        glAttachShader(m_ShaderProgramID, m_VertexShader);
        glAttachShader(m_ShaderProgramID, m_FragmentShader);
        glLinkProgram(m_ShaderProgramID);
    }

    void Shader::UseShader()
    {
        glUseProgram(m_ShaderProgramID);
    }

    void Shader::UnbindShader()
    {
        glUseProgram(0);
    }

    uint32_t Shader::GetUniformLocation(const std::string& uniformName) const
    {
        m_GetUniformLocation = glGetUniformLocation(m_ShaderProgramID, uniformName.c_str());
        return m_GetUniformLocation;
    }

    void Shader::SetMatrix4fv(uint32_t loc, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(m_GetUniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetVector2f(uint32_t loc, const glm::vec2& vector)
    {
        glUniform2f(m_GetUniformLocation, vector[0], vector[1]);
    }

    void Shader::SetVector3f(uint32_t loc, const glm::vec3& vector)
    {
        glUniform3f(m_GetUniformLocation, vector[0], vector[1], vector[2]);
    }

    void Shader::SetVector4f(uint32_t loc, const glm::vec4& vector)
    {
        glUniform4f(m_GetUniformLocation, vector[0], vector[1], vector[2], vector[3]);
    }

    void Shader::SetInteger(uint32_t loc, int index)
    {
        glUniform1i(m_GetUniformLocation, index);
    }

    Shader::~Shader()
    {
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);
    }
};