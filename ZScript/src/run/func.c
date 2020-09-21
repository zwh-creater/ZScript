#include "..\..\include\func.h"

ZSAPI ZObject* zsCreateFunc()
{
	ZS_CREATE(z, ZObject);
	if (z != NULL) {
		z->m_typecode = 'func';
		z->m_value = zsCreateArray(512);
	}
	return z;
}

ZSAPI void zsWriteFunc(ZObject* func,zbas_ptr v)
{
	zsArrayPush((zbas_array*)func->m_value,(zbas_uint)v);
}
