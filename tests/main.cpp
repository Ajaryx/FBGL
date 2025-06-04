#include <iostream>
#include <SDL3/SDL.h>
#include <cmath>

#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void GL_Error_Callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam)
{
    if(severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_HIGH)
    std::cerr << "[OPEN_GL ERROR]: " << message << '\n';
}


void SetupFrameBuffer()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
}

void CreateWindow(SDL_Window** window, SDL_GLContext& context)
{
    *window = SDL_CreateWindow("OpenGL is so nice", 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(*window);

    if(!context)
    {
         std::cout << "Error creating context for OpenGL!:(\nError: " << SDL_GetError() << std::endl;
        return;
    }

}


int main()
{

    SetupFrameBuffer();
    SDL_Window* window;
    SDL_GLContext glContext;
    CreateWindow(&window, glContext);
    bool ShouldRun = true;


    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        std::cout << "Error Init OpenGL func ptrs! :(\nError: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL Shader: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(GL_Error_Callback, nullptr);



    Vertex2D vertecies[]=
    {
        Vertex2D{-0.5f, -0.5f,
        1.f, 0.f, 0.f, 1.f},
         Vertex2D{-0.5f, 0.5f,
         0.f, 1.f, 0.f, 1.f},
          Vertex2D{0.5f, -0.5f,
         0.f, 0.f, 1.f, 1.f},
          Vertex2D{0.5f, 0.5f,
         0.f, 0.f, 1.f, 1.f},

    };
    uint8_t numVerts = 4;



    VertexBuffer2D buffer2D(numVerts, GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertecies);



    Shader shader("Test_Shader", "../Shader/basic.vert", "../Shader/basic.frag");


    uint64_t perfCounterFreq = SDL_GetPerformanceFrequency();
    uint64_t lastCounter = SDL_GetPerformanceCounter();
    float deltaTime = 0.f;
    std::cout.sync_with_stdio(false);
shader.bind();
    int loc = shader.GetUnfiformLocation("u_viewProjection");
    glm::mat4 m = glm::mat4(1.f);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);

    while (ShouldRun)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
           if(event.type == SDL_EVENT_QUIT)
           {
                ShouldRun = false;
                return 0;
           }
           if(event.type == SDL_EVENT_KEY_DOWN)
           {
                if(event.key.key == SDLK_ESCAPE)
                {
                    ShouldRun = false;
                    return 0;
                }
           }
        }

        shader.bind();
        buffer2D.bind();

        glDrawArrays(GL_TRIANGLE_STRIP, 0, numVerts);
        buffer2D.unbind();
        shader.unbind();

        SDL_GL_SwapWindow(window);


        uint64_t endCounter = SDL_GetPerformanceCounter();
        uint64_t counterElapsed = endCounter - lastCounter;
        deltaTime = static_cast<float>(counterElapsed) / static_cast<float>(perfCounterFreq);
        uint32_t FPS = static_cast<float>(perfCounterFreq) / static_cast<float>(counterElapsed);

        lastCounter = endCounter;



    }
    SDL_DestroyWindow(window);
    SDL_GL_DestroyContext(glContext);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    return 0;
}
