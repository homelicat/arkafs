#include "types.h"
typedef struct
{
	dstruct d;
	int cur;
}arka;

int arkapath(dstruct d, char * ipath);
void arkanew(char * name,int size);
void arkalist(char * name, char * path);
/*
void arka_write(char * name,char * path);
void arka_read(char * name, char * path);
void arka_del();*/
