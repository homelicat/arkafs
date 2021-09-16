#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../h/types.h"
#include "../h/dio.h"
#include "../h/st.h"
#include "../h/dir.h"
#include "../h/debug.h"

//возвращает указатель на файл по пути, 0 если файл не существует
int arkapath(dstruct d, char * ipath)
{
	if(ipath[0]!='/')
	{
		return 0;
	}
	if(strlen(ipath)==1)return (d.sts+1)*512;
	char * path = malloc(strlen(ipath));
	strcpy(path,ipath+1);
	int cur = (d.sts+1)*512;
	char * name = strtok(path,"/");
	while (name != NULL)
	{
		fstruct dir = dirread(d,cur);
		cur = dirsearch(d,dir,name);
		if(cur==0)return cur;
		name = strtok(NULL,"/");
   	}
	return cur;
}

//создает диск
void arkanew(char * name,int size)
{
	dcreate(name,size);
}

//выводит содержимое директории
void arkalist(char * name, char * path)
{
	dstruct d = dopen(name);
	int ptr = arkapath(d,path);
	if(ptr==0)
	{
		puts("Dir not found");
		dclose(d);
		return;
	}
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
	dclose(d);
}

//TODO UNDER
//пишет в файл
void arka_write(char * name,char * path)
{
	fs_struct fs = fs_open(name);
	int i = strlen(path);
	while(path[i-1]!='/')i--;
	char * dir_path = malloc(i);
	memcpy(dir_path,path,i-1);
	dir_path[i-1]=0;
	file_struct dir = arka_path(fs,dir_path);
	if(dir.name[0]==0)
	{
		puts("Dir not found");
		fs_close(fs);
		return;
	}
	file_struct file = dir_search(fs,dir,path+i);
	if (file.name[0]!=0)
	{
		arka_del(name,path);
	}
	word size = file.size;
	file = file_add(fs,file);
	if(size==file.size)
	{
		puts("Not enough space");
		fs_close(fs);
		return;
	}
	sector * table = file_sectors(fs,file);
	char c;
	int ptr = 0;
	while((c=getchar())!=EOF)
	{
		
	}
	}
	fs_close(fs);
}

//читает из файла
void arka_read(char * name, char * path)
{
	fs_struct fs = fs_open(name);
	file_struct file = arka_path(fs,path);
	if(file.name[0]==0)
	{
		puts("File not found");
		fs_close(fs);
		return;
	}
	sector * table = file_sectors(fs,file);
	for(int i = 0;i<file.size;i++)
	{
		for(int j = 0;j<512;j++)
		{
			putchar(byte_read(fs,table[i],j));
		}
	}
	free(table);
	fs_close(fs);
}

//удаляет файл
void arka_del(char * name, char * path)
{
	fs_struct fs = fs_open(name);
	file_struct file = arka_path(fs,path);
	if(file.name[0]==0)
	{
		puts("File not found");
		fs_close(fs);
		return;
	}
	sector * table = file_sectors(fs,file);
	for(int i = 0;i<file.size;i++)
	{
		st_write(fs,table[i],0);
	}
	int i = strlen(path);
	while(path[i-1]!='/')i--;
	char * dir_path = malloc(i);
	memcpy(dir_path,path,i-1);
	dir_path[i-1]=0;
	file_struct dir = arka_path(fs,dir_path);
	free(table);
	table = file_sectors(fs,dir);
	for(int i = 0;i<dir.size;i++)
	{
		for(int j = 0;j<32;j+=16)
		{
			byte arr[16] = {0};
			for(int k=0;k<16;k++)
			{
				arr[k]=byte_read(fs,table[i],j*16+k);
			}
			if(!memcmp(&file,arr,16))
			{
				for(int k=0;k<16;k++)
				{
					byte_write(fs,table[i],j*16+k,0);
				}
			}
		}
	}
	free(table);
	fs_close(fs);
}*/
