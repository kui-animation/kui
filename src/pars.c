#include "inc/pars.h"

uint8_t pars_file(uint8_t* line) {
        if (line[0] == 'c') {
            if (line[1] != 'o') { return 0; } 
            if (line[2] != 'l') { return 0; }
            return COL;
        } else if (line[0] == 'r') {
            return R; } else if (line[0] == 'p') { if (line[1] == 'i') { if (line[2] != 'x') { return 0; }
                return PIX;
            }
            if (line[1] == 'r') {
                if (line[2] != 'i') { return 0; }
                if (line[3] != 'n') { return 0; }
                if (line[4] != 't') { return 0; }
                return PRINT;
            }
        } else if (line[0] == 's') {
            if (line[1] == 'b') {
                if (line[2] != 'u') { return 0; }
                if (line[3] != 'f') { return 0; }
                if (line[4] != 'f') { return 0; }
                return SBUFF;
            } else if (line[1] == 't') {
                if (line[2] != 'm') { return 0; }
                return STM;
            } else if (line[1] == 's') {
                if (line[2] != 't') { return 0; }
                if (line[3] != 'e') { return 0; }
                if (line[4] != 'm') { return 0; }
                return SSTEM;
            } else if (line[1] == 'p') {
                if (line[2] != 'i') { return 0; }
                return SPI;
            }
        } else return NO;
}

