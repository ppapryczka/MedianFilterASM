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

uint8_t* read_BMP_header(BMPFile* bmp_file){
    // allocate memory
    uint8_t* header_memory;
    header_memory =  (uint8_t*)malloc(bmp_file->BMP_starting_address_of_data * sizeof(uint8_t));
    
    // check if allocation is success, if not return NULL
    if (header_memory == NULL){
        return NULL;
    }
    // read header data from file
    fseek(bmp_file->file, 0, 0);
    fread(header_memory, 1, bmp_file->BMP_starting_address_of_data, bmp_file->file);
    
    return header_memory;
}


uint8_t* convert_BMP_data_to_image_data(BMPFile* bmp_file, uint8_t* bmp_data){
    // get size for image data
    uint64_t result_data_size = bmp_file->BMP_width * bmp_file->BMP_height * 3;
    
    // allocate memory for result data
    uint8_t* result_image_data;
    result_image_data = (uint8_t*) malloc(result_data_size * sizeof(uint8_t));
    
    // iterate over image pixels as 2D table
    for (uint64_t i=0; i<bmp_file->BMP_height; ++i){
        for(uint64_t k=0; k<bmp_file->BMP_width; ++k){
            
            // address of pixel in BMP data
            uint64_t pixel_address_in_bmp_data = 
                (bmp_file->BMP_width*3+bmp_file->BMP_padding)*i + k*3 + bmp_file->BMP_starting_address_of_data;
            
            // address of pixel in result image data
            uint64_t pixel_address_in_image_data = (bmp_file->BMP_width*i + k)*3;
            
            
            // copy pixel
            for(uint8_t l = 0; l<3; ++l){
                result_image_data[pixel_address_in_image_data + l] = 
                    bmp_data[pixel_address_in_bmp_data + l];
            }
        }
    }
    
    return result_image_data;
} 

uint8_t* get_image_data_from_BMP_image(BMPFile *bmp_file){
    // get BMP data from bmp_file
    uint8_t* bmp_data = read_BMP_data(bmp_file);
    
    // convert BMP data to image data
    uint8_t* image_data = convert_BMP_data_to_image_data(bmp_file, bmp_data);
    
    // free BMP data
    free(bmp_data);
    
    return image_data;
}

uint8_t* produce_BMP_file(BMPFile *bmp_file, uint8_t* image_data){
    // allocate memory for BMP image
    uint8_t* result_data;
    result_data = malloc(bmp_file->BMP_file_size * sizeof(uint8_t));
    
    // get header from original data
    uint8_t* header_data = read_BMP_header(bmp_file);
    
    // copy header to result data
    for (uint64_t i = 0; i<bmp_file->BMP_starting_address_of_data; ++i){
        result_data[i] = header_data[i];
    }
    
    // free header data
    free(header_data);
    
    // copy pixels from image_data to result_data padding is omitted
    for (uint64_t i=0; i<bmp_file->BMP_height; ++i){
        for(uint64_t k=0; k<bmp_file->BMP_width; ++k){
            
            // address of pixel in image_data
            uint64_t pixel_address_in_image_data = (bmp_file->BMP_width*i + k)*3;
            
            // address of pixel in result BMP data
            uint64_t pixel_address_in_result_data = 
                (bmp_file->BMP_width*3+bmp_file->BMP_padding)*i + k*3 + bmp_file->BMP_starting_address_of_data;
            
            // copy one pixel
            for(uint8_t l = 0; l<3; ++l){
                result_data[pixel_address_in_result_data + l] = 
                    image_data[pixel_address_in_image_data + l];
            }
        }
    }
    
    return result_data;
}

void print_BMP_file_info(BMPFile* bmp_file){
    // print BMP file info
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
