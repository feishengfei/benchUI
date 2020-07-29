/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file objectlabel.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for objectlabel related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static const char *TestLabel = "Test Label";
#define TestLabelLen 10

bool check_label_and_length(char *label, int length, GLenum object)
{
	bool pass = true;
	const char *name = get_enum_name(object);

	LOGI("Checking label and length of %s object\n", name);

	if (GL_NO_ERROR != glGetError())
		pass = false;

	LOGI("  actual label: %s actual length: %i\n", label, length);
	LOGI("  expected label: %s expected length: %i\n", TestLabel, TestLabelLen);
	if (length != TestLabelLen || (strcmp(TestLabel, label) != 0)) {
        	LOGI("Label or length does not match in %s object\n", name);
		pass = false;
	}
	return pass;
}

bool test_object_label()
{
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    #define numObjects 12
    GLsizei length[numObjects];
    GLchar label[numObjects][TestLabelLen + 1];
    enum test_object_indices {
		BUFFER_IDX, SHADER_IDX, PROGRAM_IDX, VERTEX_ARRAY_IDX, RENDERBUFFER_IDX,
		FRAMEBUFFER_IDX, QUERY_IDX, PROGRAM_PIPELINE_IDX, TRANSFORM_FEEDBACK_IDX,
		SAMPLER_IDX, TEXTURE_IDX, DISPLAY_LIST_IDX
    };
	bool pass = true;
	GLuint buffer;
	GLuint program;
	GLuint texture;

    program = glCreateProgram();
    glObjectLabel(GL_PROGRAM, program, -1, TestLabel);
    glGetObjectLabel(GL_PROGRAM, program, TestLabelLen + 1, &length[PROGRAM_IDX],
                     label[PROGRAM_IDX]);
    pass = check_label_and_length(label[PROGRAM_IDX], length[PROGRAM_IDX], GL_PROGRAM) && pass;
    glDeleteProgram(program);

    GL_CHECK(glGenBuffers(1, &buffer));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    glObjectLabel(GL_BUFFER, buffer, -1, TestLabel);
    glGetObjectLabel(GL_BUFFER, buffer, TestLabelLen + 1, &length[BUFFER_IDX], label[BUFFER_IDX]);
    pass = check_label_and_length(label[BUFFER_IDX], length[BUFFER_IDX], GL_BUFFER) && pass;
    glDeleteBuffers(1, &buffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glObjectLabel(GL_TEXTURE, texture, -1, TestLabel);
    glGetObjectLabel(GL_TEXTURE, texture, TestLabelLen + 1, &length[TEXTURE_IDX],
                     label[TEXTURE_IDX]);
    pass = check_label_and_length(label[TEXTURE_IDX], length[TEXTURE_IDX], GL_TEXTURE) && pass;
    glDeleteTextures(1, &texture);

    return pass;
}

bool test_object_ptr_label()
{
	GLsync sync;
	GLsizei length;
	GLchar label[TestLabelLen + 1];
	bool pass = true;

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	puts("Test ObjectPtrLabel");

	sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	glObjectPtrLabel(sync, -1, TestLabel);
	glGetObjectPtrLabel(sync, TestLabelLen + 1, &length, label);

	LOGI("  actual label: %s actual length: %i\n", label, length);
	LOGI("  expected label: %s expected length: %i\n", TestLabel, TestLabelLen);
	if (length != TestLabelLen || (strcmp(TestLabel, label) != 0)) {
		LOGE("Label or length does not match\n");
		pass = false;
	}
	glDeleteSync(sync);

	glObjectPtrLabel(NULL, length, label);

	if (GL_NO_ERROR != glGetError()) {
		pass = false;
	}

	return pass;
}

void renderFrame()
{
    bool pass = true;
    pass = test_object_label();
    LOGI("Test test_object_label: %s\n", pass?"PASS":"FAILED");
    pass = test_object_ptr_label();
    LOGI("Test test_object_ptr_label: %s\n", pass?"PASS":"FAILED");
}

void Sample::test() {
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
