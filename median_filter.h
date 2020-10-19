// for uin8_t, uint_32 itp.
#include <stdint.h>


typedef struct sPixel{
    float brightness;
    uint8_t pixel_colors[3];
} Pixel;


/**
 * Median filter algorithm. As input it takes pixel data and filter size. It uses 
 * simple selection sort for choosing pixel with middle brightness value.
 * 
 * @param image_data Data on which will be applied median filter. 
 * @param image_width Width of image data.
 * @param image_height Height of image data.
 * @param filter_width Width of filter. 
 * @param filter_height Height of filter.
 * 
 * @return Image data with applied median filter.
 */

uint8_t* median_filter(
    uint8_t* image_data,  
    uint64_t image_width, 
    uint64_t image_height, 
    uint8_t filter_width, 
    uint8_t filter_height
);

void pixel_selection_sort(uint8_t* table, uint64_t size);

/**
 * Iterate over 2D table of image data and print pixels as three values. 
 * 
 * @param image_data Image data to print.
 * @param image_width Width of image data. 
 * @param image_height Height of image data.
 */
void printf_image_data(
    uint8_t* image_data,
    uint64_t image_width, 
    uint64_t image_height
);


