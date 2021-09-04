#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "../h/types.h"
#include "../h/driveio.h"
#include "../h/st.h"
#include "../h/fs.h"
#include "../h/file.h"
#include "../h/dir.h"
#include "../h/debug.h"

void arka_new(char * name,int size)
{
	fs_create(name,size);
}

void arka_dir(char * name, char * path)
{
	fs_struct fs = fs_open(name);
	file_struct root = dir_root(fs);
	for (int i = 0; i<root.size*32;i++)
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
	file_struct root = dir_root(fs);
	file_struct file = dir_search(fs,root,path);
	if (file.ptr==fs.sts+1)
	{
		puts("File not found");
	} else
	{
		if (file.size==0) file = file_add(fs,file);
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
	file_struct root = dir_root(fs);
	file_struct file = dir_search(fs,root,path);
	if(file.ptr==fs.sts+1) puts("File not found");
	sector * table = 
}

void arka_del();

