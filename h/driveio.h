void word_write(fs_struct f,sector s,int ptr, word data);
void byte_write(fs_struct f,sector s,int ptr, byte data);
byte byte_read(fs_struct f,sector s,int ptr);
word word_read(fs_struct f,sector s,int ptr);
