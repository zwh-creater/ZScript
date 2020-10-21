#include "include/zs/ZScript.h"
#include <stdio.h>
int main()
{
	MYHASH* hash=MyHashCreate(256);
	MyHashInsert(hash, "haha", "1111");
	MyHashInsert(hash, "fan", "11gavfdsg");
	MyHashInsert(hash, "sa", "11fdg");
	MyHashInsert(hash, "ha", "11egt4t3");
	MyHashInsert(hash, "no", "4353453411");
	printf("%s\n",MyHashLookUp(hash, "fan"));
	MyHashDelete(hash);
}