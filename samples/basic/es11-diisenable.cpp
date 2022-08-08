/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file diisenable.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-20, Add commit
 * @brief basic test for diisenable related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLenum factors[] = {
	GL_ALPHA_TEST,
	GL_BLEND,
	GL_COLOR_LOGIC_OP,

	GL_CLIP_PLANE0,

	GL_COLOR_MATERIAL,
	GL_CULL_FACE,
	GL_DEPTH_TEST,
	GL_DITHER,
	GL_FOG,
	GL_LIGHT0,
	GL_LIGHTING,
	GL_LINE_SMOOTH,
	GL_MULTISAMPLE,
	GL_NORMALIZE,
	GL_POINT_SMOOTH,
	GL_POINT_SPRITE_OES,
	GL_POLYGON_OFFSET_FILL,
	GL_RESCALE_NORMAL,
	GL_SAMPLE_ALPHA_TO_COVERAGE,
	GL_SAMPLE_ALPHA_TO_ONE,
	GL_SAMPLE_COVERAGE,
	GL_SCISSOR_TEST,
	GL_STENCIL_TEST,
	GL_TEXTURE_2D,
	GL_COLOR_ARRAY,
	GL_NORMAL_ARRAY,
	GL_POINT_SIZE_ARRAY_OES,
	GL_TEXTURE_COORD_ARRAY
};

void renderFrame()
{
    int i=0;
    GLboolean isEn;
    bool pass = true;

    LOGI("initial========\n");
    for(i=0; i<ARRAY_NUM(factors); i++) {
	isEn = glIsEnabled(factors[i]);
        LOGI("%s = %d", get_enum_name(factors[i]), i);
    }

    LOGI("enable========\n");
    for(i=0; i<ARRAY_NUM(factors); i++)
	GL_CHECK(glEnable(factors[i]));
    for(i=0; i<ARRAY_NUM(factors); i++) {
	isEn = glIsEnabled(factors[i]);
        LOGI("%s = %d", get_enum_name(factors[i]), i);
    }

    LOGI("disable========\n");
    for(i=0; i<ARRAY_NUM(factors); i++)
	GL_CHECK(glDisable(factors[i]));
    for(i=0; i<ARRAY_NUM(factors); i++) {
	isEn = glIsEnabled(factors[i]);
        LOGI("%s = %d", get_enum_name(factors[i]), i);
    }
    LOGI("END========\n");
}

void Sample::test()
{
	renderFrame();
    SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
