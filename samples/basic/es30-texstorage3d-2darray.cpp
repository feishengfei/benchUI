/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstorage3d-2darray.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstorage3d-2darray related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "teximage3d.vert";
string fragmentShaderFilename = "teximage3d.frag";

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iTexPosition = -1;
GLuint vao;
GLuint positionBufferObject;
const int texUnit=0;
GLuint samplerUniform;
GLuint texBufferObject;
Matrix trans;
GLint MVPLoc;
float vertices[] = {
	0,0,0,  1,0,0,  0,1,0,
	1,0,0,  0,1,0,  1,1,0,

	0,0,0,  0,1,0,  0,0,1,
	0,1,0,  0,0,1,  0,1,1,

	0,0,0,  0,0,1,  1,0,0,
	0,0,1,  1,0,0,  1,0,1,  

	0,0,1,  0,1,1,  1,0,1,
	0,1,1,  1,0,1,  1,1,1,

	0,1,0,  0,1,1,  1,1,0,
	0,1,1,  1,1,0,  1,1,1,

	1,0,0,  1,0,1,  1,1,0,
	1,0,1,  1,1,0,  1,1,1,
};

struct {
	GLenum interfmt;
	GLenum format;
	GLenum type;
} factors[] = {
	{GL_R8, GL_RED , GL_UNSIGNED_BYTE},
	{GL_R8_SNORM, GL_RED , GL_BYTE},
	{GL_R8UI, GL_RED_INTEGER , GL_UNSIGNED_BYTE},
	{GL_R8I, GL_RED_INTEGER , GL_BYTE},
	{GL_RG8, GL_RG , GL_UNSIGNED_BYTE},
	{GL_RG8_SNORM, GL_RG , GL_BYTE},
	{GL_RG8UI, GL_RG_INTEGER , GL_UNSIGNED_BYTE},
	{GL_RG8I, GL_RG_INTEGER , GL_BYTE},
	{GL_RGB8, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_SRGB8, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_RGB565, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_RGB8_SNORM, GL_RGB , GL_BYTE},
	{GL_RGB8UI, GL_RGB_INTEGER , GL_UNSIGNED_BYTE},
	{GL_RGB8I, GL_RGB_INTEGER , GL_BYTE},
	{GL_RGBA8, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_SRGB8_ALPHA8, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_RGBA8_SNORM, GL_RGBA , GL_BYTE},
	{GL_RGB5_A1, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_RGBA4, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_RGBA8UI, GL_RGBA_INTEGER , GL_UNSIGNED_BYTE},
	{GL_RGBA8I, GL_RGBA_INTEGER , GL_BYTE},
	{GL_R16F, GL_RED , GL_FLOAT},
	{GL_R32F, GL_RED , GL_FLOAT},
	{GL_RG16F, GL_RG , GL_FLOAT},
	{GL_RG32F, GL_RG , GL_FLOAT},
	{GL_R11F_G11F_B10F, GL_RGB , GL_FLOAT},
	{GL_RGB9_E5, GL_RGB , GL_FLOAT},
	{GL_RGB16F, GL_RGB , GL_FLOAT},
	{GL_RGB32F, GL_RGB , GL_FLOAT},
	{GL_RGBA16F, GL_RGBA , GL_FLOAT},
	{GL_RGBA32F, GL_RGBA , GL_FLOAT},
	{GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT , GL_FLOAT},
	{GL_R16UI, GL_RED_INTEGER , GL_UNSIGNED_SHORT},
	{GL_R16I, GL_RED_INTEGER , GL_SHORT},
	{GL_RG16UI, GL_RG_INTEGER , GL_UNSIGNED_SHORT},
	{GL_RG16I, GL_RG_INTEGER , GL_SHORT},
	{GL_RGB16UI, GL_RGB_INTEGER , GL_UNSIGNED_SHORT},
	{GL_RGB16I, GL_RGB_INTEGER , GL_SHORT},
	{GL_RGBA16UI, GL_RGBA_INTEGER , GL_UNSIGNED_SHORT},
	{GL_RGBA16I, GL_RGBA_INTEGER , GL_SHORT},
	{GL_R32UI, GL_RED_INTEGER , GL_UNSIGNED_INT},
	{GL_R32I, GL_RED_INTEGER , GL_INT},
	{GL_RG32UI, GL_RG_INTEGER , GL_UNSIGNED_INT},
	{GL_RG32I, GL_RG_INTEGER , GL_INT},
	{GL_RGB32UI, GL_RGB_INTEGER , GL_UNSIGNED_INT},
	{GL_RGB32I, GL_RGB_INTEGER , GL_INT},
	{GL_RGB10_A2, GL_RGBA , GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGB10_A2UI, GL_RGBA_INTEGER , GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGBA32I, GL_RGBA_INTEGER , GL_INT},
	{GL_RGBA32UI, GL_RGBA_INTEGER , GL_UNSIGNED_INT},
	{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT , GL_UNSIGNED_INT},
	{GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT , GL_UNSIGNED_INT},
	{GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL , GL_UNSIGNED_INT_24_8},
	{GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL , GL_FLOAT_32_UNSIGNED_INT_24_8_REV},
	{GL_COMPRESSED_RGB8_ETC2, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_COMPRESSED_SRGB8_ETC2, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_COMPRESSED_RGBA8_ETC2_EAC, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_COMPRESSED_R11_EAC, GL_RED , GL_UNSIGNED_SHORT},
	{GL_COMPRESSED_SIGNED_R11_EAC, GL_RED , GL_UNSIGNED_SHORT},
	{GL_COMPRESSED_RG11_EAC, GL_RG , GL_UNSIGNED_SHORT},
	{GL_COMPRESSED_SIGNED_RG11_EAC, GL_RG , GL_UNSIGNED_SHORT},
	{GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, GL_RGBA , GL_UNSIGNED_SHORT},
};

#define	iWidth 16
#define	iHeight 16
#define iDepth 16

float angleX = 30, angleY = 30, angleZ = 30;
static GLubyte imageb[iDepth][iHeight][iWidth][4];
static GLushort images[iDepth][iHeight][iWidth][4];
static GLfloat imagef[iDepth][iHeight][iWidth][4];
static GLuint imagei[iDepth][iHeight][iWidth][4];

static GLuint image[] = {
	0x6a15b5ef, 0xba8ef150,
	0x3801e0af, 0xfcb32db2,
	0x1203b9ff, 0x9bb08df8,
	0x1d008ff1, 0x98bf7fff,
	0x9101ee70, 0xb7b9fddf,
	0x8e31d09a, 0xbc49faff,
	0xc744b64b, 0xc0259bd7,
	0x0e791424, 0x092941c1,
	0x4b04c23a, 0xf4a79cae,
	0x5a004f92, 0xdc27554c,
	0x660de1d4, 0x8192086e,
	0x31ca1286, 0x26182988,
	0xc1348023, 0xf0f4bf3f,
	0x8727dd2a, 0xacb79400,
	0x4d2b751d, 0x2745a39d,
	0x681ded60, 0x77b6efc7,
	0x6b08b670, 0x73fde1a7,
	0x11b50230, 0x00e1d66d,
	0x8f024992, 0x249c0068,
	0x4e0449fc, 0x786a0b6c,
	0x5d14ce1b, 0xb3664b0e,
	0x631d135d, 0xdb760531,
	0x6314063c, 0xf8cd9fa7,
	0x96004ff2, 0xfcf7caa1,
	0x39002190, 0x14496e1b,
	0x6315a696, 0x4cd58691,
	0x56345a27, 0x69589d5c,
	0x5d2998b5, 0x3e1cc54a,
	0x75308394, 0xbaac5dbb,
	0x9a221ce3, 0xf0ff5a83,
	0x4d1dbe9b, 0xdbb54d0e,
	0x5620f56b, 0xfb650d27,
	0x820cc94f, 0xb683afd5,
	0x5c181be1, 0xfcf99dbc,
	0x651da07b, 0xdb7fc2fa,
	0x462b03fd, 0xbb291d36,
	0x7527ddea, 0xbf316d2c,
	0x0261c914, 0x0a1bb001,
	0x0767120b, 0xa58060db,
	0xb300256d, 0xdfc991dc,
	0xaf1d27db, 0xf9e893f8,
	0x4e185fcb, 0xd122a635,
	0x0c3f93d2, 0x322d8b31,
	0x6c2a2f71, 0x927ee2d7,
	0x6d079038, 0x769db426,
	0x7b101d06, 0x088e9de4,
	0xd64fbf6d, 0xc15f9f27,
	0x69209063, 0x728258c7,
	0x7f2a9159, 0x873ce1d3,
	0x63008004, 0x686e9b73,
	0xa3301df9, 0xd7994f34,
	0x60211047, 0xb6e473ff,
	0x5d0000cd, 0xe7fedf3e,
	0x1c006832, 0xdad2f63a,
	0x440049f2, 0xe43791bb,
	0x0aa83624, 0x2664298d,
	0xc7273957, 0x178fe9ff,
	0x741498af, 0x9cad30d5,
	0x0496d2c8, 0x249c0003,
	0x7001800f, 0x3f319d94,
	0x42004f9e, 0xc4f62400,
	0x33024efe, 0xdb100dde,
	0x2b08e568, 0x137642d4,
	0x07511240, 0x4e582b36,
	0x6500a284, 0x1112483f,
	0x91051508, 0x3efefdda,
	0x4b0b44ff, 0x3d26d957,
	0x6f0d7ffc, 0xfcc9dd18,
	0x660bf5ef, 0x969d863e,
	0x8100ff4f, 0x60b59dd8,
	0x6f01b62b, 0x01dd94fc,
	0x640cdc0c, 0xb18098fc,
	0x891cb9fd, 0xdf26d47a,
	0x6e13d88d, 0xdf3f9f68,
	0x02313330, 0xc0ecc410,
	0x1000ced1, 0x3af1ffe7,
	0x30009d90, 0xdccf9fe7,
	0x3503a03b, 0x926e9724,
	0x30061e54, 0x029b9874,
	0x1e5c1ba3, 0xb158bb8d,
	0x520049e2, 0x0d9bc04d,
	0x6503a6b3, 0x262620cd,
	0x610289e9, 0x4ed0faff,
	0x5c071c06, 0x714fee3f,
	0x3402ee80, 0xb5929e6a,
	0x8700feff, 0x24f97b17,
	0x7e1db9fb, 0xd2d00f0c,
	0x930e6d4d, 0x309aa391,
	0x18703066, 0x4823c545,
	0x6600bc49, 0x30b1e407,
	0x7206769f, 0xdb760bd6,
	0x2e0049d2, 0x27908391,
	0x1e00c9ff, 0x3c493c09,
	0x42004f92, 0x246e07ac,
	0x49004978, 0x5312f07b,
	0x4222eb80, 0x4d5abb27,
	0x4c098236, 0xbaa2dfc7,
	0x104cb2bd, 0x0d222529,
	0x04513600, 0x18121009,
	0x3101ee60, 0x0ff59b9c,
	0x2b10cd2f, 0x41b427b1,
	0xa007b7f9, 0x782654e0,
	0x90072387, 0xb1ac9d8e,
	0x6b0150ef, 0x246dddb6,
	0x6c0321fa, 0x0dfeef3f,
	0x01361d9a, 0xc1d2aa86,
	0x8300027f, 0xaaa59fe4,
	0x7c0476b5, 0x097e623b,
	0x0480e9d6, 0x8eda6888,
	0x8f00f503, 0xdaabdddf,
	0x640049ee, 0xdfed4089,
	0x64052e39, 0x6d1216b7,
	0x552aff4c, 0x80a294d7,
	0x5116f956, 0x80c0bcd5,
	0x46097c5e, 0x7731c46d,
	0x750d794b, 0x8d14451b,
	0x6f1c364b, 0xdbc82ff6,
	0xb7168576, 0x02f798fc,
	0xa70bb5ad, 0x096dfd27,
	0x9f00f58f, 0x55dd6a3e,
	0x16ac1a90, 0x4adb6648,
	0x4600dbd3, 0x3bbb8db5,
	0x7b057119, 0xd3bf6b13,
	0x4800d236, 0x0c7ba224,
	0x02496c1a, 0xca006083,
	0x790649f6, 0x17e736da,
	0x056bdd10, 0xc9a1c491,
	0x3c003190, 0x18b627f1,
	0x5322e60a, 0x6cb79fff,
	0x5f2db9dd, 0xed77fd1b,
	0x7b2c4f9e, 0xe47f0248,
	0xc02ee678, 0x6b293a39,
	0xb037b563, 0xffb11b0f,
	0xa244f9cf, 0x56cc8156,
	0xc425ff2f, 0xda7032b6,
	0x7d02742e, 0x89152a8c,
	0x5e1cb9d9, 0xba9c8dba,
	0x562b80bd, 0x916fc93e,
	0x55232eb4, 0xd5649dfc,
	0x0e7682b1, 0xad6bc850,
	0x7e184927, 0xc2f79e97,
	0x4a0c7377, 0x82f1f4b8,
	0x5c278e1d, 0xb3034fcc,
	0x5d0f6d5d, 0x0ab56f27,
	0x1d7c80b6, 0x4dd2c226,
	0xaa24b760, 0xa9f2fffc,
	0xb63702f0, 0xdbb99d24,
	0x712bc87d, 0x9764fd3c,
	0xaf2c1e50, 0xfa4ffe3f,
	0xcf250256, 0xc9af9a42,
	0xa24ffe9f, 0xdc7e02da,
	0x80267651, 0xb7ad0389,
	0x7928fbfd, 0x9fcfc117,
	0x87205d03, 0xa822f5a7,
	0xab27c969, 0x7382288d,
	0x902278e2, 0xdb62d7b7,
	0x4d20b9d1, 0xb88c9ffc,
	0x570c7b0a, 0xbe52098c,
	0x471c6aa1, 0xb64cee5b,
	0x531bebd3, 0x6d9e046d,
	0x660110d9, 0xc4ff73db,
	0x530f633d, 0x40e9e09b,
	0x8329c96f, 0xff43d331,
	0x6822b67f, 0xffc9d3c1,
	0x4512c328, 0x48dc164e,
	0x6128af50, 0x3ffefb58,
	0x9b22b59b, 0x9894883d,
	0xd424e4d0, 0x96ad733b,
	0x870df8dd, 0xff9cef3e,
	0x7b109d60, 0xd64ff2fb,
	0x1c749d20, 0xa98002a8,
	0x7522668f, 0xe7bdbdb5,
	0x22680008, 0x91dbb835,
	0x68062bd7, 0x4140c3bf,
	0x0a5f253b, 0xa910cbb4,
	0x34a15a37, 0x319224d8,
	0x39003637, 0xbf702ead,
	0x4900f6fb, 0xe77ffe04,
	0x9100e6f6, 0x77c90ff6,
	0x7a245083, 0x76b917bb,
	0xee1af9ff, 0xff6d6b13,
	0xc627bf9b, 0xcaa40fdf,
	0x73108e69, 0x62a4bfb1,
	0x830ded60, 0xbbff6d27,
	0x8f06d048, 0x09769bfc,
	0xc903b63f, 0x416d9b24,
	0xd8077727, 0xcc1c99c4,
	0xc323fc9d, 0xf79b3ff4,
	0x7a291cff, 0xb8a64648,
	0x7723f9b0, 0x8d1bb991,
	0x6722e038, 0xed93abe5,
	0x4119b5d3, 0xdaa04b96,
	0x4528c2bc, 0x3e856cd2,
	0x6a117ff1, 0x6e8ffdbb,
	0xd505c0d3, 0xfe7f59b2,
	0x722231d9, 0x4a0064db,
	0xba35f750, 0xf67ef224,
	0x643530db, 0xf15da23d,
	0x380b90c8, 0xd6980b39,
	0x3910aef3, 0x731b1677,
	0x3210212c, 0xe0f58fbe,
	0x012a3624, 0x418d9008,
	0x3401ae57, 0x672ff741,
	0xaf371403, 0xb11dfb97,
	0x56206c61, 0x3fb6bfda,
	0x7d3d6c1d, 0xfc964fde,
	0x641a8233, 0xac13bdfe,
	0x0f3758bb, 0x356c4bb6,
	0x7820b60d, 0x08b79bbb,
	0x88212e01, 0x5aa43e36,
	0x075d9134, 0x43862d01,
	0x5f062567, 0x93717717,
	0x6a0ee4c6, 0x0d6adbbc,
	0x963efe43, 0xdb051c63,
	0x56155353, 0xb2730b72,
	0x0b473628, 0x40e494a4,
	0x520874e2, 0xa7b720c9,
	0x5602662d, 0x88d49ce4,
	0x500815cb, 0x26f9fb0a,
	0x9c14f614, 0x0b76fbdf,
	0xba117509, 0x48c34a3e,
	0x8c29228d, 0xfaf51db3,
	0x641fcf5d, 0x72130fb2,
	0x6422b5ab, 0x0db9fdf7,
	0xc7319c48, 0x6037f927,
	0xad0ccfaf, 0xdac25c6e,
	0x7d20f9f3, 0xbbae0f27,
	0x4d141524, 0xb1899ddc,
	0x46231548, 0x01c97397,
	0x801c36c1, 0x3ef9ed96,
	0xb91aac9d, 0xe4775981,
	0x6b11dce8, 0xae008c31,
	0x5005a2f3, 0xc4f91063,
	0x4f11b94d, 0xfa1ce0f6,
	0x5900255b, 0x6e10fd27,
	0x4f017645, 0xf7569361,
	0x840af39d, 0xd1850db9,
	0x41141be0, 0xbcf53db6,
	0x5d22c094, 0xbb716b3e,
	0xc82f1bf9, 0x42779dff,
	0x54198d5b, 0x13d428f4,
	0x740e5241, 0xd776eb36,
	0x9a0020c9, 0x914f9eff,
	0x7a070244, 0x6ecff9c7,
	0xad1f645d, 0x0f4fe5bf,
	0x7237eeba, 0xbc7a0e39,
	0x1666e940, 0xd880246d,
	0x9e06371b, 0xab864649,
	0x8e2071ff, 0xfff0bddb,
	0x3c057fb2, 0xd190b4c7,
	0x4a0249f2, 0xbcd8c401,
	0x5b1299c8, 0x8d0307ac,
	0xc830596d, 0xa1b17e3e,
	0x80207e72, 0x134ed5bb,
	0x611e150d, 0xb74ddedf,
	0x21401ba9, 0x7103342e
};

void makeImage(void) {
   int s, t, r;
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            imageb[r][t][s][0] = (GLubyte) (s * 17);
            imageb[r][t][s][1] = (GLubyte) (t * 17);
            imageb[r][t][s][2] = (GLubyte) (r * 17);
            imageb[r][t][s][3] = (GLubyte) (r * 17);
         }
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            imagef[r][t][s][0] = (GLfloat) (s * 17);
            imagef[r][t][s][1] = (GLfloat) (t * 17);
            imagef[r][t][s][2] = (GLfloat) (r * 17);
            imagef[r][t][s][3] = (GLfloat) (r * 17);
         }
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            images[r][t][s][0] = (GLushort) (s * 17);
            images[r][t][s][1] = (GLushort) (t * 17);
            images[r][t][s][2] = (GLushort) (r * 17);
            images[r][t][s][3] = (GLushort) (r * 17);
         }
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            imagei[r][t][s][0] = (GLuint) (s * 17);
            imagei[r][t][s][1] = (GLuint) (t * 17);
            imagei[r][t][s][2] = (GLuint) (r * 17);
            imagei[r][t][s][3] = (GLuint) (r * 17);
         }
}
bool setupGraphics(int width, int height, int i)
{
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
    		fragmentShaderPath.c_str());

    iLocPosition = glGetAttribLocation(programID, "pos");
    samplerUniform = glGetUniformLocation  (programID, "texSampler"); 
    MVPLoc = glGetUniformLocation  (programID, "MVP"); 
    trans = Matrix::createTranslation(-0.5, -0.5, -0.5);

    glUseProgram(programID);
    makeImage();
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texBufferObject);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, factors[i].interfmt,
							iWidth, iHeight, iDepth));
    if(i<21) {
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0,0,0, iWidth, iHeight,
							 iDepth, factors[i].format, factors[i].type, imageb));
    } else if(i<32) {
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0,0,0, iWidth, iHeight,
							 iDepth, factors[i].format, factors[i].type, imagef));
    } else if(i<40) {
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0,0,0, iWidth, iHeight,
							 iDepth, factors[i].format, factors[i].type, images));
    } else if(i<54) {
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0,0,0, iWidth, iHeight,
							 iDepth, factors[i].format, factors[i].type, imagei));
    } else {
    GL_CHECK(glCompressedTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0,0,0, 16,16,16,
									   factors[i].interfmt, sizeof(image), image));
    }

    Matrix rotationX = Matrix::createRotationX(angleX);
    Matrix rotationY = Matrix::createRotationY(angleY);
    Matrix rotationZ = Matrix::createRotationY(angleY);
    Matrix rotation = rotationX * rotationY;
    rotation = rotation * rotationZ;

    Matrix MVP = rotation * trans;
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, MVP.getAsArray());
    glUniform1i(samplerUniform, 0);

    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    GL_CHECK(glUseProgram(programID));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY,texBufferObject);

    glEnableVertexAttribArray(iLocPosition);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
}

void Sample::test() {
	for(int i=0; i<ARRAY_NUM(factors); i++) {
		setupGraphics(WINDOW_W, WINDOW_H, i);
		renderFrame();
		char ss[2];
		sprintf(ss, "%d", i);
		string factorname = get_enum_name(factors[i].interfmt);
		string bmp_file  = filename + "-" + ss + "-" + factorname + ".bmp";
		LOGI("bmp_file=%s", bmp_file.c_str());
		save2bmp(bmp_file.c_str());
		Sample::SwapBuffers();
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
