#ifndef EXE_H
#define EXE_H

#include "defins.h"

void draw_image(uint8_t* buf, const uint8_t *name, uint16_t res);

void draw_pixle(uint8_t* buf, uint8_t x, uint8_t y, uint8_t color);

uint8_t pars_file(uint8_t* line);

#endif
