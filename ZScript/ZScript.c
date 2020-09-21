
#include <stdio.h>
#include "include/zobject.h"
#include "include/proc.h"

int main() {
	zbas_ptr g_CurrentProc = zsCreateArray(256);
	
	//加载函数
	ZObject* func = zsCreateFunc();
	zsWriteFunc(func, "vnvnvnvn", 8);
	zsWriteFunc(func, "sn\1\0\0\0", 6);
	
	double v = 62.5;
	zsWriteFunc(func, &v ,sizeof(double));
	zsWriteFunc(func, "sn\2\0\0\0", 6);
	v = 72.3;
	zsWriteFunc(func, &v, sizeof(double));

	zsWriteFunc(func, "an\1\0\0\0\2\0\0\0",10);

	zsWriteFunc(func, "crrrr", 5);

	//创建进程
	ZProc* _root;
	ZProc* proc = zsCreateProc(func);
	_root = proc;
	zsArrayPush(g_CurrentProc, proc);

	zbas_uint n=((zbas_lpstr)func->m_value)->m_top;

	char c;

	zbas_ptr p = 0;

	while(1) {
		c = zsGetChar(func->m_value, proc->m_pointer);
		switch (c)
		{
		case 's':
			p=((zbas_lpstr)func->m_value)->m_data+ proc->m_pointer;
			zsSetNumber(zsGetVar(proc, *(int*)(p + 2)),*(double*)(p+6));
			proc->m_pointer += 5 + sizeof(double);
			break;
		case 'a':
			p = ((zbas_lpstr)func->m_value)->m_data + proc->m_pointer;
			zsAddNumbers(zsGetVar(proc, *(int*)(p + 2)), zsGetVar(proc, *(int*)(p + 2)), zsGetVar(proc, *(int*)(p + 6)));
			proc->m_pointer += 9;
			break;
		case 'c':
			//proc = zsCreateProc(func);
			//zsArrayPush(g_CurrentProc,proc);
			break;
		case 'r':
			zsDeleteProc(proc);
			proc=zsArrayPop(g_CurrentProc);
			if (proc == _root) {
				proc = NULL;
			}
		default:
			break;
		}
		if (proc != NULL)
			++proc->m_pointer;
		else
			break;
	}
	zsDeleteObject(func);
	return 0;
}