#include "inc/defins.h"
#include "inc/exe.h"
#include "inc/pars.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "add a file name\n");
        return 1;
    }
    
    uint8_t* line= malloc(255*sizeof(uint8_t));
    if (!line) {
        fprintf(stderr, "coden alocat memory to line\n");
        return 1;
    }
    uint8_t* buf = malloc(RES*sizeof(uint8_t));
    if (!buf) {
        free(line);
        fprintf(stderr, "coden alocat memory to buf\n");
        return 1;
    }
    uint8_t* stemp = malloc(64*sizeof(uint8_t));
    if (!stemp) {
        free(buf);
        free(line);
        fprintf(stderr, "coden alocat memory to buf\n");
        return 1;
    }


    FILE* file = fopen(argv[1], "r");
    if (!file) {
        free(line);
        free(buf);
        fprintf(stderr, "coden open file %s\n", argv[1]);
        return 1;
    }
    uint32_t line_index = 0;
    uint32_t image_num = 1;
    uint8_t color = 0;
    memset(buf, (char)color, RES);
    while (fgets(line, 7, file)) {
        switch(pars_file(line)) {
        case NO:
            printf("%d\n", line_index);
            break;
        case PRINT:
            uint8_t name[16];
            sprintf(name, "img/%d.tga", image_num);
            draw_image(buf, name,  RES_H);
            printf("%d print\n", line_index);
            image_num ++;
            break;
        case COL:
            color = line[3]+line[4];
            printf("%d color\n", line_index);
            break;
        case R:
            draw_rectengle(buf, line[1]-65,line[2]-65,line[3]-64,line[4]-64, color, RES_W);
            printf("%d rect\n", line_index);
            break;
        case PIX:
            draw_pixle(buf, (int)line[3]-65, (int)line[4]-65, color, RES_W);
            printf("%d pixel\n", line_index);
            break;
        case SBUFF:
            memset(buf, (char)color, RES);
            printf("%d set buffer\n", line_index);
            break;
        case STM:
            draw_stemp(stemp, buf,  (int)line[3]-65, (int)line[4]-65, 8, RES_W);
            printf("%d stemp\n", line_index);
            break;
        case SSTEM:
            memset(stemp, (char)color, 64);
            printf("%d set stemp\n", line_index);
            break;
        case SPI:
            draw_pixle(stemp, (int)line[3]-65, (int)line[4]-65, color, 8);
            printf("%d setmp pixel\n", line_index);
            break;
        }
        line_index ++;
    }

    free(line);
    free(stemp);
    free(buf);
    fclose(file);
    
    return 0;
}
