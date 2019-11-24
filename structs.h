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

// struct que define a cor do pincel atual
typedef struct {
    int r, g, b;
} PPMColor;

// struct do objeto PPM manipulado em tempo de execução
PPMImage *imageGlobal;
PPMColor *ppmColor;
PPMColor *backgroundColor;
PPMImage *imageRotate;