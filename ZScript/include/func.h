#ifndef  __FUNC_H
#define  __FUNC_H
#include "def.h"
#include "zbas.h"

typedef struct {
	zbas_ptr m_type;
	//	1:copy memory
	//	2:parse expression
	//	3:
	//
	//
	//
	//
	//
	//
	zbas_ptr m_arg;
}zsline;

ZSAPI zbas_ptr zsCreateFunc();
ZSAPI void zsPushCommand(zbas_ptr func,zsline l);

#endif // ! __FUNC_H
