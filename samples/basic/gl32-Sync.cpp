/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl32-Sync.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2019-06-28, create file
 * @param TestPoints:
 *
 *  glFenceSync
 *  glIsSync
 *  glDeleteSync
 *  glClientWaitSync
 *  glWaitSync
 *  glGetSynciv
 *     
 */
#include "Sample.h"

//
using std::string;
GLuint programID = -1;

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
};

GLfloat color[] = {
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0
};

GLfloat color1[] = {
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0
};

/*vbo project*/
GLuint buffers[2];
GLuint vao;


bool setupGraphics()
{
    string vertexShaderPath = (string)GLSL_PATH + "Sync.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "Sync.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));
    glClearColor(0.0,0.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);
}

void renderFrame()
{
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(2, buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

    void * data = GL_CHECK(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
    memcpy(data ,color1 ,sizeof(color1) );
    GL_CHECK(glUnmapBuffer(GL_ARRAY_BUFFER));

    GLsync s;

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

    LOGI("Whether GLsync exists ? : %d\n",glIsSync(s));

    //create fence
    s = GL_CHECK(glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0));
    LOGI("Whether GLsync exists ? : %d\n",glIsSync(s));

    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 0.0f));
    
    GLenum iResult = GL_CHECK(glClientWaitSync(s, GL_SYNC_FLUSH_COMMANDS_BIT, 1000));
    switch(iResult)
    {
        case GL_ALREADY_SIGNALED:
            LOGI("glClientWaitSync return : GL_ALREADY_SIGNALED \n");
            break;
        case GL_TIMEOUT_EXPIRED:
            LOGI("glClientWaitSync return : GL_TIMEOUT_EXPIRED \n");
            break;
        case GL_CONDITION_SATISFIED:
            LOGI("glClientWaitSync return : GL_CONDITION_SATISFIED \n");
            break;
        case GL_WAIT_FAILED:
            LOGI("glClientWaitSync return : GL_WAIT_FAILED \n");
            break;
        default:
            LOGI("glClientWaitSync return : defult error!!!!!!!!\n");
    }

    GL_CHECK(glWaitSync(s, 0, GL_TIMEOUT_IGNORED));
    GLint sync_[2];
    GL_CHECK(glGetSynciv(s, GL_SYNC_STATUS, sizeof(sync_[1]), &sync_[0], &sync_[1]));
    LOGI("glGetSynciv length = %d \n",sync_[0]);
    LOGI("glGetSynciv values = %d \n",sync_[1]);

    GL_CHECK(glDeleteSync(s));
    LOGI("Whether GLsync exists ? : %d\n",glIsSync(s));

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

     
    }

void Sample::test() {
    string bmp_file = filename + ".bmp";
    LOGI("[]: filename=%s\n", bmp_file.c_str());
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    
    setupGraphics();
    renderFrame();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
