/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string>

#include "HDRImage.h"

using std::string;

#ifndef _WIN32
    #define MAXSHORT 0x7fff
    #define MAXCHAR  0x7f
#endif

static const string radianceHeader = "?#RADIANCE";
const int    radianceHeaderLength = 11;

const int rgbComponentsCount = 3;
const int rgbeComponentsCount = 4;
const int minLineLength = 8;
const int maxLineLength = MAXSHORT;

const char startOfText = '\002';

namespace BotsonSDK
{
    HDRImage::HDRImage(void)
    {
        width = 0;
        height = 0;
        rgbData = NULL;
    }

    HDRImage::HDRImage(const std::string& filePath)
    {
        loadFromFile(filePath);
    }

    HDRImage::~HDRImage(void)
    {
        if (rgbData != NULL)
        {
            delete [] rgbData;
            rgbData = NULL;
        }
    }

    HDRImage& HDRImage::operator= (const HDRImage &another)
    {
        if(this != &another)
        {
            delete [] rgbData;
            this->width = another.width;
            this->height = another.height;
            this->rgbData = new float[this->width * this->height * rgbComponentsCount];
            memcpy(this->rgbData, another.rgbData, this->width * this->width * rgbComponentsCount * sizeof(float));
        }

        return *this;
    }

    HDRImage::HDRImage(HDRImage& another)
    {
        if(this != &another)
        {
            this->width = another.width;
            this->height = another.height;
            this->rgbData = new float[this->width * this->height * rgbComponentsCount];
            memcpy(this->rgbData, another.rgbData, this->width * this->width * rgbComponentsCount * sizeof(float));
        }
    }

    void HDRImage::loadFromFile(const std::string& filePath)
    {
        FILE* file;

        file = fopen(filePath.c_str(), "rb");

        if (file == NULL)
        {
            printf("Could not open file %s", filePath.c_str());
            return;
        }

        /* Read header. */
        char header[radianceHeaderLength];

        fread(header, 1, radianceHeaderLength, file);
        header[radianceHeaderLength - 1] = 0;
        string readHeader = header;

        if (!readHeader.compare(radianceHeader))
        {
            printf("File header has not been recognized.\n");
            fclose(file);
            return;
        }

        /* Search for resolution data. */
        char currentChar  = 0;
        char previousChar = 0;

        while ((previousChar != '\n' || currentChar != '\n') && currentChar != EOF)
        {
            previousChar = currentChar;
            currentChar = fgetc(file);
        }

        int imageWidth = 0;
        int imageHeight = 0;

        fscanf(file, "-Y %d ", &imageHeight);
        fscanf(file, "+X %d ", &imageWidth);

        if (imageWidth < minLineLength || imageWidth > maxLineLength)
        {
            printf("Cannot decode image with width lower than %d or higher than %d", minLineLength, maxLineLength);
            return;
        }

        height = imageHeight;
        width = imageWidth;

        RGBEPixel* scanLine = NULL;

        try
        {
            rgbData = new float[imageWidth * imageHeight * rgbComponentsCount];
            scanLine = new RGBEPixel[imageWidth * rgbeComponentsCount];
        }
        catch (std::bad_alloc& ba)
        {
            printf("Exception caught: %s", ba.what());
            return;
        }

        for (int y = 0; y < imageHeight; ++y)
        {
            if (!decodeLine(file, imageWidth, scanLine))
            {
                printf("One of the scan lines has not been encoded correctly.\n");

                delete [] scanLine;
                fclose(file);

                return;
            }

            for (int x = 0; x < imageWidth; ++x)
            {
                int rgbPixelMove = (y * imageWidth + x) * 3;
                convertRGBEPixel(scanLine[x], rgbData + rgbPixelMove);
            }
        }

        delete [] scanLine;

        fclose(file);
    }

    inline void HDRImage::convertRGBEPixel(const RGBEPixel& pixel, float* rgbData)
    {
        int exponent = pixel.e - 128;

        rgbData[0] = convertSingleComponent(pixel.r, exponent);
        rgbData[1] = convertSingleComponent(pixel.g, exponent);
        rgbData[2] = convertSingleComponent(pixel.b, exponent);
    }

    inline float HDRImage::convertSingleComponent(unsigned char value, int exponent)
    {
        float floatValue = static_cast<float> (value) / MAXCHAR;
        float multiplier = pow(2.0f, exponent);

        return floatValue * multiplier;
    }

    bool HDRImage::decodeLine(FILE* file, int lineLength, RGBEPixel* scanLine)
    {
        /* Check if line beginning is correct. */
        char startLineChar1 = fgetc(file);
        char startLineChar2 = fgetc(file);
        char startLineChar3 = fgetc(file);

        if (startLineChar1 != startOfText || startLineChar2 != startOfText || startLineChar3 & 0x80)
        {
            printf("Error occured while encoding HDR data. Unknown line beginnings.");

            return false;
        }

        /* Move file position indicator by one character. */
        fgetc(file);

        for (int componentIndex = 0; componentIndex < rgbeComponentsCount; ++componentIndex)
        {
            int pixelIndex = 0;

            while (pixelIndex < lineLength)
            {
                /* Code for RLE compression algorithm. */
                unsigned char rleCode = fgetc(file);

                if (rleCode > MAXCHAR + 1)
                {
                    /* 
                     * Read code indicates how many pixels are written with the same value,
                     *.so it is read only once.
                     */
                    unsigned char value = fgetc(file);

                    rleCode &= MAXCHAR;

                    while (rleCode--)
                    {
                        writeDecodedComponent(componentIndex, value, &scanLine[pixelIndex++]);
                    }
                }
                else
                {
                    while (rleCode--)
                    {
                        /* 
                         * Read code indicates how many pixels are written next to each other,
                         * so their value must be read each time this loop is executed.
                         */
                        unsigned char value = fgetc(file);

                        writeDecodedComponent(componentIndex, value, &scanLine[pixelIndex++]);
                    }
                }
            }
        }

        return true;
    }

    inline void HDRImage::writeDecodedComponent(int componentIndicator, unsigned char value, RGBEPixel* rgbePixel)
    {
        if (rgbePixel == NULL)
        {
            printf("Cannot write encoded component to a NULL pointer.\n");

            return;
        }

        switch (componentIndicator)
        {
            case 0:
                rgbePixel->r = value;
                break;

            case 1:
                rgbePixel->g = value;
                break;

            case 2:
                rgbePixel->b = value;
                break;

            case 3:
                rgbePixel->e = value;
                break;

            default:
                printf("Invalid value of componentIndicator was passed.\n");
        }
    }
}

