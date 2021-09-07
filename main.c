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
#include "h/arka.h"

void main(/*int argc, char * argv[]*/)
{
	arka_new("test.img",16);
	arka_read("test.img","/");
}
