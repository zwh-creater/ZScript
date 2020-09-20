#ifndef __ZOBJECT_H
#define __ZONJECT_H

#include "def.h"
#include "zbas.h"

typedef struct
{
	zbas_ptr    m_typecode;
	zbas_ptr  m_value;
}ZObject;

ZSAPI ZObject* zsCreateObject(zbas_ptr typecode);
ZSAPI void zsDeleteObject(ZObject* z);

#endif