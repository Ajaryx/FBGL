#ifdef _WIN32

#ifdef FBGL_BUILD_DLL
#define FBGL_API __declspec(dllexport)

#else
#define FBGL_API __declspec(dllimport)
#endif

#else

#define FBGL_API __attribute__((visibility("default")))

#endif
