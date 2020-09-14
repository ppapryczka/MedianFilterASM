// for uin8_t, uint_32 itp.
#include <stdint.h>


typedef struct sPixel{
    float brightness;
    uint8_t pixel_colors[3];
} Pixel;


uint8_t* median_filter(
    uint8_t* original_data,  
    uint64_t starting_address_of_data, 
    uint64_t width, 
    uint64_t height, 
    uint64_t padding,
    uint64_t image_full_size,
    uint8_t filter_width, 
    uint8_t filter_height
);

uint8_t* get_pixel_data(
    uint8_t* image_data,
    uint64_t starting_address_of_data, 
    uint64_t width, 
    uint64_t height, 
    uint64_t padding
);

uint8_t* produce_image(
    uint8_t* pixel_data, 
    uint8_t* original_data,
    uint8_t starting_address_of_data,  
    uint64_t width, 
    uint64_t height, 
    uint64_t padding, 
    uint64_t image_size
);

void printf_pixel_data(
    uint8_t* pixel_data,
    uint64_t width, 
    uint64_t height
);


void pixel_selection_sort(uint8_t* table, uint64_t size);
