#include "Texture2D.hpp"

Texture2D::Texture2D(const std::string &path, GLuint shaderID)
{
    this->m_shaderID = shaderID;
    m_uniformTextLoc = glGetUniformLocation(m_shaderID, "u_texture");
    glUniform1i(m_uniformTextLoc, 0);
    loadImageFromFile(path);
}

Texture2D::~Texture2D()
{
    stbi_image_free(m_textureBufferData);
    m_textureBufferData = nullptr;
    glDeleteTextures(1, &m_TextureBufferID);
}

bool Texture2D::loadImageFromFile(const std::string &path)
{
    this->m_texturePath = path;

    if(!fopen(path.c_str(), "r"))
    {
        std::cerr << "File Image: " << path <<  " doesnt exists\n";
        return false;
    }

    m_textureBufferData = stbi_load(path.c_str(), &m_TextureWidth, &m_TextureHeight, &m_bitsPerPixel, 4);

    glGenTextures(1, &m_TextureBufferID);
    glBindTexture(GL_TEXTURE_2D, m_TextureBufferID);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_TextureWidth, m_TextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureBufferData);

    return true;
}
void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureBufferID);
    
}
void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
