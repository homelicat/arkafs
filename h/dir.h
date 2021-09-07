file_struct dir_read(fs_struct fs,file_struct file,byte file_ptr);
file_struct dir_root(fs_struct fs);
void dir_write(fs_struct fs,file_struct dir,file_struct file,byte file_ptr);
byte dir_free(fs_struct fs,file_struct dir);
file_struct dir_make(char * name);
file_struct dir_search(fs_struct fs, file_struct dir, char * name);
file_struct dir_null();
