#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r,g,b; //struct dos pixels em RGB;
}pixel;

void savePPM(const char *filename, char *type, int x, int y, int max){
    FILE *fn;
    fn = fopen(filename, "w+");
    fprintf(fn, "%s\n%d %d\n%d\n",type,x,y,max);
    static unsigned int color[3];
    for(int j = 0; j<x;j++){
        for(int i = 0;i<y;i++){
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
        }
    for(int k=0;k<3;k++){
        fprintf(fn,"%i ",color[k]);
    }           
    fprintf(fn,"\n");
    }
    fclose(fn);
}

int main(){
    int dimx = 800;
    int dimy = 600;
    int max = 255;
    //char namearq = "test.ppm";
    //char tipo = "P3";

    savePPM("teste.ppm","P3",dimx,dimy,max);

    pixel **RGB =(pixel**)malloc(dimx*sizeof(pixel*));//cria e aloca espaço para a matriz
	for(int i=0;i<dimx;i++){						// que vai receber as infos do arquivo original
		RGB[i] = (pixel*)malloc(dimy*sizeof(pixel));
	}

}