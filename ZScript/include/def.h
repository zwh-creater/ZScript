#ifndef __DEF_H
#define __DEF_H

#define ZSAPI //_declspec(dllexport)

//using "malloc.h"
#define ZS_CREATE(obj,classname) classname* obj = (classname*)malloc(sizeof(classname))


#endif