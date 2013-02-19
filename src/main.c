#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


void __attribute__ ((constructor)) sGL_load(void);
void __attribute__ ((destructor))  sGL_unload(void);

void sGL_load(void)
 {
    printf("preload!\n");
 }

 void sGL_unload(void)
 {
     printf("preUnload!\n");

 }
