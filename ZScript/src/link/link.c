#include "link.h"

ZSAPI ZObject* zsGetPortValue(ZPort* pt)
{
	pt->b_is_positive = !pt->b_is_positive;
	return pt->obj[pt->b_is_positive];
}

ZSAPI void zsSendSignal()
{

}

ZSAPI void zsSetBlock(ZBlock* dst,zbas_uint t,ZObject* value,zbas_uint n_in,zbas_uint n_out)
{
	dst->chrs_type = t;
	dst->arr_in_ports = zsCreateArray(n_in);
	for (int i = 0; i < n_in; i++)
	{
		((ZPort*)zsGetAt(dst->arr_in_ports, i))->obj[0] = zsCreateNumber(0.0);
		((ZPort*)zsGetAt(dst->arr_in_ports, i))->obj[1] = zsCreateNumber(0.0);
	}
	dst->obj_my_value = value;
	dst->arr_out_ports = zsCreateArray(n_out);
	for (int i = 0; i < n_out; i++)
	{
		((ZPort*)zsGetAt(dst->arr_out_ports, i))->obj[0] = zsCreateNumber(0.0);
		((ZPort*)zsGetAt(dst->arr_out_ports, i))->obj[1] = zsCreateNumber(0.0);
	}
}

ZSAPI void zsSetLink(ZLink* dst, ZPort* port_in, ZPort* port_out)
{

}

ZSAPI void zsBlockUpdate(ZBlock* blk)
{
	ZObject* tmp;
	switch (blk->chrs_type)
	{
	case 'num':
		
		break;
	}
}