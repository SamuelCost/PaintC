void makeDefaultPPMImageGlobal() {
    imageGlobal = (PPMImage *)malloc(sizeof(PPMImage));
    ppmColor = (PPMColor *)malloc(sizeof(PPMColor));

    imageGlobal->x = 400;
    imageGlobal->y = 200;
    imageGlobal->maxRGBRange = 255;
    imageGlobal->fileName = "image.ppm";
    imageGlobal->typeEncoding = "P3";
    ppmColor->r = 255;
    ppmColor->g = 0;
    ppmColor->b = 0;
}

char *removeBreakLine(char *string){
    unsigned int sizeLine = strlen(string) - 1;
    if (*string && string[sizeLine] == '\n') {
        string[sizeLine] = '\0';
    }
    return string;
}

void color(int r, int g, int b) {
    ppmColor->r = r;
    ppmColor->g = g;
    ppmColor->b = b;
}

void clear(int r, int g, int b) {
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
    clear(0, 0, 0);
}

void save(char * fileName) {
    FILE *fn;

    fn = fopen(fileName, "w+");

    // constrói o cabeçalho do PPM 
    fprintf(fn, "%s\n", imageGlobal->typeEncoding); // type enconding image
    fprintf(fn, "%d %d\n", imageGlobal->x, imageGlobal->y); // dimension image
    fprintf(fn, "%d\n", imageGlobal->maxRGBRange); // max RGB value

    // atribui uma cor padrão a todos os pixels da imagem, como foi lido na ordem inversa, é escrito invertido
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
        // armazena os pixels na ordem inversa
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

int drawPixelPPM(int x, int y) {
    int pixelPosition = (y * imageGlobal->y) - x;
    imageGlobal->matrizDePixels[pixelPosition].r = ppmColor->r;
    imageGlobal->matrizDePixels[pixelPosition].g = ppmColor->g;
    imageGlobal->matrizDePixels[pixelPosition].b = ppmColor->b;
}

void line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = (dx > dy ? dx : -dy) / 2, e2 = 0;

    int maxPixelSteps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    for (int i = 0; i <= maxPixelSteps; i++) {
        drawPixelPPM(x0, y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void drawCircle(int xc, int yc, int x, int y) { 
    drawPixelPPM(xc+x, yc+y); 
    drawPixelPPM(xc-x, yc+y); 
    drawPixelPPM(xc+x, yc-y); 
    drawPixelPPM(xc-x, yc-y); 
    drawPixelPPM(xc+y, yc+x); 
    drawPixelPPM(xc-y, yc+x); 
    drawPixelPPM(xc+y, yc-x); 
    drawPixelPPM(xc-y, yc-x); 
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