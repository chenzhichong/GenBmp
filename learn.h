#include <stdio.h>

#ifndef _LEARN_H_
#define _LEARN_H_

#define false 0
#define true 1
typedef int bool; // or #define bool int
  
typedef struct  
{  
    //unsigned short    bfType;   
    unsigned long    bfSize;  
    unsigned short    bfReserved1;  
    unsigned short    bfReserved2;  
    unsigned long    bfOffBits;  
} ClBitMapFileHeader;  
  
typedef struct  
{  
    unsigned long  biSize;   
    long   biWidth;   
    long   biHeight;   
    unsigned short   biPlanes;   
    unsigned short   biBitCount;  
    unsigned long  biCompression;   
    unsigned long  biSizeImage;   
    long   biXPelsPerMeter;   
    long   biYPelsPerMeter;   
    unsigned long   biClrUsed;   
    unsigned long   biClrImportant;   
} ClBitMapInfoHeader;  
  
typedef struct   
{  
    unsigned char rgbBlue; //该颜色的蓝色分量   
    unsigned char rgbGreen; //该颜色的绿色分量   
    unsigned char rgbRed; //该颜色的红色分量   
    unsigned char rgbReserved; //保留值   
} ClRgbQuad;  
  
typedef struct  
{  
    int width;  
    int height;  
    int channels;  
    unsigned char* imageData;  
}ClImage;  
  
ClImage* clLoadImage(char* path);  
ClImage* clLoadRaw(char* path, int width, int height, int channels);
ClImage* clLoadBlockRaw(FILE* fp, int width, int height, int channels, int h_offset, int v_offset, int number);
double* getHistogramData(ClImage* bmpImg);
double modelMatch(double* srcData, double* desData);
bool clSaveImage(char* path, ClImage* bmpImg);  
  
#endif   