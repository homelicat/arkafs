#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "h/types.h"
#include "h/dio.h"
#include "h/st.h"
#include "h/dir.h"
#include "h/debug.h"
#include "h/arka.h"

void main(/*int argc, char * argv[]*/)
{
	dcreate("test.img",16);
	dstruct d = dopen("test.img");
	fstruct f;
	bzero(&f,16);
	memcpy(&f,"test",4);
	fstruct root = dirread(d,(d.sts+1)*512);
	int ptr = dirfree(d,root);
	dirwrite(d,f,ptr);
	dirinc(d,ptr);
	dirinc(d,ptr);
	dclose(d);
	//arka_new("test.img",16);
	//arka_read("test.img","/");
}
