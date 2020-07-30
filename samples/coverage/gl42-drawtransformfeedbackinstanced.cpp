/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl40-drawtransformfeedback.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-14, Init file
 * @brief basic test for related API
 * @par TestPoints:
        glGenTransformFeedback
        glIsTransformFeedback
        glDeleteTransformfeedback
        glDrawTransformfeedback
 *
 */

#include "Sample.h"
#include <array>

using std::string;
using namespace BotsonSDK;

namespace buffer
{
	enum type
	{
		VERTEX,
		FEEDBACK,
		TRANSFORM,
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
std::array<GLuint, program::MAX> VertexArrayName;

#define NUM 7
GLuint vao;
GLfloat data[NUM]={0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
GLint iLocA=0, iLocPos=0;
GLuint FeedbackName=0;

bool createProgramFeedback()
{
    string vertex = ((string)GLSL_PATH) + "TransformFeedback.vert"; 
    string fragment = ((string)GLSL_PATH) + "TransformFeedback.frag"; 
    ProgramName[program::FEEDBACK] = Shader::CreateProgram(vertex.c_str(), fragment.c_str());
    if (!ProgramName[program::FEEDBACK]) 
    {
        printf("Could not create program.");
        return false;
    }
    iLocPos=glGetAttribLocation(ProgramName[program::FEEDBACK], "pos");
    return true;
}

bool createProgramTransform()
{
    GLuint vertexID=-1;

    string vertex = ((string)GLSL_PATH) + "tf_translate.vert"; 
    Shader::processShader(&vertexID, vertex.c_str(), GL_VERTEX_SHADER);
    ProgramName[program::TRANSFORM] = GL_CHECK(glCreateProgram());
    if (!ProgramName[program::TRANSFORM]) 
    {
        printf("Could not create program.");
        return false;
    }
    //GL_CHECK(glProgramParameteri(ProgramName[program::TRANSFORM], GL_PROGRAM_SEPARABLE, GL_TRUE));
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

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(data), NULL, GL_STATIC_READ);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
}

void initVertexArray() {
    GL_CHECK(glGenVertexArrays(program::MAX, &VertexArrayName[0]));

    GL_CHECK(glBindVertexArray(VertexArrayName[program::TRANSFORM]));
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
	glEnableVertexAttribArray(iLocA);
	glVertexAttribPointer(iLocA, 1, GL_FLOAT, GL_FALSE, 0, 0);
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glBindVertexArray(VertexArrayName[program::FEEDBACK]));
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::FEEDBACK]);
	glEnableVertexAttribArray(iLocPos);
	glVertexAttribPointer(iLocPos, 1, GL_FLOAT, GL_FALSE, 0, 0);
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
    createProgramFeedback();
    createProgramTransform();
    glPointSize(4.0);
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    initBuffer();
    initVertexArray();
    initTFO();

    return true;
}

void renderFrame(int k) {
    GL_CHECK(glUseProgram(ProgramName[program::TRANSFORM]));
    GL_CHECK(glEnable(GL_RASTERIZER_DISCARD));

    GL_CHECK(glBindVertexArray(VertexArrayName[program::TRANSFORM]));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));
        GL_CHECK(glBeginTransformFeedback(GL_POINTS));
            GL_CHECK(glDrawArrays(GL_POINTS, 0, NUM));
        GL_CHECK(glEndTransformFeedback());
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
    glDisable(GL_RASTERIZER_DISCARD);

    GLfloat *feedback;
    glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::FEEDBACK]);
    feedback = (GLfloat *)glMapBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0,
                                           sizeof(data), GL_MAP_READ_BIT);
    if (!feedback) {
        LOGI("feedback == NULL\n");
    } else {
        LOGI("feedback == \n");
        for (int i = 0; i < NUM; i++) {
            LOGI("%f\n", *(feedback + i));
        }
    }
    if (glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER) == GL_FALSE) {
        LOGE("Error unmapping array buffer object.");
    } else {
        GL_CHECK(glUseProgram(ProgramName[program::FEEDBACK]));
        GL_CHECK(glBindVertexArray(VertexArrayName[program::FEEDBACK]));
        switch(k){
        case 0:
        GL_CHECK(glDrawTransformFeedbackInstanced(GL_POINTS, FeedbackName, 2));
        break;
        case 1:
        GL_CHECK(glDrawTransformFeedback(GL_POINTS, FeedbackName));
        break;
        default:
            break;
        }

    }
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for (int i = 0; i < 2; i++) {
        char ss[5];
        sprintf(ss, "%d", i);
        renderFrame(i);
        string bmp_file = filename + ss + ".bmp";
        LOGI("%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
    glDeleteBuffers(buffer::MAX, &BufferName[0]);
    glDeleteTransformFeedbacks(1, &FeedbackName);
    glDeleteVertexArrays(program::MAX, &VertexArrayName[0]);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
