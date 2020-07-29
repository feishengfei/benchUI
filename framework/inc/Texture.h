
/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */


#ifndef TEXTURE_H
#define TEXTURE_H

#include "ETCHeader.h"


#ifdef API_ES
#if API_VERSION == 11
    #include <GLES/gl.h>
	#include <GLES/glext.h>
#elif API_VERSION == 20
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
#elif API_VERSION == 30
    #include <GLES3/gl3.h>
	#include <GLES3/gl3ext.h>
#elif API_VERSION == 31
	#include <GLES3/gl31.h>
	#include <GLES3/gl3ext.h>
#elif API_VERSION == 32
	#include <GLES3/gl32.h>
	#include <GLES3/gl3ext.h>
#endif
#include <EGL/egl.h>
#else
#define GL_GLEXT_PROTOTYPES
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glcorearb.h>
    #include <GL/glext.h>
#endif

namespace BotsonSDK
{
    /** Structure holding bitmap file header elements. */
    struct tagBITMAPFILEHEADER
    {
        short bfType;
        int   bfSize;
        short bfReserved1;
        short bfReserved2;
        int   bfOffBits;
    };

    /** Structure holding bitmap info header elements. */
    struct tagBITMAPINFOHEADER
    {
        int   biSize;
        int   biWidth;
        int   biHeight;
        short biPlanes;
        short biBitCount;
        int   biCompression;
        int   biSizeImage;
        int   biXPelsPerMeter;
        int   biYPelsPerMeter;
        int   biClrUsed;
        int   biClrImportant;
    };

    /** 
     * \brief Functions for working with textures.
     */
    class Texture
    {
    private:
        /**
         * \brief Read BMP file header.
         *
         * \param filePtr             File pointer where BMP file header data is stored.
         *                            Cannot be NULL.
         * \param bitmapFileHeaderPtr Deref will be used to store loaded data.
         *                            Cannot be NULL.
         */
        static void readBitmapFileHeader(FILE* filePtr, tagBITMAPFILEHEADER* bitmapFileHeaderPtr);
        /**
         * \brief Read BMP info header.
         *
         * \param filePtr             File pointer where BMP info header data is stored.
         *                            Cannot be NULL.
         * \param bitmapInfoHeaderPtr Deref will be used to store loaded data.
         *                            Cannot be NULL.
         */
        static void readBitmapInforHeader(FILE* filePtr, tagBITMAPINFOHEADER* bitmapInfoHeaderPtr);
        /**
         * \brief Uses glGetIntegerv to get the number of compressed texture formats and the formats themselves.
         
         * Calls glGetIntegerv with GL_NUM_COMPRESSED_TEXTURE_FORMATS and GL_COMPRESSED_TEXTURE_FORMATS.
         * \param[out] textureFormats Pointer to the array of texture formats.
         * \param[out] numberOfTextureFormats Pointer to the number of compressed texture formats.
         */
        static void getCompressedTextureFormats(GLint **textureFormats, int* numberOfTextureFormats);
    public:
        /**
         * \brief Reports whether or not ETC (Ericsson Texture Compression) is supported.
         *
         * Uses getCompressedTextureFormats to get the list of supported compression 
         * formats and then checks to see if any of them are GL_ETC1_RGB8_OES.
         * \param[in] verbose If true, prints out the number of supported texture compression formats and then lists the formats supported.
         */
        static bool isETCSupported(bool verbose = false);

        /**
         * \brief Create a texture using random data.
         *     
         * \param[in] width The required width of the texture.
         * \param[in] height The required height of the texture.
         * \param[in] textureData A pointer to the created texture data.
         */
        static void createTexture(unsigned int width, unsigned int height, GLvoid **textureData);

        /**
         * \brief Create a 1 component texture of uniform colour.
         * 
         * \param [in]  width       The required width of the texture.
         * \param [in]  height      The required height of the texture.
         * \param [in]  red         The required red channel.
         * \param [out] textureData Output texture.
         */
        static void createTexture(unsigned int width, unsigned int height, unsigned int red, GLvoid **textureData);

        /**
         * \brief Create uniform texture using given color with 1 short integer components
         * 
         * \param [in]  width       The required width of the texture.
         * \param [in]  height      The required height of the texture.
         * \param [in]  red         The required red channel.
         * \param [out] textureData Output texture.
         */
        static void createTexture(unsigned int width, unsigned int height, short red, short **textureData);

        /**
         * \brief Deletes previously created texture.
         * 
         * \param [in] textureData Texture to be deleted.
         */
        static void deleteTextureData(GLvoid **textureData);

        /**
         * \brief Load texture data from a file into memory.
         *
         * \param[in] filename The filename of the texture to load.
         * \param[out] textureData Pointer to the texture that has been loaded.
         */
        static void loadData(const char *filename, unsigned char **textureData);

        /**
         * \brief Load header and texture data from a pkm file into memory.
         *
         * \param[in] filename The filename of the texture to load.
         * \param[out] etcHeader Pointer to the header that has been loaded.
         * \param[out] textureData Pointer to the texture that has been loaded.      
         */
        static void loadPKMData(const char *filename, ETCHeader* etcHeader, unsigned char **textureData);

        /**
         * \brief Load compressed mipmaps into memory
         *
         * Load the base level, calculate how many Mipmap levels there are.
         * Load the PKM files into memory.
         * Load the data into the texture mipmap levels.
         * \param[in] filenameBase The base filename of the texture mipmap levels. Will have the mipmap level number appended to it to load all of the mipmap levels.
         * For example, if filenameBase = "texture_", this method will try to load the files "texture_0", "texture_1", "texture_2", etc..
         * \param[in] filenameSuffix Any suffix to the mipmap filenames. Most commonly used for file extensions.
         * For example, if filenameSuffix = ".pkm", this method will append ".pkm" to all the files it tries to load.
         * \param[out] textureID The texture ID of the texture that has been loaded.
         */
        static void loadCompressedMipmaps(const char *filenameBase, const char *filenameSuffix, GLuint *textureID);

        /**
         * \brief Copies float pixel data of one line of the image from source to
         * destination in the reverse direction.
         *
         * \param[out] destination Place in memory where the reversed data will be copied to. Cannot be NULL.
         * \param[in] source Place from which the copying should start from. Cannot be NULL.
         * \param[in] lineWidth Number of RGB pixels that will be copied.
         */
        static void reversePixelLine(float* destination, const float* source, int lineWidth);

        /**
         * \brief Load BMP texture data from a file into memory.
         *
         * \param fileName          The file name of the texture to be loaded.
         *                          Cannot be NULL.
         * \param imageWidthPtr     Deref will be used to store image width.
         * \param imageHeightPtr    Deref will be used to store image height.
         * \param textureDataPtrPtr Pointer to a memory where loaded texture data will be stored.
         *                          Cannot be NULL.
         */
        static void loadBmpImageData(const char*     fileName,
                                     int*            imageWidthPtr,
                                     int*            imageHeightPtr,
                                     unsigned char** textureDataPtrPtr);
    };
}
#endif /* TEXTURE_H */
