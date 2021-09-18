fstruct dirread(dstruct d,int ptr);
void dirwrite(dstruct d,fstruct f,int ptr);
int dirfree(dstruct d,fstruct dir);
int dirsearch(dstruct d, fstruct dir, char * name);
word dirinc(dstruct d,int ptr);
word dirdec(dstruct d, int ptr);
