
#include <stdio.h>
#include "include/zobject.h"
#include "include/proc.h"

int main() {
	zbas_ptr g_CurrentProcs = zsCreateArray(256);
	zbas_array* g_CodePointers = zsCreateArray(256);
	ZObject* func = zsCreateFunc();
	zsWriteFunc(func, 'var');
	zsWriteFunc(func, 'num');
	zsWriteFunc(func, 'var');
	zsWriteFunc(func, 'num');
	zsWriteFunc(func, 'set');
	zsWriteFunc(func, 0x000);
	zsWriteFunc(func, );
	zsWriteFunc(func, 'add');
	zsWriteFunc(func, 0x000);
	zsWriteFunc(func, 0x001);
	zsWriteFunc(func, 'ret');


	ZProc* proc = zsCreateProc(func);
	zsArrayPush(g_CurrentProcs, proc);
	zsArrayPop(g_CodePointers);
	zsSetNumber(zsGetVar(proc, 0), 1.0f);
	zsSetNumber(zsGetVar(proc, 1), 2.0f);
	//GETV(proc,0) = 10.1f;
	//GETV(proc,1) = 18.1f;
	zsAddNumbers(zsGetVar(proc,0), zsGetVar(proc, 0),zsGetVar(proc,1));
	zsDeleteProc(proc);


	zsDeleteObject(func);
	return 0;
}