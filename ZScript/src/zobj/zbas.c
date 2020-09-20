#include "../../include/zbas.h"

ZSAPI zbas_lpstr zsCreateString(zbas_uint n)
{
	ZS_CREATE(str, zbas_string);
	if (str != NULL) {
		str->m_data = (zbas_ptr)malloc(n);
		if (str->m_data == NULL) {
			free(str);
			return NULL;
		}
		str->m_size = n;
		str->m_top = 0;
	}
	return str;
}

ZSAPI void zsDeleteString(zbas_ptr p)
{
	if (p != NULL) {
		free(((zbas_lpstr)p)->m_data);
		((zbas_lpstr)p)->m_size = 0;
		((zbas_lpstr)p)->m_top = 0;
		free(p);
	}
}

ZSAPI void zsSetString(zbas_ptr p, const char* src, zbas_uint n)
{
	if (p != NULL) {
		for (zbas_uint i = 0; i < n; i++) {
			((zbas_lpstr)p)->m_data[i] = src[i];
		}
		((zbas_lpstr)p)->m_top = n;
	}
}

ZSAPI zbas_bool zsCompare(zbas_lpstr str1, zbas_lpstr str2)
{
	zbas_uint i;
	if (str1->m_top != str2->m_top)
		return 0;
	for (i = 0; i < str1->m_top; ++i) {
		if (str1->m_data[i] != str2->m_data[i])
			return 0;
	}
	return 1;
}


ZSAPI zbas_node* zsCreateNode(zbas_ptr value)
{
	ZS_CREATE(node, zbas_node);
	if (node != NULL) {
		node->m_prev = NULL;
		node->m_next = NULL;
		node->m_value = value;
	}
	return node;
}

ZSAPI void zsDeleteNode(zbas_node* node, zbas_node** node_end)
{
	if (node == (*node_end)) {
		(*node_end) = (zbas_node*)(*node_end)->m_prev;
		(*node_end)->m_next = NULL;
		free(node);
		return;
	}
	if (node != NULL) {
		node->m_value = 0;
		if (node->m_prev != NULL) {
			((zbas_node*)node->m_prev)->m_next = node->m_next;
		}
		if (node->m_next != NULL) {
			((zbas_node*)node->m_next)->m_prev = node->m_prev;
		}
		free(node);
	}
}

ZSAPI zbas_ptr zsChainPush(zbas_ptr node, zbas_ptr value)
{
	((zbas_node*)node)->m_next = zsCreateNode(value);
	((zbas_node*)((zbas_node*)node)->m_next)->m_prev = node;
	return ((zbas_node*)node)->m_next;
}

ZSAPI zbas_ptr zsCreateArray(zbas_uint n)
{
	ZS_CREATE(arr,zbas_array);
	if (arr != NULL) {
		arr->m_data = malloc(n * sizeof(zbas_ptr));
		arr->m_size = n;
		arr->m_top = 0;
	}
	return (zbas_ptr)arr;
}

ZSAPI void zsDeleteArray(zbas_ptr p)
{
	if (p != NULL) {
		free(p);
	}
}

ZSAPI void zsArrayPush(zbas_ptr p, zbas_ptr value_p)
{
	if (((zbas_array*)p)->m_top < ((zbas_array*)p)->m_size) {
		zsSetAt(p, ((zbas_array*)p)->m_top, value_p);
		++((zbas_array*)p)->m_top;
	}
}

ZSAPI zbas_ptr zsArrayPop(zbas_ptr p)
{
	if (((zbas_array*)p)->m_top > 0) {
		--((zbas_array*)p)->m_top;
	}
	return zsGetAt(p, ((zbas_array*)p)->m_top);
}

ZSAPI zbas_ptr zsGetAt(zbas_ptr p, zbas_uint n)
{
	return *(zbas_ptr*)(((zbas_array*)p)->m_data+n*sizeof(zbas_ptr));
}

ZSAPI void zsSetAt(zbas_ptr p, zbas_uint n, zbas_ptr v)
{
	*(zbas_ptr*)(((zbas_array*)p)->m_data + n * sizeof(zbas_ptr)) = v;
}
