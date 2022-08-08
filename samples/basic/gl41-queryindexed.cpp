/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl40-transformfeedback.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-14, Init file
 * @brief basic test for related API
 * @par TestPoints:
       glBeginQueryIndexed
       glEndQueryIndexed
       glGetQueryIndexed
       target: GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED, GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_TIME_ELAPSED
     GL_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED, GL_ANY_SAMPLES_PASSED_CONSERVATIVE GL_PRIMITIVES_GENERATED, GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, GL_TIME_ELAPSED, or GL_TIMESTAMP   
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
std::array<GLuint, program::MAX> PipelineName;
std::array<GLuint, program::MAX> ProgramName;
std::array<GLuint, program::MAX> VertexArrayName;

#define NUM 7
GLuint vao;
GLfloat data[NUM]={0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
GLint iLocA=0, iLocPos=0;
GLuint FeedbackName=0;
GLuint QueryName=0;

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
        GL_CHECK(glGetProgramiv(ProgramName[program::TRANSFORM], GL_INFO_LOG_LENGTH, &len ));

        GLchar* linklog = new GLchar[len+1];
        GL_CHECK(glGetProgramInfoLog(ProgramName[program::TRANSFORM], len, &len, linklog ));
        printf("Shader linking failed: %s\n", linklog);
        delete [] linklog;

        GL_CHECK(glDeleteShader(vertexID));
        GL_CHECK(glDeleteProgram(ProgramName[program::TRANSFORM]));
        
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

bool initQuery()
{
    GL_CHECK(glGenQueries(1, &QueryName));
    GL_CHECK(glIsQuery(QueryName));
    int QueryBits(0);
    GL_CHECK(glGetQueryiv(GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, GL_QUERY_COUNTER_BITS, &QueryBits));

    return QueryBits >= 1;
}

void  initBuffer()
{
	GL_CHECK(glGenBuffers(buffer::MAX, &BufferName[0]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK]));
	GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(data), NULL, GL_STATIC_READ));
	GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0));
}

void initVertexArray() {
    GL_CHECK(glGenVertexArrays(program::MAX, &VertexArrayName[0]));

    GL_CHECK(glBindVertexArray(VertexArrayName[program::TRANSFORM]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]));
    GL_CHECK(glEnableVertexAttribArray(iLocA));
    GL_CHECK(glVertexAttribPointer(iLocA, 1, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glBindVertexArray(0));
}

void initTFO() {
    GL_CHECK(glGenTransformFeedbacks(1,&FeedbackName));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));
    LOGI("isTransformFeedback: %d\n", glIsTransformFeedback(FeedbackName));
    LOGI("FeedbackName: %d\n", FeedbackName);
    GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, BufferName[buffer::FEEDBACK]));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
}

bool setupGraphics(int w, int h) {
    initQuery();
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

    GL_CHECK(glBindVertexArray(VertexArrayName[program::TRANSFORM]));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));
    GL_CHECK(glBeginQueryIndexed(GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, 0, QueryName));
        GL_CHECK(glBeginTransformFeedback(GL_POINTS));
        GL_CHECK(glDrawArrays(GL_POINTS, 0, NUM));
        GL_CHECK(glEndTransformFeedback());
    GLint data=0;
    GL_CHECK(glGetQueryIndexediv(GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, 0, GL_CURRENT_QUERY, &data));
    printf("======data:%d\n",data);
//, or
    GL_CHECK(glGetQueryIndexediv(GL_TIME_ELAPSED, 0, GL_CURRENT_QUERY, &data));
    printf("======GL_TIME_ELAPSED:%d\n",data);
    GL_CHECK(glEndQueryIndexed(GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, 0));

    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
    glDisable(GL_RASTERIZER_DISCARD);

    float fb[NUM];
    GL_CHECK(glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(fb), fb));
    LOGI("get transform feedback:\n");
    for(int i=0; i<NUM; i++) {
        LOGI("%f\n", fb[i]);
    }
//  or GL_QUERY_COUNTER_BITS

}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file    = filename + ".bmp";
    LOGI("%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    GL_CHECK(glDeleteBuffers(buffer::MAX, &BufferName[0]));
    GL_CHECK(glDeleteBuffers(1,&BufferName[buffer::VERTEX]));
    GL_CHECK(glDeleteVertexArrays(1,&vao));
    GL_CHECK(glDeleteTransformFeedbacks(1,&FeedbackName));
    GL_CHECK(glDeleteVertexArrays(program::MAX, &VertexArrayName[0]));
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
