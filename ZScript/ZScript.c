
#include <stdio.h>
#include "include/zobject.h"
#include "include/proc.h"
#include "ZScript.h"

typedef struct {
	ZObject* m_return_value;
}ZVirtualRegister;

int Run() {
	zbas_ptr g_CurrentProc = zsCreateArray(256);
	ZVirtualRegister reg;
	reg.m_return_value = NULL;

	//加载函数
	double v;
	ZObject* func = zsCreateFunc();
	zsWriteFunc(func, "vnvnvnvn", 8);
	zsWriteFunc(func, "sn\1\0\0\0", 6);v =1.0;zsWriteFunc(func, &v, sizeof(double));
	zsWriteFunc(func, "sn\2\0\0\0", 6);v =2.0;zsWriteFunc(func, &v, sizeof(double));
	zsWriteFunc(func, "an\1\0\0\0\2\0\0\0", 10);
	zsWriteFunc(func, "ccccrn\0\0\0\0xxxxxxxxxxxr", 8);
	ZObject* func2 = zsCreateFunc();
	zsWriteFunc(func2, "vnvn", 4);
	zsWriteFunc(func2, "sn\0\0\0\0", 6); v = 10.0; zsWriteFunc(func2, &v, sizeof(double));
	zsWriteFunc(func2, "sn\1\0\0\0", 6); v = 20.0; zsWriteFunc(func2, &v, sizeof(double));
	zsWriteFunc(func2, "xxrn\0\0\0\0",8);

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
			p = ((zbas_lpstr)proc->m_func->m_value)->m_data + proc->m_pointer;
			zsSetNumber(ZS_FIND_VAR(proc,p+2),*(double*)(p+6));
			proc->m_pointer += 5 + sizeof(double);
			break;
		case 'a':
			printf("exec ADD\n");
			p = ((zbas_lpstr)proc->m_func->m_value)->m_data + proc->m_pointer;
			zsAddNumbers(ZS_FIND_VAR(proc, p + 2), ZS_FIND_VAR(proc, p + 2), ZS_FIND_VAR(proc, p + 6));
			proc->m_pointer += 9;
			break;
		case 'c':
			printf("CREATEPROC\n");
			proc = zsCreateProc(func2);
			zsArrayPush(g_CurrentProc,proc);
			flag = 1;
			break;
		case 'r':
			printf("RETURN ");
			p = ((zbas_lpstr)proc->m_func->m_value)->m_data + proc->m_pointer;
			zsDeleteProc(proc);
			if (proc == _root) {
				proc = NULL;
				return 1;
			}
			printf("\n");
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

typedef struct{
	zbas_lpstr name;
	zbas_ptr   value;
}zbas_entry;

zbas_uint zsFindEnd(zbas_ptr text,zbas_uint start)
{
	int n = strlen(text);
	int layer = 0;
	char started = 0;
	if (n == 0)
	{
		return 0;
	}
	for (int i = start; i < n;i++)
	{
		if (started)
		{
			if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9'))
			{

			}
			else if (text[i] == '(') {
				++layer;
			}
			else if (text[i] == ')') {
				if (layer == 0)
					return i;
				--layer;
			}
			else {
				if (layer == 0)
					return i;
			}
		}else if (((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9')) || text[i] == '(')
		{
			started = 1;
		}
	}
	return n-1;
}

//void zsExpression(zbas_ptr func, zbas_ptr text,zbas_uint n)
//{

//}

zbas_uint zsComplie(zbas_ptr func, zbas_ptr text,zbas_uint s,zbas_uint n)
{
	int state = 'head';
	int readTextCount = 0;
	//zbas_node* label = zsCreateNode(0);
	zbas_entry entry;
	char str[32];
	char right[256];
	int strcount=0;
	printf(" begin ");
	for (int i = s; i < n; i++)
	{
		printf(" %c", text[i]);
		switch (state)
		{
		case 'head':
			if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9')||text[i]=='.')
			{
				str[strcount++] = text[i];
			}
			else {
				str[strcount++] = 0;
				state = 'oper';
				--i;
				printf("\b");
			}
			break;
		case 'oper':
			switch (text[i])
			{
			case '(':
				state = 'inbk';
				break;
			case ',':case ')':
				zsWriteFunc(func, "[o=", 3);
				zsWriteFunc(func, str, strlen(str));
				zsWriteFunc(func, "]", 1);
				return i;
			default:
				break;
			}
			break;
		case 'inbk':
			if (text[i] == ')')
			{
				zsWriteFunc(func, "[f=", 3);
				zsWriteFunc(func, str, strlen(str));
				zsWriteFunc(func, "]", 1);
				return i;
			}
			i = zsComplie(func, text, i,n);
			if (text[i] == ')')
			{
				zsWriteFunc(func, "[f=", 3);
				zsWriteFunc(func, str, strlen(str));
				zsWriteFunc(func, "]", 1);
				return i;
			}
			break;
		}
	}
	return n;
}

double zsAtof(const char* str,int sv_count)
{
	double sv_number = 0.0;
	char after_dot=0;
	int w = 0;
	for (int i = 0; i < sv_count; i++)
	{
		if (str[i] == '.') {
			after_dot = 1;
		}
		else if (str[i]<'0'||str[i]>'9')
		{
			return sv_number;
		}
		else if (after_dot) {
			sv_number = sv_number + (str[i] - '0') * 1.0 / (10 ^ (w++));
		}
		else {
			sv_number = sv_number * 10 + (str[i] - '0') * 1.0;
		}
	}
	return sv_number;
}


int exec(ZProc* proc)
{
	ZObject* func = proc->m_func;
	zbas_byte c;
	int state='out';
	char save[32];
	int sv_count = 0;
	for (zbas_uint i = 0; i < 256; i++)
	{
		c = ((zbas_lpstr)func->m_value)->m_data[i];
		if (c == '$')
			return 0;
		switch (state)
		{
		case 'out':
			if (c == '[')
				state = 'in';
			break;
		case 'in':
			if (c == 'o') {
				state = 'obj0';
			}
			else if (c == 'f') {
				state = 'fun0';
			}
			break;
		case 'obj0':
			if (c == '=') {
				state = 'obj';
			}
			break;
		case 'obj':
			if (c == ']') {
				save[sv_count++] = 0;
				state = 'end';
				--i;
			}
			else {
				save[sv_count++] = c;
			}
			break;
		case 'end':
			if (save[0] == '0')
			{
				zsAppendVar(proc, zsCreateNumber(zsAtof(save, sv_count)));
			}
			sv_count = 0;
			state = 'out';
			break;
		case 'fun0':
			if (c == '=') {
				state = 'fun';
			}
			break;
		case 'fun':
			if (c == ']') {
				save[sv_count++] = 0;
				state = 'endf';
				--i;
			}
			else {
				save[sv_count++] = c;
			}
			break;
		case 'endf':
			if (strcmp(save, "add")==0)
			{
				zsAddNumbers(zsGetVarBack(proc,1),zsGetVarBack(proc, 1), zsGetVarBack(proc, 2));
				zsResetVarTop(proc, 2, zsGetVarBack(proc, 1));
			}
			sv_count = 0;
			state = 'out';
			break;
		}
	}
}

int main()
{
	char* text = "add(01223.5,07765)";

	ZObject* func = zsCreateFunc();
	zsComplie(func, text, 0,strlen(text));
	zsWriteFunc(func, "$", 1);

	ZProc* proc = zsCreateProc(func);
	exec(proc);
	printf(((zbas_lpstr)func->m_value)->m_data);
	zsDeleteProc(proc);
	zsDeleteObject(func);

	return 0;
}