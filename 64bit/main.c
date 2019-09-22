// files operations
#include<stdio.h>
// for uin8_t, uint_32 itp.
#include<stdint.h>
// free/malloc
#include<stdlib.h>

#ifdef _cplusplus
extern "C" {
#endif
    uint64_t MedianFilter_x64(uint8_t *inputFileMemory, uint8_t *outputFileMemory, 
        uint64_t startingAddressOfData, uint64_t width, uint64_t height, uint64_t padding);
#ifdef _cplusplus
}
#endif

/*
 *  This consts describe Windows BITMAPINFOHEADER header of BMP and
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
    uint64_t BMPFileSize, BMPStartingAddresOfData;
    uint64_t BMPWidth, BMPHeight; 
    uint64_t BMPPadding;

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

    MedianFilter_x64(inputFileMemory, outputFileMemory, BMPStartingAddresOfData, 
        BMPWidth, BMPHeight, BMPPadding);

    // Write proccessed memory to output file
    fwrite(outputFileMemory, 1, BMPFileSize, outputFile);
    
    // Free resources
    fclose(inputFile);
    fclose(outputFile);
    free(inputFileMemory);
   	free(outputFileMemory);

	return 0;
}
