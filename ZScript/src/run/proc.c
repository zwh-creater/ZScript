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
        z->m_func = func;
        z->m_pointer = 0;
        z->m_labels_start = zsCreateNode(0);
        z->m_labels_end = z->m_labels_start;
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
    zbas_node old_node;
    ZS_BEGIN_ITER(iter,proc->m_labels_start)
        if (NULL != iter->m_value)
        {
            zsDeleteString(iter->m_value);
            old_node.m_next = iter->m_next;
            zsDeleteNode(iter, &proc->m_labels_end);
            iter = &old_node;
        }
    ZS_END_ITER(iter)
}

ZSAPI ZObject* zsGetVar(ZProc* proc, zbas_uint n)
{
    return zsGetAt(proc->m_vars,n);
}

ZSAPI ZObject* zsGetVarBack(ZProc* proc, zbas_uint n)
{
    return zsGetAt(proc->m_vars, ((zbas_array*)proc->m_vars)->m_top-n);
}

ZSAPI void zsResetVarTop(ZProc* proc, zbas_uint n,ZObject* z)
{
    ((zbas_array*)proc->m_vars)->m_top -= n;
    zsAppendVar(proc, z);
}