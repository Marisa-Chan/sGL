// The functions contained in this file are pretty dummy
// and are included only as a placeholder. Nevertheless,
// they *will* get included in the shared library if you
// don't remove them :)
//
// Obviously, you 'll have to write yourself the super-duper
// functions to include in the resulting library...
// Also, it's not necessary to write every function in this file.
// Feel free to add more files in this project. They will be
// included in the resulting library.

// A function adding two integers and returning the result

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


void __attribute__ ((constructor)) sGL_load(void);
void __attribute__ ((destructor))  sGL_unload(void);

void ( *glmatrixf)(void *m);
void ( *glmatmode)(unsigned int m);


void glLoadMatrixf(void *m)
{
    printf("glLoadMatrix\n");
    glmatrixf(m);
}


void sGL_load(void)
 {
    printf("preload!\n");

    void *hndl = dlopen("libGL.so",RTLD_LAZY);

    glmatrixf = dlsym(hndl, "glLoadMatrixf");
    glmatmode = dlsym(hndl, "glMatrixMode");
 }

void glMatrixMode(unsigned int m)
{
    printf("glMatrixMode(%d)\n",m);
    glmatmode(m);
}

 void sGL_unload(void)
 {
     printf("preUnload!\n");

 }


int SampleAddInt(int i1, int i2)
{
    return i1 + i2;
}

// A function doing nothing ;)
void SampleFunction1()
{
    // insert code here
}

// A function always returning zero
int SampleFunction2()
{
    // insert code here

    return 0;
}
