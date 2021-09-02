#include "../h/types.h"
#include "../h/file.h"
#include "../h/driveio.h"
#include <stdio.h>
#include <stdlib.h>

file_struct dir_read(fs_struct fs,file_struct dir,byte file_ptr)
{
	sector * table = file_sectors(fs,dir);
	file_struct file;
	sector s = table[file_ptr/32];
	for(int i = 0; i<12;i++)
	{
		file.name[i]=byte_read(fs,s,file_ptr*16+i);
	}
	file.ptr=word_read(fs,s,file_ptr*16+12);
	file.size=word_read(fs,s,file_ptr*16+14);
	free(table);
	return file;
}

file_struct dir_root(fs_struct fs)
{
	file_struct file;
	for(int i = 0; i<12;i++)
	{
		file.name[i]=byte_read(fs,fs.sts+1,i);
	}
	file.ptr=word_read(fs,fs.sts+1,12);
	file.size=word_read(fs,fs.sts+1,14);
	return file;
}

void dir_write(fs_struct fs,file_struct dir,file_struct file,byte file_ptr)
{
	sector * table = file_sectors(fs,dir);
	sector s = table[file_ptr/32];
	for(int i = 0;i<12;i++)
	{
		byte_write(fs,s,file_ptr*16+i,(byte)file.name[i]);
	}
	word_write(fs,s,file_ptr*16+12,file.ptr);
	word_write(fs,s,file_ptr*16+14,file.size);
	free(table);
}

byte dir_free(fs_struct fs,file_struct dir)
{
	int i;
	for (i = 0; i<dir.size*32+1;i++)
	{
		if(i==dir.size*32+1)break;
		file_struct f = dir_read(fs,dir,i);
		if(f.name[0]==0) break;	
	}
	if(i==dir.size*32+1) return 0;
	return i;
}

void dir_list(fs_struct fs,file_struct file)
{
	for (int i = 0; i<file.size*32;i++)
	{
		file_struct f = dir_read(fs,file,i);
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
