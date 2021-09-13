#include "../h/types.h"
#include "../h/dio.h"
#include "../h/st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//считывает файловую структуру
fstruct dirread(dstruct d,int ptr)
{
	fstruct file;
	dread(d,ptr,&file,16);
	return file;
}

//записывает файловую структуру
void dirwrite(dstruct d,fstruct file,int ptr)
{
	dwrite(d,ptr,&file,16);
}

//ищет пустую ячейку в директории, 0 если нет
int dirfree(dstruct d,fstruct dir)
{
	word * table = stfile(d,dir);
	for (int i = 0; i<dir.size/512;i++)
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
	byte sects = (dir.size%512) ? (dir.size/512)+1 : (dir.size/512);
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

//расширяет файл, 0 если нет места, или новый сектор
word dirinc(dstruct d,int ptr)
{
	word s = stfree(d);
	if(s==0) return 0;
	fstruct file = dirread(d,ptr);
	if(file.size==0)
	{
		file.ptr = s;
	} else
	{
		word * table = stfile(d,file);
		st_write(fs,table[file.size-1],s);
		free(table);
	}
	st_write(fs,s,s);
	file.size++;
	return file;
}

file_struct file_sub(fs_struct fs, file_struct file)
{
	if(file.size!=0)
	{
		sector * table = file_sectors(fs,file);
		st_write(fs,table[file.size-1],0);
		if(file.size==1)
		{
			file.ptr=0;
		} else
		{
			st_write(fs,table[file.size-2],table[file.size-2]);
		}
		file.size--;
		free(table);
	}
	return file;
}
