#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "h/arka.h"

void main(/*int argc, char * argv[]*/)
{
	arkanew("test.img",16);
	arka a = arkamount("test.img");
	arkawrite(a,"test");
	arkaread(a,"test");
}
