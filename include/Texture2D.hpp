#pragma once

#include "FBGL_Export.hpp"
#include "stb_image.h"

class FBGL_API Texture2D
{
public:
    Texture2D(const std::string& path, GLuint shaderID);
    ~Texture2D();


    bool loadImageFromFile(const std::string& path);
    void bind();
    void unbind();

    inline GLuint GetTextureBufferID() const
    {
        return m_TextureBufferID;
    }
    inline int GetTextureWidth() const
    {
        return m_TextureWidth;
    } 
    inline int GetTextureHeight() const
    {
        return m_TextureHeight;
    }
    //Can return nullptr!
    inline stbi_uc* GetTextureBufferData() const
    {
        return m_textureBufferData;
    }  
    inline std::string GetTexturePath() const
    {
        return m_texturePath;
    }

private:

    std::string m_texturePath;
    int m_TextureWidth;
    int m_TextureHeight;
    int m_bitsPerPixel;
    stbi_uc* m_textureBufferData = nullptr;

    GLuint m_TextureBufferID;

    GLuint m_shaderID;

    int m_uniformTextLoc;

};