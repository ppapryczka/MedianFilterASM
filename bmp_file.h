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
 *  Format description: https://en.wikipedia.org/wiki/BMP_file_format
 */
extern const uint32_t TABLE_FOR_READ_SIZE;
extern const uint32_t BMP_FILE_SIZE_INFO_IN_FILE_OFFSET;
extern const uint32_t STARTING_ADDRESS_OF_DATA_INFO_IN_FILE_OFFSET;
extern const uint32_t WIDTH_INFO_IN_FILE_OFFSET;
extern const uint32_t HEIGHT_INFO_IN_FILE_OFFSET;

/**
 * Representation of BMP image as pointer to file and set of informations about image.
 */ 
typedef struct sBMPFile{
    FILE* file;  
    uint64_t BMP_file_size; 
    uint64_t BMP_width;
    uint64_t BMP_height; 
    uint64_t BMP_padding;
    uint64_t BMP_starting_address_of_data;
} BMPFile;

/**
 * Load image from location given by path. 
 * 
 * @param filename Path to file where is located image to read.
 * 
 * @return Pointer to BMPFile struct or NULL pointer if error.
 */
BMPFile* init_BMP_file(char* filename);

/**
 * Read data from BMP image. BMP data is a full BMP file data.
 * 
 * @param bmp_file BMP image from which data will be read.
 * 
 * @return Pointer do BMP data or NULL pointer if error.
 */
uint8_t* read_BMP_data(BMPFile* bmp_file);


/**
 * Read BMP image header.
 * 
 * @param bmp_file BMP image as a stuct. 
 * 
 * @return BMP header data. 
 */
uint8_t* read_BMP_header(BMPFile* bmp_file); 

/**
 * Convert BMP data to image data.
 * 
 * @param bmp_file BMP file as struct.
 * @param bmp_data Data read from given BMP file.
 * 
 * @return Image data from given BMP file.
 */
uint8_t* convert_BMP_data_to_image_data(BMPFile* bmp_file, uint8_t* bmp_data);

/**
 * Get image data from BMP file. BMP data contains only image data as BGR value for 
 * each pixel.
 * 
 * @param bmp_file BMP file as a struct.
 * 
 * @return Image data. 
 */
uint8_t* get_image_data_from_BMP_image(BMPFile* bmp_file);

/**
 * Print info about BMP file. 
 * 
 * @param bmp_file BMPFile struct which data will be printed. 
 */
void print_BMP_file_info(BMPFile* bmp_file);

/**
 * Read header from file in given BMP file. Fill data using given image data.
 * 
 * @param bmp_file BMP file as a struct.
 * @param image_data Image data, which is 2D table which holds only BGR values of each
 * pixel.
 * 
 * @return Data for BMP image. 
 */
uint8_t* produce_BMP_file(BMPFile* bmp_file, uint8_t* image_data);

/**
 * Check if given pointer is not NULL, then close file and free memory holded by 
 * given pointer.
 * 
 * @param bmp_file BMPFile to clear. 
 */
void clear_BMP_file(BMPFile* bmp_file);
