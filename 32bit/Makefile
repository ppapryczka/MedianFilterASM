CC=gcc
CFLAGS=-m32

ASM=nasm
AFLAGS=-f elf32

all: MedianFilter_x86 clean 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

MedianFilter_x86.o: MedianFilter_x86.asm
	$(ASM) $(AFLAGS) MedianFilter_x86.asm	

MedianFilter_x86: main.o MedianFilter_x86.o
	$(CC) $(CFLAGS) main.o MedianFilter_x86.o -o MedianFilter_x86  

clean:
	rm *.o

