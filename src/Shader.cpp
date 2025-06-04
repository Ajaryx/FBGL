#include "Shader.hpp"

Shader::Shader(const std::string& shaderName)
{
    m_ShaderState |= ShaderState::ESS_SHADER_OK;
    this->m_ShaderName = shaderName;
}


Shader::Shader(const std::string& shaderName, const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{

    this->m_ShaderName = shaderName;

    this->m_vertexShaderFilePath = vertexShaderFilePath;
    this->m_fragmentShaderFilePath = fragmentShaderFilePath;

    m_ShaderState |= ShaderState::ESS_SHADER_OK;

    m_programID = CreateShader(m_vertexShaderFilePath, m_fragmentShaderFilePath);

}

Shader::~Shader()
{
    glDetachShader(m_programID, m_vertShaderID);
    glDetachShader(m_programID, m_fragShaderID);

    glDeleteProgram(m_programID);
}

int Shader::GetUnfiformLocation(const std::string &uniformName)
{
    int uniformLocation = glGetUniformLocation(m_programID, uniformName.c_str());

    if(uniformLocation <= -1)
    {
        std::cerr << "Cannot find uniform: " << uniformName << '\n';
        return -1;
    }

    return uniformLocation;

}

std::string Shader::parse(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios_base::ate);

    if(!file)
    {
        std::cerr << "Cannot open file path: " << filePath << std::endl;
        m_ShaderState |= ShaderState::EES_SHADER_NO_SRC;
        return std::string();
    }

    std::streampos lenght = file.tellg();

    file.seekg(0);


    std::string src;

    std::string str;


    while (std::getline(file, str))
    {
        src += str + '\n';
    }

    if(src.empty())
    {
        std::cerr << "Shader Source Code: " << filePath << " is empty!\n";
        lastError = "Shader Source Code: " + filePath + " is empty!\n";
        m_ShaderState |= ShaderState::EES_SHADER_NO_SRC;
    }

    return src;


}
GLuint Shader::compileShader(GLenum type, const std::string &src)
{

    GLuint shaderID = glCreateShader(type);

    const char* shaderSrc = src.c_str();

    std::string shaderType;
    if(type == GL_VERTEX_SHADER)
    {
        shaderType = "VERTEX SHADER";
        this->m_vertShaderID = shaderID;
    }
    else if(type == GL_FRAGMENT_SHADER)
    {
        shaderType = "FRAGMENT SHADER";
        this->m_fragShaderID = shaderID;
    }

    glShaderSource(shaderID, 1, &shaderSrc, 0);

    glCompileShader(shaderID);

    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

    if(result != GL_TRUE)
    {

        m_ShaderState |= ShaderState::ESS_SHADER_COMPILE_ERROR;

        int lenght;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lenght);

        char* errorLog = new char[lenght];

        glGetShaderInfoLog(shaderID, lenght, &lenght, errorLog);


        std::cerr << "SHADER COMPILE ERROR OF TYPE: " << shaderType << '\n' << errorLog << std::endl;

        lastError = errorLog;

        delete[] errorLog;
        errorLog = nullptr;

        return 0;
    }



    return shaderID;
}
GLuint Shader::CreateShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
    std::string vertSrc = parse(vertexShaderFilePath);
    std::string fragSrc = parse(fragmentShaderFilePath);



    GLuint vertID = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fragID = compileShader(GL_FRAGMENT_SHADER, fragSrc);


    GLuint programID = glCreateProgram();


    glAttachShader(programID, vertID);
    glAttachShader(programID, fragID);


    glLinkProgram(programID);


    return programID;

}

void Shader::bind()
{
    if(m_ShaderState & (ShaderState::ESS_SHADER_COMPILE_ERROR | ShaderState::EES_SHADER_NO_SRC))
    return;
    glUseProgram(m_programID);
}
void Shader::unbind()
{
    glUseProgram(0);
}
