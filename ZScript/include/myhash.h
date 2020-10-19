#ifndef __HASH_H
#define __HASH_H

#include <malloc.h>
typedef unsigned long MYHASHPOSITIONTYPE;
typedef struct
{
	char** data;
	MYHASHPOSITIONTYPE size;
}MYHASH;
typedef struct
{
	char* name;
	char* pvalue;
}MYHASHELEMENT;
MYHASH* MyHashCreate(MYHASHPOSITIONTYPE size);
void MyHashDelete(MYHASH* mh);
MYHASHPOSITIONTYPE MyHashGetKey(const char* str);
char MyHashInsert(MYHASH* mh, const char* name, char* value);
char* MyHashLookUp(MYHASH* mh, const char* name);

#endif // !__HASH_H
