/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file subroutine.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-11-25, Add commit
 * @brief basic test for Subroutine related API
 * @par TestPoints:
 *    glGetSubroutineUniformLocation 
 *    glGetSubroutineIndex
 *    glGetActiveSubroutineUniformiv
 *    glGetActiveSubroutineUniformName
 *    glGetActiveSubroutineName
 *    glUniformSubroutinesuiv
 *    glGetUniformSubroutineuiv
 * @par demo design: 
     use vertex shader for glGetActiveSubroutineUniformName pname and multi subroutine test
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "subrotine_mirror.vert";
string fragmentShaderFilename = "subrotine_rg.frag";

GLuint programID;
GLuint Index[5]={0, 0, 0, 0, 0};

bool setupGraphics(int width, int height) 
{
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    Index[1] = GL_CHECK(glGetSubroutineIndex(programID, GL_FRAGMENT_SHADER, "Red"));
    Index[0] = GL_CHECK(glGetSubroutineIndex(programID, GL_FRAGMENT_SHADER, "Green"));
    LOGI("GetSubroutineIndex(GL_FRAGMENT_SHADER): %d, %d\n", Index[0], Index[1]);
    Index[2] = GL_CHECK(glGetSubroutineIndex(programID, GL_VERTEX_SHADER, "Normal"));
    Index[3] = GL_CHECK(glGetSubroutineIndex(programID, GL_VERTEX_SHADER, "MirrorX"));
    Index[4] = GL_CHECK(glGetSubroutineIndex(programID, GL_VERTEX_SHADER, "MirrorY"));
    LOGI("GetSubroutineIndex(GL_VERTEX_SHADER): %d, %d, %d\n", Index[2], Index[3], Index[4]);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
}

void fillData()
{
    GLfloat vertices[2] = {0.5, 0.5};
    GLint iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v2Position"));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
 
    GL_CHECK(glPointSize(4.0));
}

void getData(GLenum shadertype)
{
    LOGI("Get shader type: %s\n", get_enum_name(shadertype));

    GLint ProgramSubroutine = 0;
    GL_CHECK(glGetProgramStageiv(programID, shadertype, GL_ACTIVE_SUBROUTINE_UNIFORMS, &ProgramSubroutine));
    LOGI("GetProgramStageiv(GL_ACTIVE_SUBROUTINE_UNIFORMS): %d\n", ProgramSubroutine);
    GL_CHECK(glGetProgramStageiv(programID, shadertype, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &ProgramSubroutine));
    LOGI("GetProgramStageiv(GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS): %d\n", ProgramSubroutine);
    GL_CHECK(glGetProgramStageiv(programID, shadertype, GL_ACTIVE_SUBROUTINES, &ProgramSubroutine));
    LOGI("GetProgramStageiv(GL_ACTIVE_SUBROUTINES): %d\n", ProgramSubroutine);
    GL_CHECK(glGetProgramStageiv(programID, shadertype, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &ProgramSubroutine));
    LOGI("GetProgramStageiv(GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH): %d\n", ProgramSubroutine);
    GL_CHECK(glGetProgramStageiv(programID, shadertype, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &ProgramSubroutine));
    LOGI("GetProgramStageiv(GL_ACTIVE_SUBROUTINE_MAX_LENGTH): %d\n", ProgramSubroutine);

    if(shadertype==GL_FRAGMENT_SHADER) {
        GLint locSetColor=GL_CHECK(glGetSubroutineUniformLocation(programID, shadertype, "SetColor"));
        LOGI("GetSubroutineUniformLocation: %d\n", locSetColor);
        GLuint uniformsub = 0;
        GL_CHECK(glGetUniformSubroutineuiv(shadertype, locSetColor, &uniformsub));
        LOGI("GetUniformSubroutineuiv: %d\n", uniformsub);
    }
    if(shadertype==GL_VERTEX_SHADER) {
        GLint locSetPos=GL_CHECK(glGetSubroutineUniformLocation(programID, shadertype, "SetPos"));
        LOGI("GetSubroutineUniformLocation: %d\n", locSetPos);
        GLuint uniformsub = 0;
        GL_CHECK(glGetUniformSubroutineuiv(shadertype, locSetPos, &uniformsub));
        LOGI("GetUniformSubroutineuiv: %d\n", uniformsub);
    }

    GLchar actsubname[50];
    GLsizei length=0;
    GL_CHECK(glGetActiveSubroutineName(programID, shadertype, 0, 50, &length, actsubname));
    LOGI("GetActiveSubroutineName: %d, %s\n", length, actsubname);
    GL_CHECK(glGetActiveSubroutineUniformName(programID, shadertype, 0, 50, &length, actsubname));
    LOGI("GetActiveSubroutineUniformName: %d, %s\n", length, actsubname);

    GLint value=0;
    GL_CHECK(glGetActiveSubroutineUniformiv(programID, shadertype, 0, GL_NUM_COMPATIBLE_SUBROUTINES, &value));
    LOGI("GetActiveSubroutineUniformiv(GL_NUM_COMPIATIBLE_SUBROUTINES): %d\n", value);
    GL_CHECK(glGetActiveSubroutineUniformiv(programID, shadertype, 0, GL_COMPATIBLE_SUBROUTINES, &value));
    LOGI("GetActiveSubroutineUniformiv(GL_COMPATIBLE_SUBROUTINES): %d\n", value);
    GL_CHECK(glGetActiveSubroutineUniformiv(programID, shadertype, 0, GL_UNIFORM_SIZE, &value));
    LOGI("GetActiveSubroutineUniformiv(GL_UNIFORM_SIZE): %d\n", value);
    GL_CHECK(glGetActiveSubroutineUniformiv(programID, shadertype, 0, GL_UNIFORM_NAME_LENGTH, &value));
    LOGI("GetActiveSubroutineUniformiv(GL_UNIFORM_NAME_LENGTH): %d\n", value);
}

void renderFrame(int i) 
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    fillData();
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &Index[0]);
    glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &Index[3]);
    getData(GL_FRAGMENT_SHADER);
    getData(GL_VERTEX_SHADER);
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 1));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
//    for(int i=0; i<2; i++) {
//        renderFrame(i);
//        char ss[3];
//        sprintf(ss, "_%d", i);
//        string bmp_file = filename + ss + ".bmp";
        renderFrame(0);
        string bmp_file = filename + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
//    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
