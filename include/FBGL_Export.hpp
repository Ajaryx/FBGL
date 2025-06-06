#pragma once


#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include "stb_image.h"


#ifdef _WIN32

#ifdef FBGL_STATIC
#define FBGL_API
#elif FBGL_BUILD_DLL

#define FBGL_API __declspec(dllexport)

#else
#define FBGL_API __declspec(dllimport)
#endif

#else

#define FBGL_API

#endif
