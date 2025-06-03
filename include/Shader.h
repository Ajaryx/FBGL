#pragma once

#include "FBGL_Export.h"
#include "defines.h"

class FBGL_API Shader
{
public:
    Shader();
    Shader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
    ~Shader();

        void bind();
        void unbind();


private:


    std::string parse(const std::string& filePath);
    GLuint compileShader(GLenum type, const std::string& src);
    GLuint CreateShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

    GLuint m_programID;

    std::string m_vertexShaderFilePath;
    std::string m_fragmentShaderFilePath;

    std::string lastError = "";

};
