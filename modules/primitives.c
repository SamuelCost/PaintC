/**
 * @file primitives.c
 * @brief Contém as implementações das primitivas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "primitives.h"

/**
* Função auxilixar que remove a quebra de linha no final de um texto
* @param text Texto com quebra de linha final
* @return Texto sem a quebra de linha no final
*/
char *removeBreakLine(char *text){
    unsigned int sizeLine = strlen(text) - 1;
    if (*text && text[sizeLine] == '\n') {
        text[sizeLine] = '\0';
    }
    return text;
}

/**
* Função que muda a cor atual para uma cor especificada, recebendo novos valores em RGB
* @param r Cor relacionada ao vermelho
* @param g Cor relacionada ao verde
* @param b Cor relacionada ao azul
* @details As cores são armazenadas na struct global ppmColor do tipo PPMColor
*/
void color(int r, int g, int b) {
    ppmColor->r = r;
    ppmColor->g = g;
    ppmColor->b = b;
}

/**
* Função que limpa a imagem, setando todos os pixels para a cor especificada, recebendo novos valores em RGB
* @param r Cor relacionada ao vermelho
* @param g Cor relacionada ao verde
* @param b Cor relacionada ao azul
* @details As cores são armazenadas na struct global backgroundColor do tipo PPMColor
*/
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

/**
* Função que criar uma nova “imagem”, com a largura e altura especificadas, recebendo as novos tamanhos de largura e altura
* @param x Largura da imagem PPM
* @param g Altura da imagem PPM
* @details A função além de realocar o novo espaço na memória com base nos valores específicados, redimensiona a imagem e limpa o background para a cor branca
*/
void image(int x, int y) {
    imageGlobal->x = x;
    imageGlobal->y = y;

    imageGlobal->matrizDePixels = (PPMPixel *)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
    imageRotate->matrizDePixels = (PPMPixel *)malloc(imageGlobal->x * imageGlobal->y * sizeof(PPMPixel));
    clear(255, 255, 255);
}

void rotate (){
    imageRotate->x = imageGlobal->y;
    imageRotate->y = imageGlobal->x;

    int i = 0;
    int aux, count = 0;
    for (i; i < imageGlobal->y; i++){
        for (int j = imageGlobal->x; j > 0; j--){

            aux = i + ((j-1)*imageGlobal->y);
            printf("%i ", aux);
            imageRotate->matrizDePixels[count].r = imageGlobal->matrizDePixels[aux].r;
            imageRotate->matrizDePixels[count].g = imageGlobal->matrizDePixels[aux].g;
            imageRotate->matrizDePixels[count].b = imageGlobal->matrizDePixels[aux].b;
            count = count + 1;
        }
        printf("\n");
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

/**
* Função que salvar a imagem atual em um arquivo usando o formato ppm, recebendo o nome do arquivo
* @param fileName Nome do arquivo PPM
* @details A função open ler os pixels na ordem inversa, por isso, salvamos na ordem inversa
*/
void save(char *fileName) {
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

/**
* Função que abre uma imagem no formato ppm e carrega essa imagem no programa para futuras operações de desenho, recebendo o nome do arquivo
* @param fileName Nome do arquivo PPM
* @details A função open ler os pixels na ordem inversa, e seta na struct imageGlobal do tipo PPMImage as informações encontradas no PPM
*/
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

/**
* Função auxiliar que pinta o pixel com base em suas coordenada x, y
* @param x Valor horizontal da coordenada
* @param y Valor vertical da coordenada
* @details Como salvamos e lemos os pixels em um array unidimensional, é necessário encontra o índice equivalente a coordenada x,y a partir da variável pixelPosition
*/
void drawPixelPPM(int x, int y) {
    int pixelPosition = (y * imageGlobal->y) - x;
    imageGlobal->matrizDePixels[pixelPosition].r = ppmColor->r;
    imageGlobal->matrizDePixels[pixelPosition].g = ppmColor->g;
    imageGlobal->matrizDePixels[pixelPosition].b = ppmColor->b;
}

/**
* Função que específica os dois pontos das extremidades da linha a ser desenhada, cada um com suas coordenadas (x, y)
* @param x0 Valor horizontal da primeira coordenada
* @param y0 Valor vertical da primeira coordenada
* @param x1 Valor horizontal da segunda coordenada
* @param y1 Valor vertical da segunda coordenada
* @details Foi utilizado como base o algoritmo de linha de Bresenham
*/
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

/**
* Função auxiliar que pinta os pixels a partir das coordenadas especificadas
* @param xc Valor horizontal da primeira coordenada
* @param yc Valor vertical da primeira coordenada
* @param x Valor horizontal da segunda coordenada
* @param y Valor vertical da segunda coordenada
*/
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

/**
* Função que desenha um círculo nas posições x, y e tamanho especificados
* @param xc Valor horizontal da coordenada
* @param yc Valor vertical da coordenada
* @param r Valor do raio do círculo
* @details Foi utilizado como base o algoritmo de Bresenham, https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
*/
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
            d = d + 4 * (x - y); 
        } else {
            d = d + 4 * x; 
        }
        drawCircle(xc, yc, x, y); 
    } 
} 

/**
* Função que Desenha um polígono delimitado por uma lista de pontos
* @param arguments Lista de coordenadas
*/
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

/**
* Função que vira a imagem na vertical ou na horizontal
* @param orientation Valor da orientação 'vertical' ou 'horizontal'
*/
void flip(char *orientation) {
    if ((strcmp(orientation, "horizontal") == 0)) {
        int halfHorizontal = (int) imageGlobal->x / 2;
        for (int y = 0; y < imageGlobal->y; y++){
            for(int x = 0; x < halfHorizontal; x++){
                int rightPixelPosition = abs((y * imageGlobal->y) - (imageGlobal->x - x -1));
                int leftPixelPosition = abs((y * imageGlobal->y) - x);

                PPMPixel pixel = imageGlobal->matrizDePixels[leftPixelPosition];
                imageGlobal->matrizDePixels[leftPixelPosition] = imageGlobal->matrizDePixels[rightPixelPosition];
                imageGlobal->matrizDePixels[rightPixelPosition] = pixel;
            }
        }
    }

    if ((strcmp(orientation, "vertical") == 0)) {
        int halfVertical = (int) imageGlobal->y / 2;
        for (int y = 0; y < halfVertical; y++){
            for(int x = 0; x < imageGlobal->x; x++){
                int topPixelPosition = abs(((imageGlobal->y - y -1) * imageGlobal->y) - x);
                int bottomPixelPosition = abs((y * imageGlobal->y) - x);

                PPMPixel pixel = imageGlobal->matrizDePixels[bottomPixelPosition];
                imageGlobal->matrizDePixels[bottomPixelPosition] = imageGlobal->matrizDePixels[topPixelPosition];
                imageGlobal->matrizDePixels[topPixelPosition] = pixel;
            }
        }
    }
}

/**
* Função que move a imagem em uma quantidade de pixels para direita, esquerda, cima ou baixo
* @param orientation Valor da orientação 'right', 'left', 'top' ou 'bottom'
* @param size Valor da quantidade de pixels a ser movida
*/
void move(char *orientation, int size) {
    if ((strcmp(orientation, "right") == 0)) {
        for (int y = 0; y < imageGlobal->y; y++){
            for(int x = imageGlobal->x -1; x > 0; x--){
                int pixelPosition = abs((y * imageGlobal->y) - x);
                if(x >= size) {
                    int oldPixelPosition = abs((y * imageGlobal->y) - (x - size));
                    PPMPixel pixel = imageGlobal->matrizDePixels[oldPixelPosition];
                    imageGlobal->matrizDePixels[oldPixelPosition] = imageGlobal->matrizDePixels[pixelPosition];
                    imageGlobal->matrizDePixels[pixelPosition] = pixel;
                } else {
                    imageGlobal->matrizDePixels[pixelPosition].r = ppmColor->r;
                    imageGlobal->matrizDePixels[pixelPosition].g = ppmColor->g;
                    imageGlobal->matrizDePixels[pixelPosition].b = ppmColor->b;
                }
            }
        }
    }
    if ((strcmp(orientation, "left") == 0)) {
        for (int y = 0; y < imageGlobal->y; y++){
            for(int x = 0; x < imageGlobal->x; x++){
                int pixelPosition = abs((y * imageGlobal->y) - x);
                if(x >= size) {
                    int oldPixelPosition = abs((y * imageGlobal->y) - (x - size));
                    PPMPixel pixel = imageGlobal->matrizDePixels[oldPixelPosition];
                    imageGlobal->matrizDePixels[oldPixelPosition] = imageGlobal->matrizDePixels[pixelPosition];
                    imageGlobal->matrizDePixels[pixelPosition] = pixel;
                } else {
                    imageGlobal->matrizDePixels[pixelPosition].r = ppmColor->r;
                    imageGlobal->matrizDePixels[pixelPosition].g = ppmColor->g;
                    imageGlobal->matrizDePixels[pixelPosition].b = ppmColor->b;
                }
            }
        }
    }
    if ((strcmp(orientation, "bottom") == 0)) {
        for (int y = imageGlobal->y -1; y > 0; y--){
            for(int x = 0; x < imageGlobal->x; x++){
                int pixelPosition = abs((y * imageGlobal->y) - x);
                if(y >= size) {
                    int oldPixelPosition = abs(((y -size) * imageGlobal->y) - x);
                    PPMPixel pixel = imageGlobal->matrizDePixels[oldPixelPosition];
                    imageGlobal->matrizDePixels[oldPixelPosition] = imageGlobal->matrizDePixels[pixelPosition];
                    imageGlobal->matrizDePixels[pixelPosition] = pixel;
                } else {
                    imageGlobal->matrizDePixels[pixelPosition].r = ppmColor->r;
                    imageGlobal->matrizDePixels[pixelPosition].g = ppmColor->g;
                    imageGlobal->matrizDePixels[pixelPosition].b = ppmColor->b;
                }
            }
        }
    }
    if ((strcmp(orientation, "top") == 0)) {
        for (int y = 0; y < imageGlobal->y; y++){
            for(int x = 0; x < imageGlobal->x; x++){
                int pixelPosition = abs((y * imageGlobal->y) - x);
                if(y >= size) {
                    int oldPixelPosition = abs(((y -size) * imageGlobal->y) - x);
                    PPMPixel pixel = imageGlobal->matrizDePixels[oldPixelPosition];
                    imageGlobal->matrizDePixels[oldPixelPosition] = imageGlobal->matrizDePixels[pixelPosition];
                    imageGlobal->matrizDePixels[pixelPosition] = pixel;
                } else {
                    imageGlobal->matrizDePixels[pixelPosition].r = ppmColor->r;
                    imageGlobal->matrizDePixels[pixelPosition].g = ppmColor->g;
                    imageGlobal->matrizDePixels[pixelPosition].b = ppmColor->b;
                }
            }
        }
    }
}
