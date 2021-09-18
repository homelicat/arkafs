#include "../h/dtypes.h"
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

//поиск свободного сектора в таблице секторов,0 если нет
word stfree(dstruct d)
{
	word result = 0;
	for (int i = 1; i<d.size+1;i++)
	{
		if(i==d.size)break;
		if(stread(d,i)==0)
		{
			result = i;
			break;
		}
	}
	return result;
}

//создает таблицу файловых секторов
word * stfile(dstruct d, fstruct f)
{
	word * table = malloc((f.size/512+1)*2);
	table[0]=f.ptr;
	for(int i = 1;i<f.size/512+1;i++)
	{
		table[i]=stread(d,table[i-1]);
	}
	return table;
}
