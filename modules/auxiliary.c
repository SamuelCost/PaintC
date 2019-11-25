#include <stdlib.h>

#include "structs.h"

void makeDefaultPPMImageGlobal() {
    imageGlobal = (PPMImage *)malloc(sizeof(PPMImage));
    imageRotate = (PPMImage *)malloc(sizeof(PPMImage));
    ppmColor = (PPMColor *)malloc(sizeof(PPMColor));
    backgroundColor = (PPMColor *)malloc(sizeof(PPMColor));

    imageGlobal->x = 400;
    imageGlobal->y = 200;
    imageGlobal->maxRGBRange = 255;
    imageGlobal->fileName = "image.ppm";
    imageGlobal->typeEncoding = "P3";
    ppmColor->r = 255;
    ppmColor->g = 0;
    ppmColor->b = 0;
    backgroundColor->r = 255;
    backgroundColor->g = 255;
    backgroundColor->b = 255;
}
