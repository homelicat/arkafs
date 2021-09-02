#include <stdio.h>

typedef unsigned short st_ptr;
typedef unsigned short word;
typedef unsigned char byte;
typedef unsigned short sector;

typedef struct
{
	FILE * file;
	sector size; //ptr 508	
	sector sts;
} fs_struct;

typedef struct
{
	char name[12];
	sector ptr;
	sector size;
} file_struct;

