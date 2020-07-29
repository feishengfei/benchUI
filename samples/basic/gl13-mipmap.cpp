/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

GLfloat texcoord[]={
	0.0, 1.0, 
	0.0, 0.0,
	1.0, 1.0, 
	1.0, 0.0
};

GLfloat vertice[]={
	-2.0, 1.0, 0.0,
	-2.0, -1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, -1.0, 0.0
};

GLenum factors[] = {
            GL_NEAREST_MIPMAP_NEAREST,
            GL_LINEAR_MIPMAP_NEAREST,
            GL_NEAREST_MIPMAP_LINEAR,
            GL_LINEAR_MIPMAP_LINEAR
};

GLenum gens[] = {
          GL_TRUE,
          GL_FALSE
};

GLenum hints[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};


unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
void makeCheckImages()
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) (255-c);
         checkImage[i][j][1] = (GLubyte) 255;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

static GLuint texName;

GLvoid draw_rect_tex(float x, float y, float w, float h,
	      float tx, float ty, float tw, float th)
{
	float verts[4][4];
	float tex[4][2];

	verts[0][0] = x + w;
	verts[0][1] = y;
	verts[0][2] = 0.0;
	verts[0][3] = 1.0;
	tex[0][0] = tx + tw;
	tex[0][1] = ty;
	verts[1][0] = x;
	verts[1][1] = y;
	verts[1][2] = 0.0;
	verts[1][3] = 1.0;
	tex[1][0] = tx;
	tex[1][1] = ty;
	verts[2][0] = x + w;
	verts[2][1] = y + h;
	verts[2][2] = 0.0;
	verts[2][3] = 1.0;
	tex[2][0] = tx + tw;
	tex[2][1] = ty + th;
	verts[3][0] = x;
	verts[3][1] = y + h;
	verts[3][2] = 0.0;
	verts[3][3] = 1.0;
	tex[3][0] = tx;
	tex[3][1] = ty + th;

	glVertexPointer(4, GL_FLOAT, 0, verts);
	glEnableClientState(GL_VERTEX_ARRAY);

	glClientActiveTexture(GL_TEXTURE1);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

GLuint rgbw_texture(GLenum internalFormat, int w, int h,GLenum hint, GLenum factor, GLenum gen)
{
	int size, level;
	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
        GL_CHECK(glHint(GL_GENERATE_MIPMAP_HINT, hint));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, factor);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, gen);

	for (level = 0, size = w > h ? w : h; size > 0; level++, size >>= 1) {
		makeCheckImages();
		glTexImage2D(GL_TEXTURE_2D, level, internalFormat,
			     w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

		if (w > 1)
			w >>= 1;
		if (h > 1)
			h >>= 1;
	}

	return tex;
}

void getdata()
{
GLint parami;
glGetIntegerv(GL_CLIENT_ACTIVE_TEXTURE, &parami);
LOGIF("get(GL_CLIENT_ACTIVE_TEXTURE)=%d\n",parami);
}

void renderFrame(GLenum hint, GLenum factor, GLenum gen)
{
	GLuint tex;
	GLint param;

	tex = rgbw_texture(GL_RGBA, checkImageWidth, checkImageHeight,hint,factor, gen);
	glClearColor(0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);

	draw_rect_tex(-1, -1, 2, 2, 0, 0, 1, 1);
	glGetTexParameteriv(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, &param);
	LOGIF("GetTexParameter(GL_GENERATE_MIPMAP): %d\n", param);
	glFlush(); 
getdata();
	glDeleteTextures(1, &tex);
	glDisable(GL_TEXTURE_2D);
}

int main(int argc, char** argv)
{
    string file = "gl13-mipmap";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<4; i++) {
        for(int j=0; j<2; j++) {
        for(int k=0; k<3; k++) {
            string factor_name = get_enum_name(factors[i]);
            string gen_name = GET_BOOL(gens[j]);
            string hint_name = get_enum_name(hints[k]);
	    string filename = file + "-" + factor_name + "-" + gen_name + "-" + hint_name + ".bmp";
	    LOGIF("filename=%s\n",filename.c_str());
            renderFrame(hints[k], factors[i], gens[j]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}}
    GBtest_deinit();

    return 0;
}
