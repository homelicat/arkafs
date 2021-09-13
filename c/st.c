#include "../h/types.h"
#include "../h/dio.h"
#include <stdlib.h>

//запись в таблицу секторов
void stwrite(dstruct d,word sect, word data)
{	
	dwrite(d,(sect*2)+512,&data,2);
}

//чтение из таблицы секторов
word stread(dstruct d,word sect)
{
	word result;
	dread(d,(sect*2)+512,&result,2);
	return result;
}

//поиск свободного сектора в таблице секторов, если нет, возвращает размер диска
word stfree(dstruct d)
{
	word result;
	for (result = 1; result<d.size+1;result++)
	{
		if(result==d.size)break;
		if(stread(d,result)==0)break;
	}
	return result;
}

//создает таблицу файловых секторов, 0 если файл пуст
word * stfile(dstruct d, fstruct file)
{
	if (file.size==0) return 0;
	word * table = malloc(file.size/512);
	table[0]=file.ptr;
	for(int i = 1;i<file.size/512;i++)
	{
		table[i]=stread(d,table[i-1]);
	}
	return table;
}
