<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const int dimx = 800, dimy = 600;//Dimensão da matriz
    int i, j;
    
    FILE *fp = fopen("first.ppm", "wb"); /* b - modo binário */
    
    //Descrição do arquivo
    fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    //Varre a matriz em coloca uma cor na posição
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{    
    int i, j;
    const int dimx = 800, dimy = 600;

    FILE *fp = fopen("first.ppm", "w+"); 
    fprintf(fp, "P3\n%d %d\n255\n", dimx, dimy);

>>>>>>> PC-001
    for (j = 0; j < dimy; ++j)
    {
        for (i = 0; i < dimx; ++i)
        {
<<<<<<< HEAD
            //tente trocar o unsigned char por outros tipos
            //Verifique o que significa unsigned char
=======
>>>>>>> PC-001
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