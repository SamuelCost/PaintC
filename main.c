#include<stdio.h>
#include<stdlib.h>

/*typedef struct {
     unsigned char red,green,blue;
} PPMPixel;*/

typedef struct {
     int x, y;
     //PPMPixel *data;
} PPMImage;

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255



/* static PPMImage *readPPM(const char *filename)
{
         char buff[16];
         PPMImage *img;
         FILE *fp;
         int c, rgb_comp_color;
         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              perror(filename);
              exit(1);
         }

    check the image format - commit
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    alloc memory form image - commit
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    check for comments - commit
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    read image size information commit
    if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    read rgb component - commit
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    check rgb component depth - commit
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    read pixel data from file - commit
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}
*/
void savePPM(const char *filename, int x, int y)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P3\n");

    //comments
    //fprintf(fp, "# Created by %s\n",CREATOR);

    //image size
    fprintf(fp, "%d %d\n",x,y);

    for (int i = 0; i < x; i++){
        for (int j = 0; j<y;j++){
            static unsigned char color[3];
            color[0] = i+2*j % 256;  /* red */
            color[1] = i-j % 256;  /* green */
            color[2] = (i+j) % 256;  /* blue */
            fwrite(color, 1, 3, fp);
            fwrite(color, 1, 3, fp);//Escreve no arquivo a cor
        }
    }

    // rgb component depth
    //fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    //fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
}

/*void changeColorPPM(PPMImage *img)
{
    int i;
    if(img){

         for(i=0;i<img->x*img->y;i++){
              img->data[i].red=RGB_COMPONENT_COLOR-img->data[i].red;
              img->data[i].green=RGB_COMPONENT_COLOR-img->data[i].green;
              img->data[i].blue=RGB_COMPONENT_COLOR-img->data[i].blue;
         }
    }
}*/

int main(){    
    //PPMImage *img;
    const int imgx = 800, imgy = 600;
    //image = readPPM("first.ppm");
    //changeColorPPM(image);
    savePPM("first.ppm",imgx, imgy);
    printf("Press any key...");
    getchar();
}