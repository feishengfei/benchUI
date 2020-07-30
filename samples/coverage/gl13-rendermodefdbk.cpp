/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

static float vertex_array[] = {
	1.0, 2.0, 0.4, 1.0,
	3.0, 4.0, 0.6, 1.0,
	5.0, 6.0, 0.8, 1.0,
};

static float color_array[] = {
	0.01, 0.02, 0.03, 0.04,
	0.05, 0.06, 0.07, 0.08,
	0.09, 0.10, 0.11, 0.12,
};

static float texcoord_array[] = {
	101.0, 102.0, 103.0, 104.0,
	105.0, 106.0, 107.0, 108.0,
	109.0, 110.0, 111.0, 112.0,
};

static const float gl_2d_values[] =
	{GL_POLYGON_TOKEN, 3,
	 1.0, 2.0,
	 3.0, 4.0,
	 5.0, 6.0};

static const float gl_3d_values[] =
	{GL_POLYGON_TOKEN, 3,
	 1.0, 2.0, 0.3,
	 3.0, 4.0, 0.2,
	 5.0, 6.0, 0.1};

static const float gl_3d_color_values[] =
	{GL_POLYGON_TOKEN, 3,
	 1.0, 2.0, 0.3, 0.01, 0.02, 0.03, 0.04,
	 3.0, 4.0, 0.2, 0.05, 0.06, 0.07, 0.08,
	 5.0, 6.0, 0.1, 0.09, 0.10, 0.11, 0.12};

static const float gl_3d_color_texture_values[] =
	{GL_POLYGON_TOKEN, 3,
	 1.0, 2.0, 0.3, 0.01, 0.02, 0.03, 0.04, 101.0, 102.0, 103.0, 104.0,
	 3.0, 4.0, 0.2, 0.05, 0.06, 0.07, 0.08, 105.0, 106.0, 107.0, 108.0,
	 5.0, 6.0, 0.1, 0.09, 0.10, 0.11, 0.12, 109.0, 110.0, 111.0, 112.0};

static const float gl_4d_color_texture_values[] =
	{GL_POLYGON_TOKEN, 3,
	 1.0, 2.0, 0.3, 1.0, 0.01, 0.02, 0.03, 0.04, 101.0, 102.0, 103.0, 104.0,
	 3.0, 4.0, 0.2, 1.0, 0.05, 0.06, 0.07, 0.08, 105.0, 106.0, 107.0, 108.0,
	 5.0, 6.0, 0.1, 1.0, 0.09, 0.10, 0.11, 0.12, 109.0, 110.0, 111.0, 112.0};

struct type {
	GLenum type;
	const float *values;
	int count;
} types[] = {
	{ GL_2D, gl_2d_values, ARRAY_NUM(gl_2d_values) },

	{ GL_3D, gl_3d_values, ARRAY_NUM(gl_3d_values) },

	{ GL_3D_COLOR, gl_3d_color_values, ARRAY_NUM(gl_3d_color_values) },

	{ GL_3D_COLOR_TEXTURE, gl_3d_color_texture_values,
	  ARRAY_NUM(gl_3d_color_texture_values) },

	{ GL_4D_COLOR_TEXTURE, gl_4d_color_texture_values,
	  ARRAY_NUM(gl_4d_color_texture_values) },
};

static void
report_failure(struct type *type, float *buffer, int count)
{
	int i;

	LOGIF("Feeback failed for %s:\n",
		get_enum_name(type->type));

	LOGIF("  Expected:    Observed: (%d/%d)\n",
		count, type->count);
	for (i = 0; i < types->count; i++) {
		LOGIF("  %9f    %9f\n", type->values[i], buffer[i]);
	}
	LOGIF("\n");
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, w, 0, h, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

bool renderFrame()
{
	bool pass = true;
	float buffer[2 +
		     ARRAY_NUM(vertex_array) +
		     ARRAY_NUM(color_array) +
		     ARRAY_NUM(texcoord_array)];
	int i, j;

//	piglit_ortho_projection(w, h, false);
//piglit_gen_ortho_projection(0, w, 0, h, -1, 1, false);

	glClearColor(0.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glVertexPointer(4, GL_FLOAT, 0, vertex_array);
	glColorPointer(4, GL_FLOAT, 0, color_array);
	glTexCoordPointer(4, GL_FLOAT, 0, texcoord_array);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	for (i = 0; i < ARRAY_NUM(types); i++) {
		bool case_pass = true;
		int returned_count;
		const char *name = get_enum_name(types[i].type);

		LOGIF("Testing %s\n", name);

		for (j = 0; j < ARRAY_NUM(buffer); j++)
			buffer[j] = -1.0;

		glFeedbackBuffer(ARRAY_NUM(buffer), types[i].type, buffer);
		glRenderMode(GL_FEEDBACK);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		returned_count = glRenderMode(GL_RENDER);

		if (returned_count != types[i].count) {
			case_pass = false;
		} else {
			for (j = 0; j < types[i].count; j++) {
				if (fabs(buffer[j] - types[i].values[j]) > .01)
					case_pass = false;
			}
		}

		if (!case_pass) {
			pass = false;
			report_failure(&types[i], buffer, returned_count);
		}
	}

	return pass ? true : false;
}

int main(int argc, char** argv)
{
    string file = "gl13-rendermodefdbk";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    LOGIF("test result: %d\n",renderFrame());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
