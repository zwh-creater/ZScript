#ifndef __ZOBJECT_H
#define __ZONJECT_H

#include <malloc.h>
#include "def.h"

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
	zbas_ptr m_value;
	zbas_ptr m_prev;
	zbas_ptr m_next;
}zbas_node;

typedef struct
{
	zbas_ptr    m_typecode;
	zbas_ptr  m_value;
}ZObject;

ZSAPI zbas_lpstr zsCreateString(zbas_uint n);
ZSAPI void zsDeleteString(zbas_ptr p);
ZSAPI void zsSetString(zbas_ptr p, const char* src,zbas_uint n);

ZSAPI zbas_bool zsCompare(zbas_lpstr str1, zbas_lpstr str2);

typedef unsigned long zbas_dword;
ZSAPI zbas_ptr zsCreateArray(zbas_uint n);
ZSAPI void zsDeleteArray(zbas_ptr p);
ZSAPI void zsArrayPush(zbas_ptr p, zbas_ptr value_p);

ZSAPI zbas_node* zsCreateNode(zbas_ptr value);
ZSAPI void zsDeleteNode(zbas_node* node,zbas_node** node_end);
ZSAPI zbas_ptr zsChainPush(zbas_ptr node,zbas_ptr value);

#define ZS_BEGIN_ITER(iter,start) \
	zbas_node* iter = start; \
	while(iter!=NULL){ 

#define ZS_NOT_NULL(n)	if(n!=NULL)

#define ZS_END_ITER(iter) \
	iter = iter->m_next;}

ZSAPI ZObject* zsCreateObject(zbas_ptr typecode);
ZSAPI void zsDeleteObject(ZObject* z);

#endif