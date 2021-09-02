#include "../h/types.h"
#include "../h/st.h"
#include <string.h>
#include <stdlib.h>

sector * file_sectors(fs_struct fs, file_struct file)
{
	sector * table = malloc(file.size);
	table[0]=file.ptr;
	for(int i = 1;i<file.size;i++)
	{
		table[i]=st_read(fs,table[i-1]);
	}
	return table;
}

