#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "and a file name");
        return 1;
    }
    
    uint8_t* line= malloc(255*sizeof(uint8_t));
    if (!line) {
        fprintf(stderr, "coden alocat memory to line\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        free(line);

        fprintf(stderr, "coden open file %s", argv[1]);
        return 1;
    }
    uint32_t line_index = 0;
    uint8_t space_counter = 0;
    while (fgets(line, 7, file)) {
        if (line[0] == 'c') {
            //comper_if_color();
            if (line[1] != 'o') { printf("\n"); continue; } 
            if (line[2] != 'l') { printf("\n"); continue; }
            printf("color\n");
        } else if (line[0] == 'r') {
            printf("rectengle\n");
        } else if (line[0] == 'p') {
            printf("pixel\n");
        } else if (line[0] == 's') {
            if (line[1] == 'b') {
                //comper_if_sbuff();
                if (line[2] != 'u') { printf("\n"); continue; }
                if (line[3] != 'f') { printf("\n"); continue; }
                if (line[4] != 'f') { printf("\n"); continue; }
                printf("set buffer\n");
            } else if (line[1] == 't') {
                //comper_if_stm();
                if (line[2] != 'm') { printf("\n"); continue; }
                printf("stemp\n");
            } else if (line[1] == 's') {
                //comper_if_sstem();
                if (line[2] != 't') { printf("\n"); continue; }
                if (line[3] != 'e') { printf("\n"); continue; }
                if (line[4] != 'm') { printf("\n"); continue; }
                printf("set stemp\n");
            } else if (line[1] == 'p') {
                //comper_if_spi();
                if (line[2] != 'i') { printf("\n"); continue; }
                printf("stemp pixel\n");
            }
        } else printf("\n");
        line_index ++;
    }

    free(line);
    fclose(file);
    
    return 0;
}
