/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl40-pausefeedback.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-18, Init file
 * @brief basic test for related API
 * @par TestPoints:
        glPauseTransformFeedback
        glResumeTransformFeedback
 *
 */

#include "Sample.h"
#include <array>

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "tf_sqrt.vert";
namespace buffer
{
	enum type
	{
		DATA1,
		DATA2,
		FEEDBACK,
		MAX
	};
}//namespace buffer
std::array<GLuint, buffer::MAX> BufferName;

namespace program
{
	enum type
	{
		FEEDBACK,
		TRANSFORM,
		MAX
	};
}//namespace program
std::array<GLuint, program::MAX> ProgramName;
std::array<GLuint, buffer::MAX> VertexArrayName;

#define NUM 3
GLfloat data2[NUM]={1.0f,2.0f,3.0f};
GLfloat data1[NUM]={4.0f,5.0f,6.0f};
GLint iLocA=0, iLocPos=0;
GLuint FeedbackName=0;

bool createProgramTransform()
{
    GLuint vertexID=-1;

    string vertex = ((string)GLSL_PATH) + "tf_sqrt.vert"; 
    Shader::processShader(&vertexID, vertex.c_str(), GL_VERTEX_SHADER);
    ProgramName[program::TRANSFORM] = GL_CHECK(glCreateProgram());
    if (!ProgramName[program::TRANSFORM]) 
    {
        printf("Could not create program.");
        return false;
    }
    GL_CHECK(glProgramParameteri(ProgramName[program::TRANSFORM], GL_PROGRAM_SEPARABLE, GL_TRUE));
    GL_CHECK(glAttachShader(ProgramName[program::TRANSFORM], vertexID));
    const GLchar * feedbackVarying[] = {"b"};
    GL_CHECK(glTransformFeedbackVaryings(ProgramName[program::TRANSFORM], 1, feedbackVarying, GL_INTERLEAVED_ATTRIBS));
    GL_CHECK(glLinkProgram(ProgramName[program::TRANSFORM]));

    GLint linked;
    GL_CHECK(glGetProgramiv(ProgramName[program::TRANSFORM], GL_LINK_STATUS, &linked ));
    if ( !linked ) {
        GLsizei len;
        glGetProgramiv(ProgramName[program::TRANSFORM], GL_INFO_LOG_LENGTH, &len );

        GLchar* linklog = new GLchar[len+1];
        glGetProgramInfoLog(ProgramName[program::TRANSFORM], len, &len, linklog );
        printf("Shader linking failed: %s\n", linklog);
        delete [] linklog;

        glDeleteShader(vertexID);
        glDeleteProgram(ProgramName[program::TRANSFORM]);
        
        return false;

    }
    GL_CHECK(glValidateProgram(ProgramName[program::TRANSFORM]));
    GL_CHECK(glGetProgramiv(ProgramName[program::TRANSFORM],GL_VALIDATE_STATUS,&linked));
    if(linked==0) {
	LOGE("validate error\n");
        return false;
    }

    iLocA=glGetAttribLocation(ProgramName[program::TRANSFORM], "a");
    return true;
}

void  initBuffer()
{
	glGenBuffers(buffer::MAX, &BufferName[0]);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::DATA1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data1), data1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::DATA2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data2), data2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(data2), NULL, GL_STATIC_READ);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
}

void initVertexArray() {
    GL_CHECK(glGenVertexArrays(buffer::MAX, &VertexArrayName[0]));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::DATA1]));
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::DATA1]);
	glEnableVertexAttribArray(iLocA);
	glVertexAttribPointer(iLocA, 1, GL_FLOAT, GL_FALSE, 0, 0);
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::DATA2]));
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::DATA2]);
	glEnableVertexAttribArray(iLocA);
	glVertexAttribPointer(iLocA, 1, GL_FLOAT, GL_FALSE, 0, 0);
    GL_CHECK(glBindVertexArray(0));
}

void initTFO() {
    GL_CHECK(glGenTransformFeedbacks(1,&FeedbackName));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));
    LOGI("isTransformFeedback: %d\n", glIsTransformFeedback(FeedbackName));
    LOGI("FeedbackName: %d\n", FeedbackName);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, BufferName[buffer::FEEDBACK]);
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
}

bool setupGraphics(int w, int h) {
    createProgramTransform();
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    initBuffer();
    initVertexArray();
    initTFO();

    return true;
}

void renderFrame(void) {
    GL_CHECK(glUseProgram(ProgramName[program::TRANSFORM]));
    GL_CHECK(glEnable(GL_RASTERIZER_DISCARD));
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK]);

    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));

    GL_CHECK(glBeginTransformFeedback(GL_POINTS));
    GL_CHECK(glPauseTransformFeedback());
    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::DATA1]));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, NUM));

    GL_CHECK(glResumeTransformFeedback());
    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::DATA2]));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, NUM));
    GL_CHECK(glEndTransformFeedback());
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
    glDisable(GL_RASTERIZER_DISCARD);

    float fb[NUM];
    GL_CHECK(glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(fb), fb));
    LOGI("get transform feedback:\n");
    for (int i = 0; i < NUM; i++) {
        LOGI("%f\n", fb[i]);
    }
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    glDeleteBuffers(buffer::MAX, &BufferName[0]);
    glDeleteBuffers(1,&BufferName[0]);
    glDeleteTransformFeedbacks(1,&FeedbackName);
    glDeleteVertexArrays(buffer::MAX, &VertexArrayName[0]);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
