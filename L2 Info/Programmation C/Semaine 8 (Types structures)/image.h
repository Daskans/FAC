#ifndef _IMAGE
#define _IMAGE

#include <stdbool.h>

typedef unsigned int uint;

typedef struct colorRGB {
     unsigned char red;
     unsigned char green;
     unsigned char blue;
} s_colorRGB;

typedef struct colorYCbCr {
     float y;
     float cb;
     float cr;
} s_colorYCbCr;

typedef union color {
     s_colorRGB rgb;
     s_colorYCbCr ycbcr;
     unsigned char gray;
} u_color;

typedef enum {
    RGB,
    GRAY,
    YCBCR
} e_color;


typedef struct _pixMat {
	uint width;
	uint height;
	u_color ** matrix;
}pixMat;

typedef struct image {
    uint width;
	uint height;
    e_color color_type;
    pixMat * pixels;
} s_image;

pixMat* createPixMat(uint width, uint height);
void setPixel(pixMat* matrix, uint x, uint y, u_color color);
u_color getPixel(pixMat* matrix, uint x, uint y);
void freePixMatrix(pixMat* matrix);
char* e_colorAsChar(e_color ctype);
void openFile (char *name, FILE **desc, char *mode);
void writeImage (char *name, s_image *image);
s_image* readImage (char *name);
s_image* createImage(uint width, uint height, e_color ctype);
void freeImage(s_image* image);
bool isRGB(s_image* image);
bool isGray(s_image* image);
bool isYCbCr(s_image* image);
void flipH(s_image* image_src, s_image* image_dest);
void flipV(s_image* image_src, s_image* image_dest);
void rgb2gray(s_image* image_src, s_image* image_dest);
void rgb2YCbCr(s_image* image_src, s_image* image_dest);
void YCbCr2rgb(s_image* image_src, s_image* image_dest);
void blendH(s_image* image, unsigned char col1, unsigned char col2);
void flipVsource(s_image* image);
void flipHsource(s_image* image);
void fprintimage(FILE* f, s_image* s);

#endif
