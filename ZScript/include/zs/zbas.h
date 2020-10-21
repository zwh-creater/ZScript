#ifndef __ZBAS_H
#define __ZBAS_H


#include <malloc.h>
#include "def.h"

typedef unsigned char zbas_byte;
typedef unsigned int zbas_uint;
typedef char* zbas_ptr;
typedef unsigned char zbas_bool;

typedef struct
{
	zbas_ptr m_data;
	zbas_uint m_size;
	zbas_uint m_top;
}zbas_string;

typedef zbas_string* zbas_lpstr;

typedef struct
{
	zbas_ptr m_data;
	zbas_uint m_size;
	zbas_uint m_top;
}zbas_array;

typedef struct
{
	zbas_ptr m_value;
	zbas_ptr m_prev;
	zbas_ptr m_next;
}zbas_node;

ZSAPI zbas_lpstr zsCreateString(zbas_uint n);
ZSAPI void zsDeleteString(zbas_ptr p);
ZSAPI void zsSetString(zbas_ptr p, const char* src, zbas_uint n);

ZSAPI void zsStringCat(zbas_ptr p, const char* src, zbas_uint n);

ZSAPI zbas_uint zsGetChar(zbas_ptr p, zbas_uint n);

ZSAPI zbas_bool zsCompare(zbas_lpstr str1, zbas_lpstr str2);

typedef unsigned long zbas_dword;
ZSAPI zbas_ptr zsCreateArray(zbas_uint n);
ZSAPI void zsDeleteArray(zbas_ptr p);
ZSAPI void zsArrayPush(zbas_ptr p, zbas_ptr value_p);
ZSAPI zbas_ptr zsArrayPop(zbas_ptr p);
ZSAPI zbas_ptr zsGetAt(zbas_ptr p,zbas_uint n);
ZSAPI void zsSetAt(zbas_ptr p,zbas_uint n,zbas_ptr v);

ZSAPI zbas_node* zsCreateNode(zbas_ptr value);
ZSAPI void zsDeleteNode(zbas_node* node, zbas_node** node_end);
ZSAPI zbas_ptr zsChainPush(zbas_ptr node, zbas_ptr value);

#define ZS_BEGIN_ITER(iter,start) \
	zbas_node* iter = start; \
	while(iter!=NULL){ 

#define ZS_NOT_NULL(n)	if(n!=NULL)

#define ZS_END_ITER(iter) \
	iter = iter->m_next;}

#endif // !
