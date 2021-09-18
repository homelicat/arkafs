#include "types.h"
typedef struct
{
	dstruct d;
	int cur;
}arka;

void arkanew(char * name,int size);
arka arkamount(char * name);
void arkaumount(arka a);
int arkacd(arka a, char * name);
int arkawrite(arka a,char * name);
int arkaread(arka a,char * name);
int arkadel(arka a,char * name);
void arkalist(arka a);
int arkadir(arka a,char *name);
