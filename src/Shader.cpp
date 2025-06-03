#include "Shader.h"

Shader::Shader()
{

}


Shader::Shader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
    this->m_vertexShaderFilePath = vertexShaderFilePath;
    this->m_fragmentShaderFilePath = fragmentShaderFilePath;

    m_programID = CreateShader(m_vertexShaderFilePath, m_fragmentShaderFilePath);

}

Shader::~Shader()
{

}

std::string Shader::parse(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios_base::ate);

    if(!file)
    {
        std::cout << "Cannot open file path: " << filePath << std::endl;
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
    }
    else if(type == GL_FRAGMENT_SHADER)
    {
        shaderType = "FRAGMENT SHADER";
    }

    glShaderSource(shaderID, 1, &shaderSrc, 0);

    glCompileShader(shaderID);

    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

    if(result != GL_TRUE)
    {
        int lenght;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lenght);

        char* errorLog = new char[lenght];

        glGetShaderInfoLog(shaderID, lenght, &lenght, errorLog);


        std::cout << "SHADER COMPILE ERROR OF TYPE: " << shaderType << '\n' << errorLog << std::endl;

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
    glUseProgram(m_programID);
}
void Shader::unbind()
{
    glUseProgram(0);
}
