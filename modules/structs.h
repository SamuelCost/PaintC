/**
 * @file structs.h
 * @brief Contém as definições das structs
*/

#ifndef structs
#define structs

/**
 * Define a estrutura de RGB;
 */
typedef struct{
	unsigned int r, g, b;
} PPMPixel;

/**
 * Define estrutura da imagem em formato PPM
 */ 
typedef struct {
     int x, y, maxRGBRange;
     char *fileName, *typeEncoding;
     PPMPixel *matrizDePixels;
} PPMImage;

/**
 * Define a estrutura da cor (color)
 */
typedef struct {
    int r, g, b;
} PPMColor;

/**
 * Inicializa uma variável global da imagem PPM
 */
PPMImage *imageGlobal;
/**
 * Inicializa uma variável global para auxilicar a primitiva color
 */
PPMColor *ppmColor;
/**
 * Inicializa uma varável global para auxilicar a primitiva clear
 */
PPMColor *backgroundColor;
/**
 * Inicializa uma variável global da imagem PPM para a auxiliar a primitiva rotate
 */
PPMImage *imageRotate;

#endif