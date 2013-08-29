#include "learn.h"   
#include <stdio.h>   
#include <stdlib.h>
#include <math.h>   
  
ClImage* clLoadImage(char* path)  
{  
    ClImage* bmpImg;  
    FILE* pFile;  
    unsigned short fileType;  
    ClBitMapFileHeader bmpFileHeader;  
    ClBitMapInfoHeader bmpInfoHeader;  
    int channels = 1;  
    int width = 0;  
    int height = 0;  
    int step = 0;  
    int offset = 0;  
    unsigned char pixVal;  
    ClRgbQuad* quad;  
    int i, j, k;  
  
    bmpImg = (ClImage*)malloc(sizeof(ClImage));  
    pFile = fopen(path, "rb");  
    if (!pFile)  
    {  
        printf("no %s file! \n", path); 
        free(bmpImg);  
        return NULL;  
    }  
  
    fread(&fileType, sizeof(unsigned short), 1, pFile);  
    if (fileType == 0x4D42)  
    {  
        //printf("bmp file! \n");   
  
        fread(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);  
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"); 
        printf("bmp filehead:\n"); 
        printf("Size of file: %d \n", bmpFileHeader.bfSize); 
        printf("Reserved: %d \n", bmpFileHeader.bfReserved1); 
        printf("Reserved: %d \n", bmpFileHeader.bfReserved2); 
        printf("Off bits: %d \n", bmpFileHeader.bfOffBits);
  
        fread(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);  
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n"); 
        printf("bmp文件信息头\n"); 
        printf("结构体长度：%d \n", bmpInfoHeader.biSize); 
        printf("位图宽度：%d \n", bmpInfoHeader.biWidth); 
        printf("位图高度：%d \n", bmpInfoHeader.biHeight); 
        printf("位图平面数：%d \n", bmpInfoHeader.biPlanes); 
        printf("biBitCount: %d \n", bmpInfoHeader.biBitCount); 
        printf("压缩方式：%d \n", bmpInfoHeader.biCompression); 
        printf("实际位图数据占用的字节数：%d \n", bmpInfoHeader.biSizeImage); 
        printf("X方向分辨率：%d \n", bmpInfoHeader.biXPelsPerMeter); 
        printf("Y方向分辨率：%d \n", bmpInfoHeader.biYPelsPerMeter); 
        printf("使用的颜色数：%d \n", bmpInfoHeader.biClrUsed); 
        printf("重要颜色数：%d \n", bmpInfoHeader.biClrImportant); 
        printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
  
        if (bmpInfoHeader.biBitCount == 8)  
        {  
            //printf("该文件有调色板，即该位图为非真彩色\n\n");   
            channels = 1;  
            width = bmpInfoHeader.biWidth;  
            height = bmpInfoHeader.biHeight;  
            offset = (channels*width)%4;  
            if (offset != 0)  
            {  
                offset = 4 - offset;  
            }  
            //bmpImg->mat = kzCreateMat(height, width, 1, 0);   
            bmpImg->width = width;  
            bmpImg->height = height;  
            bmpImg->channels = 1;  
            bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height);  
            step = channels*width;  
  
            quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad)*256);  
            fread(quad, sizeof(ClRgbQuad), 256, pFile);  
            free(quad);  
  
            for (i=0; i<height; i++)  
            {  
                for (j=0; j<width; j++)  
                {  
                    fread(&pixVal, sizeof(unsigned char), 1, pFile);  
                    bmpImg->imageData[(height-1-i)*step+j] = pixVal;  
                }  
                if (offset != 0)  
                {  
                    for (j=0; j<offset; j++)  
                    {  
                        fread(&pixVal, sizeof(unsigned char), 1, pFile);  
                    }  
                }  
            }             
        }  
        else if (bmpInfoHeader.biBitCount == 24)  
        {  
            printf("This is true bmp!\n\n");   
            channels = 3;  
            width = bmpInfoHeader.biWidth;  
            height = bmpInfoHeader.biHeight;  
  
            bmpImg->width = width;  
            bmpImg->height = height;  
            bmpImg->channels = 3;  
            bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*3*height);  
            step = channels*width;  
  
            offset = (channels*width)%4;  
            if (offset != 0)  
            {  
                offset = 4 - offset;  
            }  
  
            for (i=0; i<height; i++)  
            {  
                for (j=0; j<width; j++)  
                {  
                    for (k=0; k<3; k++)  
                    {  
                        fread(&pixVal, sizeof(unsigned char), 1, pFile);  
                        bmpImg->imageData[(height-1-i)*step+j*3+k] = pixVal;  
                    }  
                    //kzSetMat(bmpImg->mat, height-1-i, j, kzScalar(pixVal[0], pixVal[1], pixVal[2]));   
                }  
                if (offset != 0)  
                {  
                    for (j=0; j<offset; j++)  
                    {  
                        fread(&pixVal, sizeof(unsigned char), 1, pFile);  
                    }  
                }  
            }  
        }  
    }  
  
    return bmpImg;  
}  

ClImage* clLoadRaw(char* path, int width, int height, int channels)
{
    ClImage* bmpImg;  
    FILE* pFile; 
  
    bmpImg = (ClImage*)malloc(sizeof(ClImage));  
    if (bmpImg == NULL)  
    {    
        printf("bmpImg malloc fail!\n");
        return NULL;  
    }  
    pFile = fopen(path, "rb");  
    if (!pFile)  
    {  
        printf("no %s file! \n", path); 
        free(bmpImg);  
        return NULL;  
    }  
  
    //fread(&fileType, sizeof(unsigned short), 1, pFile);
    bmpImg->width = width;
    bmpImg->height = height;
    bmpImg->channels = channels;
    bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height*channels);
    if (bmpImg->imageData == NULL)  
    {    
        printf("bmpImg->imageData malloc fail!\n");
        return NULL;  
    }  
    fread(bmpImg->imageData, width*height*channels, 1, pFile);
    fclose(pFile);
    return bmpImg;
}

ClImage* clLoadBlockRaw(FILE* fp, int width, int height, int channels, int h_offset, int v_offset, int number)
{
    ClImage* bmpImg;  
    int i, x, y, row, col;
    unsigned char* tmpImgData;
    //FILE* pFile; 
  
    bmpImg = (ClImage*)malloc(sizeof(ClImage));  
    if (bmpImg == NULL)  
    {    
        printf("bmpImg malloc fail!\n");
        return NULL;  
    }  
    //pFile = fopen(path, "rb");  
    if (!fp)  
    {  
        printf("no file! \n"); 
        free(bmpImg);  
        return NULL;  
    }  
    
    //fread(&fileType, sizeof(unsigned short), 1, pFile);
    bmpImg->width = width;
    bmpImg->height = height;
    bmpImg->channels = channels;
    bmpImg->imageData = (unsigned char*)malloc(sizeof(unsigned char)*width*height*channels);
    if (bmpImg->imageData == NULL)  
    {    
        printf("bmpImg->imageData malloc fail!\n");
        return NULL;  
    }  
    row = number / 7;
    col = number % 7;
    //大方块的定位
    x = h_offset + col * width;
    y = v_offset + row * height;
    //定位文件指针
    fseek(fp, (y*480+x)*channels, 0);
    tmpImgData = bmpImg->imageData;
    for (i = 0; i < height; ++i)
    {
        fread(tmpImgData, width*channels, 1, fp);
        fseek(fp, 480*channels-width*channels, 1);
        tmpImgData += width * channels;
    }
    return bmpImg;
}
int getBinIndex(unsigned char colorVal)
{
    if (colorVal < 64)
    {
        return 0;
    } else if (colorVal < 128)
    {
        return 1;
    } else if (colorVal < 192)
    {
        return 2;
    } else if (colorVal < 256)
    {
        return 3;
    } else
    {
        return -1;
    }
}
double* getHistogramData(ClImage* bmpImg)
{        
    double* histogramData = (double*)malloc(sizeof(double)*4*4*4);;
	memset(histogramData, 0, sizeof(double)*4*4*4);
    int row, col;
    int width = bmpImg->width;
    int height = bmpImg->height;
    int channels = bmpImg->channels;
    unsigned char* pixels = bmpImg->imageData;
    //printf("width=%d,height=%d,channels=%d\n", width, height, channels);
    
    int index;
    int redIdx, greenIdx, blueIdx;
    int singleIndex;
    double total = 0;
    int i;
	//printf("start total=%f\n", total);
    for(row=0; row<height; row++) {        
        for(col=0; col<width; col++) {
            index = (row * width + col)*channels;
            redIdx = (int)getBinIndex(pixels[index]);
            //printf("redIdx=%d\n", redIdx); 
            greenIdx = (int)getBinIndex(pixels[index+1]);
            //printf("greenIdx=%d\n", greenIdx); 
            blueIdx = (int)getBinIndex(pixels[index+2]);
            //printf("blueIdx=%d\n", blueIdx); 
            singleIndex = redIdx + greenIdx * 4 + blueIdx * 4 * 4;
            //printf("singleIndex=%d\n", singleIndex);
            histogramData[singleIndex] += 1;
            total += 1;
        }
    }
    //printf("total=%f\n", total);
        // start to normalize the histogram data
    for (i = 0; i < 64; i++)
    {
        histogramData[i] = histogramData[i] / total;
        //printf("histogramData[%d]:%f\n", i, histogramData[i]);
    }
    return histogramData;
}

double modelMatch(double* srcData, double* desData) 
{
    double mixedData[4*4*4] = {0};
    for(int i=0; i<64; i++ ) {
        mixedData[i] = sqrt(srcData[i] * desData[i]);
    }

        // The values of Bhattacharyya Coefficient ranges from 0 to 1,
    double similarity = 0;
    for(int i=0; i<64; i++ ) {
        similarity += mixedData[i];
    }

        // The degree of similarity
    return similarity;
}
  
bool clSaveImage(char* path, ClImage* bmpImg)  
{  
    FILE *pFile;  
    unsigned short fileType;  
    ClBitMapFileHeader bmpFileHeader;  
    ClBitMapInfoHeader bmpInfoHeader;  
    int step;  
    int offset;  
    unsigned char pixVal = '\0';  
    int i, j;  
    ClRgbQuad* quad;  
  
    pFile = fopen(path, "wb");  
    if (!pFile)  
    {  
        return false;  
    }  
  
    fileType = 0x4D42;  
    fwrite(&fileType, sizeof(unsigned short), 1, pFile);  
  
    if (bmpImg->channels == 3)//24位，通道，彩图   
    {  
        step = bmpImg->channels*bmpImg->width;  
        //printf("step = %d\n", step);
        offset = step%4; 
        //printf("offset = %d\n", offset); 
        if (offset != 4)  
        {  
            step += 4-offset;  
        }  
  
        bmpFileHeader.bfSize = bmpImg->height*step + 54;  
        bmpFileHeader.bfReserved1 = 0;  
        bmpFileHeader.bfReserved2 = 0;  
        bmpFileHeader.bfOffBits = 54;  
        fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);  
  
        bmpInfoHeader.biSize = 40;  
        bmpInfoHeader.biWidth = bmpImg->width;  
        bmpInfoHeader.biHeight = bmpImg->height;  
        bmpInfoHeader.biPlanes = 1;  
        bmpInfoHeader.biBitCount = 24;  
        bmpInfoHeader.biCompression = 0;  
        bmpInfoHeader.biSizeImage = bmpImg->height*step;  
        bmpInfoHeader.biXPelsPerMeter = 0;  
        bmpInfoHeader.biYPelsPerMeter = 0;  
        bmpInfoHeader.biClrUsed = 0;  
        bmpInfoHeader.biClrImportant = 0;  
        fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);  
  
        for (i=bmpImg->height-1; i>-1; i--)  
        {  
            for (j=0; j<bmpImg->width; j++)  
            {  
                /*pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile); */ 
                /*pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3+1];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);*/  
                pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3+2];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
                pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3+1];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
                pixVal = bmpImg->imageData[i*bmpImg->width*3+j*3];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);   
            }  
            if (offset!=0)  
            {  
                for (j=0; j<offset; j++)  
                {  
                    pixVal = 0;  
                    fwrite(&pixVal, sizeof(unsigned char), 1, pFile);  
                }  
            }  
        }  
    }  
    else if (bmpImg->channels == 4)//32位，通道，彩图   
    {  
        step = bmpImg->channels*bmpImg->width;  
        //printf("step = %d\n", step);
        offset = step%4; 
        //printf("offset = %d\n", offset); 
        if (offset != 4)  
        {  
            step += 4-offset;  
        }  
  
        bmpFileHeader.bfSize = bmpImg->height*step + 54;  
        bmpFileHeader.bfReserved1 = 0;  
        bmpFileHeader.bfReserved2 = 0;  
        bmpFileHeader.bfOffBits = 54;  
        fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);  
  
        bmpInfoHeader.biSize = 40;  
        bmpInfoHeader.biWidth = bmpImg->width;  
        bmpInfoHeader.biHeight = bmpImg->height;  
        bmpInfoHeader.biPlanes = 1;  
        bmpInfoHeader.biBitCount = 32;  
        bmpInfoHeader.biCompression = 0;  
        bmpInfoHeader.biSizeImage = bmpImg->height*step;  
        bmpInfoHeader.biXPelsPerMeter = 0;  
        bmpInfoHeader.biYPelsPerMeter = 0;  
        bmpInfoHeader.biClrUsed = 0;  
        bmpInfoHeader.biClrImportant = 0;  
        fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);  
  
        for (i=bmpImg->height-1; i>-1; i--)  
        {  
            for (j=0; j<bmpImg->width; j++)  
            {  
                //B
                pixVal = bmpImg->imageData[i*bmpImg->width*4+j*4+2];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);  
                //G
                pixVal = bmpImg->imageData[i*bmpImg->width*4+j*4+1];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);  
                //R
                pixVal = bmpImg->imageData[i*bmpImg->width*4+j*4];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile); 
                //A
                pixVal = bmpImg->imageData[i*bmpImg->width*4+j*4+3];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);   
            }  
            if (offset!=0)  
            {  
                for (j=0; j<offset; j++)  
                {  
                    pixVal = 0;  
                    fwrite(&pixVal, sizeof(unsigned char), 1, pFile);  
                }  
            }  
        }  
    }  
    else if (bmpImg->channels == 1)//8位，单通道，灰度图   
    {  
        step = bmpImg->width;  
        offset = step%4;  
        if (offset != 4)  
        {  
            step += 4-offset;  
        }  
  
        bmpFileHeader.bfSize = 54 + 256*4 + bmpImg->width;  
        bmpFileHeader.bfReserved1 = 0;  
        bmpFileHeader.bfReserved2 = 0;  
        bmpFileHeader.bfOffBits = 54 + 256*4;  
        fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);  
  
        bmpInfoHeader.biSize = 40;  
        bmpInfoHeader.biWidth = bmpImg->width;  
        bmpInfoHeader.biHeight = bmpImg->height;  
        bmpInfoHeader.biPlanes = 1;  
        bmpInfoHeader.biBitCount = 8;  
        bmpInfoHeader.biCompression = 0;  
        bmpInfoHeader.biSizeImage = bmpImg->height*step;  
        bmpInfoHeader.biXPelsPerMeter = 0;  
        bmpInfoHeader.biYPelsPerMeter = 0;  
        bmpInfoHeader.biClrUsed = 256;  
        bmpInfoHeader.biClrImportant = 256;  
        fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);  
  
        quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad)*256);  
        for (i=0; i<256; i++)  
        {  
            quad[i].rgbBlue = i;  
            quad[i].rgbGreen = i;  
            quad[i].rgbRed = i;  
            quad[i].rgbReserved = 0;  
        }  
        fwrite(quad, sizeof(ClRgbQuad), 256, pFile);  
        free(quad);  
  
        for (i=bmpImg->height-1; i>-1; i--)  
        {  
            for (j=0; j<bmpImg->width; j++)  
            {  
                pixVal = bmpImg->imageData[i*bmpImg->width+j];  
                fwrite(&pixVal, sizeof(unsigned char), 1, pFile);  
            }  
            if (offset!=0)  
            {  
                for (j=0; j<offset; j++)  
                {  
                    pixVal = 0;  
                    fwrite(&pixVal, sizeof(unsigned char), 1, pFile);  
                }  
            }  
        }  
    }  
    fclose(pFile);  
  
    return true;  
}  