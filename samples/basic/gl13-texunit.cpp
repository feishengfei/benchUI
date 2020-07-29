/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"
#include "rgb.h"

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

#define	imageWidth 64
#define	imageHeight 64
GLubyte image[3*imageWidth*imageHeight];

void makeImage(void)
{
   int i, j;
   float ti, tj;
   
   for (i = 0; i < imageWidth; i++) {
      ti = 2.0*3.14159265*i/imageWidth;
      for (j = 0; j < imageHeight; j++) {
         tj = 2.0*3.14159265*j/imageHeight;

         image[3*(imageHeight*i+j)] = (GLubyte) 127*(1.0+sin(ti));
         image[3*(imageHeight*i+j)+1] = (GLubyte) 127*(1.0+cos(2*tj));
         image[3*(imageHeight*i+j)+2] = (GLubyte) 127*(1.0+cos(ti+tj));
      }
   }
}

GLvoid
draw_rect_tex(float x, float y, float w, float h,
	      float tx, float ty, float tw, float th)
{
	float verts[4][4];
	float tex[4][2];

	verts[0][0] = x;
	verts[0][1] = y;
	verts[0][2] = 0.0;
	verts[0][3] = 1.0;
	tex[0][0] = tx;
	tex[0][1] = ty;
	verts[1][0] = x + w;
	verts[1][1] = y;
	verts[1][2] = 0.0;
	verts[1][3] = 1.0;
	tex[1][0] = tx + tw;
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

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


GLuint
piglit_rgbw_texture()
{
	int size, level;
	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image);

	return tex;
}

void renderFrame(void)
{
	GLboolean pass = GL_TRUE;
	GLuint tex;
	float red[4]   = {1.0, 0.0, 0.0, 1.0};
	float green[4] = {0.0, 1.0, 0.0, 1.0};
	float blue[4]  = {0.0, 0.0, 1.0, 1.0};
	float white[4] = {1.0, 1.0, 1.0, 1.0};

	makeImage();
	tex = piglit_rgbw_texture();
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);

	draw_rect_tex(-1, -1, 2, 2, 0, 0, 1, 1);
}

int main(int argc, char **argv)
{
    string file = "gl13-texunit";
    GBtest_init(&argc,argv,file,DisplayMode);
	    string filename = file + ".bmp";
	    LOGIF("filename=%s\n", filename.c_str());
            renderFrame();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();
}
