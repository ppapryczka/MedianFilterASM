CC=gcc
CFLAGS=-m64

ASM=nasm
AFLAGS=-f elf64

all: MedianFilter_x64 clean 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

MedianFilter_x64.o: MedianFilter_x64.asm
	$(ASM) $(AFLAGS) MedianFilter_x64.asm

MedianFilter_x64: main.o MedianFilter_x64.o
	$(CC) $(CFLAGS) main.o MedianFilter_x64.o -o MedianFilter_x64

clean:
	rm *.o
