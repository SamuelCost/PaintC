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

PPMImage *imageGlobal;

void makeDefaultPPMImageGlobal() {
    imageGlobal = (PPMImage *)malloc(sizeof(PPMImage));

    imageGlobal->x = 400;
    imageGlobal->y = 200;
    imageGlobal->maxRGBRange = 255;
    imageGlobal->fileName = "image.ppm";
    imageGlobal->typeEncoding = "P3";
}

char *removeBreakLine(char *string){
    unsigned int sizeLine = strlen(string) - 1;
    if (*string && string[sizeLine] == '\n') {
        string[sizeLine] = '\0';
    }
    return string;
}

void drawAllPixels() {
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < imageGlobal->x * imageGlobal->y; i++){
        imageGlobal->matrizDePixels[i].r = r;
        imageGlobal->matrizDePixels[i].g = g;
        imageGlobal->matrizDePixels[i].b = b;
    }
}

void image(int x, int y) {
    imageGlobal->x = x;
    imageGlobal->y = y;

    imageGlobal->matrizDePixels = (PPMPixel *)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
    drawAllPixels();
}

void save(char * fileName) {
    FILE *fn;

    fn = fopen(fileName, "w+");

    // constrói o cabeçalho do PPM 
    fprintf(fn, "%s\n", imageGlobal->typeEncoding); // type enconding image
    fprintf(fn, "%d %d\n", imageGlobal->x, imageGlobal->y); // dimension image
    fprintf(fn, "%d\n", imageGlobal->maxRGBRange); // max RGB value

    // atribui uma cor padrão a todos os pixels da imagem
    for (int i = (imageGlobal->x * imageGlobal->y) - 1; i >= 0 ; i--){
        fprintf(fn,"%d %d %d\n", imageGlobal->matrizDePixels[i].r, imageGlobal->matrizDePixels[i].g, imageGlobal->matrizDePixels[i].b);
    }

    fclose(fn);
}

void open(char *fileName) {
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
            imageGlobal->typeEncoding = (char *)malloc(sizeof(char));
            strcpy(imageGlobal->typeEncoding, removeBreakLine(lineArguments[0]));
        }
        // armazena o x e y (dimensões) na struct image global
        if (lineIndex == 1) {
            imageGlobal->x = atoi(lineArguments[0]);
            imageGlobal->y = atoi(lineArguments[1]);
            imageGlobal->matrizDePixels = (PPMPixel *)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
        }
        // armazena o maxRGBRange na struct image global
        if (lineIndex == 2) {
            imageGlobal->maxRGBRange = atoi(lineArguments[0]);
        }
        // armazena os pixels na struct image global
        // lineIndex - 3: a matriz de pixels começa a contar a partir da terceira linha
        if (lineIndex > 2) {
            int pixelsSize = imageGlobal->x * imageGlobal->y;
            int index = pixelsSize - (lineIndex - 3);
            imageGlobal->matrizDePixels[index].r = atoi(lineArguments[0]);
            imageGlobal->matrizDePixels[index].g = atoi(lineArguments[1]);
            imageGlobal->matrizDePixels[index].b = atoi(lineArguments[2]);
        }
    }

    fclose(arq);
}

int drawPixelPPM(int pixelPosition, int x, int y) {
    if (pixelPosition == -1) {
        printf("\nCircle: x, y (%d, %d)", x, y);
        pixelPosition = (y * imageGlobal->y) - x;
        printf("\nPosition: (%d)", pixelPosition);
    } else {
        printf("\nLine: x, y (%d, %d)", x, y);
        printf("\nPosition: (%d)", pixelPosition);
    }
    int r = 255, g = 0, b = 0;
    imageGlobal->matrizDePixels[pixelPosition].r = r;
    imageGlobal->matrizDePixels[pixelPosition].g = g;
    imageGlobal->matrizDePixels[pixelPosition].b = b;
}

int getPixelPosition(int x, int y) {
    int rowSize = 0;
    for (int i = imageGlobal->y; i > y; i--) {
        rowSize++;
    }
    return rowSize * imageGlobal->y + x;
}

void line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy) / 2, e2 = 0;

    int maxPixelSteps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    for (int i = 0; i <= maxPixelSteps; i++) {
        int pixelPosition = y0 * imageGlobal->y - x0;
        drawPixelPPM(pixelPosition, -1, -1);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void drawCircle(int xc, int yc, int x, int y) { 
    drawPixelPPM(-1, xc+x, yc+y); 
    drawPixelPPM(-1, xc-x, yc+y); 
    drawPixelPPM(-1, xc+x, yc-y); 
    drawPixelPPM(-1, xc-x, yc-y); 
    drawPixelPPM(-1, xc+y, yc+x); 
    drawPixelPPM(-1, xc-y, yc+x); 
    drawPixelPPM(-1, xc+y, yc-x); 
    drawPixelPPM(-1, xc-y, yc-x); 
} 

void cicle(int xc, int yc, int r) { 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    drawCircle(xc, yc, x, y); 
    while (y >= x) { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } else {
            d = d + 4 * x + 6; 
        }
        drawCircle(xc, yc, x, y); 
    } 
}

void checkPrimitive(char *name, char *arguments[100]){
    if (strcmp(name, "image") == 0){
        image(atoi(arguments[0]), atoi(arguments[1]));
    }
    if (strcmp(name, "color") == 0){

    }
    if (strcmp(name, "clear") == 0){

    }
    if (strcmp(name, "rect") == 0){

    }
    if (strcmp(name, "circle") == 0){
        cicle(atoi(arguments[0]), atoi(arguments[1]), atoi(arguments[2]));
    }
    if (strcmp(name, "polygon") == 0){

    }
    if (strcmp(name, "fill") == 0){

    }
    if (strcmp(name, "save") == 0){
        save(arguments[0]);
    }
    if (strcmp(name, "line") == 0){
        line(atoi(arguments[0]), atoi(arguments[1]), atoi(arguments[2]), atoi(arguments[3]));
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

void readPrimitesFile() {
    char primitiveLine[100];
  
    FILE *arq;
    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("primitives", "r");
    // Se houve erro na abertura
    if (arq == NULL) {
        printf("Problemas na abertura do arquivo\n");
        exit(0);
    }
    while (fgets(primitiveLine, 100, arq) != NULL){
        extractArgumentsPrimitive(primitiveLine);
    }
    fclose(arq);
}

int main(){
    makeDefaultPPMImageGlobal();
    readPrimitesFile();
}


/* 

0 0 0
0 0 0
0 0 0

*/