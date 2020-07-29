/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file getInternalformat.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-27, Init file
 * @brief basic test for related API
 * @par TestPoints:
        void glGetInternalformativ(GLenum target,GLenum internalformat,	GLenum pname,GLsizei bufSize,GLint *params);

The following base internal formats from table 3.16 are color-renderable:ALPHA,RED,RG,RGB,and RGBA.
The  sized  internal  formats  from  ta-ble  3.17  that  have  a  color-renderable  base  internal  format  are  also  color-renderable.   
RGBA, Depth, and Stencil ValuesInternal ComponentsALPHAAADEPTH_COMPONENTDepthDDEPTH_STENCILDepth,StencilD,SLUMINANCERLLUMINANCE_ALPHAR,AL,AINTENSITYRIREDRRRGR,GR,GRGBR,G,BR,G,BRGBA

An internal format is depth-renderable if it is DEPTH_COMPONENT or one of  the  formats  from  table  3.19  whose  base  internal  format  is DEPTH_COMPONENT or DEPTH_STENCIL. 

stencil-renderable internalformat is:
GL_STENCIL_INDEX1          
GL_STENCIL_INDEX4          
GL_STENCIL_INDEX8          
GL_STENCIL_INDEX16
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLenum targets[] = {
    GL_TEXTURE_1D, 
    GL_TEXTURE_1D_ARRAY, 
    GL_TEXTURE_2D, 
    GL_TEXTURE_2D_ARRAY, 
    GL_TEXTURE_3D, 
    GL_TEXTURE_CUBE_MAP, 
    GL_TEXTURE_CUBE_MAP_ARRAY, 
    GL_TEXTURE_RECTANGLE, 
    GL_TEXTURE_BUFFER, 
    GL_RENDERBUFFER, 
    GL_TEXTURE_2D_MULTISAMPLE, 
    GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

GLenum pnames[] = {
    GL_NUM_SAMPLE_COUNTS,
    GL_SAMPLES, /*The maximum value in GL_SAMPLES is guaranteed to be at least the lowest of the following:
    The value of GL_MAX_INTEGER_SAMPLES if internalformat is a signed or unsigned integer format.
    The value of GL_MAX_DEPTH_TEXTURE_SAMPLES if internalformat is a depth- or stencil-renderable format and target is GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
    The value of GL_MAX_COLOR_TEXTURE_SAMPLES if internalformat is a color-renderable format and target is GL_TEXTURE_2D_MULTISAMPLE or GL_TEXTURE_2D_MULTISAMPLE_ARRAY.
    The value of GL_MAX_SAMPLES.
*/
    GL_INTERNALFORMAT_SUPPORTED,
    GL_INTERNALFORMAT_PREFERRED,
    GL_INTERNALFORMAT_RED_SIZE, 
    GL_INTERNALFORMAT_GREEN_SIZE, 
    GL_INTERNALFORMAT_BLUE_SIZE, 
    GL_INTERNALFORMAT_ALPHA_SIZE, 
    GL_INTERNALFORMAT_DEPTH_SIZE, 
    GL_INTERNALFORMAT_STENCIL_SIZE, 
    GL_INTERNALFORMAT_SHARED_SIZE,
    GL_INTERNALFORMAT_RED_TYPE, 
    GL_INTERNALFORMAT_GREEN_TYPE, 
    GL_INTERNALFORMAT_BLUE_TYPE, 
    GL_INTERNALFORMAT_ALPHA_TYPE, 
    GL_INTERNALFORMAT_DEPTH_TYPE, 
    GL_INTERNALFORMAT_STENCIL_TYPE,
    GL_MAX_WIDTH, 
    GL_MAX_HEIGHT, 
    GL_MAX_DEPTH, 
    GL_MAX_LAYERS,
    GL_COLOR_COMPONENTS,
    GL_COLOR_RENDERABLE, 
    GL_DEPTH_RENDERABLE,
    GL_STENCIL_RENDERABLE,
    GL_FRAMEBUFFER_RENDERABLE,  
    GL_FRAMEBUFFER_RENDERABLE_LAYERED,
    GL_FRAMEBUFFER_BLEND,
    GL_READ_PIXELS,
    GL_READ_PIXELS_FORMAT,
    GL_READ_PIXELS_TYPE,
    GL_TEXTURE_IMAGE_FORMAT,
    GL_TEXTURE_IMAGE_TYPE,
    GL_GET_TEXTURE_IMAGE_FORMAT,
    GL_GET_TEXTURE_IMAGE_TYPE,
    GL_MIPMAP,
    GL_GENERATE_MIPMAP,
    GL_AUTO_GENERATE_MIPMAP,
    GL_COLOR_ENCODING,
    GL_SRGB_READ,
    GL_SRGB_WRITE,
    GL_FILTER,
    GL_VERTEX_TEXTURE,
    GL_TESS_CONTROL_TEXTURE, 
    GL_TESS_EVALUATION_TEXTURE, 
    GL_GEOMETRY_TEXTURE, 
    GL_FRAGMENT_TEXTURE, 
    GL_COMPUTE_TEXTURE, 
    GL_TEXTURE_SHADOW, 
    GL_TEXTURE_GATHER, 
    GL_TEXTURE_GATHER_SHADOW, 
    GL_SHADER_IMAGE_LOAD, 
    GL_SHADER_IMAGE_STORE, 
    GL_SHADER_IMAGE_ATOMIC, 
    GL_IMAGE_TEXEL_SIZE, 
    GL_IMAGE_COMPATIBILITY_CLASS, 
    GL_IMAGE_PIXEL_FORMAT, 
    GL_IMAGE_PIXEL_TYPE, 
    GL_IMAGE_FORMAT_COMPATIBILITY_TYPE, 
    GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST, 
    GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST, 
    GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE, 
    GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE, 
    GL_TEXTURE_COMPRESSED, 
    GL_TEXTURE_COMPRESSED_BLOCK_WIDTH, 
    GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT, 
    GL_TEXTURE_COMPRESSED_BLOCK_SIZE, 
    GL_CLEAR_BUFFER, 
    GL_TEXTURE_VIEW, 
    GL_VIEW_COMPATIBILITY_CLASS, 
    GL_CLEAR_TEXTURE
};

GLenum internalformats[] = {
    GL_R16F                          ,
    GL_R32F                          ,
    GL_RG16F                         ,
    GL_RG32F                         ,
    GL_RGBA32F                       ,
    GL_RGB32F                        ,
    GL_RGBA16F                       ,
    GL_RGB16F                        ,
    GL_R11F_G11F_B10F                ,
    GL_RGB9_E5                       ,
    GL_R8I                           ,
    GL_R8UI                          ,
    GL_R16I                          ,
    GL_R16UI                         ,
    GL_R32I                          ,
    GL_R32UI                         ,
    GL_RG8I                          ,
    GL_RG8UI                         ,
    GL_RG16I                         ,
    GL_RG16UI                        ,
    GL_RG32I                         ,
    GL_RG32UI                        ,
    GL_RGBA32UI                      ,
    GL_RGB32UI                       ,
    GL_RGBA16UI                      ,
    GL_RGB16UI                       ,
    GL_RGBA8UI                       ,
    GL_RGB8UI                        ,
    GL_RGBA32I                       ,
    GL_RGB32I                        ,
    GL_RGBA16I                       ,
    GL_RGB16I                        ,
    GL_RGBA8I                        ,
    GL_RGB8I                         ,

    GL_RED                           ,
    GL_GREEN                         ,
    GL_BLUE                          ,
    GL_ALPHA                         ,
    GL_RGB                           ,
    GL_RGBA                          
};

void Sample::test() {
    GLenum target;
    GLenum internalformat;
    GLenum pname;
    GLsizei bufSize;
    GLint params[2];
//glGetInternalformativ(GLenum target,GLenum internalformat,	GLenum pname,GLsizei bufSize,GLint *params);
    for(int i=0; i<ARRAY_NUM(targets); i++) {
    for(int j=0; j<ARRAY_NUM(pnames); j++) {
        target = targets[i];
        pname = pnames[j];
        GL_CHECK(glGetInternalformativ(target, GL_RGBA, pname, sizeof(params), params));
        LOGI("%d:Get(%s, %s) %d, %s\n", i*ARRAY_NUM(pnames)+j, get_enum_name(target), get_enum_name(pname), params[0], get_enum_name(params[0]));
    }}
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}
