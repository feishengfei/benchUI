/**
 * @file depth.c
 * @testpoint glDepthFunc glClearDepthf glDepthRangef glDepthMask
 *
 */
#include "gl-util.h"

GLenum factors[] = {
	GL_ALPHA_TEST,
	GL_AUTO_NORMAL,
	GL_BLEND,
	GL_CLIP_PLANE0,
	GL_COLOR_LOGIC_OP,
	GL_COLOR_MATERIAL,
//	GL_COLOR_SUM, 
//	GL_COLOR_TABLE,
//	GL_CONVOLUTION_1D,
//	GL_CONVOLUTION_2D,
	GL_CULL_FACE,
	GL_DEPTH_TEST,
	GL_DITHER,
	GL_FOG,
//	GL_HISTOGRAM,
	GL_INDEX_LOGIC_OP,
	GL_LIGHT0,
	GL_LIGHTING,
	GL_LINE_SMOOTH,
	GL_LINE_STIPPLE,
	GL_MAP1_COLOR_4,
	GL_MAP1_INDEX,
	GL_MAP1_NORMAL,
	GL_MAP1_TEXTURE_COORD_1,
	GL_MAP1_TEXTURE_COORD_2,
	GL_MAP1_TEXTURE_COORD_3,
	GL_MAP1_TEXTURE_COORD_4,
	GL_MAP1_VERTEX_3,
	GL_MAP1_VERTEX_4,
	GL_MAP2_COLOR_4,
	GL_MAP2_INDEX,
	GL_MAP2_NORMAL,
	GL_MAP2_TEXTURE_COORD_1,
	GL_MAP2_TEXTURE_COORD_2,
	GL_MAP2_TEXTURE_COORD_3,
	GL_MAP2_TEXTURE_COORD_4,
	GL_MAP2_VERTEX_3,
	GL_MAP2_VERTEX_4,
//	GL_MINMAX,
	GL_MULTISAMPLE,
	GL_NORMALIZE,
	GL_POINT_SMOOTH,
	GL_POINT_SPRITE,
	GL_POLYGON_OFFSET_FILL,
	GL_POLYGON_OFFSET_LINE,
	GL_POLYGON_OFFSET_POINT,
	GL_POLYGON_SMOOTH,
	GL_POLYGON_STIPPLE,
//	GL_POST_COLOR_MATRIX_COLOR_TABLE,
//	GL_POST_CONVOLUTION_COLOR_TABLE,
	GL_RESCALE_NORMAL,
	GL_SAMPLE_ALPHA_TO_COVERAGE,
	GL_SAMPLE_ALPHA_TO_ONE,
	GL_SAMPLE_COVERAGE,
//	GL_SEPARABLE_2D,
	GL_SCISSOR_TEST,
	GL_STENCIL_TEST,
	GL_TEXTURE_1D,
	GL_TEXTURE_2D,
	GL_TEXTURE_3D,
	GL_TEXTURE_CUBE_MAP,
	GL_TEXTURE_GEN_Q,
	GL_TEXTURE_GEN_R,
	GL_TEXTURE_GEN_S,
	GL_TEXTURE_GEN_T,
	GL_VERTEX_PROGRAM_POINT_SIZE,
	GL_VERTEX_PROGRAM_TWO_SIDE
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

void renderFrame()
{
    int i=0;
    GLboolean isEn;
    bool pass=true;

    LOGIF("initial========\n");
    for(i=0; i<ARRAY_NUM(factors); i++) {
	isEn = GL_CHECK(glIsEnabled(factors[i]));
        LOGIF("%s = %d\n", get_enum_name(factors[i]), isEn);	
    }

    LOGIF("enable========\n");
    for(i=0; i<ARRAY_NUM(factors); i++)
	GL_CHECK(glEnable(factors[i]));
    for(i=0; i<ARRAY_NUM(factors); i++) {
	isEn = glIsEnabled(factors[i]);
        LOGIF("%s = %d\n", get_enum_name(factors[i]), isEn);	
    }

    LOGIF("disable========\n");
    for(i=0; i<ARRAY_NUM(factors); i++)
	GL_CHECK(glDisable(factors[i]));
    for(i=0; i<ARRAY_NUM(factors); i++) {
	isEn = glIsEnabled(factors[i]);
        LOGIF("%s = %d\n", get_enum_name(factors[i]), isEn);	
    }
    LOGIF("END========\n");
}

int main(int argc, char** argv)
{
    string file = "gl13-diisenable";
    GBtest_init(&argc,argv,file,DisplayMode);
    renderFrame();
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
