#include "../h/types.h"
#include "../h/st.h"
#include <string.h>
#include <stdlib.h>

sector * file_sectors(fs_struct fs, file_struct file)
{
	if (file.size==0) return 0;
	sector * table = malloc(file.size);
	table[0]=file.ptr;
	for(int i = 1;i<file.size;i++)
	{
		table[i]=st_read(fs,table[i-1]);
	}
	return table;
}

file_struct file_add(fs_struct fs,file_struct file)
{
	st_ptr s = st_free(fs);
	if(s==0) return file;
	if(file.size==0)
	{
		file.ptr = s;
	} else
	{
		sector * table = file_sectors(fs,file);
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
