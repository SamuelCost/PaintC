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

void checarPrimitiva(char *primitiva, int xInputed, int yInputed, char *fileNameInputed) {
    int x = 600, y = 400, maxRGBRange = 255;
    char *fileName = "image.ppm", *typeEncoding = "P3";

    if (strcmp(primitiva, "image") == 0 && xInputed > 0 && yInputed > 0) {
        x = xInputed;
        y = yInputed;

        PPMImage *image = makeStructPPMImage(x, y, maxRGBRange, fileName, typeEncoding);
        createPPM(image);
    } else {
        if (strcmp(primitiva, "save") == 0 && strcmp(fileNameInputed, "") != 0) {
            fileName = fileNameInputed;
    
            PPMImage *image = makeStructPPMImage(x, y, maxRGBRange, fileName, typeEncoding);
            createPPM(image);
        } else {
            printf("Primitiva inválida");
        }
    }
}

int main(){
    int xInputed = 0, yInputed = 0;
    char *primitiva = "", *fileNameInputed = "";
    
    primitiva = malloc(sizeof(char));
    fileNameInputed = malloc(sizeof(char));

    scanf("%s %s", primitiva, fileNameInputed);

    checarPrimitiva(primitiva, xInputed, yInputed, fileNameInputed);
}