/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

#define HISTOGRAM_SIZE  16   /* Must be a power of 2 */

GLubyte  *pixels;
GLsizei   width, height;
GLboolean sinks[2] = {GL_FALSE, GL_TRUE};
struct hist_type_t {
	GLenum hformat;
	GLenum type;
	GLenum gformat;
} hist_types[] = {
	{GL_ALPHA, GL_ALPHA, },
	{GL_ALPHA4, GL_ALPHA, },
	{GL_ALPHA8, GL_ALPHA, },
	{GL_ALPHA12, GL_ALPHA, },
	{GL_ALPHA16, GL_ALPHA, },
	{GL_LUMINANCE, GL_LUMINANCE, },
	{GL_LUMINANCE4, GL_LUMINANCE, },
	{GL_LUMINANCE8, GL_LUMINANCE, },
	{GL_LUMINANCE12, GL_LUMINANCE, },
	{GL_LUMINANCE16, GL_LUMINANCE, },
	{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, },
	{GL_LUMINANCE4_ALPHA4, GL_LUMINANCE_ALPHA, },
	{GL_LUMINANCE6_ALPHA2, GL_LUMINANCE_ALPHA, },
	{GL_LUMINANCE8_ALPHA8, GL_LUMINANCE_ALPHA, },
	{GL_LUMINANCE12_ALPHA4, GL_LUMINANCE_ALPHA, },
	{GL_LUMINANCE12_ALPHA12, GL_LUMINANCE_ALPHA, },
	{GL_LUMINANCE16_ALPHA16, GL_LUMINANCE_ALPHA, },
	{GL_R3_G3_B2, GL_RGB, GL_UNSIGNED_BYTE_3_3_2},
	{GL_RGB, GL_BGR, GL_INT},//
	{GL_RGB, GL_RED, GL_BYTE},//
	{GL_RGB, GL_BGR, GL_BITMAP},//
	{GL_RGB, GL_GREEN, GL_SHORT},//
	{GL_RGB, GL_BLUE, GL_FLOAT},//
	{GL_RGB4, GL_BGRA, GL_UNSIGNED_SHORT_4_4_4_4},
	{GL_RGB5, GL_BGR, GL_UNSIGNED_SHORT_5_6_5_REV},
	{GL_RGB8, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV},
	{GL_RGB10, GL_BGRA, GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGB12, GL_RGB, GL_UNSIGNED_SHORT_5_6_5},
	{GL_RGB16, GL_RGB, GL_UNSIGNED_SHORT},
	{GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV},
	{GL_RGBA2, GL_BGR, GL_UNSIGNED_BYTE_2_3_3_REV},
	{GL_RGBA4, GL_BGRA, GL_UNSIGNED_SHORT_4_4_4_4_REV},
	{GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1},
	{GL_RGBA8, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8},
	{GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_10_10_10_2},
	{GL_RGBA12, GL_RGBA, GL_UNSIGNED_BYTE},
	{GL_RGBA16, GL_RGBA, GL_UNSIGNED_INT}
};

GLenum targets[] = {
        GL_HISTOGRAM,
	GL_PROXY_HISTOGRAM
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

void init(void)
{
    string file = (string)PICTURE_PATH + "leeds.bin";
    pixels = readImage(file.c_str(), &width, &height); 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void getdata(GLenum target)
{
	GLfloat paramf;
	GLint parami;

	glGetHistogramParameterfv(target, GL_HISTOGRAM_WIDTH, &paramf);
	LOGIF("GL_HISTOGRAM_WIDTH=%f\n", paramf);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_FORMAT, &parami);
	LOGIF("GL_HISTOGRAM_FORMAT=%d\n", parami);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_RED_SIZE, &parami);
	LOGIF("GL_HISTOGRAM_RED_SIZE=%d\n", parami);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_GREEN_SIZE, &parami);
	LOGIF("GL_HISTOGRAM_GREEN_SIZE=%d\n", parami);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_BLUE_SIZE, &parami);
	LOGIF("GL_HISTOGRAM_BLUE_SIZE=%d\n", parami);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_ALPHA_SIZE, &parami);
	LOGIF("GL_HISTOGRAM_ALPHA_SIZE=%d\n", parami);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_LUMINANCE_SIZE, &parami);
	LOGIF("GL_HISTOGRAM_LUMINANCE_SIZE=%d\n", parami);
	glGetHistogramParameteriv(target, GL_HISTOGRAM_SINK, &parami);
	LOGIF("GL_HISTOGRAM_SINK=%d\n", parami);
}

void display(GLenum target, int i, GLboolean sink)
{
   GLushort values[HISTOGRAM_SIZE][3];
   
   glHistogram(GL_HISTOGRAM, HISTOGRAM_SIZE, hist_types[i].hformat, sink);
   glEnable(GL_HISTOGRAM);

   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(1, 1);
   glDrawPixels(width, height, GL_RGB, hist_types[i].type, pixels);
   
   glGetHistogram(GL_HISTOGRAM, sink, hist_types[i].gformat, hist_types[i].type, values);

   /* Plot histogram */
   
   glBegin(GL_LINE_STRIP);
   glColor3f(1.0, 0.0, 0.0);
   for ( i = 0; i < HISTOGRAM_SIZE; i++ )
       glVertex2s(i, values[i][0]);
   glEnd();

   glBegin(GL_LINE_STRIP);
   glColor3f(0.0, 1.0, 0.0);
   for ( i = 0; i < HISTOGRAM_SIZE; i++ )
       glVertex2s(i, values[i][1]);
   glEnd();

   glBegin(GL_LINE_STRIP);
   glColor3f(0.0, 0.0, 1.0);
   for ( i = 0; i < HISTOGRAM_SIZE; i++ )
       glVertex2s(i, values[i][2]);
   glEnd();
   glFlush();
getdata(target);
glResetHistogram(target);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 256, 0, 10000, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    string file = "gl13-histrogram";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    init();
    for(int i=0;i<ARRAY_NUM(hist_types);i++) {
    for(int j=0;j<ARRAY_NUM(sinks);j++) {
    for(int k=0;k<ARRAY_NUM(targets);k++) {
	display(targets[k], i, sinks[j]);
	string sink_name = GET_BOOL(sinks[i]);
	char ss[2];
	sprintf(ss, "%d", i);
	string target_name = get_enum_name(targets[k]);
	string filename = file + "-" + sink_name + "-" + "-" + target_name + ss + ".bmp";
	LOGIF("filename=%s\n", filename.c_str());
	save2bmp(filename.c_str());
    }}}
    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
