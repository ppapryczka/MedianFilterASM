#include<stdio.h>

// for uin8_t, uint_32 itp.
#include<stdint.h>
#include<stdlib.h>

#ifdef _cplusplus
extern "C" {
#endif
uint32_t MedianFilter_x86(uint8_t *inMemory, uint8_t *outMemory, 
    uint32_t startingAddressOfData, uint32_t width, uint32_t height);
#ifdef _cplusplus
}
#endif


/*
 *  This is description for Windows BITMAPINFOHEADER header of BMP and
 *  program works only with that format.
 */

uint32_t TABLE_FOR_READ_SIZE = 4;
uint32_t BMP_FILE_SIZE_INFO_IN_FILE_OFFSET = 2;
uint32_t STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET = 10;
uint32_t WIDTH_INFO_IN_FILE_OFFSET = 18;
uint32_t HEIGHT_INFO_IN_FILE_OFFSET = 22;

int main(int argc, char* argv[])
{
    if(argc<3 || argc>3){
        printf("Usage: program <input file path> <output file path>\n");
        return 1;
    }

    FILE *inputFile, *outputFile;

    uint8_t tableForRead[TABLE_FOR_READ_SIZE];
    uint32_t BMPFileSize, BMPStartingAddresOfData;
    uint32_t BMPWidth, BMPHeight; 

    uint8_t *inputFileMemory,  *outputFileMemory;

    if ((inputFile=fopen(argv[1], "rb"))==NULL){
        printf ("Error when try to open: %s!\n", argv[1]);
        return 1;
    }

    if((outputFile=fopen(argv[2], "wb"))==NULL){
        printf("Error when try to open: %s!\n", argv[2]);
        return 1;
    }

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

    // Read data
    fseek(inputFile, 0, 0);
    fread(inputFileMemory, 1, BMPFileSize, inputFile);

    // Run median filter in x86 version
    MedianFilter_x86(inputFileMemory, outputFileMemory, 
        BMPStartingAddresOfData, BMPWidth, BMPHeight);

    // Write proccessed memory to output file
    fwrite(outputFileMemory, 1, BMPFileSize, outputFile);
    
    // Free resources
    fclose(inputFile);
    fclose(outputFile);
    free(inputFileMemory);
   	free(outputFileMemory);

    return 0;
}
