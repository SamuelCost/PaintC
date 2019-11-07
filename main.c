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
    char *arguments[100];
} PPMPrimitive;

PPMImage *imageGlobal;

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

char *removeBreakLine(char *string){
    size_t sizeLine = strlen(string) - 1;
    if (*string && string[sizeLine] == '\n') {
        string[sizeLine] = '\0';
    }
    return string;
}

void open(char *fileName) {
    imageGlobal = (PPMImage *)malloc(sizeof(PPMImage));
    char line[100];
    int lineIndex = -1;

    FILE *arq;
    arq = fopen(fileName, "r");

    if (arq == NULL) {
        printf("Problemas na abertura do arquivo '%s'\n", fileName);
        exit(0);
    }

    // armazena o fileName na struct image global
    imageGlobal->fileName = fileName;

    // ler todas as linhas da imagem PPM
    while (fgets(line, 100, arq) != NULL){
        char delimiter[] = " "; // delimitador de argumentos
        char *lineArgument = strtok(line, delimiter);
        char *lineArguments[100];
        int lineArgumentIndex = -1;
        // extrai os argumentos de cada linha delimitando pelo espaço entre eles
        while (lineArgument != NULL) {
            lineArgumentIndex++;
            lineArguments[lineArgumentIndex] = lineArgument;
            lineArgument = strtok(NULL, delimiter);
        }

        lineIndex++;
        // armazena o typeEncoding na struct image global
        if (lineIndex == 0) {
            imageGlobal->typeEncoding = lineArguments[0];
        }
        // armazena o x e y (dimensões) na struct image global
        if (lineIndex == 1) {
            imageGlobal->x = atoi(lineArguments[0]);
            imageGlobal->y = atoi(lineArguments[1]);
            imageGlobal->matrizDePixels = (PPMPixel*)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
        }
        // armazena o maxRGBRange na struct image global
        if (lineIndex == 2) {
            imageGlobal->maxRGBRange = atoi(lineArguments[0]);
        }
        // armazena os pixels na struct image global
        // lineIndex - 3: a matriz de pixels começa a contar a partir da terceira linha
        if (lineIndex > 2) {
            imageGlobal->matrizDePixels[lineIndex - 3].r = atoi(lineArguments[0]);
            imageGlobal->matrizDePixels[lineIndex - 3].g = atoi(lineArguments[1]);
            imageGlobal->matrizDePixels[lineIndex - 3].b = atoi(lineArguments[2]);
        }
    }

    fclose(arq);
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

void checkPrimitive(char *primitiveName, char *fileName){
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
        open(fileName);
    }
}

void extractArgumentsPrimitive(char *primitiveLine) {
	char delimiter[] = " ";
	char *primitiveArgument = strtok(primitiveLine, delimiter);
    char *primitiveArguments[10];
    int i = -1;

    while (primitiveArgument != NULL) {
        i++;
        primitiveArguments[i] = removeBreakLine(primitiveArgument);
        printf("\nLine size %s", removeBreakLine(primitiveArgument));
		primitiveArgument = strtok(NULL, delimiter);
	}

    checkPrimitive(primitiveArguments[0], primitiveArguments[1]);
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