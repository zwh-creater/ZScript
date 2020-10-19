#ifndef __ZOBJECT_H
#define __ZOBJECT_H

#include "def.h"
#include "zbas.h"
#include "error.h"

/// 
/// type code:
/// 'cls'		Class Type
/// 'func'		Funtion Type
/// 'arr'		Array Type
/// 'hash'		Hash Type
/// 'dict'		Dictionary Type
/// 'num'		Number Type
/// 'int'		Integer Type
/// 'user'		User Type
/// 'xxxx'		Other Type
/// 

typedef struct
{
	zbas_uint  m_typecode;
	zbas_ptr  m_value;
	//zbas_uint m_count;
}ZObject;

typedef struct
{
	zbas_ptr m_name;
	zbas_ptr m_object;
}ZLabel;

ZSAPI ZObject* zsCreateObject(zbas_ptr typecode);
ZSAPI void zsDeleteObject(ZObject* z);

ZSAPI void zsChangeObject(ZObject** object, ZObject* n_object);

//ZSAPI void zsSetLabel(ZLabel* a,ZObject* b);

ZSAPI ZObject* zsCreateNumber(double number);
ZSAPI double zsGetNumber(ZObject* z);
ZSAPI void zsSetNumber(ZObject* z,double number);
ZSAPI void zsCopyNumber(ZObject* dst,ZObject* src);
ZSAPI void zsAddNumbers(ZObject* z,ZObject* a, ZObject* b);
ZSAPI void zsSubNumbers(ZObject* z, ZObject* a, ZObject* b);
ZSAPI void zsMulNumbers(ZObject* z, ZObject* a, ZObject* b);
ZSAPI void zsDivNumbers(ZObject* z, ZObject* a, ZObject* b);
//ZSAPI ZObject* zsSubNumbers(ZObject* a, ZObject* b);
//ZSAPI ZObject* zsMulNumbers(ZObject* a, ZObject* b);
//ZSAPI ZObject* zsDivNumbers(ZObject* a, ZObject* b);
//ZSAPI ZObject* zsExpNumber(ZObject* a);

ZSAPI ZObject* zsCreateStringObject(const char* str);

ZSAPI ZObject* zsCreatePointer(ZObject* object);

#endif