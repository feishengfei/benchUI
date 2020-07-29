/**
 * @file buffer.cpp
 * @testpoint:
 *   glGetBufferParameteri64v
 *   glGetMultisamplefv
 *   glGetInteger64v
 */

#include "Sample.h"
#include <cstring>
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint buffers;

float vertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
const float vertColor[] =
{
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f
};

GLubyte indices[] = {0,1,2, 2,4,5};
GLuint VAOs, abo, ebo, programID;

static const GLenum types[] = {
    GL_BUFFER_ACCESS_FLAGS,
    GL_BUFFER_MAPPED,
    GL_BUFFER_SIZE,
    GL_BUFFER_USAGE
};

static const GLenum factors[] = {
    GL_ARRAY_BUFFER, 
    GL_ATOMIC_COUNTER_BUFFER,
    GL_COPY_READ_BUFFER,
    GL_COPY_WRITE_BUFFER,
    GL_DISPATCH_INDIRECT_BUFFER,
    GL_DRAW_INDIRECT_BUFFER,
    GL_ELEMENT_ARRAY_BUFFER,
    GL_PIXEL_PACK_BUFFER,
    GL_PIXEL_UNPACK_BUFFER,
    GL_QUERY_BUFFER,
    GL_SHADER_STORAGE_BUFFER,
    GL_TEXTURE_BUFFER,
    GL_TRANSFORM_FEEDBACK_BUFFER,
    GL_UNIFORM_BUFFER
};

void getdata()
{
    GLint64 params64;
    GLint64 valData64;
    GL_CHECK(glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &params64));
    LOGI("array buffer size is %d\n", params64);
    GL_CHECK(glGetInteger64v(GL_MAX_ELEMENT_INDEX, &valData64));
    LOGI("glGetInteger64v(pname = GL_MAX_ELEMENT_INDEX): valData64 =%lld\n", valData64);
    }

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "gl32basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "gl32basic.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &abo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, abo));
    GLuint isBuffer = GL_CHECK(glIsBuffer(abo));
    LOGI("glIsBuffer=%d\n", isBuffer);
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertColor) + sizeof(vertices), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertColor), vertColor));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    getdata();


    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0));
    GL_CHECK(glFlush());
    GL_CHECK(glDeleteBuffers(1, &buffers));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
    LOGI("[]: filename=%s\n", bmp_file.c_str());
    renderFrame();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}