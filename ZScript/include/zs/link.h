#ifndef __LINK_H
#define __LINK_H
#include "zobject.h"
typedef struct
{
	char b_is_positive;
	ZObject* obj[2];
}ZPort;
typedef struct
{
	zbas_ptr arr_in_ports;
	zbas_ptr obj_my_value;
	zbas_ptr arr_out_ports;
	zbas_uint chrs_type;
}ZBlock;

typedef struct
{
	zbas_ptr arr_in_ports;
	zbas_ptr arr_out_ports;
}ZLink;

#endif // !__LINK_H
