/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl40-drawfeedbackstream.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-18, Init file
 * @brief basic test for related API
 * @par TestPoints:
 *      glDrawTransformfeedbackStreamInstanced
 *
 */

#include "Sample.h"
#include <iostream>
#include <array>

using std::string;
using namespace BotsonSDK;
using namespace std;

GLuint FeedbackName=0;

namespace buffer
{
	enum type
	{
		FEEDBACK1,
		FEEDBACK2,
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
std::array<GLuint, buffer::MAX> VertexArrayName;
std::array<GLuint, program::MAX> iLocPosition;

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

#define NUM 1

bool createProgramTranslate()
{
    GLuint vertexID=-1, geometryID=-1, fragmentID=-1;

    string vertex = ((string)GLSL_PATH) + "geometry.vert"; 
    string geometry = ((string)GLSL_PATH) + "tf_translate.geom"; 
    string fragment = ((string)GLSL_PATH) + "geometry.frag"; 
    Shader::processShader(&vertexID, vertex.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentID, geometry.c_str(), GL_GEOMETRY_SHADER);
    Shader::processShader(&geometryID, fragment.c_str(), GL_FRAGMENT_SHADER);
    ProgramName[program::TRANSFORM] = GL_CHECK(glCreateProgram());
    if (!ProgramName[program::TRANSFORM]) 
    {
        printf("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(ProgramName[program::TRANSFORM], vertexID));
    GL_CHECK(glAttachShader(ProgramName[program::TRANSFORM], geometryID));
    GL_CHECK(glAttachShader(ProgramName[program::TRANSFORM], fragmentID));

    const GLchar * varyings[] = {"rf_position", "gl_NextBuffer", "lf_position"};
    glTransformFeedbackVaryings(ProgramName[program::TRANSFORM], 3, varyings, GL_INTERLEAVED_ATTRIBS);

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
    iLocPosition[program::TRANSFORM] = GL_CHECK(glGetAttribLocation(ProgramName[program::TRANSFORM], "aPos"));

    return true;
}

void initBuffer()
{
    GLfloat points[4*3] = {
         0.5, 0.5, 0.0,
         0.5, -0.5, 0.0,
         -0.5, -0.5, 0.0,
         -0.5, 0.5, 0.0
    };

    glGenBuffers(buffer::MAX, &BufferName[0]);
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::TRANSFORM]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK1]));
    GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4*4, NULL, GL_DYNAMIC_COPY));
    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0));

    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK2]));
    GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4*4, NULL, GL_DYNAMIC_COPY));
    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0));
}

void initVertexArray()
{
    GL_CHECK(glGenVertexArrays(buffer::MAX, &VertexArrayName[0]));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::TRANSFORM]));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::TRANSFORM]));
        GL_CHECK(glEnableVertexAttribArray(iLocPosition[program::TRANSFORM]));
        GL_CHECK(glVertexAttribPointer(iLocPosition[program::TRANSFORM], 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0))); 
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::FEEDBACK1]));
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::FEEDBACK1]);
	glEnableVertexAttribArray(iLocPosition[program::FEEDBACK]);
	glVertexAttribPointer(iLocPosition[program::FEEDBACK], 4, GL_FLOAT, GL_FALSE, 0, 0);
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::FEEDBACK2]));
	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::FEEDBACK2]);
	glEnableVertexAttribArray(iLocPosition[program::FEEDBACK]);
	glVertexAttribPointer(iLocPosition[program::FEEDBACK], 4, GL_FLOAT, GL_FALSE, 0, 0);
    GL_CHECK(glBindVertexArray(0));
}

void initTF()
{
    glGenTransformFeedbacks(1 , &FeedbackName);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName);
      GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK1]));
      GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, BufferName[buffer::FEEDBACK1]));
      GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK2]));
      GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, BufferName[buffer::FEEDBACK2]));
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

bool setupGraphics(int width, int height)
{
    glEnable( GL_DEPTH_TEST );
    glPointSize(4.0);
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glViewport( 0, 0, width, height );

    createProgramTranslate();

    string vertex = ((string)GLSL_PATH) + "vert4_passby_instanced.vert"; 
    string fragment = ((string)GLSL_PATH) + "fix_green.frag"; 
    ProgramName[program::FEEDBACK] = Shader::CreateProgram(vertex.c_str(), fragment.c_str());
    iLocPosition[program::FEEDBACK] = GL_CHECK(glGetAttribLocation(ProgramName[program::FEEDBACK], "a_v4Position"));

    initBuffer();
    initVertexArray();
    initTF();

    return true;
}

void renderFrame(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GL_CHECK(glUseProgram(ProgramName[program::TRANSFORM]));
    GL_CHECK(glEnable(GL_RASTERIZER_DISCARD));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::TRANSFORM]));
        
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName);
    GL_CHECK(glBeginTransformFeedback(GL_POINTS));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 4));
    GL_CHECK(glEndTransformFeedback());
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
    glDisable(GL_RASTERIZER_DISCARD);

    float tbv[4][4] = {0.0f};
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK1]);
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbv), tbv);
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
           cout << tbv[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, BufferName[buffer::FEEDBACK2]);
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbv), tbv);
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
           cout << tbv[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    GL_CHECK(glUseProgram(ProgramName[program::FEEDBACK]));
    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::FEEDBACK1]));
    GL_CHECK(glDrawTransformFeedbackStreamInstanced(GL_POINTS, FeedbackName, 0, 2));

    GL_CHECK(glBindVertexArray(VertexArrayName[buffer::FEEDBACK2]));
    GL_CHECK(glDrawTransformFeedbackStreamInstanced(GL_POINTS, FeedbackName, 1, 2));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    glDeleteBuffers(buffer::MAX, &BufferName[0]);
    glDeleteVertexArrays(buffer::MAX, &VertexArrayName[0]);
    glDeleteTransformFeedbacks(1,&FeedbackName);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
