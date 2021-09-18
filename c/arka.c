#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../h/types.h"
#include "../h/dio.h"
#include "../h/st.h"
#include "../h/dir.h"
#include "../h/debug.h"

typedef struct
{
	dstruct d;
	int cur;
}arka;

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
	fstruct dir = dirread(a.d,ptr);
	word * table = stfile(a.d,dir);
	for (int i = 0; i<dir.size/512+1;i++)
	{
		for(int j = 0;j<512;j+=16)
		{
			fstruct f = dirread(a.d,table[i]*512+j);
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
	if(ptr==0)return 0;
	a.cur=ptr;
	return 1;
}

//удаляет файл, 0 если файл не существует
int arkadel(arka a,char * name)
{
	fstruct dir = dirread(a.d,a.cur);
	int ptr = dirsearch(a.d,dir,name);
	if(ptr==0)return 0;
	fstruct f = dirread(a.d,ptr);
	word * table = stfile(a.d,f);
	for(int i = 0;i<f.size/512+1;i++)
	{
		stwrite(a.d,table[i],0);
	}
	free(table);
	bzero(&f,16);
	dirwrite(a.d,f,ptr);
	return 1;
}

//пишет в файл,0 если нет места,1 если место закончилось еще при записи, 2 если все успешно
int arkawrite(arka a,char * name)
{
	arkadel(a,name);
	fstruct dir = dirread(a.d,a.cur);
	int fre = dirfree(a.d,dir);
	if(fre==0)return 0;
	fstruct f;
	bzero(&f,16);
	memcpy(&f.name,name,strlen(name));
	word ptr = stfree(a.d);
	if(ptr==0)return 0;
	f.ptr=ptr;

	char c;
	word cursect = ptr;
	int curptr = 0;
	word nextsect = 0;
	while((c=getchar())!=EOF)
	{
		dwrite(a.d,cursect*512+curptr,&c,1);
		f.size++;
		curptr++;
		if(curptr==511)
		{
			nextsect=stfree(a.d);
			if(nextsect==0)
			{	
				stwrite(a.d,cursect,cursect);
				return 1;
			}
		}
		if(curptr==512)
		{
			curptr=0;
			stwrite(a.d,cursect,nextsect);
			cursect=nextsect;
		}
	}
	stwrite(a.d,cursect,cursect);
	dirwrite(a.d,f,fre);
	return 2;
}

//читает из файла, 0 если файл не существует
int arkaread(arka a,char * name)
{
	fstruct dir = dirread(a.d,a.cur);
	int ptr = dirsearch(a.d,dir,name);
	if(ptr==0)return 0;
	fstruct f = dirread(a.d,ptr);
	word * table = stfile(a.d,f);
	for(int i = 0;i<f.size/512+1;i++)
	{
		if(i<f.size/512)
		{
			for(int j=0;j<512;j++)
			{
				byte c;
				dread(a.d,table[i]*512+j,&c,1);
				putchar(c);
			}
		} else
		{
			for(int j = 0;j<f.size%512;j++)
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

//создает директориюб 0 если нет места
int arkadir(arka a,char *name)
{


}
