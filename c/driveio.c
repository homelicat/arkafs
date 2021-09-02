#include <stdio.h>
#include "../h/types.h"

void word_write(fs_struct f,sector s,int  ptr, word data)
{
	fseek(f.file,s*512+ptr,SEEK_SET);
	fwrite(&data,2,1,f.file);
}

void byte_write(fs_struct f,sector s, int ptr, byte data)
{
	fseek(f.file,s*512+ptr,SEEK_SET);
	fwrite(&data,1,1,f.file);
}

word word_read(fs_struct f,sector s,int ptr)
{
	word result;
	fseek(f.file,s*512+ptr,SEEK_SET);
	fread(&result,2,1,f.file);
	return result;
}

byte byte_read(fs_struct f,sector s, int ptr)
{
	byte result;
	fseek(f.file,s*512+ptr,SEEK_SET);
	fread(&result,1,1,f.file);
	return result;
}

