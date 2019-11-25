/**
 * @file primitives.h
 * @brief Contém as assinaturas das primitivas
*/


#ifndef primitives
#define primitives

char *removeBreakLine(char *string);

void color(int r, int g, int b);

void clear(int r, int g, int b);

void fill(int x, int y);

void image(int x, int y);

void rotate();

void save(char * fileName);

void open(char *fileName);

void drawPixelPPM(int x, int y);

void line(int x0, int y0, int x1, int y1);

void drawCircle(int xc, int yc, int x, int y);

void cicle(int xc, int yc, int r);

void polygon(char **arguments);

void flip(char *orientation);

void move(char *orientation, int size);

#endif
