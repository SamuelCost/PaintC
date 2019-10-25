#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{    
    int i, j;
    const int dimx = 800, dimy = 600;

    FILE *fp = fopen("first.ppm", "w+"); 
    fprintf(fp, "P3\n%d %d\n255\n", dimx, dimy);

    for (j = 0; j < dimy; ++j)
    {
        for (i = 0; i < dimx; ++i)
        {
            static unsigned char color[3];
            color[0] = i+2*j % 256;  /* red */
            color[1] = i-j % 256;  /* green */
            color[2] = (i+j) % 256;  /* blue */
            fwrite(color, 1, 3, fp);//Escreve no arquivo a cor
        }
    }
    fclose(fp);//Salva o arquivo
    return EXIT_SUCCESS;
}