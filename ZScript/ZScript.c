
#include <stdio.h>
#include "include/zobject.h"
#include "include/proc.h"
#include "ZScript.h"
#include <math.h>

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
	for (zbas_uint i = s; i < n; i++)
	{
		printf(" %c", text[i]);
		switch (state)
		{
		case 'head':
			if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= '0' && text[i] <= '9')||text[i]=='.'||text[i]=='$')
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
				return i-1;
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
			if (text[i] == ',')
			{
				i++;
			}
			i = zsComplie(func, text, i,n);
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

void add(ZProc* proc)
{
	zsAddNumbers(zsGetVarBack(proc, 2), zsGetVarBack(proc, 2), zsGetVarBack(proc, 1));
}
void sub(ZProc* proc)
{
	zsSubNumbers(zsGetVarBack(proc, 2), zsGetVarBack(proc, 2), zsGetVarBack(proc, 1));
}
void mul(ZProc* proc)
{
	zsMulNumbers(zsGetVarBack(proc, 2), zsGetVarBack(proc, 2), zsGetVarBack(proc, 1));
}
void _div(ZProc* proc)
{
	zsDivNumbers(zsGetVarBack(proc, 2), zsGetVarBack(proc, 2), zsGetVarBack(proc, 1));
}

void sqrt_tmp(ZProc* proc) {
	ZObject* z=zsGetVarBack(proc, 1);
	*(double*)z->m_value = sqrt(*(double*)z->m_value);
}

typedef struct {
	zbas_ptr m_start;
	zbas_ptr m_end;
}MainApp;

MainApp g_App;

void GlobalAppend(const char* name,ZObject* value)
{
	ZS_CREATE(lb, ZLabel);
	lb->m_name = malloc(strlen(name));
	strcpy(lb->m_name, name);
	lb->m_object = value;
	g_App.m_end = zsChainPush(g_App.m_end, lb);
}

ZObject* GlobalFind(const char* name)
{
	ZS_BEGIN_ITER(iter,g_App.m_start)
		if (iter->m_value != NULL)
		{
			if (0==strcmp(((ZLabel*)iter->m_value)->m_name, name))
			{
				return ((ZLabel*)iter->m_value)->m_object;
			}
		}
	ZS_END_ITER(iter)
	return NULL;
}

void ShowList()
{
	ZS_BEGIN_ITER(iter, g_App.m_start)
		if (iter->m_value != NULL)
		{
			printf(((ZLabel*)iter->m_value)->m_name);
			printf("=");
			printf("%lf\n", *(double*)((ZObject*)((ZLabel*)iter->m_value)->m_object)->m_value);
		}
	ZS_END_ITER(iter)
}

int exec(ZProc* proc)
{
	ZObject* func = proc->m_func;
	zbas_byte c;
	int state='out';
	char save[32];
	int sv_count = 0;
	printf("\n================RUNTIME====================\n");
	ZCFunctionStruct funcstr[20];
	funcstr[0].func = add;
	funcstr[0].argn = 2;
	funcstr[1].func = sub;
	funcstr[1].argn = 2;
	funcstr[2].func = mul;
	funcstr[2].argn = 2;
	funcstr[3].func = _div;
	funcstr[3].argn = 2;
	funcstr[4].func = sqrt_tmp;
	funcstr[4].argn = 1;
	for (zbas_uint i = 0; i < 256; i++)
	{
		c = ((zbas_lpstr)func->m_value)->m_data[i];
		if (c == 0) {
			printf("\n================END====================\n");
			return 0;
		}
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
			else {
				if (GlobalFind(save) != NULL)
					zsAppendVar(proc,zsCreateNumber(*(double*)GlobalFind(save)->m_value));
				else
					GlobalAppend(save, zsCreateNumber(*(double*)zsPopVar(proc)->m_value));

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
			
			if (strcmp(save, "put") == 0) {
				printf("\n**********高**级**输**出*************************\nNumber = %f\n*************************************************\n",*(double*)zsGetVarBack(proc, 1)->m_value);
				zsDeleteObject(zsPopVar(proc));
			}
			else if (strcmp(save, "get") == 0) {
				printf("高级输入:");
				double flt;
				while (1 != scanf("%lf", &flt))
				{
					printf("错了，你要输入小数才对。\n");
				}
				zsAppendVar(proc, zsCreateNumber(flt));
			}
			else if (strcmp(save, "add") == 0) {
				CallCFunction(proc, &funcstr[0]);
			}
			else if (strcmp(save, "sub") == 0) {
				CallCFunction(proc, &funcstr[1]);
			}
			else if (strcmp(save, "mul") == 0) {
				CallCFunction(proc, &funcstr[2]);
			}
			else if (strcmp(save, "div") == 0) {
				CallCFunction(proc, &funcstr[3]);
			}
			else if (strcmp(save, "sqrt") == 0) {
				CallCFunction(proc, &funcstr[4]);
			}
			sv_count = 0;
			state = 'out';
			break;
		}
	}
	return 0;
}

void LoadFile(ZObject* func,const char* filename)
{
	FILE* file=fopen(filename,"r");
	if (file == NULL)
		return;
	char text[256];
	while (!feof(file))
	{
		if(1==fscanf(file, "%s", text))
			zsComplie(func, text, 0, strlen(text));
	}
	zsWriteFunc(func, "$", 2);
}

int main(int argn,char** args)
{
	char  filename[128];
	if (argn > 1) {
		strcpy(filename, args[1]);
		printf(args[1]);
		printf("\n");
	}
	else {
		strcpy(filename, "test.zs");
	}

	g_App.m_start = zsCreateNode(0);
	g_App.m_end = g_App.m_start;

	ZObject* func = zsCreateFunc();
	LoadFile(func,filename);
	ZProc* proc = zsCreateProc(func);
	printf(((zbas_lpstr)func->m_value)->m_data);

	exec(proc);
	
	zsDeleteProc(proc);
	zsDeleteObject(func);

	getchar();

	return 0;
}