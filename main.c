#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "h/arka.h"

void main(/*int argc, char * argv[]*/)
{
	arka a = arkamount("test.img");
	arkalist(a);
}
