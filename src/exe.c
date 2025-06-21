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
    for (uint32_t j = 0; j < (res*res)*3; j++) {
        fprintf(img, "%c", (char)buf[j]);
    }

    fclose(img);
}

void draw_pixle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t* color, uint16_t res_w) {

    uint16_t offset = (res_w*y)+x;
    buf[offset*3] = color[2];
    buf[offset*3+1] = color[1];
    buf[offset*3+2] = color[0];    
    

}
void draw_rectengle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t* color, uint16_t res_w) {
    for (uint8_t i = 0; i < h; i++) {
        for (uint8_t j = 0; j < w; j++) {
            draw_pixle(buf, j+x, i+y, color, res_w);
        }
    }
}

void draw_stemp(uint8_t* stemp, uint8_t* buf, uint8_t x, uint8_t y, uint8_t stemp_res_w, uint16_t res_w) {
    for (uint8_t i = 0; i < stemp_res_w; i++) {
        for (uint8_t j = 0; j < stemp_res_w; j++) {
            uint16_t offset = (stemp_res_w*(i))+(j);
            uint8_t color[3] = {stemp[offset*3+2], stemp[offset*3+1], stemp[offset*3]};
            draw_pixle(buf, j+x, i+y, color, 32);
        }
    }
}

void set_buffer(uint8_t* buf, uint8_t* color, uint16_t res) {
    for (uint16_t i = 0; i < res; i++) {
        buf[i*3] = color[2];
        buf[i*3+1] = color[1];
        buf[i*3+2] = color[0];
    }
}

void draw_points(uint8_t* buf, uint8_t* name, uint8_t* color, uint16_t res_w) {
    FILE *obj = fopen(name, "r");
    if (!obj) {
        return;
    }
    uint16_t v_amount = 4;
    uint8_t line[255];
    float *v = malloc(v_amount*3*sizeof(float));
    uint16_t line_number = 0;

    while (fgets(line, 255, obj)) {
        if (line_number >= v_amount) {
            v_amount = line_number+2;
            float *tmp_v = realloc(v, v_amount*3*sizeof(float));
            if (!tmp_v) {
                free(v);
                fclose(obj);
                return;
            }
            v = tmp_v;
        }
        float x, y, z;
        if (line[0] != 'v') {
            continue;
        }
        line[0] = ' ';
        if (sscanf(line, "%f %f %f", &x, &y, &z) != 3) {
            continue; // skip invalid lines
        }

        v[line_number * 3 + 0] = x*10;
        v[line_number * 3 + 1] = -y*10;
        v[line_number * 3 + 2] = z*10;

        line_number ++;
    }
    fclose(obj);

    float r_angle = 23.5*(PI/180.0);
    for (int i = 0; i < line_number; i++) {
        float tmp_x = v[i*3];
        float tmp_y = v[i*3+1];
        float z = v[i*3+2];
        uint8_t x = tmp_x + 1/2.0*z*cos(r_angle);
        uint8_t y = tmp_y + 1/2.0*z*sin(r_angle);
        draw_pixle(buf, x+res_w/2, y+res_w/2, color, res_w);
    }

    free(v);
}