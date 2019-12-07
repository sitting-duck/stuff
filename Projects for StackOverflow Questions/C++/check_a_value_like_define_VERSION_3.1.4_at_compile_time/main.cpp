
#include <string.h>
#include <stdint.h>
#include <stdio.h>


#define xstr(s) str(s)
#define str(s) #s

#define . 0

#define VERSION 3.1.4

#define CORRECT_VERSION 30104

//#if strcmp(xstr(VERSION), CORRECT_VERSION)==0
#if VERSION==CORRECT_VERSION
#else
#error OMG INCORRECT VERSION!
#endif
