/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file getstring.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for getstring related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

void renderFrame(void) {
	const char *renderer = (const char *) glGetString(GL_RENDERER);
	const char *version = (const char *) glGetString(GL_VERSION);
	const char *vendor = (const char *) glGetString(GL_VENDOR);

	LOGI("GL_RENDERER = %s\n", renderer);
	LOGI("GL_VERSION = %s\n", version);
	LOGI("GL_VENDOR = %s\n", vendor);

	if (version[0] >= '2') {
		LOGI("GL_SHADING_LANGUAGE_VERSION = %s\n", (const char *)
		       glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	LOGI("Extensions:\n");
		const char *ext = (const char *) glGetString(GL_EXTENSIONS);
		const char *c = ext;
		for (c = ext; *c; c++) {
			if (*c == ' ')
				fputc('\n',LOG_FILE);
			else
				fputc(*c,LOG_FILE);
		}
}

void Sample::test() {
	renderFrame();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

