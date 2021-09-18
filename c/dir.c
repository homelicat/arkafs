#include "../h/dtypes.h"
#include "../h/dio.h"
#include "../h/st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//считывает файловую структуру
fstruct dirread(dstruct d,int ptr)
{
	fstruct f;
	dread(d,ptr,&f,16);
	return f;
}

//записывает файловую структуру
void dirwrite(dstruct d,fstruct f,int ptr)
{
	dwrite(d,ptr,&f,16);
}

//ищет пустую ячейку в директории, 0 если нет
int dirfree(dstruct d,int ptr)
{
	fstruct dir = dirread(d,ptr);
	word * table = stfile(d,dir);
	for (int i = 0; i<dir.size/512+1;i++)
	{
		for(int j = 0;j<512;j+=16)
		{
			fstruct f = dirread(d,table[i]*512+j);
			if(f.name[0]==0)
			{
				int result = table[i]*512+j;
				free(table);
				return result;
			}
		}
	}
	word s = stfree(d);
	if(s==0)
	{
		free(table);
		return 0;
	}
	stwrite(d,table[dir.size/512],s);
	stwrite(d,s,s);
	dir.size+=512;
	dirwrite(d,dir,ptr);
	return s*512;
}

//ищет ячейку по имени в директории, 0 если нет
int dirsearch(dstruct d,int ptr,char * name)
{
	fstruct dir = dirread(d,ptr);
	char s[12]={0};
	memcpy(s,name,strlen(name));
	word * table = stfile(d,dir);
	byte sects = (dir.size/512)+1;
	for(int i = 0; i<sects;i++)
	{
		for(int j = 0;j<512;j+=16)
		{
			fstruct f = dirread(d,table[i]*512+j);
			if(!memcmp(&f,s,12))
			{
				int result = table[i]*512+j;
				free(table);
				return result;
			}
		}
	}
	free(table);
	return 0;
}
