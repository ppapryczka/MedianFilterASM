CC=gcc
CFLAGS=-m64

ASM=nasm
AFLAGS=-f elf64

all: median_filter clean 

median_filter: main.o MedianFilter_x64.o bmp_file.o median_filter.o image_data.o
	$(CC) $(CFLAGS) main.o MedianFilter_x64.o bmp_file.o median_filter.o image_data.o -o $@

main.o: main.c

MedianFilter_x64.o: MedianFilter_x64.asm
	$(ASM) $(AFLAGS) MedianFilter_x64.asm

bmp_file.o: bmp_file.c bmp_file.h 

median_filter.o: median_filter.c median_filter.h

image_data.o: image_data.c image_data.h

clean:
	rm *.o
