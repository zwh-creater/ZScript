#include "../../include/zs/zobject.h"

ZSAPI ZObject* zsCreateObject(zbas_ptr typecode)
{
	ZS_CREATE(z, ZObject);

	if (z != NULL) {
		z->m_typecode = typecode;
		z->m_value = 0;
	}

	return z;
}

ZSAPI void zsDeleteObject(ZObject* z)
{
	if (z != NULL) {
		switch (z->m_typecode)
		{
		case 'num':
			PRINT_S("DELETE:");
			PRINT_F(*(double*)z->m_value);
			PRINT_S("\n");
			break;
		case 'func':
			zsDeleteArray(z->m_value);
			break;
		case 'str':
			zsDeleteString(z->m_value);
			break;
		default:
			break;
		}
		
		free(z);
	}
}

ZSAPI void zsChangeObject(ZObject** object, ZObject* n_object)
{
	zsDeleteObject(*object);
	(*object) = n_object;
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

ZSAPI void zsSubNumbers(ZObject* z, ZObject* a, ZObject* b)
{
	(*(double*)z->m_value) = (*(double*)a->m_value) - (*(double*)b->m_value);
}

ZSAPI void zsMulNumbers(ZObject* z, ZObject* a, ZObject* b)
{
	(*(double*)z->m_value) = (*(double*)a->m_value) * (*(double*)b->m_value);
}

ZSAPI void zsDivNumbers(ZObject* z, ZObject* a, ZObject* b)
{
	(*(double*)z->m_value) = (*(double*)a->m_value) / (*(double*)b->m_value);
}

ZSAPI ZObject* zsCreateStringObject(const char* str)
{
	ZS_CREATE(z, ZObject);
	if (z) {
		z->m_typecode = 'str';
		z->m_value = zsCreateString(256);
		return z;
	}
	return NULL;
}

ZSAPI ZObject* zsCreatePointer(ZObject* object)
{
	ZS_CREATE(z, ZObject);
	if (z) {
		z->m_typecode = 'ptr';
		z->m_value =object;
		return z;
	}
	return NULL;
}

ZSAPI ZObject* zsCreateNameSpace(MYHASHPOSITIONTYPE size)
{
	MYHASH* mh = MyHashCreate(size);
	ZS_CREATE(z, ZObject);
	if (z != NULL)
	{
		z->m_typecode = 'nms';
		z->m_value = (zbas_ptr)mh;
		return z;
	}
	return NULL;
}

ZSAPI ZObject* zsDeleteNameSpace(ZObject* z)
{
	if (z != NULL)
	{
		if (z->m_typecode == 'nms')
		{
			MyHashDelete(z->m_value);
		}
	}
}

ZSAPI void zsNameSpaceInsert(ZObject* hash, const char* name, ZObject* value)
{
	MyHashInsert((MYHASH*)hash->m_value, name, (char*)value);
}

ZSAPI ZObject* zsNameSpaceLookUp(ZObject* hash, const char* name)
{
	return (ZObject*)MyHashLookUp((MYHASH*)hash->m_value, name);
}

