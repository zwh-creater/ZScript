#include "..\..\include\func.h"

ZSAPI zbas_ptr zsCreateFunc()
{
	return zsCreateArray(512);
}

ZSAPI void zsPushCommand(zbas_ptr func,zsline l)
{
	zsArrayPush(func, l.m_type);
	zsArrayPush(func, l.m_arg);
}
