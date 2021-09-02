#include "../h/types.h"
#include "../h/driveio.h"

void st_write(fs_struct fs,st_ptr ptr, word data)
{	
	word_write(fs,1,ptr*2,data);
}

word st_read(fs_struct fs,st_ptr ptr)
{
	word result;
	result = word_read(fs,1,ptr*2);
	return result;
}

st_ptr st_free(fs_struct fs)
{
	st_ptr ptr;
	for (ptr = 1; ptr<fs.size+1;ptr++)
	{
		word state;
		if (ptr == fs.size)break;
		state = st_read(fs,ptr);
		if (state==0) break;
	}
	if (ptr==fs.size) return 0;
	return ptr;
}
