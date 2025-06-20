#include "inc/exe.h"

void draw_image(uint8_t* buf, const uint8_t *name, uint16_t res) {
    uint8_t head[18] = {0};
    
    head[0x2] = 0x02;
    head[0xC] = 0x20;
    head[0xE] = 0x20;
    head[0x10] = 0x18;
    head[0x11] = 0x20;

    FILE *img = fopen(name, "w");
    if (!img) {
        fprintf(stderr, "file cand crat");
        return;
    }
    for (uint8_t i = 0; i < 18; i++) { 
        fprintf(img, "%c", (char)head[i]);
    }
    for (uint16_t j = 0; j < res; j++) {
        fprintf(img, "%c%c%c", (char)buf[j], (char)buf[j], (char)buf[j]);
    }

    fclose(img);
}

void draw_pixle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t color) {

    uint16_t offset = (32*y)+x;
    buf[offset] = color;    
    

}



