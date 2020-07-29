/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file framebuffertexture.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for framebuffertexture related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static GLuint fbo[2];
static GLuint texture[2];
static const int layers = 3;

bool display_layered_texture(int x, int y, int w, int h, int texWidth, int texHeight,
			GLenum textureType, GLuint texture, int layers) {
	GLuint tempFBO;
	int i;
	int dx1, dy1, dx2, dy2;

	dx1 = x;
	dx2 = x+w;

	glGenFramebuffers(1, &tempFBO);

	for(i = 0; i < layers; i++) {
		GLenum framebufferStatus;

		dy1 = y + (i)  *(h/layers);
		dy2 = y + (i+1)*(h/layers);

		glBindFramebuffer(GL_FRAMEBUFFER, tempFBO);
		glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
					  texture, 0, i);

		framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if(framebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
			LOGE("Framebuffer Status:  != GL_FRAMEBUFFER_COMPLETE\n");
			return false;
		}

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, tempFBO);
		glBlitFramebuffer(0, 0, texWidth, texHeight,
				  dx1, dy1, dx2, dy2, GL_COLOR_BUFFER_BIT,
				  GL_NEAREST);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &tempFBO);
        
	return (GL_NO_ERROR == glGetError());
}

bool setupGraphics(int width, int height) {
	int    i, j;
	GLenum fbstatus;
	float  *colorLayers = (float *)malloc(sizeof(float) * layers * WINDOW_W * WINDOW_H * 3);
	float  colors[3][3] = {
			{0.0, 0.0, 1.0},
			{0.0, 1.0, 0.0},
			{1.0, 0.0, 0.0}
	};

	for (j = 0; j < layers; j++) {
		float *thisLayer = &colorLayers[j * WINDOW_W * WINDOW_H * 3];
		for (i = 0; i < WINDOW_W * WINDOW_H; i++) {
			thisLayer[i * 3 + 0] = colors[j][0];
			thisLayer[i * 3 + 1] = colors[j][1];
			thisLayer[i * 3 + 2] = colors[j][2];
		}
	}

	glGenTextures(2, texture);
	glGenFramebuffers(2, fbo);
	for (i = 0; i < 2; i++) {
		GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture[i]));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_REPEAT));
		GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, WINDOW_W, WINDOW_H,
					 layers, 0, GL_RGB, GL_FLOAT, colorLayers));

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo[i]));
		GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
							 texture[i], 0));

		fbstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fbstatus != GL_FRAMEBUFFER_COMPLETE) {
			LOGE("Framebuffer Status:  != GL_FRAMEBUFFER_COMPLETE\n");
			return false;
		}
	}
	return true;
}

void renderFrame()
{
	bool pass = true;
	const float clearColor[3] = { 1, 1, 0 };

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo[0]);
	glClearColor(clearColor[0], clearColor[1], clearColor[2], 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo[1]);
	glClearBufferfv(GL_COLOR, 0, clearColor);

	if(!display_layered_texture(0, 0, WINDOW_W/2, WINDOW_H,
				    WINDOW_W, WINDOW_H, GL_TEXTURE_2D_ARRAY,
				    texture[0], layers)) {
		LOGE("Failed to display layered texture for glClear\n");
	}

	if(!display_layered_texture(WINDOW_W/2, 0, WINDOW_W/2,
				    WINDOW_H, WINDOW_W, WINDOW_H,
				    GL_TEXTURE_2D_ARRAY, texture[1], layers)) {
		LOGE("Failed to display layered texture for glClearBuffer\n");
	}
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	renderFrame();
	string bmp_file  = filename + ".bmp";
	LOGI("bmp_file=%s", bmp_file.c_str());
	save2bmp(bmp_file.c_str());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
