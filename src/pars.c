#include "inc/pars.h"

uint8_t pars_file(uint8_t* line) {
    uint8_t comand[COMAD_SIZE][6] = {
        {"dyR"},
        {"dyG"},
        {"dyB"},
        {"r"},
        {"pix"},
        {"print"},
        {"sbuff"},
        {"stm"},
        {"sstem"},
        {"spi"},
        {"m"},
    };
    for (uint8_t i = 0; i < COMAD_SIZE; i++) {
        for (uint8_t j = 0; j < strlen(comand[i]); j++ ) {
            if (line[j] != comand[i][j]) {
                i++;
                j = 0;
                if (i == COMAD_SIZE) {
                    return NO;
                }
            } if (j+1 == strlen(comand[i]) && line[j] == comand[i][j]) {
                return i+1;
            }
        }
    }
    return NO;
}

