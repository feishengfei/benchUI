/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file colormask.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for colormask related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLboolean mask[2] = {GL_TRUE,GL_FALSE};

void failRGB(GLint chan, GLfloat expected, GLfloat actual) {
        static const char *chanNames[] = { "Red", "Green", "Blue", "Alpha" };
        GLboolean mask[4];
        glGetBooleanv(GL_COLOR_WRITEMASK, mask);
        LOGI("masked-clear: %s is %f, expected %f\n",
               chanNames[chan], actual, expected);
        LOGI("\tGL_COLOR_WRITEMASK = (%s, %s, %s, %s)\n",
               (mask[0] ? "GL_TRUE" : "GL_FALSE"),
               (mask[1] ? "GL_TRUE" : "GL_FALSE"),
               (mask[2] ? "GL_TRUE" : "GL_FALSE"),
               (mask[3] ? "GL_TRUE" : "GL_FALSE"));
}

bool test_color_masking(GLenum buffer) {
	GLint a;
	int chan, comp, numChannels;
	bool passed = true;

	glGetIntegerv(GL_ALPHA_BITS, &a);
	numChannels = a ? 4 : 3;

	for (chan = 0; chan < numChannels && passed; chan++) {
		GLfloat pixel[4];
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColorMask(chan == 0, chan == 1, chan == 2, chan == 3);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glReadPixels(4, 4, 1, 1, GL_RGBA, GL_FLOAT, pixel);

		for (comp = 0; comp < numChannels && passed; comp++) {
			if (comp == chan) {
				if (pixel[comp] < 0.5) {
					passed = false;
					failRGB(comp, 1.0,
						pixel[comp]);
				}
			} else {
				if (pixel[comp] > 0.5) {
					passed = false;
					failRGB(comp, 0.0,
						pixel[comp]);
				}
			}
		}
	}

	return passed;
}

bool setupGraphics(int width, int height) {
    GL_CHECK(glViewport(0, 0, width, height));

    return true;
}


GLboolean renderFrame(GLboolean maskR,GLboolean maskG,GLboolean maskB,
                      GLboolean maskA) {
    GLfloat pixel[4];
    bool passed = true;
    GLfloat expected;
    GLfloat mask[4]={maskR, maskG, maskB, maskA};

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColorMask(mask[0], mask[1], mask[2], mask[3]);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    return passed;
}

void Sample::test() {
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int m=0; m<2; m++) {
                for (int n = 0; n < 2; n++) {
                    setupGraphics(WINDOW_W, WINDOW_H);
                    renderFrame(mask[i], mask[j], mask[m], mask[n]);
                    char ss[10];
                    sprintf(ss, "_%d_%d_%d_%d", i, j, m, n);
                    string bmp_file = filename + ss + ".bmp";
                    LOGI("bmp_file=%s", bmp_file.c_str());
                    save2bmp(bmp_file.c_str());
                    Sample::SwapBuffers();
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
