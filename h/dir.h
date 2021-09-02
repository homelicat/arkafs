file_struct dir_read(fs_struct fs,file_struct file,byte file_ptr);
file_struct dir_root(fs_struct fs);
void dir_write(fs_struct fs,file_struct dir,file_struct file,byte file_ptr);
void dir_list(fs_struct fs,file_struct file);
byte dir_free(fs_struct fs,file_struct dir);
