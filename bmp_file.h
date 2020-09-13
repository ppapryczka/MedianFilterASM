// files operations
#include <stdio.h>
// for uin8_t, uint_32 itp.
#include <stdint.h>


/*
 *  This consts describe Windows BITMAPINFOHEADER header of BMP and
 *  program works only with that format.
 * 
 *  TABLE_FOR_READ_SIZE - size of table to read start address of data for image, 
 *  width, size and height of image - all values listed below.
 *  BMP_FILE_SIZE_INFO_IN_FILE_OFFSET - offset in BMP file with information about size 
 *  of file
 *  STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET - offset in BMP file with starting 
 *  address of image data
 *  WIDTH_INFO_IN_FILE_OFFSET - offset in BMP file with infomation about image width 
 *  HEIGHT_INFO_IN_FILE_OFFSET - offset in BMP file with information about image height
 *  
 *  All listed values are describtion of mentioned BITMAPINFOHEADER. 
 */
extern const uint32_t TABLE_FOR_READ_SIZE;
extern const uint32_t BMP_FILE_SIZE_INFO_IN_FILE_OFFSET;
extern const uint32_t STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET;
extern const uint32_t WIDTH_INFO_IN_FILE_OFFSET;
extern const uint32_t HEIGHT_INFO_IN_FILE_OFFSET;



typedef struct sBMPFile{
    FILE* file;  
    uint64_t BMP_file_size; 
    uint64_t BMP_width;
    uint64_t BMP_height; 
    uint64_t BMP_padding;
    uint64_t BMP_starting_address_of_data;
} BMPFile;


BMPFile* init_BMP_file(char* filename);

uint8_t* read_BMP_data(BMPFile* bmp_file);

void print_BMP_file_info(BMPFile* bmp_file);

void clear_BMP_file(BMPFile* bmp_file);
