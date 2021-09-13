void dwrite(dstruct d,int dest, void * src,int n);
void dread(dstruct d,int src, void * dest,int n);
void dcreate(char * name,word size);
void dclose(dstruct d);
dstruct dopen(char * name);
