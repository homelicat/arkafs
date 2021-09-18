#include "../h/types.h"
#include "../h/dio.h"
#include "../h/st.h"
//#include "../h/dir.h"
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
int dirfree(dstruct d,fstruct dir)
{
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
	free(table);
	return 0;
}

//ищет ячейку по имени в директории, 0 если нет
int dirsearch(dstruct d,fstruct dir,char * name)
{
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

//увеличивает файл, 0 если нет места, или новый сектор
word dirinc(dstruct d,int ptr)
{
	word s = stfree(d);
	if(s==0) return 0;
	fstruct f = dirread(d,ptr);
	if(f.size==0)
	{
		f.ptr = s;
	} else
	{
		word * table = stfile(d,f);
		stwrite(d,table[f.size/512],s);
		free(table);
	}
	f.size += 512-(f.size%512);
	stwrite(d,s,s);
	dirwrite(d,f,ptr);
	return s;
}

//уменьшает файл, 0 если файл пуст
word dirdec(dstruct d, int ptr)
{
	fstruct f = dirread(d,ptr);
	if(f.size==0) return 0;
	word * table = stfile(d,f);
	stwrite(d,table[f.size/512],0);
	if(f.size/512==0)f.ptr=0;
	if(f.size/512>0)stwrite(d,table[f.size/512-1],table[f.size/512-1]);
	f.size -= f.size%512;
	free(table);
	dirwrite(d,f,ptr);
}
