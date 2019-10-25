#include <stdio.h>
 
void make_pixel
    (
    int r, // red intensity
    int g, // green intensity
    int b) // blue intensity
     
    {
    fprintf(stdout, "%c%c%c", r, g, b);
    }
 
void make_ppm_header (int width, int height)
    {
     
    fprintf(stdout, "P6\n");
    fprintf(stdout, "%d %d %d\n",width, height, 255);
     
 
    }
 
void make_ppm_image(int country_code, int width)
    {
     int i;
    int j;
    int height;
 
    height=0;
 
    if (country_code == 0){
        height = 2 * width / 3;
        make_ppm_header(width, height);
 
        for (i = 0; i < height; i++){
 
            for (j = 0; j < width; j++){
                if(j < width / 3)
                    make_pixel(0, 85, 164);
                else if(j > width / 3 && j < width /3 * 2)
                    make_pixel(255,255,255);
                else
                    make_pixel(250,60,50);
            }
        }
    }
    else if(country_code == 1){
        height = 2 * width/ 3;
        make_ppm_header(width, height);
 
        for (i = 1; i < height; i++){
 
            for(j = 0; j < width; j++){
                if(j < width/ 3)
                    make_pixel(0,0,0);
                else if(j > width / 3 && j < width /3 * 2)
                    make_pixel(255,0,0);
                else
                    make_pixel(250,204,0);    
            }
        }
    }
    else(country_code = 2);{
        height = 2 * width/ 3;
        make_ppm_header(width, height);
 
        for (i = 2; i < height; i++){
         
            for(j = 0; j < width; j++){
                if(j < width/ 3)
                    make_pixel(253,185,19);
                else if(j > width / 3 && j < width /3 * 2)
                    make_pixel(0,106,68);
                else make_pixel(193,39,45);
    }
    }
 
    }
    }
 
int main()
{
    int width;
    int country_code;
     
 
    /* Read image dimensions and pixel color */
     
    fscanf(stdin, "%d %d", &country_code, &width);
    fprintf(stderr, "Making country %d width %d\n", country_code, width);
 
    /* Write the image data */
 
    make_ppm_image(country_code, width);
 
    return 0;
}