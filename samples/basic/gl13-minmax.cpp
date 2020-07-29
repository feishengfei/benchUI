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
GLboolean sinks[] = {
        GL_FALSE,
	GL_TRUE
};
struct minmax_param_t {
	GLenum format;
	GLenum getformat;
	GLenum gettype;
} minmax_params[] = {
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
	{GL_R3_G3_B2, GL_RGB, GL_UNSIGNED_BYTE_3_3_2},
	{GL_R3_G3_B2, GL_BGR, GL_UNSIGNED_BYTE_2_3_3_REV},
	{GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5},
	{GL_RED, GL_RGB, GL_BYTE},
	{GL_GREEN, GL_RGB, GL_BYTE},
	{GL_BLUE, GL_RGB, GL_SHORT},
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

void getdata(int i, GLboolean sink)
{
   GLint params;
   GLint values[2];

   glGetMinmax(GL_MINMAX, sink, minmax_params[i].getformat, minmax_params[i].gettype, values);
   LOGIF(" Red   : min = %d   max = %d\n", values[0], values[3]);
   glGetMinmaxParameteriv(GL_MINMAX, GL_MINMAX_FORMAT, &params);
   LOGIF("glGetMinmaxParameteriv(GL_MINMAX_FORMAT) = %d\n", params);
   glGetMinmaxParameteriv(GL_MINMAX, GL_MINMAX_SINK, &params);
   LOGIF("glGetMinmaxParameteriv(GL_MINMAX_SINK) = %d\n", params);
}

void display(int i, GLboolean sink)
{
   GLubyte  values[6];
   
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glClearColor(0.0, 0.0, 0.0, 0.0);

   glMinmax(GL_MINMAX, minmax_params[i].format, sink);
   glEnable(GL_MINMAX);

   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(1, 1);
   glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
   glFlush();
getdata(i, sink);
glResetMinmax(GL_MINMAX);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{

    string file = (string)PICTURE_PATH + "leeds.bin";
    pixels = readImage(file.c_str(), &width, &height); 

    file = "resethistrogram";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0;i<ARRAY_NUM(minmax_params);i++) {
    for(int j=0;j<ARRAY_NUM(sinks);j++) {
	display(i,sinks[j]);
	char ss[2];
	sprintf(ss, "%d", i);
	string target_name = GET_BOOL(sinks[j]);
	string filename = file + "-" + target_name + ss + ".bmp";
	LOGIF("filename=%s\n", filename.c_str());
	save2bmp(filename.c_str());
	glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
