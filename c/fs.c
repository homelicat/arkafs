#include "../h/types.h"
#include "../h/driveio.h"
#include <stdio.h>
#include "../h/dir.h"
#include <string.h>

void fs_create(char * str, sector size)
{
	FILE *f = fopen(str,"wb+");
	fs_struct fs;
	fs.file = f;
	fs.size = size;
	sector sts = size%256 ? (size/256)+1 : (size/256);
	fs.sts = sts;
	word_write(fs,0,508,size);
	for(int i = 0;i<sts;i++)
	{
		for(int j = 0;j<256;j++)
		{
			word data = (i*256+j)<sts+2 ? i*256+j : 0;
			word_write(fs,1+i,j*2,data);
		}
	}
	for(int i = sts+1;i<size;i++)
	{
		for(int j = 0;j<512;j++)
		{
			byte_write(fs,i,j,0);
		}
	}
	file_struct file;
	bzero(&file,16);
	file.name[0]='#';
	file.ptr=sts+1;
	file.size=1;
	dir_write(fs,file,file,0);
	fclose(f);	
}

void fs_close(fs_struct fs)
{
	fclose(fs.file);
}

fs_struct fs_open(char * str)
{
	fs_struct result;
	result.file=fopen(str,"rb+");
	result.size = word_read(result,0,508);
	result.sts = result.size%256 ? (result.size/256)+1 : (result.size/256);
	return result;
}
