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
    char *name;
    char *arguments[100];
} PPMPrimitive;

PPMImage *imageGlobal;

void image(int x, int y) {
    imageGlobal->matrizDePixels = (PPMPixel*)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
}

void save(char * fileName) {
    FILE *fn;

    fn = fopen(fileName, "w+");

    imageGlobal->matrizDePixels = (PPMPixel*)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));

    // constrói o cabeçalho do PPM 
    fprintf(fn, "%s\n", imageGlobal->typeEncoding); // type enconding image
    fprintf(fn, "%d %d\n", imageGlobal->x, imageGlobal->y); // dimension image
    fprintf(fn, "%d\n", imageGlobal->maxRGBRange); // max RGB value

    // atribui uma cor padrão a todos os pixels da imagem
    for (int i = 0; i < imageGlobal->x * imageGlobal->y; i++){
        imageGlobal->matrizDePixels[i].r = 255;
        imageGlobal->matrizDePixels[i].g = 0;
        imageGlobal->matrizDePixels[i].b = 0;

        fprintf(fn,"%d %d %d\n", imageGlobal->matrizDePixels[i].r, imageGlobal->matrizDePixels[i].g, imageGlobal->matrizDePixels[i].b);
    }

    fclose(fn);
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
        printf("\nProblemas na abertura do arquivo '%s'", fileName);
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

void makeDefaultPPMImageGlobal() {
    imageGlobal->x = 400;
    imageGlobal->y = 200;
    imageGlobal->maxRGBRange = 255;
    imageGlobal->fileName = "image.ppm";
    imageGlobal->typeEncoding = "P3";
}

void checkPrimitive(char *name, char *arguments[100]){
    if (strcmp(name, "image") == 0){
        printf("Finded image primitive \n");
    }
    if (strcmp(name, "color") == 0){

    }
    if (strcmp(name, "clear") == 0){

    }
    if (strcmp(name, "rect") == 0){

    }
    if (strcmp(name, "circle") == 0){

    }
    if (strcmp(name, "polygon") == 0){

    }
    if (strcmp(name, "fill") == 0){

    }
    if (strcmp(name, "save") == 0){

    }
    if (strcmp(name, "open") == 0){
        open(arguments[0]);
    }
}

void extractArgumentsPrimitive(char *primitiveLine) {
	char delimiter[] = " ";
	char *primitiveName = strtok(primitiveLine, delimiter);
	char *primitiveArgument = strtok(NULL, delimiter);
    char *primitiveArguments[100];
    int i = -1;

    while (primitiveArgument != NULL) {
        i++;
        primitiveArguments[i] = removeBreakLine(primitiveArgument);
		primitiveArgument = strtok(NULL, delimiter);
	}

    checkPrimitive(primitiveName, primitiveArguments);
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