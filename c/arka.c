#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../h/types.h"
#include "../h/dio.h"
#include "../h/st.h"
#include "../h/dir.h"
#include "../h/debug.h"
#include "../h/arka.h"

//создает диск
void arkanew(char * name,int size)
{
	dcreate(name,size);
}

//монтирует диск
arka arkamount(char * name)
{
	arka result;
	result.d = dopen(name);
	result.cur = (result.d.sts+1)*512;
	return result;
}

//отмонтирует диск
void arkaumount(arka a)
{
	dclose(a.d);
}

//выводит содержимое директории
void arkalist(arka a)
{
	int ptr = a.cur;
	fstruct dir = dirread(d,ptr);
	word * table = stfile(d,dir);
	for (int i = 0; i<dir.size/512+1;i++)
	{
		for(int j = 0;j<512;j+=16)
		{
			fstruct f = dirread(d,table[i]*512+j);
			if(f.name[0]==0) continue;
			for(int k = 0; k<12;k++)
			{
				if(f.name[k]==0)
				{
					putchar(' ');
				} else
				{
					putchar(f.name[k]);
				}
			}
			printf(" %X %X\n",f.ptr,f.size);
		}
	}
	free(table);
}

//переходит в директорию, 0 если не существует
int arkacd(arka a, char * name)
{
	fstruct dir = dirread(a.d,a.cur);
	int ptr = dirsearch(a.d,dir,name);
	if(ptr==)return 0;
	a.cur=ptr;
	return 1;
}

//TODO пишет в файл,0 если нет места
void arkawrite(arka a,char * name)
{
	arkadel(a,name);
	fstruct dir = dirread(a.d,a.cur);
	int fre = dirfree(a.d,dir);
	if(fre==0)return 0;
	fstruct file;
	bzero(&file,16);
	memcpy(&file.name,name,strlen(name));
	word ptr = stfree(a.d);
	if(ptr==0)return 0;
	file.ptr=ptr;
	stwrite(a.d,ptr,ptr);
	//dirwrite(a.d,file,fre);
	char c;
	word cursect = ptr;
	while((c=getchar())!=EOF)
	{
		int infileptr=cursect*512+(file.size%512);
		dwrite(a.d,infileptr,&c,1);
		file.size++;
		if(file.size
	}
}

//читает из файла, 0 если файл не существует
int arkaread(arka a,char * name)
{
	fstruct dir = dirread(a.d,a.cur);
	int ptr = dirsearch(a.d,dir,name);
	if(ptr==0)return 0;
	fstruct file = dirread(a.d,ptr);
	word * table = stfile(a.d,file);
	for(int i = 0;i<file.size/512+1;i++)
	{
		if(i<file.size/512)
		{
			for(int j=0;j<512;j++)
			{
				byte c;
				dread(a.d,table[i]*512+j,&c,1);
				putchar(c);
			}
		} else
		{
			for(int j = 0;j<file.size%512;j++)
			{
				byte c;
				dread(a.d,table[i]*512+j,&c,1);
				putchar(c);
			}

		}
	}
	free(table);
	return 1;
}

//удаляет файл, 0 если файл не существует
int arkadel(arka a,char * name)
{
	fstruct dir = dirread(a.d,a.cur);
	int ptr = dirsearch(a.d,dir,name);
	if(ptr==0)return 0;
	fstruct file = dirread(a.d,ptr);
	word * table = stfile(a.d,file);
	for(int i = 0;i<file.size/512+1;i++)
	{
		stwrite(a.d,table[i],0);
	}
	free(table);
	bzero(&file,16);
	dirwrite(a.d,file,ptr);
	return 1;
}
