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
    backgroundColor->r = r;
    backgroundColor->g = g;
    backgroundColor->b = b;
    for (int i = 0; i < imageGlobal->x * imageGlobal->y; i++){
        imageGlobal->matrizDePixels[i].r = r;
        imageGlobal->matrizDePixels[i].g = g;
        imageGlobal->matrizDePixels[i].b = b;
    }
}

void fill(int x, int y){
    int borda = 0;
    int i = (y * imageGlobal->y) - x;
    for (i; i < imageGlobal->x * imageGlobal->y; i++){
        if (backgroundColor->r == imageGlobal->matrizDePixels[i].r && backgroundColor->g == imageGlobal->matrizDePixels[i].g && backgroundColor->b == imageGlobal->matrizDePixels[i].b){
            if (borda != 1){
                imageGlobal->matrizDePixels[i].r = 90;
                imageGlobal->matrizDePixels[i].g = 172;
                imageGlobal->matrizDePixels[i].b = 68; 
            }
        }else{
            if (borda == 1){
                borda = 0;
            }else{
                borda = 1;
            }
        }

    }
    for(i = 0; i < ((y * imageGlobal->y) - x); i++){
        if (backgroundColor->r == imageGlobal->matrizDePixels[i].r && backgroundColor->g == imageGlobal->matrizDePixels[i].g && backgroundColor->b == imageGlobal->matrizDePixels[i].b){
            if (borda != 1){
                imageGlobal->matrizDePixels[i].r = 90;
                imageGlobal->matrizDePixels[i].g = 172;
                imageGlobal->matrizDePixels[i].b = 68; 
            }
        }else{
            if (borda == 1){
                borda = 0;
            }else{
                borda = 1;
            }
        }

    }
}

void image(int x, int y) {
    imageGlobal->x = x;
    imageGlobal->y = y;

    imageGlobal->matrizDePixels = (PPMPixel *)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
    imageRotate->matrizDePixels = (PPMPixel *)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
    clear(255, 255, 255);
}

void rotate (){
    printf("teste");
    imageRotate->matrizDePixels = imageGlobal->matrizDePixels;
    imageRotate->x = imageGlobal->y;
    imageRotate->y = imageGlobal->x;

    int i = 0;
    int j = imageGlobal->x;
    int aux, count = 0;
    for (i; i < imageGlobal->y; i++){
        for (j; j > 0; j--){
            
            aux = i + ((j-1)*imageGlobal->y);
            printf("%i", aux);
            imageRotate->matrizDePixels[count].r = imageGlobal->matrizDePixels[aux].r;
            imageRotate->matrizDePixels[count].g = imageGlobal->matrizDePixels[aux].g;
            imageRotate->matrizDePixels[count].b = imageGlobal->matrizDePixels[aux].b;
            count += 1;
        }
    }
    imageGlobal->x = imageRotate->x;
    imageGlobal->y = imageRotate->y;
    for (i = 0; i < imageGlobal->x * imageGlobal->y; i++){
        imageGlobal->matrizDePixels[i].r = imageRotate->matrizDePixels[i].r;
        imageGlobal->matrizDePixels[i].g = imageRotate->matrizDePixels[i].g;
        imageGlobal->matrizDePixels[i].b = imageRotate->matrizDePixels[i].b; 
    }

}

/* 1  2  3  4  5     posiçãoRotação = i + ((j-1) * (y));
6  7  8  9  10
11 12 13 14 15

11 6  1
12 7  2
13 8  3
14 9  4
15 10 5 */

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

void polygon(char **arguments){
    int p1 = 1, p2 = 2, p3 = 3, p4 = 4;
    int sides = atoi(arguments[0]);
    for (int i = 0; i < sides - 1; i++){
        line(atoi(arguments[p1]), atoi(arguments[p2]), atoi(arguments[p3]), atoi(arguments[p4]));
        p1 = p3;
        p2 = p4;
        p3 += 2;
        p4 += 2;
    }
    p1 = 1;
    p2 = 2;
    p3 -= 2;
    p4 -= 2;
    line(atoi(arguments[p3]), atoi(arguments[p4]), atoi(arguments[p1]), atoi(arguments[p2]));
}