gcc -o o/driveio.o -c c/driveio.c
gcc -o o/st.o -c c/st.c
gcc -o o/fs.o -c c/fs.c
gcc -o o/file.o -c c/file.c
gcc -o o/dir.o -c c/dir.c
gcc -o o/debug.o -c c/debug.c
gcc -o main.o -c main.c
gcc -o main main.o o/*.o