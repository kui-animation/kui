#include "inc/exe.h"

void draw_image(uint8_t* buf, const uint8_t *name, uint8_t res) {
    uint8_t head[18] = {0};
    
    head[0x2] = 0x02;
    head[0xC] = res;
    head[0xE] = res;
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
    for (uint16_t j = 0; j < res*res; j++) {
        fprintf(img, "%c%c%c", (char)buf[j], (char)buf[j], (char)buf[j]);
    }

    fclose(img);
}

void draw_pixle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t color, uint16_t res_w) {

    uint16_t offset = (res_w*y)+x;
    buf[offset] = color;    
    

}
void draw_rectengle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color, uint16_t res_w) {
    for (uint8_t i = 0; i < h; i++) {
        for (uint8_t j = 0; j < w; j++) {
            draw_pixle(buf, j+x, i+y, color, res_w);
        }
    }
}

void draw_stemp(uint8_t* stemp, uint8_t* buf, uint8_t x, uint8_t y, uint8_t stemp_res_w, uint16_t res_w) {
    for (uint8_t i = 0; i < stemp_res_w; i++) {
        for (uint8_t j = 0; j < stemp_res_w; j++) {
            uint16_t offset = (stemp_res_w*i)+j;
            draw_pixle(buf, j+x, i+y, stemp[offset], res_w);
        }
    }
}

