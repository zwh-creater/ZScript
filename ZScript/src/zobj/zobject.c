#include "../../include/zobject.h"

ZSAPI ZObject* zsCreateObject(zbas_ptr typecode)
{
	ZS_CREATE(z, ZObject);

	if (z != NULL) {
		z->m_typecode = typecode;
		z->m_value = 0;
	}

	return z;
}

#include <stdio.h>

ZSAPI void zsDeleteObject(ZObject* z)
{
	if (z != NULL) {
		switch (z->m_typecode)
		{
		case 'num':
			PRINT_S("\nDELETE:");
			PRINT_F(*(double*)z->m_value);
			PRINT_S("\n");
			break;
		case 'func':
			zsDeleteArray(z->m_value);
			break;
		default:
			break;
		}
		
		free(z);
	}
}

ZSAPI ZObject* zsCreateNumber(double number)
{
	ZS_CREATE(z, ZObject);
	if (z != NULL) {
		z->m_typecode = 'num';
		if((z->m_value = malloc(sizeof(double)))!=NULL)
			(*(double*)z->m_value) = number;
	}
	return z;
}

ZSAPI double zsGetNumber(ZObject* z)
{
	return (*(double*)z->m_value);
}

ZSAPI void zsSetNumber(ZObject* z, double number)
{
	(*(double*)z->m_value) = number;
}

ZSAPI void zsCopyNumber(ZObject* dst, ZObject* src)
{
	(*(double*)dst->m_value) = (*(double*)src->m_value);
}

ZSAPI void zsAddNumbers(ZObject* z,ZObject* a, ZObject* b)
{
	(*(double*)z->m_value) = (*(double*)a->m_value)+(*(double*)b->m_value);
}

