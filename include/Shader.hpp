#pragma once

#include "FBGL.hpp"

class FBGL_API Shader
{
public:
    Shader(const std::string& shaderName);
    Shader(const std::string& shaderName, const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
    ~Shader();

        void bind();
        void unbind();

        //Getter
    inline uint16_t GetShaderState() const
    {
        return m_ShaderState;
    };
    inline std::string GetShaderName() const
    {
        return m_ShaderName;
    }
    inline GLuint GetShaderID() const
    {
        return m_programID;
    }

public:

    int GetUnfiformLocation(const std::string& uniformName);



private:


    std::string parse(const std::string& filePath);
    GLuint compileShader(GLenum type, const std::string& src);
    GLuint CreateShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

    GLuint m_programID;
    GLuint m_vertShaderID = -1;
    GLuint m_fragShaderID = -1;

    std::string m_vertexShaderFilePath;
    std::string m_fragmentShaderFilePath;

    std::string lastError = "";

    uint16_t m_ShaderState;

    std::string m_ShaderName;

};
