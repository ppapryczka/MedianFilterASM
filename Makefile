CC=gcc
CFLAGS=-m64

ASM=nasm
AFLAGS=-f elf64

all: MedianFilter_x64 clean 

MedianFilter_x64: main.o MedianFilter_x64.o bmp_file.o
	$(CC) $(CFLAGS) main.o MedianFilter_x64.o bmp_file.o -o $@


main.o: main.c
	$(CC) $(CFLAGS) -c main.c


MedianFilter_x64.o: MedianFilter_x64.asm
	$(ASM) $(AFLAGS) MedianFilter_x64.asm

bmp_file.o: bmp_file.c bmp_file.h 


clean:
	rm *.o
