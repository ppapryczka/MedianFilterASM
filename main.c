// files operations
#include <stdio.h>
// for uin8_t, uint_32 itp.
#include <stdint.h>
// free/malloc
#include <stdlib.h>

// BMPFile and functions
#include "bmp_file.h"

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
    
    // allocate memory for result
    uint8_t* result_data;
    result_data = malloc(bmp_file->BMP_file_size * sizeof(uint8_t));
    
    // if any is NULL there is error in allocation
    if (original_data == NULL || result_data == NULL){
        printf("Error when try to allocate memory!");
        return 1;
    }
    
    // run median filter on original data
    printf("Running median filter...\n");
    median_filter_x64(
        original_data, 
        result_data,
        bmp_file->BMP_starting_address_of_data,
        bmp_file->BMP_width,
        bmp_file->BMP_height,
        bmp_file->BMP_padding
    );

    // write result data to output file
    printf("Writing result file to %s...\n", argv[2]);
    fwrite(result_data, 1, bmp_file->BMP_file_size, result_file);
    
    // clear result memory and file
    free(result_data);
    fclose(result_file);
    
    clear_BMP_file(bmp_file);
    
    printf("Done!\n");
    
	return 0;
}
 
/*
    // check if program gets appropriate number of arguments
    if(argc<3 || argc>3){
        printf("Usage: program <input file path> <output file path>\n");
        return 1;
    }
    
    FILE *inputFile, *outputFile;
    
    if ((inputFile=fopen(argv[1], "rb"))==NULL){
        printf ("Error when try to open: %s!\n", argv[1]);
        return 1;
    }

    if((outputFile=fopen(argv[2], "wb"))==NULL){
        printf("Error when try to open: %s!\n", argv[2]);
        return 1;
    }
    

    uint8_t tableForRead[TABLE_FOR_READ_SIZE];
    uint64_t BMPFileSize, BMPStartingAddresOfData;
    uint64_t BMPWidth, BMPHeight; 
    uint64_t BMPPadding;

    uint8_t *inputFileMemory,  *outputFileMemory;

    
    
    // Load size of file in bytes
    fseek(inputFile, BMP_FILE_SIZE_INFO_IN_FILE_OFFSET, 0);
    fread(tableForRead, 1, TABLE_FOR_READ_SIZE, inputFile);    
    BMPFileSize = *(uint32_t*)tableForRead;

    // Load starting address of data
    fseek(inputFile, STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET, 0);
    fread(tableForRead, 1, TABLE_FOR_READ_SIZE, inputFile); 
    BMPStartingAddresOfData = *(uint32_t*)tableForRead;

    // Load width
    fseek(inputFile, WIDTH_INFO_IN_FILE_OFFSET, 0);
    fread(tableForRead, 1, TABLE_FOR_READ_SIZE, inputFile);    
    BMPWidth = *(uint32_t*)tableForRead;

    // Load heigth
    fseek(inputFile, HEIGHT_INFO_IN_FILE_OFFSET, 0);
    fread(tableForRead, 1, TABLE_FOR_READ_SIZE, inputFile);    
    BMPHeight = *(uint32_t*)tableForRead;

    // Allocate memory 
    inputFileMemory =  malloc(BMPFileSize * sizeof(uint8_t));
    outputFileMemory = malloc(BMPFileSize * sizeof(uint8_t));
    
    if (inputFileMemory == NULL || outputFileMemory == NULL){
        printf("Error when try to allocate memory!");
        return 2;
    }

    // Count padding
    BMPPadding = (BMPWidth*3)%4;
    if(BMPPadding!=0){
        BMPPadding = 4 - BMPPadding;
    }

    // Read data
    fseek(inputFile, 0, 0);
    fread(inputFileMemory, 1, BMPFileSize, inputFile);

    median_filter_x64(inputFileMemory, outputFileMemory, BMPStartingAddresOfData, 
        BMPWidth, BMPHeight, BMPPadding);

    // Write proccessed memory to output file
    fwrite(outputFileMemory, 1, BMPFileSize, outputFile);
    
    // Free resources
    fclose(inputFile);
    fclose(outputFile);
    free(inputFileMemory);
   	free(outputFileMemory);
*/
