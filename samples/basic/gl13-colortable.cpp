/**
 void glResetHistogram(GLenum target);
 Parameters: target Must be GL_HISTOGRAM.
 Description: glResetHistogram resets all the elements of the current histogram table to zero.
 Notes:
       glResetHistogram is present only if ARB_imaging is returned when glGetString is called with an argument of GL_EXTENSIONS.
 */
#include "gl-util.h"

#define HISTOGRAM_SIZE  16   /* Must be a power of 2 */

GLubyte  *pixels;
GLsizei   width, height;
GLenum targets[] = {
        GL_COLOR_TABLE,
        GL_POST_CONVOLUTION_COLOR_TABLE,
        GL_POST_COLOR_MATRIX_COLOR_TABLE,
        GL_PROXY_COLOR_TABLE,
        GL_PROXY_POST_CONVOLUTION_COLOR_TABLE,
        GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE
};
struct colortable_t {
	GLenum interformat;
	GLenum format;
	GLenum type;
} colortable_params[] = {
	{GL_ALPHA, GL_ALPHA, GL_FLOAT},
	{GL_ALPHA4, GL_ALPHA, GL_BITMAP},
	{GL_ALPHA8, GL_ALPHA, GL_UNSIGNED_BYTE},
	{GL_ALPHA12, GL_ALPHA, GL_UNSIGNED_SHORT},
	{GL_ALPHA16, GL_ALPHA, GL_UNSIGNED_SHORT},
	{GL_LUMINANCE, GL_LUMINANCE, GL_INT},
	{GL_LUMINANCE4, GL_LUMINANCE, GL_BITMAP},
	{GL_LUMINANCE8, GL_LUMINANCE, GL_UNSIGNED_BYTE},
	{GL_LUMINANCE12, GL_LUMINANCE, GL_UNSIGNED_SHORT},
	{GL_LUMINANCE16, GL_LUMINANCE, GL_UNSIGNED_SHORT},
	{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE},
	{GL_LUMINANCE4_ALPHA4, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE},
	{GL_LUMINANCE6_ALPHA2, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE},
	{GL_LUMINANCE8_ALPHA8, GL_LUMINANCE_ALPHA, GL_UNSIGNED_SHORT},
	{GL_LUMINANCE12_ALPHA4, GL_LUMINANCE_ALPHA, GL_UNSIGNED_SHORT},
	{GL_LUMINANCE12_ALPHA12, GL_LUMINANCE_ALPHA, GL_UNSIGNED_INT},
	{GL_LUMINANCE16_ALPHA16, GL_LUMINANCE_ALPHA, GL_UNSIGNED_INT},
	{GL_INTENSITY, GL_RED, GL_INT},
	{GL_INTENSITY4, GL_GREEN, GL_BITMAP},
	{GL_INTENSITY8, GL_BLUE, GL_UNSIGNED_BYTE},
	{GL_INTENSITY12, GL_LUMINANCE, GL_UNSIGNED_SHORT},
	{GL_INTENSITY16, GL_LUMINANCE, GL_UNSIGNED_SHORT},
	{GL_R3_G3_B2, GL_RGB, GL_UNSIGNED_BYTE_3_3_2},
	{GL_R3_G3_B2, GL_BGR, GL_UNSIGNED_BYTE_2_3_3_REV},
	{GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5},
	{GL_RGB4, GL_BGR, GL_UNSIGNED_SHORT_4_4_4_4_REV},
	{GL_RGB5, GL_BGR, GL_UNSIGNED_SHORT_1_5_5_5_REV},
	{GL_RGB8, GL_BGR, GL_UNSIGNED_INT_8_8_8_8_REV},
	{GL_RGB10, GL_BGR, GL_UNSIGNED_INT_10_10_10_2},
	{GL_RGB12, GL_RGB, GL_UNSIGNED_SHORT},
	{GL_RGB16, GL_RGB, GL_UNSIGNED_SHORT},
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_6_5_REV},
	{GL_RGBA2, GL_RGBA, GL_UNSIGNED_BYTE},
	{GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4},
	{GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1},
	{GL_RGBA8, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8},
	{GL_RGB10_A2, GL_BGRA, GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGBA12, GL_RGBA, GL_UNSIGNED_INT},
	{GL_RGBA16, GL_RGBA, GL_UNSIGNED_INT}
};
unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLubyte*
readImage( const char* filename, GLsizei* width, GLsizei *height )
{
    int       n;
    GLubyte*  pixels;

    FILE* infile = fopen( filename, "rb" );

    if ( !infile ) {
	fprintf( stderr, "Unable to open file '%s'\n", filename );
	return NULL;
    }

    fread( width, sizeof( GLsizei ), 1, infile );
    fread( height, sizeof( GLsizei ), 1, infile );

    n = 3 * (*width) * (*height);

    pixels = (GLubyte *) malloc( n * sizeof( GLubyte ));
    if ( !pixels ) {
	fprintf( stderr, "Unable to malloc() bytes for pixels\n" );
	return NULL;
    }

    fread( pixels, sizeof( GLubyte ), n, infile );
    
    fclose( infile );

    return pixels;
}

void getdata(int i, GLenum target)
{
   GLubyte  colorTable[256][3];
   GLfloat paramf;
   GLint parami;

   if(target == GL_PROXY_COLOR_TABLE)
        target = GL_COLOR_TABLE;
   else if(target == GL_PROXY_POST_CONVOLUTION_COLOR_TABLE)
        target = GL_POST_CONVOLUTION_COLOR_TABLE;
   else if(target == GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE)
        target = GL_POST_COLOR_MATRIX_COLOR_TABLE;

	glGetColorTableParameterfv(target, GL_COLOR_TABLE_BIAS, &paramf);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_BIAS=%f\n", paramf);
	glGetColorTableParameterfv(target, GL_COLOR_TABLE_SCALE, &paramf);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_SCALE=%f\n", paramf);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_FORMAT, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_FORMAT=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_WIDTH, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_WIDTH=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_RED_SIZE, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_RED_SIZE=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_GREEN_SIZE, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_GREEN_SIZE=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_BLUE_SIZE, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_BLUE_SIZE=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_ALPHA_SIZE, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_ALPHA_SIZE=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_LUMINANCE_SIZE, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_LUMINANCE_SIZE=%d\n", parami);
	glGetColorTableParameteriv(target, GL_COLOR_TABLE_INTENSITY_SIZE, &parami);
	LOGIF("GetColorTableParameteriv(target, GL_COLOR_TABLE_INTENSITY_SIZE=%d\n", parami);
   glGetColorTable(target, colortable_params[i].format, colortable_params[i].type, colorTable);
}

void display(int i, GLenum target)
{
   GLubyte  colorTable[256][3];
   GLfloat scale[4] = {0.5, 0.5, 0.5, 0.5};
   GLfloat bias[4] = {0.5, 0.5, 0.5, 0.5};
   
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glClearColor(0.0, 0.0, 0.0, 0.0);

   /* Set up an inverse color table */
   
   for ( i = 0; i < 256; ++i ) {
       colorTable[i][0] = 255 - i;
       colorTable[i][1] = 255 - i;
       colorTable[i][2] = 255 - i;
   }

   glColorTable(target, colortable_params[i].interformat, 256, colortable_params[i].format, colortable_params[i].type, colorTable);
   glEnable(GL_COLOR_TABLE);

   if(target == GL_PROXY_COLOR_TABLE)
        target = GL_COLOR_TABLE;
   else if(target == GL_PROXY_POST_CONVOLUTION_COLOR_TABLE)
        target = GL_POST_CONVOLUTION_COLOR_TABLE;
   else if(target == GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE)
        target = GL_POST_COLOR_MATRIX_COLOR_TABLE;
   glColorTableParameterfv(target, GL_COLOR_TABLE_SCALE, scale);
   glColorTableParameterfv(target, GL_COLOR_TABLE_BIAS, bias);
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i( 1, 1 );
   glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels );
   glFlush();
   getdata(i, target);
   glDisable(GL_COLOR_TABLE);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
    string picture = (string)PICTURE_PATH + "leeds.bin";
    pixels = readImage(picture.c_str(), &width, &height);   
    string file = "gl13-colortable";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0;i<ARRAY_NUM(colortable_params);i++) {
    for(int j=0;j<ARRAY_NUM(targets);j++) {
	display(i,targets[j]);
	char ss[2];
	sprintf(ss, "%d", i);
	string target_name = get_enum_name(targets[j]);
	string filename = file + "-" + target_name + ss + ".bmp";
	LOGIF("filename=%s\n", filename.c_str());
	save2bmp(filename.c_str());
    glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
