// files operations
#include <stdio.h>
// for uin8_t, uint_32 itp.
#include <stdint.h>
// free/malloc
#include <stdlib.h>

// BMPFile and functions
#include "bmp_file.h"

// median filter in C
#include "median_filter.h"

#ifdef _cplusplus
extern "C" {
#endif
    uint64_t median_filter_x64(
        uint8_t *input_file_memory, 
        uint8_t *output_file_memory, 
        uint64_t starting_address_of_data, 
        uint64_t width, 
        uint64_t height, 
        uint64_t padding);
#ifdef _cplusplus
}
#endif

uint8_t* run_median_filter_on_image_asm(BMPFile* bmp_file, uint8_t* bmp_data){
    // allocate memory on result data
    uint8_t* result_data;
    result_data = malloc(bmp_file->BMP_file_size * sizeof(uint8_t));
    if (result_data == NULL){
        return NULL;
    }
    
    // run median filter
    median_filter_x64(
        bmp_data, 
        result_data,
        bmp_file->BMP_starting_address_of_data,
        bmp_file->BMP_width,
        bmp_file->BMP_height,
        bmp_file->BMP_padding
    );
    
    return result_data;
}

uint8_t* run_median_filter_on_image_c(BMPFile* bmp_file, uint8_t* bmp_data){
    uint8_t* pixel_data = get_pixel_data(
        bmp_data, 
        bmp_file->BMP_starting_address_of_data,
        bmp_file->BMP_width,
        bmp_file->BMP_height,
        bmp_file->BMP_padding
    );
    
    printf_pixel_data(
        pixel_data,
        bmp_file->BMP_width, 
        bmp_file->BMP_height 
    );
    
    uint8_t* result_data = produce_image(
        pixel_data, 
        bmp_data,
        bmp_file->BMP_starting_address_of_data,
        bmp_file->BMP_width,
        bmp_file->BMP_height, 
        bmp_file->BMP_padding, 
        bmp_file->BMP_file_size
    );
    
    return result_data;
}

int main(int argc, char* argv[])
{   
    
    // check if program gets appropriate number of arguments
    if(argc<3 || argc>3){
        printf("Usage: program <BMP input file path> <BMP output file path>\n");
        return 1;
    }
    
    // try to open result file to write 
    FILE* result_file;
    if((result_file=fopen(argv[2], "wb"))==NULL){
        printf("Error when try to open result file: %s!\n", argv[2]);
        return 1;
    }
    
    // read bmp file info 
    printf("Reading BMP file info...\n");
    BMPFile* bmp_file = init_BMP_file(argv[1]);
    if (bmp_file==NULL){
        printf("Error when try to open and read input file: %s!\n", argv[1]);
        return 1;
    }
    
    // printf file info
    print_BMP_file_info(bmp_file);
    
    
    // read original BMP data
    printf("Reading data...\n");
    uint8_t* original_data = read_BMP_data(bmp_file);
    
    // if any is NULL there is error in allocation
    if (original_data == NULL){
        printf("Error when try to allocate memory!");
        return 1;
    }
    
    // run median filter on original data
    printf("Running median filter...\n");
    
    // run asm median filter version
    uint8_t* result_data = run_median_filter_on_image_asm(bmp_file, original_data);
    if (result_data == NULL){
        printf("Error when try to allocate memory for result data!");
        return 1;
    }
    // run C median filter version
    // C version
    
    
    // write result data to output file
    printf("Writing result file to %s...\n", argv[2]);
    fwrite(result_data, 1, bmp_file->BMP_file_size, result_file);
    
    // clear result memory and and close file
    free(result_data);
    fclose(result_file);
    
    // clear result BMP
    clear_BMP_file(bmp_file);
    
    printf("Done!\n");
    
	return 0;
}

