#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "h/types.h"
#include "h/driveio.h"
#include "h/st.h"
#include "h/fs.h"
#include "h/file.h"
#include "h/dir.h"
#include "h/debug.h"

void main(/*int argc, char * argv[]*/)
{
	fs_create("test.img",16);
	fs_struct fs = fs_open("test.img");

	file_struct file = dir_make("test");
	for(int i = 0; i<16;i++) file = file_add(fs,file);
		
	file_struct root = dir_root(fs);
	byte fre = dir_free(fs,root);
	dir_write(fs,root,file,fre);
	//dir_list(fs,root);

	fs_close(fs);
}
