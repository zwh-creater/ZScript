#ifndef __DEF_H
#define __DEF_H
#ifndef ZSIMPORT
#define ZSAPI //_declspec(dllexport)
#else
#define ZSAPI //_declspec(dllimport)
#endif

//using "malloc.h"
#define ZS_CREATE(obj,classname) classname* obj = (classname*)malloc(sizeof(classname))


#endif