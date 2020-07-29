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
 * @par parameters:
        GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, and GL_PATCHES are accepted. 
 *
 */

#include "Sample.h"
#include <array>

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

std::string FEEDBACK_VERT = std::string("vert2_passby.vert"); 
std::string FEEDBACK_FRAG = std::string("fix_green.frag"); 
std::string TRANSFORM_VERT = std::string("generate_vert.vert"); 
std::string TRANSFORM_GEOM = std::string("generate_vert.geom"); 
//std::string TRANSFORM_VERT = std::string("generate_vert."); 

GLenum factors[] = {
    GL_POINTS, 
    GL_LINE_STRIP, 
    GL_LINE_LOOP, 
    GL_LINES, 
    GL_TRIANGLE_STRIP, 
    GL_TRIANGLE_FAN, 
    GL_TRIANGLES, 
    //GL_LINE_STRIP_ADJACENCY, 
    //GL_LINES_ADJACENCY, 
    //GL_TRIANGLE_STRIP_ADJACENCY, 
    //GL_TRIANGLES_ADJACENCY, 
    //GL_PATCHES
};

#define NUM 7
GLuint vao;
GLfloat data[NUM]={0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
GLint iLocA=0, iLocPos=0;
GLuint FeedbackName=0;

bool createProgramFeedback()
{
    GLuint vertexID=-1, fragmentID=-1;

    std::string vertex = ((std::string)GLSL_PATH) + FEEDBACK_VERT; 
    std::string fragment = ((std::string)GLSL_PATH) + FEEDBACK_FRAG; 
    Shader::processShader(&vertexID, vertex.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentID, fragment.c_str(), GL_FRAGMENT_SHADER);
    ProgramName[program::FEEDBACK] = GL_CHECK(glCreateProgram());
    if (!ProgramName[program::FEEDBACK]) 
    {
        printf("Could not create program.");
        return false;
    }
    GL_CHECK(glProgramParameteri(ProgramName[program::FEEDBACK], GL_PROGRAM_SEPARABLE, GL_TRUE));
    GL_CHECK(glAttachShader(ProgramName[program::FEEDBACK], vertexID));
    GL_CHECK(glAttachShader(ProgramName[program::FEEDBACK], fragmentID));
    GL_CHECK(glLinkProgram(ProgramName[program::FEEDBACK]));

    GLint linked;
    GL_CHECK(glGetProgramiv(ProgramName[program::FEEDBACK], GL_LINK_STATUS, &linked ));
    if ( !linked ) {
        GLsizei len;
        glGetProgramiv(ProgramName[program::FEEDBACK], GL_INFO_LOG_LENGTH, &len );

        GLchar* linklog = new GLchar[len+1];
        glGetProgramInfoLog(ProgramName[program::FEEDBACK], len, &len, linklog );
        printf("Shader linking failed: %s\n", linklog);
        delete [] linklog;

        glDeleteShader(vertexID);
        glDeleteProgram(ProgramName[program::FEEDBACK]);
        
        return false;

    }
    GL_CHECK(glValidateProgram(ProgramName[program::FEEDBACK]));
    GL_CHECK(glGetProgramiv(ProgramName[program::FEEDBACK],GL_VALIDATE_STATUS,&linked));
    if(linked==0) {
	LOGE("validate error\n");
        return false;
    }
    iLocPos=glGetAttribLocation(ProgramName[program::FEEDBACK], "a_v2Position");
    return true;
}

bool createProgramTransform()
{
    GLuint vertexID=-1, geometryID=-1;

    std::string vertex = ((std::string)GLSL_PATH) + TRANSFORM_VERT; 
    std::string geometry = ((std::string)GLSL_PATH) + TRANSFORM_GEOM; 
    Shader::processShader(&vertexID, vertex.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&geometryID, geometry.c_str(), GL_GEOMETRY_SHADER);
    ProgramName[program::TRANSFORM] = GL_CHECK(glCreateProgram());
    if (!ProgramName[program::TRANSFORM]) 
    {
        printf("Could not create program.");
        return false;
    }
    GL_CHECK(glProgramParameteri(ProgramName[program::TRANSFORM], GL_PROGRAM_SEPARABLE, GL_TRUE));
    GL_CHECK(glAttachShader(ProgramName[program::TRANSFORM], vertexID));
    GL_CHECK(glAttachShader(ProgramName[program::TRANSFORM], geometryID));
    const GLchar * feedbackVarying[] = {"pos"};
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
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, 2*sizeof(data), NULL, GL_STATIC_READ);
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
	glVertexAttribPointer(iLocPos, 2, GL_FLOAT, GL_FALSE, 0, 0);
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
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glPointSize(4.0));
    GL_CHECK(glLineWidth(4.0));
    initBuffer();
    initVertexArray();
    initTFO();

    return true;
}

bool renderTF(void) {
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
                                           2*sizeof(data), GL_MAP_READ_BIT);
    if (!feedback) {
        LOGI("feedback == NULL\n");
    } else {
        LOGI("feedback == \n");
        for (int i = 0; i < 2*NUM; i++) {
            LOGI("%f\n", *(feedback + i));
        }
    }
    if (glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER) == GL_FALSE) {
        LOGE("Error unmapping array buffer object.");
        return false;
    }
    return true;
}

void renderFrame(GLenum mode) {
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GL_CHECK(glUseProgram(ProgramName[program::FEEDBACK]));
        GL_CHECK(glBindVertexArray(VertexArrayName[program::FEEDBACK]));                
        GL_CHECK(glDrawTransformFeedback(mode, FeedbackName));
}
void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderTF();
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        std::string bmp_file = filename + std::to_string(i) + ".bmp";
        LOGI("%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }

    glDeleteBuffers(buffer::MAX, &BufferName[0]);
    glDeleteTransformFeedbacks(1,&FeedbackName);
    glDeleteVertexArrays(program::MAX, &VertexArrayName[0]);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
