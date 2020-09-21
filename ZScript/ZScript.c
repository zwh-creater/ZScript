
#include <stdio.h>
#include "include/zobject.h"
#include "include/proc.h"
#include "ZScript.h"

int main() {
	zbas_ptr g_CurrentProc = zsCreateArray(256);

	//加载函数
	double v;
	ZObject* func = zsCreateFunc();
	zsWriteFunc(func, "vnvnvnvn", 8);
	zsWriteFunc(func, "sn\1\0\0\0", 6);v = 62.5;zsWriteFunc(func, &v, sizeof(double));
	zsWriteFunc(func, "sn\2\0\0\0", 6);v = 72.3;zsWriteFunc(func, &v, sizeof(double));
	zsWriteFunc(func, "an\1\0\0\0\2\0\0\0", 10);
	zsWriteFunc(func, "cccxxxrxxxxxxxxxxxr", 6);
	ZObject* func2 = zsCreateFunc();
	zsWriteFunc(func2, "vn", 2);
	//zsWriteFunc(func2, "sn\0\0\0\0", 6); v = 1.0; zsWriteFunc(func, &v, sizeof(double));
	//zsWriteFunc(func2, "sn\1\0\0\0", 6); v = 2.0; zsWriteFunc(func, &v, sizeof(double));
	zsWriteFunc(func2, "xxr",3);

	//创建进程
	ZProc* _root;
	ZProc* proc = zsCreateProc(func);
	_root = proc;
	zsArrayPush(g_CurrentProc, proc);
	char c;

	zbas_ptr p = 0;
	zbas_bool flag = 0;
	while (1) {
		c = zsGetChar(proc->m_func->m_value, proc->m_pointer);
		switch (c)
		{
		case 'x':
			printf("CHECK\n");
			break;
		case 's':
			printf("exec SET\n");
			p = ((zbas_lpstr)func->m_value)->m_data + proc->m_pointer;
			zsSetNumber(ZS_FIND_VAR(proc,p+2),*(double*)(p+6));
			proc->m_pointer += 5 + sizeof(double);
			break;
		case 'a':
			printf("exec ADD\n");
			p = ((zbas_lpstr)func->m_value)->m_data + proc->m_pointer;
			zsAddNumbers(ZS_FIND_VAR(proc, p + 2), ZS_FIND_VAR(proc, p + 6), ZS_FIND_VAR(proc, p + 6));
			proc->m_pointer += 9;
			break;
		case 'c':
			printf("CREATEPROC\n");
			proc = zsCreateProc(func2);
			zsArrayPush(g_CurrentProc,proc);
			flag = 1;
			break;
		case 'r':
			printf("RETURN");
			zsDeleteProc(proc);
			if (proc == _root) {
				proc = NULL;
				return 1;
			}
			zsArrayPop(g_CurrentProc);
			proc = zsArrayPop(g_CurrentProc);
			zsArrayPush(g_CurrentProc, proc);
		default:
			break;
		}
		if (proc != NULL)
			++proc->m_pointer;
		else
			break;
		if (flag) {
			flag = 0;
			proc->m_pointer = 0;
		}
	}
	zsDeleteObject(func);
	return 0;
}
