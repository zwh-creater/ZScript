#include "../../include/proc.h"

ZSAPI ZProc* zsCreateProc(ZObject* func)
{
    ZS_CREATE(z, ZProc);
    zbas_uint top = ((zbas_array*)func->m_value)->m_top;
    zbas_uint instruction = 0;
    if (z != NULL) {
        z->m_vars = zsCreateArray(32);
        int i;
        for (i = 0; i < top; i++) {
            if (instruction == 'v') {
                  zsAppendVar(z, zsCreateNumber(0.0f));
                  instruction = 0;
            }
            instruction = zsGetChar(func->m_value,i);
        }
        z->m_pointer = 0;
    }
    return z;
}

ZSAPI void zsAppendVar(ZProc* proc, ZObject* p)
{
    zsArrayPush(proc->m_vars, p);
}

ZSAPI void zsDeleteProc(ZProc* proc) 
{
    zbas_array* a=(zbas_array*)proc->m_vars;
    for (zbas_uint i = a->m_top; i > 0; i--) {
        zsDeleteObject(zsArrayPop(a));
    }
    zsDeleteArray(a);
}

ZSAPI ZObject* zsGetVar(ZProc* proc, zbas_uint n)
{
    return zsGetAt(proc->m_vars,n);
}
