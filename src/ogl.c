#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

static void *ogl_hndl = NULL;
static void *glu_hndl = NULL;

static void GLAPIENTRY (*_glClear)( GLbitfield mask )                                                                                      = NULL;
static void GLAPIENTRY (*_glColorMask)( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha )                                  = NULL;
static void GLAPIENTRY (*_glFrustum)( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val )  = NULL;
static void GLAPIENTRY (*_glLoadMatrixd)( const GLdouble *m )                                                                              = NULL;
static void GLAPIENTRY (*_glLoadMatrixf)( const GLfloat *m )                                                                               = NULL;
static void GLAPIENTRY (*_glMultMatrixd)( const GLdouble *m )                                                                              = NULL;
static void GLAPIENTRY (*_glMultMatrixf)( const GLfloat *m )                                                                               = NULL;
static void GLAPIENTRY (*_glViewport)( GLint x, GLint y, GLsizei width, GLsizei height )                                                   = NULL;
static void (*_glXSwapBuffers)( Display *dpy, GLXDrawable drawable )                                                            = NULL;
static void GLAPIENTRY (*_gluPerspective)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)                                   = NULL;

inline void check_ogl_hndl()
{
    if (!ogl_hndl)
    {
        ogl_hndl = dlopen("libGL.so",RTLD_LAZY);
        if (!ogl_hndl )
        {
            fputs(dlerror(), stderr);
            exit(1);
        }
    }
}

#define OGL_CHECK_FUNC(func, funcname)\
        if (!func)\
        {   check_ogl_hndl();\
            func = dlsym(ogl_hndl, funcname);\
            if (!func)\
            {   fputs(dlerror(), stderr);\
                exit(1);} }\

inline void check_glu_hndl()
{
    if (!glu_hndl)
    {
        glu_hndl = dlopen("libGLU.so",RTLD_LAZY);
        if (!glu_hndl )
        {
            fputs(dlerror(), stderr);
            exit(1);
        }
    }
}

#define GLU_CHECK_FUNC(func, funcname)\
        if (!func)\
        {   check_glu_hndl();\
            func = dlsym(glu_hndl, funcname);\
            if (!func)\
            {   fputs(dlerror(), stderr);\
                exit(1);} }\


GLAPI void GLAPIENTRY glClear( GLbitfield mask )
{
    OGL_CHECK_FUNC(_glClear, "glClear");
    printf("gl_Clear()\n");
    _glClear(mask);
}


GLAPI void GLAPIENTRY glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha )
{
    OGL_CHECK_FUNC(_glColorMask, "glColorMask");
    printf("glColorMask()\n");
    _glColorMask(red,green,blue,alpha);
}


GLAPI void GLAPIENTRY glFrustum( GLdouble left, GLdouble right,
                                   GLdouble bottom, GLdouble top,
                                   GLdouble near_val, GLdouble far_val )
{
    OGL_CHECK_FUNC(_glFrustum, "glFrustum");
    printf("glFrustum()\n");
    _glFrustum(left, right, bottom, top, near_val, far_val);
}


GLAPI void GLAPIENTRY glLoadMatrixd( const GLdouble *m )
{
    OGL_CHECK_FUNC(_glLoadMatrixd, "glLoadMatrixd");
    printf("glLoadMatrixd()\n");
    _glLoadMatrixd( m );
}


GLAPI void GLAPIENTRY glLoadMatrixf( const GLfloat *m )
{
    OGL_CHECK_FUNC(_glLoadMatrixf, "glLoadMatrixf");
    printf("glLoadMatrixf()\n");
    _glLoadMatrixf( m );
}


GLAPI void GLAPIENTRY glMultMatrixd( const GLdouble *m )
{
    OGL_CHECK_FUNC(_glMultMatrixd, "glMultMatrixd");
    printf("glMultMatrixd()\n");
    _glMultMatrixd( m );
}


GLAPI void GLAPIENTRY glMultMatrixf( const GLfloat *m )
{
    OGL_CHECK_FUNC(_glMultMatrixf, "glMultMatrixf");
    printf("glMultMatrixf()\n");
    _glMultMatrixf( m );
}


GLAPI void GLAPIENTRY glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
{
    OGL_CHECK_FUNC(_glViewport, "glViewport");
    printf("glViewport()\n");
    _glViewport( x, y, width, height );
}


void glXSwapBuffers( Display *dpy, GLXDrawable drawable )
{
    OGL_CHECK_FUNC(_glXSwapBuffers, "glXSwapBuffers");
    printf("glXSwapBuffers()\n");
    _glXSwapBuffers( dpy, drawable );
}


GLAPI void GLAPIENTRY gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLU_CHECK_FUNC(_gluPerspective, "gluPerspective");
    printf("gluPerspective()\n");
    _gluPerspective( fovy, aspect, zNear, zFar );
}
