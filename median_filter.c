// definitions of functions
#include "median_filter.h"
// malloc, free
#include <stdlib.h>
// memcopy
#include <string.h>
// printf
#include <stdio.h>


uint8_t* median_filter(
    uint8_t* original_data,  
    uint64_t starting_address_of_data, 
    uint64_t width, 
    uint64_t height, 
    uint64_t padding,
    uint64_t image_full_size,
    uint8_t filter_width, 
    uint8_t filter_height
){
    
    // allocate table for pixels
    uint32_t filter_size = filter_width * filter_height;
    uint8_t* filter_pixels_table;  
    filter_pixels_table = (uint8_t*) malloc(filter_size * sizeof(uint8_t));
    
    // get only pixel data
    uint8_t* pixel_data = get_pixel_data(
        original_data, 
        starting_address_of_data, 
        width,
        height,
        padding
    );
    
    
    // produce data for result image
    uint8_t* result_data = produce_image(
        pixel_data,
        original_data,
        starting_address_of_data, 
        width,
        height,
        padding, 
        image_full_size
    ); 
    
    free(pixel_data);
    free(filter_pixels_table);
    
    return result_data;
}

uint8_t* get_pixel_data(
    uint8_t* image_data,
    uint64_t starting_address_of_data, 
    uint64_t width, 
    uint64_t height, 
    uint64_t padding
){
    // allocate memory for result data
    uint8_t* result_pixel_data;
    uint64_t result_data_size = width * height * 3;
    result_pixel_data = (uint8_t*) malloc(result_data_size * sizeof(uint8_t));
    
    for (uint64_t i=0; i<height; ++i){
        for(uint64_t k=0; k<width; ++k){
            // address of pixel in original image
            uint64_t pixel_address_in_image = 
                (width*3+padding)*i + k*3 + starting_address_of_data;
            
            // address of pixel in result pixel data
            uint64_t pixel_address_in_data = (width*i + k)*3;
            
            
            // copy pixel
            for(uint8_t l = 0; l<3; ++l){
                result_pixel_data[pixel_address_in_data + l] = 
                    image_data[pixel_address_in_image + l];
            }
        }
    }
    
    return result_pixel_data;
}

uint8_t* produce_image(
    uint8_t* pixel_data, 
    uint8_t* original_data,
    uint8_t starting_address_of_data,  
    uint64_t width, 
    uint64_t height, 
    uint64_t padding, 
    uint64_t image_size
){
    // allocate memory for result image
    uint8_t* result_data;
    result_data = malloc(image_size * sizeof(uint8_t));
    
    // copy header from original_data to pixel_data
    for (uint64_t i = 0; i<starting_address_of_data; ++i){
        result_data[i] = original_data[i];
    }
    
    // copy pixels from pixel_data to result_data padding is omitted
    for (uint64_t i=0; i<height; ++i){
        for(uint64_t k=0; k<width; ++k){
            
            // address of pixel in pixel_data
            uint64_t pixel_address_in_data = (width*i + k)*3;
            
            // address of pixel in result image data
            uint64_t pixel_address_in_image = 
                (width*3+padding)*i + k*3 + starting_address_of_data;
            
            
            for(uint8_t l = 0; l<3; ++l){
                result_data[pixel_address_in_image + l] = 
                    pixel_data[pixel_address_in_data + l];
            }
        }
    }
    
    return result_data;
}

void printf_pixel_data(
    uint8_t* pixel_data,
    uint64_t width, 
    uint64_t height
){
    for (uint64_t i=0; i<height; ++i){
        for(uint64_t k=0; k<width; ++k){
            uint64_t pixel_address = (width*i + k)*3;
            printf(
                "(%d %d %d)", 
                pixel_data[pixel_address], 
                pixel_data[pixel_address+1], 
                pixel_data[pixel_address+2]
            );  
        }
        printf("\n");
    }
}



void pixel_selection_sort(uint8_t* table, uint64_t size); 
