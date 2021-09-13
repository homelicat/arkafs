gcc -o o/dio.o -c c/dio.c
gcc -o o/st.o -c c/st.c
gcc -o o/dir.o -c c/dir.c
gcc -o o/arka.o -c c/arka.c
gcc -o o/debug.o -c c/debug.c
gcc -o main.o -c main.c
gcc -o main main.o o/*.o
