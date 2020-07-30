/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file vertexbinddivisor.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-10.12, Add commit
 * @brief basic test for vertexbinddivisor related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static const GLfloat square_vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
};

static const GLfloat instance_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f
};


static const GLfloat instance_positions[] = {
        -2.0f, -2.0f, 0.0f, 0.0f,
        2.0f, -2.0f, 0.0f, 0.0f,
        2.0f,  2.0f, 0.0f, 0.0f,
        -2.0f,  2.0f, 0.0f, 0.0f
};

GLenum interfaces[]={
    GL_UNIFORM,
    GL_UNIFORM_BLOCK,
    GL_ATOMIC_COUNTER_BUFFER,
    GL_PROGRAM_INPUT,
    GL_PROGRAM_OUTPUT,
    GL_TRANSFORM_FEEDBACK_VARYING,
    GL_BUFFER_VARIABLE,
    GL_SHADER_STORAGE_BLOCK,
    GL_TRANSFORM_FEEDBACK_BUFFER
};

GLenum pnames[]={
    GL_ACTIVE_RESOURCES,
    GL_MAX_NAME_LENGTH,
    GL_MAX_NUM_ACTIVE_VARIABLES
};

GLuint programID;
GLuint square_buffer;
GLuint square_vao;

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "vertexbinddivisor.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "vertexbinddivisor.frag";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glEnable(GL_DEPTH_TEST));

    GL_CHECK(glUseProgram(programID));

    GLuint offset = 0;

    GL_CHECK(glGenVertexArrays(1, &square_vao));
    GL_CHECK(glGenBuffers(1, &square_buffer));
    GL_CHECK(glBindVertexArray(square_vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, square_buffer));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices) + sizeof(instance_colors) + sizeof(instance_positions), NULL,
            GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(square_vertices), square_vertices));
    offset += sizeof(square_vertices);
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instance_colors),
                             instance_colors));
    offset += sizeof(instance_colors);
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instance_positions), instance_positions));
    offset += sizeof(instance_positions);

    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   (GLvoid *)sizeof(square_vertices)));
    GL_CHECK(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0,
             (GLvoid *)(sizeof(square_vertices) + sizeof(instance_colors))));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glEnableVertexAttribArray(2));

    GL_CHECK(glVertexAttribBinding(1, 1));
    GL_CHECK(glVertexBindingDivisor(1, 1));
    GL_CHECK(glVertexAttribBinding(2, 2));
    GL_CHECK(glVertexBindingDivisor(2, 1));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        GL_CHECK(glClearBufferfv(GL_COLOR, 0, black));
        GL_CHECK(glUseProgram(programID));
        GL_CHECK(glBindVertexArray(square_vao));
        GL_CHECK(glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 4));
}

void get_data(){
    GLint actNUM;

    for(int i=0;i<3;i++){
        int j;
            if(i<2) {
                for (j=0; j<9; j++) {
                    glGetProgramInterfaceiv(programID, interfaces[j], pnames[i], &actNUM);
                    LOGI("glGetProgramInterfaceiv(%d,%d) = %d\n", j, i, actNUM);
                }
            }else{
                glGetProgramInterfaceiv(programID,interfaces[1],pnames[2],&actNUM);
                LOGI("glGetProgramInterfaceiv(1,2) = %d\n",actNUM);
                glGetProgramInterfaceiv(programID,interfaces[2],pnames[2],&actNUM);
                LOGI("glGetProgramInterfaceiv(2,2) = %d\n",actNUM);
                glGetProgramInterfaceiv(programID,interfaces[7],pnames[2],&actNUM);
                LOGI("glGetProgramInterfaceiv(7,2) = %d\n",actNUM);
            }
        }

    GLint f = glGetUniformLocation(programID, "resourcet_1");
    glProgramUniform1f(programID, f, 1.0);
    LOGI("resourcet_1 index get from glGetUniformLocation = %d\n",f);

    GLint m = glGetUniformLocation(programID, "resourcet_2");
    glProgramUniform1f(programID, m, 1.0);
    LOGI("resourcet_1 index get from glGetUniformLocation = %d\n",m);

    const char * names[] ={"resourcet_1","resourcet_2","Uniforms","inValue","FragColor","outValue","inValue"};

    GLuint uniform_t1 = glGetProgramResourceIndex(programID,GL_UNIFORM,names[0]);
    LOGI("resourcet_1 index get from glGetProgramResourceIndex = %d\n",uniform_t1);

    GLuint uniform_t2 = glGetProgramResourceIndex(programID,GL_UNIFORM,names[1]);
    LOGI("resourcet_2 index get from glGetProgramResourceIndex = %d\n",uniform_t2);

    GLuint uniform__block = glGetProgramResourceIndex(programID,GL_UNIFORM_BLOCK,names[2]);
    LOGI("uniform__block index get from glGetProgramResourceIndex = %d\n",uniform__block);

    GLuint input = glGetProgramResourceIndex(programID,GL_PROGRAM_INPUT,names[3]);
    LOGI("input index get from glGetProgramResourceIndex = %d\n",input);

    GLuint output = glGetProgramResourceIndex(programID,GL_PROGRAM_OUTPUT,names[4]);
    LOGI("output index get from glGetProgramResourceIndex = %d\n",output);

    GLuint transVarying = glGetProgramResourceIndex(programID,GL_TRANSFORM_FEEDBACK_VARYING,names[5]);
    LOGI("transVarying index get from glGetProgramResourceIndex = %d\n",transVarying);

    GLuint transBuffer = glGetProgramResourceIndex(programID,GL_TRANSFORM_FEEDBACK_BUFFER,names[6]);
    LOGI("transBuffer index get from glGetProgramResourceIndex = %d\n",transBuffer);

    GLchar name_prn[64];

    glGetProgramResourceName(programID,GL_UNIFORM,2,sizeof(name_prn),NULL,name_prn);
    LOGI("the name of uniform which index is 2 is = %s\n",name_prn);
    memset(name_prn,0,64);
    glGetProgramResourceName(programID,GL_PROGRAM_INPUT,1,sizeof(name_prn),NULL,name_prn);
    LOGI("the name of INput which index is 2 is = %s\n",name_prn);

    memset(name_prn,0,64);
    glGetProgramResourceName(programID,GL_PROGRAM_OUTPUT,0,sizeof(name_prn),NULL,name_prn);
    LOGI("the name of GL_PROGRAM_OUTPUT which index is 2 is = %s\n",name_prn);
    GLint k=glGetProgramResourceLocation(programID,GL_PROGRAM_OUTPUT,name_prn);
    LOGI("the location is = %d\n",k);
   // GLint p=glGetProgramResourceLocationIndex(programID,GL_PROGRAM_OUTPUT,name_prn);
   // LOGI("the location index is = %d\n",p);

    memset(name_prn,0,64);
    glGetProgramResourceName(programID,GL_UNIFORM_BLOCK,0,sizeof(name_prn),NULL,name_prn);
    LOGI("the name of GL_UNIFORM_BLOCK which index is 2 is = %s\n",name_prn);

    memset(name_prn,0,64);
    glGetProgramResourceName(programID,GL_TRANSFORM_FEEDBACK_VARYING,0,sizeof(name_prn),NULL,name_prn);
    LOGI("the name of GL_TRANSFORM_FEEDBACK_VARYING which index is 2 is = %s\n",name_prn);

    GLint params[64];
    GLenum props[] = {GL_TYPE,GL_ARRAY_SIZE,GL_REFERENCED_BY_VERTEX_SHADER,GL_REFERENCED_BY_FRAGMENT_SHADER,GL_REFERENCED_BY_COMPUTE_SHADER,GL_LOCATION,GL_NAME_LENGTH};

    glGetProgramResourceiv(programID,GL_PROGRAM_INPUT,0,7,props,64,NULL,params);

    LOGI("glGetProgramResourceiv GL_TYPE is = %d\n",params[0]);
    LOGI("glGetProgramResourceiv GL_ARRAY_SIZE is = %d\n",params[1]);
    LOGI("glGetProgramResourceiv GL_REFERENCED_BY_VERTEX_SHADER is = %d\n",params[2]);
    LOGI("glGetProgramResourceiv GL_REFERENCED_BY_FRAGMENT_SHADER is = %d\n",params[3]);
    LOGI("glGetProgramResourceiv GL_REFERENCED_BY_COMPUTE_SHADER is = %d\n",params[4]);
    LOGI("glGetProgramResourceiv GL_LOCATION is = %d\n",params[5]);
    LOGI("glGetProgramResourceiv GL_NAME_LENGTH is = %d\n \n",params[6]);
    memset(params,0,64);

    GLenum uprops[] = {GL_OFFSET,GL_BLOCK_INDEX,GL_ARRAY_STRIDE,GL_MATRIX_STRIDE,GL_IS_ROW_MAJOR,GL_ATOMIC_COUNTER_BUFFER_INDEX,GL_BUFFER_BINDING,GL_BUFFER_DATA_SIZE,GL_NUM_ACTIVE_VARIABLES,GL_ACTIVE_VARIABLES};
    glGetProgramResourceiv(programID,GL_UNIFORM,0,10,uprops,64,NULL,params);
    for(int i=0;i<10;i++){
        LOGI("glGetProgramResourceiv GL_UNIFORM is = %d\n",params[i]);
    }

}

void Sample::test() {

    setupGraphics(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
    renderFrame();
    get_data();
    save2bmp(bmp_file.c_str());
    LOGI("bmp_file=%s", bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

