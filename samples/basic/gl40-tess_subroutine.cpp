/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file draw.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Eric.Ma, 2019-11-27, Add commit
 * @brief basic test for draw related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

GLint iLocPosition = 0, colorLocation = 0;
GLuint programID = 0;
GLuint Index[5]={0, 0, 0, 0, 0};

bool setupGraphics(int width, int height)
{
    glEnable( GL_DEPTH_TEST );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glViewport( 0, 0, width, height );

    ShaderInfo  shaders[] = {
        {GL_VERTEX_SHADER, "tessellation.vert", },
        {GL_TESS_CONTROL_SHADER, "tessellation.tcs", },
        {GL_TESS_EVALUATION_SHADER, "tessellation.tes", },
        {GL_FRAGMENT_SHADER, "tessellation.frag", },
        {GL_NONE,NULL},
    };

    programID = Shader::LoadShaders( shaders );

    Index[1] = GL_CHECK(glGetSubroutineIndex(programID, GL_TESS_EVALUATION_SHADER, "omu"));
    Index[0] = GL_CHECK(glGetSubroutineIndex(programID, GL_TESS_EVALUATION_SHADER, "omv"));
    LOGI("GetSubroutineIndex(GL_TESS_EVALUATION_SHADER): %d, %d\n", Index[0], Index[1]);

    Index[1] = GL_CHECK(glGetSubroutineIndex(programID, GL_TESS_CONTROL_SHADER, "more"));
    Index[0] = GL_CHECK(glGetSubroutineIndex(programID, GL_TESS_CONTROL_SHADER, "less"));
    LOGI("GetSubroutineIndex(GL_TESS_CONTROL_SHADER): %d, %d\n", Index[2], Index[3]);
    return true;
}

void getData(GLenum shadertype)
{
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

    if(shadertype==GL_TESS_EVALUATION_SHADER) {
        GLint locSetColor=GL_CHECK(glGetSubroutineUniformLocation(programID, shadertype, "coord"));
        LOGI("GetSubroutineUniformLocation: %d\n", locSetColor);
        GLuint uniformsub = 0;
        GL_CHECK(glGetUniformSubroutineuiv(shadertype, locSetColor, &uniformsub));
        LOGI("GetUniformSubroutineuiv: %d\n", uniformsub);
    }
    if(shadertype==GL_TESS_EVALUATION_SHADER) {
        GLint locSetPos=GL_CHECK(glGetSubroutineUniformLocation(programID, shadertype, "level"));
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

void renderFrame(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram( programID );
    glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &Index[1]);
    glUniformSubroutinesuiv(GL_TESS_CONTROL_SHADER, 1, &Index[2]);
    getData(GL_TESS_EVALUATION_SHADER);
    getData(GL_TESS_CONTROL_SHADER);
    glDrawArrays(GL_PATCHES, 0, 3);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);

    sample.test();

    return 0;
}
