#include <stdio.h>
#include "../h/dtypes.h"
#include "../h/st.h"

//запись на диск
void dwrite(dstruct d,int dest,void * src, int n)
{
	fseek(d.file,dest,SEEK_SET);
	fwrite(src,1,n,d.file);
}

//чтение с диска
void dread(dstruct d,int src,void * dest,int n)
{
	fseek(d.file,src,SEEK_SET);
	fread(dest,1,n,d.file);
}

//создает диск с файловой системой
void dcreate(char * name, word size)
{
	FILE *f = fopen(name,"wb+");
	dstruct d;
	d.file = f;
	d.size = size;
	word sts = size%256 ? (size/256)+1 : (size/256);
	d.sts = sts;
	dwrite(d,508,&size,2);
	for(int i = 1;i<sts+2;i++)
	{
		stwrite(d,i,i);
	}
	dwrite(d,(sts+1)*512,"#",1);
	word data = sts+1;
	dwrite(d,(sts+1)*512+12,&data,2);
	data = 0;
	dwrite(d,(sts+1)*512+14,&data,2);
	data = 0;
	dwrite(d,(size*512)-1,&data,1);
	fclose(f);	
}

//закрывает диск
void dclose(dstruct d)
{
	fclose(d.file);
}

//открывает диск
dstruct dopen(char * name)
{
	dstruct result;
	result.file=fopen(name,"rb+");
	dread(result,508,&result.size,2);
	result.sts = result.size%256 ? (result.size/256)+1 : (result.size/256);
	return result;
}
