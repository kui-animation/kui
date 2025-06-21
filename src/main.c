#include "inc/defins.h"
#include "inc/exe.h"
#include "inc/pars.h"


int main(int argc, char *argv[]) {
    int res_w, res_h, res;
    if (argc < 3) {
        fprintf(stderr, "not enof imputs\n");
        return 1;
    }

    if (strcmp(argv[2], "--no-conf") == 0) {
        res_w = HIGH;
        res_h = HIGH;
        res = res_h*res_w;
    }

    uint8_t* line= malloc(255*sizeof(uint8_t));
    if (!line) {
        fprintf(stderr, "coden alocat memory to line\n");
        return 1;
    }
    uint8_t* buf = malloc((res*3)*sizeof(uint8_t));
    if (!buf) {
        free(line);
        fprintf(stderr, "coden alocat memory to buf\n");
        return 1;
    }
    uint8_t* stemp = malloc((64*3)*sizeof(uint8_t));
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
    uint32_t line_index = 1;
    uint32_t image_num = 1;
    uint8_t color[3] = {0,0,0};
    set_buffer(buf, color, res);
    while (fgets(line, 7, file)) {
        switch(pars_file(line)) {
        case NO:
            printf("%d\n", line_index);
            break;
        case PRINT:
            uint8_t name[16];
            sprintf(name, "img/%d.tga", image_num);
            draw_image(buf, name, res_w);
            printf("%d print\n", line_index);
            image_num ++;
            break;
        case DYR:
            color[0] = line[3]+line[4];
            printf("%d color_R: %d\n", line_index, color[0]);
            break;
        case DYG:
            color[1] = line[3]+line[4];
            printf("%d color_G: %d\n", line_index, color[1]);
            break;
        case DYB:
            color[2] = line[3]+line[4];
            printf("%d color_B: %d\n", line_index, color[2]);
            break;
        case DYBLE:
            for (uint8_t i = 0; i < 3; i++) {
                color[i] = 0;
            }
            printf("%d color_all: %d\n", line_index, 0);
            break;
        case R:
            draw_rectengle(buf, line[1]-65,line[2]-65,line[3]-64,line[4]-64, color, res_w);
            printf("%d rect\n", line_index);
            break;
        case PIX:
            draw_pixle(buf, (int)line[3]-65, (int)line[4]-65, color, res_w);
            printf("%d pixel\n", line_index);
            break;
        case SBUFF:
            set_buffer(buf, color, res);
            printf("%d set buffer\n", line_index);
            break;
        case STM:
            draw_stemp(stemp, buf, (int)line[3]-65, (int)line[4]-65, 8, res_w);
            printf("%d stemp\n", line_index);
            break;
        case SSTEM:
            set_buffer(stemp, color, 64);
            printf("%d set stemp\n", line_index);
            break;
        case SPI:
            draw_pixle(stemp, (int)line[3]-65, (int)line[4]-65, color, 8);
            printf("%d setmp pixel\n", line_index);
            break;
        case M:
            uint8_t obj_name[16];
            sprintf(obj_name, "obj/%c%c%c%c.obj", line[1], line[2], line[3], line[4]);
            draw_points(buf, obj_name, color, res_w);
            printf("%d model %s\n", line_index, obj_name);
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
