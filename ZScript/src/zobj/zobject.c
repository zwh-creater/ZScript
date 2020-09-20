#include "../../include/zobject.h"

ZSAPI ZObject* zsCreateObject(zbas_ptr typecode)
{
	ZS_CREATE(z, ZObject);

	if (z != NULL) {
		z->m_typecode = typecode;
		z->m_value = zsCreateString(32);
	}

	return z;
}

ZSAPI void zsDeleteObject(ZObject* z)
{
	if (z != NULL) {
		zsDeleteString(z->m_value);
		free(z);
	}
}
