/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef RGB_H
#define RGB_H

typedef struct _RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char *data;
} RGBImageRec;


typedef struct _rawImageRec {
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short sizeX, sizeY, sizeZ;
    unsigned long min, max;
    unsigned long wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB;
    unsigned long rleEnd;
    GLuint *rowStart;
    GLint *rowSize;
} rawImageRec;

static void ConvertLong(GLuint *array, long length);
static rawImageRec *RawImageOpen(char *fileName);
static void RawImageClose(rawImageRec *raw);
static void RawImageGetRow(rawImageRec *raw, unsigned char *buf, int y, int z);
static void RawImageGetData(rawImageRec *raw, RGBImageRec *final_d);
static RGBImageRec *rgbImageLoad(char *fileName);
#endif
