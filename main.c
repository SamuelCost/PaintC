#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct dos pixels em RGB;
typedef struct{
	unsigned int r, g, b;
} PPMPixel;

// struct da image PPM contendo a struct de pixels em RGB;
typedef struct {
     int x, y, maxRGBRange;
     char *fileName, *typeEncoding;
     PPMPixel *matrizDePixels;
} PPMImage;

void createPPM(PPMImage *image) {
    FILE *fn;

    fn = fopen(image->fileName, "w+");

    image->matrizDePixels = (PPMPixel*)malloc(image->x * image->y * sizeof(PPMPixel));

    // constrói o cabeçalho do PPM 
    fprintf(fn, "%s\n", image->typeEncoding); // type enconding image
    fprintf(fn, "%d %d\n", image->x, image->y); // dimension image
    fprintf(fn, "%d\n", image->maxRGBRange); // max RGB value

    // atribui uma cor padrão a todos os pixels da imagem
    for (int i = 0; i < image->x * image->y; i++){
        image->matrizDePixels[i].r = 255;
        image->matrizDePixels[i].g = 0;
        image->matrizDePixels[i].b = 0;

        fprintf(fn,"%d %d %d\n", image->matrizDePixels[i].r, image->matrizDePixels[i].g, image->matrizDePixels[i].b);
    }

    fclose(fn);

    free(image->matrizDePixels);
    free(image);
}

static PPMImage *makeStructPPMImage(int x, int y, int maxRGBRange, char *fileName, char *typeEncoding) {
    PPMImage *image = (PPMImage *)malloc(sizeof(PPMImage));
    image->x = x;
    image->y = y;
    image->maxRGBRange = maxRGBRange;
    image->fileName = fileName;
    image->typeEncoding = typeEncoding;
    return image;
}

void checkPrimitive(int argc, char *argv[]) {
    int x = 600, y = 400, maxRGBRange = 255;
    char *fileName = "image.ppm", *typeEncoding = "P3";
    
    if (argc == 4 && strcmp(argv[1], "image") == 0 && atoi(argv[2]) > 0 && atoi(argv[3]) > 0) {
        x = atoi(argv[2]);
        y = atoi(argv[3]);

        PPMImage *image = makeStructPPMImage(x, y, maxRGBRange, fileName, typeEncoding);
        createPPM(image);
        printf("Primitiva image realizada\n");
    } else {
        if (argc == 3 && strcmp(argv[1], "save") == 0 && strcmp((char *)argv[2], "") != 0) {
            fileName = (char *)argv[2];
    
            PPMImage *image = makeStructPPMImage(x, y, maxRGBRange, fileName, typeEncoding);
            createPPM(image);
            printf("Primitiva save realizada\n");
        } else {
            printf("Primitiva construída de forma incorreta\n");
        }
    }
}

int main(int argc, char *argv[]){
    checkPrimitive(argc, argv);
}