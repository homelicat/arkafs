#include "h/dtypes.h"
#include "h/arkatypes.h"
#include "h/arka.h"
#include <stdio.h>

void main()
{
	arkanew("test.img",16);
	arka a = arkamount("test.img");
	arkadir(&a,"newdir");
	arkacd(&a,"#newdir");
	arkawrite(&a,"test");
	arkalist(&a);
	arkacd(&a,"#");
	arkalist(&a);
	arkaumount(&a);
}
