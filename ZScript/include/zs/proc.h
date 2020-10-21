#ifndef __PROC_H
#define __PROC_H

#include <string.h>

#include "zbas.h"
#include "zobject.h"
#include "func.h"

typedef struct {
	zbas_ptr m_labels_start;
	zbas_ptr m_labels_end;
	zbas_ptr m_vars;
	zbas_uint m_pointer;
	ZObject* m_func;
}ZProc;

ZSAPI ZProc* zsCreateProc(ZObject* func);
ZSAPI void zsAppendVar(ZProc* proc,ZObject* p);
ZSAPI void zsDeleteProc(ZProc* proc);
ZSAPI ZObject* zsGetVar(ZProc* proc,zbas_uint n);

ZSAPI ZObject* zsGetVarBack(ZProc* proc, zbas_uint n);

ZSAPI void zsResetVarTop(ZProc* proc, zbas_uint n, ZObject* z);

ZSAPI ZObject* zsPopVar(ZProc* proc);

typedef void (*ZCFunction)(ZObject**);

typedef struct {
	ZCFunction func;
	zbas_uint argn;
}ZCFunctionStruct;

void CallCFunction(ZProc* proc, ZCFunctionStruct* funcstr);

#endif