/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texsub.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texsub related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;



#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLuint transform_programID;
GLuint feedback_programID;
GLuint pipeline[2];
GLuint buffer[3];
GLuint vertexarray[2];
GLuint FeedbackName;

string transformVertexShaderPath = ((string)GLSL_PATH) + "transform-feedback-transform.vert";
string feedbackVertexShaderPath = ((string)GLSL_PATH) + "transform-feedback-feedback.vert";
string feedbackFragShaderPath = ((string)GLSL_PATH) + "transform-feedback-feedback.frag";

static const GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f
};

bool init_program() {
    GLuint transvertexID=-1;
    GLuint feedvertexID=-1;
    GLuint feedfragmentID=-1;

    Shader::processShader(&transvertexID, transformVertexShaderPath.c_str(), GL_VERTEX_SHADER);
    transform_programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glProgramParameteri(transform_programID, GL_PROGRAM_SEPARABLE, GL_TRUE));
    GL_CHECK(glAttachShader(transform_programID, transvertexID));
    GL_CHECK(glLinkProgram(transform_programID));

    Shader::processShader(&feedvertexID, feedbackVertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&feedfragmentID, feedbackFragShaderPath.c_str(), GL_FRAGMENT_SHADER);
    feedback_programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glProgramParameteri(feedback_programID, GL_PROGRAM_SEPARABLE, GL_TRUE));
    GL_CHECK(glAttachShader(feedback_programID, feedvertexID));
    GL_CHECK(glAttachShader(feedback_programID, feedfragmentID));
    GL_CHECK(glLinkProgram(feedback_programID));
    return true;
}

bool initVertexArray() {
    GL_CHECK(glGenVertexArrays(2, &vertexarray[0]));
    GL_CHECK(glGenBuffers(2, &buffer[0]));

    GL_CHECK(glBindVertexArray(vertexarray[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer[0]));
    GL_CHECK(glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindVertexArray(vertexarray[1]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer[1]));
    GL_CHECK(glBufferStorage(GL_ARRAY_BUFFER, sizeof(float) * 48, NULL, 0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(float) * 4)));
    GL_CHECK(glEnableVertexAttribArray(3));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return true;
}

bool initFeedback() {
    GL_CHECK(glGenTransformFeedbacks(1, &FeedbackName));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));
    GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffer[1]));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));

    return true;
}

void render(){
    init_program();
    initVertexArray();
    initFeedback();
    GL_CHECK(glGenProgramPipelines(2, &pipeline[0]));

    GL_CHECK(glClearColor(0.1, 0.1, 0.1, 1.0));
    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    GL_CHECK(glEnable(GL_RASTERIZER_DISCARD));
    GL_CHECK(glBindProgramPipeline(pipeline[0]));
    GL_CHECK(glUseProgramStages(pipeline[0], GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT,
                                transform_programID));
    GL_CHECK(glBindVertexArray(vertexarray[0]));
    GL_CHECK(glBindVertexBuffer(0, buffer[0], 0, sizeof(float) * 4));

    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, FeedbackName));
    GL_CHECK(glBeginTransformFeedback(GL_TRIANGLES));
    GL_CHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1));
    GL_CHECK(glEndTransformFeedback());
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0));
    GL_CHECK(glDisable(GL_RASTERIZER_DISCARD));

    // Second draw, reuse the captured attributes
    GL_CHECK(glBindProgramPipeline(pipeline[1]));
    GL_CHECK(glUseProgramStages(pipeline[1], GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT,
                                feedback_programID));
    GL_CHECK(glBindVertexArray(vertexarray[1]));
    GL_CHECK(glBindVertexBuffer(0, buffer[1], 0, sizeof(float) * 8));
    GL_CHECK(glDrawTransformFeedback(GL_TRIANGLES, FeedbackName));
}
void Sample::test() {
    render();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

