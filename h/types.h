#include <stdio.h>

//переопределение типов
typedef unsigned short word;
typedef unsigned char byte;

//дисковая структура
typedef struct
{
	FILE * file;
	word size; //ptr 508	
	word sts;
} dstruct;

//файловая структура
typedef struct
{
	char name[12];
	word ptr;
	word size;
} fstruct;

