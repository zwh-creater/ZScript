#ifndef  __FUNC_H
#define  __FUNC_H
#include "def.h"
#include "zbas.h"
#include "zobject.h"

ZSAPI ZObject* zsCreateFunc();
ZSAPI void zsWriteFunc(ZObject* func,zbas_ptr v);

///
/// 'var':
/// 'call':function pointer
/// 'add':number1,number2,number3
/// 'sub':number1,number2,number3
/// 'str':str1,str2
/// 'ret':return value
/// 
/// 
/// 
/// 
/// 
/// 
/// 

#endif // NOT  __FUNC_H
