#include <stdio.h>

/* Read header part of PPM file
*
* Input parameters:
* FILE* f - an open PPM file
*
* Output parameters:
* int* width - width of the image, in pixels
* int* height - height of the image, in pixels
*/
void read_header(FILE* f, int *width, int *height) {
char buffer[256];
int rv;

fscanf(f, "%s", buffer); // magic (discard)
fscanf(f, "%d %d", width, height); // image dimensions
fscanf(f, "%d", &rv); // colour table size (discard)
}

/* Write header part of PPM file
*
* Input Parameters:
* FILE* f - an open PPM file
* int width - width of the image, in pixels
* int height - height of the image, in pixels
*/
void write_header(FILE* f, int width, int height) {
fprintf(f, "P3\n"); // magic
fprintf(f, "%d %d\n", width, height); // image dimensions
fprintf(f, "255\n"); // colour table size
}

/* Read pixel (colour) data from PPM file
*
* Input parameters:
* FILE* f - an open PPM file
* int width - width of the image, in pixels
* int height - height of the image, in pixels
*
* Output parameters:
* int red[][] - 2D array containing red colour channel data
* int green[][] - 2D array containing green colour channel data
* int blue[][] - 2D array containing blue colour channel data
*
* Returns:
* 0 if everything is ok
* non-zero otherwise
*/
int read_ppm(FILE* f, int width, int height, int red[height][width], int green[height][width], int blue[height][width] ) {

// Add code to read in a PPM file

return 1; // FIXME
}

/* Write pixel (colour) data to a PPM file
*
* Input parameters:
* FILE* f - an open PPM file
* int width - width of the image, in pixels
* int height - height of the image, in pixels
* int red[][] - 2D array containing red colour channel data
* int green[][] - 2D array containing green colour channel data
* int blue[][] - 2D array containing blue colour channel data
*/
void write_ppm(FILE* f, int width, int height, int red[height][width], int green[height][width], int blue[height][width] ) {

// Add code to write the PPM file
}