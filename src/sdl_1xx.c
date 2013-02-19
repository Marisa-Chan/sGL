#include <dlfcn.h>
#include <SDL/SDL_video.h>

static void *sdl_hndl = NULL;

static SDL_Surface * SDLCALL (* _SDL_SetVideoMode)(int width, int height, int bpp, Uint32 flags)   = NULL;
static void SDLCALL (* _SDL_GL_SwapBuffers)(void)                                                  = NULL;
static void * SDLCALL (* _SDL_GL_GetProcAddress)(const char* proc)                                 = NULL;

inline void check_sdl_hndl()
{
    if (!sdl_hndl)
    {
        sdl_hndl = dlopen("libSDL.so",RTLD_LAZY);
        if (!sdl_hndl )
        {
            fputs(dlerror(), stderr);
            exit(1);
        }
    }
}

#define SDL_CHECK_FUNC(func, funcname)\
        if (!func)\
        {   check_sdl_hndl();\
            func = dlsym(sdl_hndl, funcname);\
            if (!func)\
            {   fputs(dlerror(), stderr);\
                exit(1);} }\



DECLSPEC SDL_Surface * SDLCALL SDL_SetVideoMode (int width, int height, int bpp, Uint32 flags)
{
    SDL_CHECK_FUNC(_SDL_SetVideoMode, "SDL_SetVideoMode");
    printf("SDL_SetVideoMode()\n");
    return _SDL_SetVideoMode( width, height, bpp, flags);
}


DECLSPEC void SDLCALL SDL_GL_SwapBuffers(void)
{
    SDL_CHECK_FUNC(_SDL_GL_SwapBuffers, "SDL_GL_SwapBuffers");
    printf("SDL_GL_SwapBuffers()\n");
    _SDL_GL_SwapBuffers();
}

DECLSPEC void * SDLCALL SDL_GL_GetProcAddress(const char* proc)
{
    SDL_CHECK_FUNC(_SDL_GL_GetProcAddress, "SDL_GL_GetProcAddress");
    printf("SDL_GL_GetProcAddress()\n");
    return _SDL_GL_GetProcAddress( proc );
}
