// ZScript.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>

#include "include/zobject.h"

int main(int argn, char** args)
{
	int n;
	zbas_lpstr p = zsCreateString(1024);
	zbas_lpstr p2 = zsCreateString(256);
	zbas_lpstr p3 = zsCreateString(256);
	zsSetString(p, "abc", 4);
	zsSetString(p2, "abc", 4);
	zsSetString(p3, "acb", 4);
	printf("%s\n", ((zbas_lpstr)p)->m_data);
	printf("%d\n", zsCompare(p, p2));
	printf("%d\n", zsCompare(p, p3));

	zbas_node* start;
	zbas_node* end;
	start = zsCreateNode(zsCreateString(256));
	zsSetString(start->m_value, "START", 6);

	printf("???%s???", ((zbas_lpstr)start->m_value)->m_data);
	end = start;
	end=zsChainPush(end, zsCreateString(256));
	zsSetString(end->m_value, "FAN PEI LIN", 12);

	end=zsChainPush(end, zsCreateString(256));
	zsSetString(end->m_value, "HE XI BO", 9);

	end=zsChainPush(end, zsCreateString(256));
	zsSetString(end->m_value, "ZHANG WEN HAN", 14);

	end=zsChainPush(end, zsCreateString(256));
	zsSetString(end->m_value, "CHEN JUN LIN", 13);

	ZS_BEGIN_ITER(i, start)
		ZS_NOT_NULL(i->m_value)
			printf("\n%s\n", ((zbas_lpstr)i->m_value)->m_data);
		else
			printf("\n[ERROR]\n");
	ZS_END_ITER(i)

	char str[256];
	int j;
	char c=0;

	while (1) {
		if ((c=getch()) == 'i') {
			j = 0;
			c = 0;
			printf("\n---INSERT---\n");
			while (c!='/')
			{
				printf("%c", c);
				if ((c = getch()) != '/') {
					str[j] = c;
					if (c == '\b') {
						j--;
					}
					j++;
				}
				else {
					str[j] = 0;
					end = zsChainPush(end, zsCreateString(256));
					zsSetString(end->m_value,str, j+1);
				}
			}
			ZS_BEGIN_ITER(i, start)
				ZS_NOT_NULL(i->m_value)
				printf("\n%s\n", ((zbas_lpstr)i->m_value)->m_data);
			else
				printf("\n[ERROR]\n");
			ZS_END_ITER(i)
			
		}
		else if(c=='x') {
			j = 0;
			while (c != '/')
			{
				printf("%c", c);
				if ((c = getch()) != '/') {
					str[j] = c;
					if (c == '\b') {
						j--;
					}
					j++;
				}
				else {
					str[j] = 0;
					zbas_lpstr z = zsCreateString(j);
					zsSetString(z, str, j+1);
					ZS_BEGIN_ITER(i,start)
						ZS_NOT_NULL(i->m_value) {
							if (zsCompare(i->m_value, z)) {
								zsDeleteNode(i,&end);
								i = NULL;
								printf("\nDelete: %s\n", str);
							}
						}
					if(i!=NULL)
					ZS_END_ITER(i)
				}
			}
		}
		else {
			if (end!= start) {
				if (end != NULL) {
					if (end->m_value != 0) {
						printf("\nDelete:%s\n", ((zbas_lpstr)end->m_value)->m_data);
						if (end->m_value != NULL)
							zsDeleteString(end->m_value);
					}
					end = end->m_prev;
					zsDeleteNode(end->m_next,&end);
				}
			}
		}
	}

	zsDeleteString(p);
	return 0;
}