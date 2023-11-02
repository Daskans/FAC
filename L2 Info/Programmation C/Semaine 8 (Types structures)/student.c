#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"

/*TO BE COMPLETED*/
// pixMat* createPixMat(uint width, uint height){}
// void setPixel(pixMat* matrix, uint x, uint y, u_color color){}
// u_color getPixel(pixMat* matrix, uint x, uint y){}
// void freePixMatrix(pixMat* matrix){}
// char* e_colorAsChar(e_color ctype){}
s_image* createImage(uint width, uint height, e_color ctype){
    if (width < 1 || height < 1) {
        fprintf(stderr, "Argument error at createImage");
        exit(EXIT_FAILURE);
    }
    s_image *new_image = malloc(sizeof(s_image));
    if (!new_image) {
        fprintf(stderr,"not enough memory");
        exit(EXIT_FAILURE);
    }
    new_image->width = width;
    new_image->height = height;
    new_image->color_type = ctype;
    new_image-> pixels = createPixMat(width, height);
    return new_image;
}

void freeImage(s_image* image){
    if (image == NULL) {
        fprintf(stderr,"Argument error at freeImage\n");
    } if (image->pixels) {
        freePixMatrix(image->pixels);
    }
    free(image);
}

bool isRGB(s_image* image){
    if (image == NULL) {
        fprintf(stderr,"Argument error at isRGB\n");
        return false;
    } if (image->color_type == RGB) {
        return true;
    }
    return false;
}

bool isGray(s_image* image){
    if (image == NULL) {
        fprintf(stderr,"Argument error at isGray\n");
        return false;
    } if (image->color_type == GRAY) {
        return true;
    }
    return false;
}

bool isYCbCr(s_image* image){
    if (image == NULL) {
        fprintf(stderr,"Argument error at isYCbCr\n");
        return false;
    } if (image->color_type == YCBCR) {
        return true;
    }
    return false;
}

void flipH(s_image* image_src, s_image* image_dest){
    if (image_src == NULL || image_dest == NULL) {
        fprintf(stderr,"Argument error at flipV\n");
        exit(EXIT_FAILURE);
    } if (image_src->width != image_dest->width || 
        image_src->height != image_dest->height) {
        fprintf(stderr, "the sizes of the two images given are different");
        exit(EXIT_FAILURE);
    } if (image_src->color_type != image_dest->color_type) {
        fprintf(stderr, "the colors of the two images given are different");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image_dest->height; y++) {
        for (uint x = 0; x < image_dest->width; x++) {
            u_color pixel = getPixel(image_src->pixels, x, y);
            setPixel(image_dest->pixels, image_dest->width-1-x, y, pixel);
        }
    }
}

void flipV(s_image* image_src, s_image* image_dest){
    if (image_src == NULL || image_dest == NULL) {
        fprintf(stderr,"Argument error at flipV\n");
        exit(EXIT_FAILURE);
    } if (image_src->width != image_dest->width || 
        image_src->height != image_dest->height) {
        fprintf(stderr, "the sizes of the two images given are different");
        exit(EXIT_FAILURE);
    } if (image_src->color_type != image_dest->color_type) {
        fprintf(stderr, "the colors of the two images given are different");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image_dest->height; y++) {
        for (uint x = 0; x < image_dest->width; x++) {
            u_color pixel = getPixel(image_src->pixels, x, y);
            setPixel(image_dest->pixels, x, image_dest->height-1-y, pixel);
        }
    }
}

void rgb2gray(s_image* image_src, s_image* image_dest){
    if (image_src == NULL || image_dest == NULL) {
        fprintf(stderr,"Argument error at rgb2gray\n");
        exit(EXIT_FAILURE);
    } if (image_src->width != image_dest->width || 
        image_src->height != image_dest->height) {
        fprintf(stderr, "the sizes of the two images given are different");
        exit(EXIT_FAILURE);
    } if (!isRGB(image_src) || !isGray(image_dest)) {
        fprintf(stderr, "the colors of the two images given are different");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image_dest->height; y++) {
        for (uint x = 0; x < image_dest->width; x++) {
            u_color pixel = getPixel(image_src->pixels, x, y);
            unsigned char r = pixel.rgb.red;
            unsigned char g = pixel.rgb.green;
            unsigned char b = pixel.rgb.blue;
            u_color color;
            color.gray = 0.299*r + 0.587*g + 0.114*b;
            setPixel(image_dest->pixels, x, y, color);
        }
    }
}

void rgb2YCbCr(s_image* image_src, s_image* image_dest){
    if (image_src == NULL || image_dest == NULL) {
        fprintf(stderr,"Argument error at rgb2YCbCr\n");
        exit(EXIT_FAILURE);
    } if (image_src->width != image_dest->width || 
        image_src->height != image_dest->height) {
        fprintf(stderr, "the sizes of the two images given are different");
        exit(EXIT_FAILURE);
    } if (!isRGB(image_src) || !isYCbCr(image_dest)) {
        fprintf(stderr, "the colors of the two images given are different");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image_dest->height; y++) {
        for (uint x = 0; x < image_dest->width; x++) {
            u_color pixel = getPixel(image_src->pixels, x, y);
            unsigned char r = pixel.rgb.red;
            unsigned char g = pixel.rgb.green;
            unsigned char b = pixel.rgb.blue;
            u_color color;
            color.ycbcr.y = 0.299*r + 0.587*g + 0.114*b;
            color.ycbcr.cb = -0.1684*r  - 0.3313*g + 0.5*b + 128;
            color.ycbcr.cr = 0.5*r  - 0.4187*g - 0.0813*b + 128;
            setPixel(image_dest->pixels, x, y, color);
        }
    }
}

void YCbCr2rgb(s_image* image_src, s_image* image_dest){
    if (image_src == NULL || image_dest == NULL) {
        fprintf(stderr,"Argument error at YCbCr2rgb\n");
        exit(EXIT_FAILURE);
    } if (image_src->width != image_dest->width || 
        image_src->height != image_dest->height) {
        fprintf(stderr, "the sizes of the two images given are different");
        exit(EXIT_FAILURE);
    } if (!isYCbCr(image_src) || !isRGB(image_dest)) {
        fprintf(stderr, "the colors of the two images given are different");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image_dest->height; y++) {
        for (uint x = 0; x < image_dest->width; x++) {
            u_color pixel = getPixel(image_src->pixels, x, y);
            float Y = pixel.ycbcr.y;
            float Cb = pixel.ycbcr.cb;
            float Cr = pixel.ycbcr.cr;
            u_color color;
            color.rgb.red = Y + 1.402*(Cr - 128);
            color.rgb.green = Y - 0.34414*(Cb-128) - 0.71414*(Cr-128);
            color.rgb.blue = Y + 1.772*(Cb-128);
            setPixel(image_dest->pixels, x, y, color);
        }
    }
}

// void blendH(s_image* image, unsigned char col1, unsigned char col2){}

void flipVsource(s_image* image){
    if (image == NULL) {
        fprintf(stderr,"Argument error at flipV\n");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image->height/2; y++) {
        for (uint x = 0; x < image->width; x++) {
            u_color pixel = getPixel(image->pixels, x, image->height-1-y);
            u_color pixel2 = getPixel(image->pixels, x, y);
            setPixel(image->pixels, x, image->height-1-y, pixel2);
            setPixel(image->pixels, x, y, pixel);
        }
    }
}

void flipHsource(s_image* image){
    if (image == NULL) {
        fprintf(stderr,"Argument error at flipV\n");
        exit(EXIT_FAILURE);
    } for (uint y = 0; y < image->height; y++) {
        for (uint x = 0; x < image->width/2; x++) {
            u_color pixel = getPixel(image->pixels, image->width-1-x, y);
            u_color pixel2 = getPixel(image->pixels, x, y);
            setPixel(image->pixels, image->width-1-x, y, pixel2);
            setPixel(image->pixels, x, y, pixel);
        }
    }
}


int main(void){
    s_image* image = createImage(200, 100, RGB);
    printf(
        "image is a %dx%d image of type %s\n", 
        image->height, image->width, e_colorAsChar(image->color_type)
    );
    freeImage(image);
    
    s_image* image2 = createImage(250, 150, YCBCR);
    printf(
        "image2 is a %dx%d image of type %s\n", 
        image2->height, image2->width, e_colorAsChar(image2->color_type)
    );
    freeImage(image2);
    
    return EXIT_SUCCESS;
}