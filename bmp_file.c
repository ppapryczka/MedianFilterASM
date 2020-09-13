#include "bmp_file.h"

// printf
#include <stdio.h>
// free/malloc
#include <stdlib.h>


const uint32_t TABLE_FOR_READ_SIZE = 4;
const uint32_t BMP_FILE_SIZE_INFO_IN_FILE_OFFSET = 2;
const uint32_t STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET = 10;
const uint32_t WIDTH_INFO_IN_FILE_OFFSET = 18;
const uint32_t HEIGHT_INFO_IN_FILE_OFFSET = 22;


BMPFile* init_BMP_file(char* filename){
    // declare variables for struct attributes
    uint8_t table_for_read[TABLE_FOR_READ_SIZE];
    uint64_t BMP_file_size, BMP_starting_address_of_data;
    uint64_t BMP_width, BMP_height; 
    uint64_t BMP_padding;
    FILE* file;
    
    // try to open file 
    if ((file=fopen(filename, "rb"))==NULL){
        return NULL;
    }
    
    // load size of file in bytes
    fseek(file, BMP_FILE_SIZE_INFO_IN_FILE_OFFSET, 0);
    fread(table_for_read, 1, TABLE_FOR_READ_SIZE, file);    
    BMP_file_size = *(uint32_t*)table_for_read;

    // load starting address of data
    fseek(file, STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET, 0);
    fread(table_for_read, 1, TABLE_FOR_READ_SIZE, file); 
    BMP_starting_address_of_data = *(uint32_t*)table_for_read;

    // load width
    fseek(file, WIDTH_INFO_IN_FILE_OFFSET, 0);
    fread(table_for_read, 1, TABLE_FOR_READ_SIZE, file);    
    BMP_width = *(uint32_t*)table_for_read;

    // load heigth
    fseek(file, HEIGHT_INFO_IN_FILE_OFFSET, 0);
    fread(table_for_read, 1, TABLE_FOR_READ_SIZE, file);    
    BMP_height = *(uint32_t*)table_for_read;

    // count padding
    BMP_padding = (BMP_width * 3) % 4;
    if(BMP_padding != 0){
        BMP_padding = 4 - BMP_padding;
    }
    
    // create new BMPFile object
    BMPFile* new_BMP = (BMPFile*) malloc(sizeof(BMPFile));
    
    // set struct fields
    new_BMP->file = file;
    new_BMP->BMP_file_size = BMP_file_size;
    new_BMP->BMP_width = BMP_width;
    new_BMP->BMP_height = BMP_height;
    new_BMP->BMP_padding = BMP_padding;
    new_BMP->BMP_starting_address_of_data = BMP_starting_address_of_data;
    
    return new_BMP;
}

uint8_t* read_BMP_data(BMPFile* bmp_file){
    // allocate memory
    uint8_t* output_memory;
    output_memory =  (uint8_t*)malloc(bmp_file->BMP_file_size * sizeof(uint8_t));
    
    // check if allocation is success, if not return NULL
    if (output_memory == NULL){
        return NULL;
    }
    
    // read file data
    fseek(bmp_file->file, 0, 0);
    fread(output_memory, 1, bmp_file->BMP_file_size, bmp_file->file);
    
    return output_memory;
}

void print_BMP_file_info(BMPFile* bmp_file){
    printf("***\n");
    printf("BMP file info:\n");
    printf("File size: %ld\n", bmp_file->BMP_file_size);
    printf("Image width: %ld\n", bmp_file->BMP_width);
    printf("Image height: %ld\n", bmp_file->BMP_height);
    printf("Padding: %ld\n", bmp_file->BMP_padding);
    printf("Starting address of data: %ld\n", bmp_file->BMP_starting_address_of_data);
    printf("***\n");
}

void clear_BMP_file(BMPFile* bmp_file){
    if(bmp_file != NULL){
        // close file
        fclose(bmp_file->file);
        // free memeory
        free(bmp_file);
    }
}
