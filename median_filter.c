// definitions of functions
#include "median_filter.h"
// malloc, free
#include <stdlib.h>
// memcopy
#include <string.h>
// printf
#include <stdio.h>


uint8_t* median_filter(
    uint8_t* image_data,  
    uint64_t image_width, 
    uint64_t image_height, 
    uint8_t filter_width, 
    uint8_t filter_height
){
    
}

void printf_image_data(
    uint8_t* image_data,
    uint64_t width, 
    uint64_t height
){
    for (uint64_t i=0; i<height; ++i){
        for(uint64_t k=0; k<width; ++k){
            uint64_t pixel_address = (width*i + k)*3;
            printf(
                "(%d %d %d)", 
                image_data[pixel_address], 
                image_data[pixel_address+1], 
                image_data[pixel_address+2]
            );  
        }
        printf("\n");
    }
}



void pixel_selection_sort(uint8_t* table, uint64_t size); 
