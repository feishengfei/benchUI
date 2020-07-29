/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file getstring.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for getstring related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

void renderFrame(void)
{
	const char *renderer = (const char *) glGetString(GL_RENDERER);
	const char *version = (const char *) glGetString(GL_VERSION);
	const char *vendor = (const char *) glGetString(GL_VENDOR);

	LOGI("GL_RENDERER = %s\n", renderer);
	LOGI("GL_VERSION = %s\n", version);
	LOGI("GL_VENDOR = %s\n", vendor);

	LOGI("Extensions:\n");
	const char *ext = (const char *) glGetString(GL_EXTENSIONS);
	const char *c = ext;
	for (c = ext; *c; c++) {
		if (*c == ' ')
			fputc('\n',fp_log);
		else
			fputc(*c,fp_log);
	}
}

void Sample::test()
{
	renderFrame();
}

int main(int argc, char **argv)
{
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
