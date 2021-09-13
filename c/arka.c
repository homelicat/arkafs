#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../h/types.h"
#include "../h/dio.h"
#include "../h/st.h"
#include "../h/dir.h"
#include "../h/debug.h"
/*
file_struct arka_path(fs_struct fs, char * ipath)
{
	if(ipath[0]!='/')return dir_null();
	if(strlen(ipath)==1)return dir_root(fs);
	char * path = malloc(strlen(ipath));
	strcpy(path,ipath+1);
	file_struct cur = dir_root(fs);
	char * name = strtok(path,"/");
	while (name != NULL)
	{
		cur = dir_search(fs,cur,name);
		if(cur.name[0]==0)return cur;
		name = strtok(NULL,"/");
   	}
	return cur;
}

void arka_new(char * name,int size)
{
	fs_create(name,size);
}

void arka_dir(char * name, char * path)
{
	fs_struct fs = fs_open(name);
	file_struct dir = arka_path(fs,path);
	if(dir.name[0]==0)
	{
		puts("Dir not found");
		fs_close(fs);
		return;
	}
	for (int i = 0; i<dir.size*32;i++)
	{
		file_struct f = dir_read(fs,dir,i);
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
	fs_close(fs);
}

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
}
*/
