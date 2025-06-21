#ifndef EXE_H
#define EXE_H

#include "defins.h"

void draw_image(uint8_t* buf, const uint8_t *name, uint8_t res);
void draw_pixle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t* color, uint16_t res_w);
void draw_rectengle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t* color, uint16_t res_w);
void draw_stemp(uint8_t* stemp, uint8_t* buf, uint8_t x, uint8_t y, uint8_t stemp_res_w, uint16_t res_w);
void set_buffer(uint8_t* buf, uint8_t* color, uint16_t res);
void draw_points(uint8_t* buf, uint8_t* name, uint8_t* color, uint16_t res_w);
#endif
