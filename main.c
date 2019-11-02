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

void commandInOperation(char *primitive){
    if (strcmp(primitive, "image") == 0){
        printf("teste");
    }
    if (strcmp(primitive, "color") == 0){

    }
    if (strcmp(primitive, "clear") == 0){

    }
    if (strcmp(primitive, "rect") == 0){

    }
    if (strcmp(primitive, "circle") == 0){

    }
    if (strcmp(primitive, "polygon") == 0){

    }
    if (strcmp(primitive, "fill") == 0){

    }
    if (strcmp(primitive, "save") == 0){

    }
    if (strcmp(primitive, "open") == 0){

    }
}

void checkPrimitive(char *line) {
    char primitiva[100];
    int j = 0, i=0;
    //for(int i = 0; i < strlen(palavras); i++){
    while(line[i] != ' '){
        primitiva[j] = line[i];
        j++;
        i++;
    }
    printf("%s", primitiva);
    commandInOperation(primitiva);
}

int main(){  
    char Linha[100];
    char palavras[100];
    int i = 0, contador = 0;
  
    FILE *arq;
    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("ArqTeste.txt", "r");
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return(0);
    }
    while (fgets(Linha, sizeof Linha, arq) != NULL){
	    strcpy(palavras, Linha);
        checkPrimitive(palavras);
    }
  fclose(arq);
}