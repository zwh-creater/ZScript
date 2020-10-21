#include "../../include/zs/myhash.h"

MYHASH* MyHashCreate(MYHASHPOSITIONTYPE size)
{
	MYHASH* mh;
	mh = (MYHASH*)malloc(sizeof(MYHASH));
	mh->data = (char**)malloc(size * sizeof(char*));
	mh->size = size;
	memset(mh->data, 0, size * sizeof(char*));
	return mh;
}

void MyHashDelete(MYHASH* mh)
{
	for (MYHASHPOSITIONTYPE pos = 0; pos < mh->size; pos++)
	{
		if (mh->data[pos] != 0)
		{
			free(((MYHASHELEMENT*)mh->data[pos])->name);
			free(mh->data[pos]);
		}
	}
	free(mh->data);
	free(mh);
}

MYHASHPOSITIONTYPE MyHashGetKey(const char* str)
{
	MYHASHPOSITIONTYPE nstrsize = strlen(str);
	MYHASHPOSITIONTYPE nresult = 0;
	for (MYHASHPOSITIONTYPE pos = 0; pos < nstrsize; pos++)
	{
		nresult += str[pos] << (pos % 4) * 8;
	}
	return nresult;
}

char MyHashInsert(MYHASH* mh, const char* name, char* value)
{
	MYHASHELEMENT* ele = 0;
	for (MYHASHPOSITIONTYPE pos = 0; pos < mh->size; pos++)
	{
		ele = (MYHASHELEMENT*)mh->data[(pos + MyHashGetKey(name)) % mh->size];
		if (ele == 0)
		{
			ele = (MYHASHELEMENT*)malloc(sizeof(MYHASHELEMENT));
			mh->data[(pos + MyHashGetKey(name)) % mh->size] = (char*)ele;
			ele->name = (char*)malloc(strlen(name) + 1);
			for (int i = 0; i <= strlen(name); i++)
			{
				ele->name[i] = name[i];
			}
			ele->pvalue = value;
			return 1;
		}
	}
	return 0;
}

char* MyHashLookUp(MYHASH* mh, const char* name)
{
	MYHASHELEMENT* ele = 0;
	for (MYHASHPOSITIONTYPE pos = 0; pos < mh->size; pos++)
	{
		ele = (MYHASHELEMENT*)mh->data[(pos + MyHashGetKey(name)) % mh->size];
		if (ele != 0)
		{
			if (strcmp(ele->name, name) == 0)
			{
				return ele->pvalue;
			}
		}
	}
	return 0;
}
