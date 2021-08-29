#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void debug()
{
	puts("debug");
}

struct fs_struct
{
	FILE * file;
	unsigned short size; //ptr 508	
	unsigned short sts;
};

struct file_struct
{
	char name[12];
	unsigned short ptr;
	unsigned short size;
};


void word_write(int ptr, struct fs_struct f, unsigned short data)
{
	fseek(f.file,ptr,SEEK_SET);
	fwrite(&data,2,1,f.file);
}

void byte_write(int ptr, struct fs_struct f, unsigned char data)
{
	fseek(f.file,ptr,SEEK_SET);
	fwrite(&data,1,1,f.file);
}

unsigned short word_read(int ptr,struct fs_struct f)
{
	unsigned short result;
	fseek(f.file,ptr,SEEK_SET);
	fread(&result,2,1,f.file);
	return result;
}

unsigned char byte_read(int ptr, struct fs_struct f)
{
	unsigned char result;
	fseek(f.file,ptr,SEEK_SET);
	fread(&result,1,1,f.file);
	return result;
}

struct file_struct file_struct_read(int ptr, struct fs_struct fs)
{
	struct file_struct result;
	for(int i = 0; i<12;i++)
	{
		result.name[i]=(char)byte_read(ptr+i,fs);
	}
	result.ptr=word_read(ptr+12,fs);
	result.size=word_read(ptr+14,fs);
	return result;
}


void file_struct_write(int ptr, struct file_struct file, struct fs_struct fs)
{
	for(int i = 0;i<12;i++)
	{
		byte_write(ptr+i,fs,(unsigned char)file.name[i]);
	}
	word_write(ptr+12,fs,file.ptr);
	word_write(ptr+14,fs,file.size);
}

void st_write(unsigned short sector, struct fs_struct fs, unsigned short data)
{
	int ptr = 512+(sector*2);	
	word_write(ptr,fs,data);
}

unsigned short st_read(unsigned short sector, struct fs_struct fs)
{
	unsigned short result;
	int ptr = 512+(sector*2);
	result = word_read(ptr,fs);
	return result;
}

unsigned short st_free(struct fs_struct fs)
{
	unsigned short sector;
	for (sector = 1; sector<fs.size+1;sector++)
	{
		unsigned short state;
		if (sector == fs.size)break;
		state = st_read(sector,fs);
		if (state==0) break;
	}
	if (sector==fs.size) return 0;
	return sector;
}

unsigned short file_free(int ptr,struct fs_struct fs)
{
	int file_ptr;
	for(file_ptr = ptr;file_ptr<ptr+512+16;file_ptr+=16)
	{
		if (file_ptr==ptr+512)break;
		struct file_struct file = file_struct_read(file_ptr,fs);
		if(file.name[0]==0)break;
	}
	if(file_ptr==ptr+512)return 0;
	return file_ptr;
}

unsigned short * file_sectors(struct file_struct file, struct fs_struct fs)
{
	unsigned short * table = malloc(file.size);
	table[0]=file.ptr;
	for(int i = 1;i<file.size;i++)
	{
		table[i]=st_read(table[i-1],fs);
	}
	return table;
}

void dir_list(struct file_struct file,struct fs_struct fs)
{
	unsigned short * table = file_sectors(file,fs);
	for (int i = 0; i<file.size;i++)
	{
		for(int j=0;j<512;j+=16)
		{
			if(byte_read(table[i]*512+j,fs)==0) continue;
			for(int k = 0; k<12;k++)
			{
				char c = byte_read(table[i]*512+j+k,fs);
				if(c==0)
				{
					putchar(' ');
				} else
				{
					putchar(c);
				}
			}
			printf(" %X %X\n",word_read(table[i]*512+j+12,fs),word_read(table[i]*512+j+14,fs));
		}
	}
}

void fs_create(char * str, unsigned short size)
{
	FILE *f = fopen(str,"wb+");
	struct fs_struct fs;
	fs.file = f;
	fs.size = size;
	unsigned short sts = size%256 ? (size/256)+1 : (size/256);
	fs.sts = sts;
	word_write(508,fs,size);
	for(int i = 0;i<sts*256;i++)
	{
		unsigned short data = i<sts+2 ? i : 0;
		word_write(512+(i*2),fs,data);
	}
	for(int i = sts+1;i<size;i++)
	{
		for(int j = 0;j<512;j++)
		{
			byte_write(i*512+j,fs,0);
		}
	}
	fclose(f);	
}

struct fs_struct fs_open(char * str)
{
	struct fs_struct result;
	result.file=fopen(str,"rb+");
	result.size = word_read(508,result);
	result.sts = result.size%256 ? (result.size/256)+1 : (result.size/256);
	return result;
}

void main(int argc, char * argv[])
{
	//fs_create("test.img",16);
	struct file_struct file;
	bzero(&file,16);
	memcpy(file.name,"boot",4);
	file.ptr=2;
	file.size=1;
	struct fs_struct fs = fs_open("test.img");
	dir_list(file,fs);
	//file_struct_write(512*2+16,file,fs);
}
