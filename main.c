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

typedef struct {
    char *primitiveName;
    char *arguments[10];
} PPMPrimitive;

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

void checkPrimitive(char *primitiveName){
    if (strcmp(primitiveName, "image") == 0){
        printf("Finded image primitive \n");
    }
    if (strcmp(primitiveName, "color") == 0){

    }
    if (strcmp(primitiveName, "clear") == 0){

    }
    if (strcmp(primitiveName, "rect") == 0){

    }
    if (strcmp(primitiveName, "circle") == 0){

    }
    if (strcmp(primitiveName, "polygon") == 0){

    }
    if (strcmp(primitiveName, "fill") == 0){

    }
    if (strcmp(primitiveName, "save") == 0){

    }
    if (strcmp(primitiveName, "open") == 0){

    }
}

void extractArgumentsPrimitive(char *primitiveLine) {
	char delimiter[] = " ";
	char *primitiveName = strtok(primitiveLine, delimiter);
    char *argument = strtok(primitiveLine, delimiter);
    char *arguments[10];
    int index = 0;
    
    checkPrimitive(primitiveName);

    while (argument != NULL) {
		argument = strtok(NULL, delimiter);
        printf("\n%s", argument);
	} 
}

int main(){  
    char primitiveLine[100];
  
    FILE *arq;
    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("ArqTeste.txt", "r");
    // Se houve erro na abertura
    if (arq == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return(0);
    }
    while (fgets(primitiveLine, 100, arq) != NULL){
        extractArgumentsPrimitive(primitiveLine);
    }
    fclose(arq);
}