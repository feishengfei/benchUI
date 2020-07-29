/**
 * @file buffer.cpp
 * @testpoint:
 *   glGetBufferParameteri64v
 *   glGetMultisamplefv
 *   glGetInteger64v
 */

#include "Sample.h"
#include <cstring>

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

GLuint buffers[2];
GLuint vao;

float triangleVertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
const float triangleVertices1[] =
{
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
     0.0f,-0.5f, 0.0f,
};

GLubyte indices[] = {1,2,4, 0,3,5};
GLubyte indices1[] = {5,4,1};


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
    GLfloat val;
    GLint64 valData64;
    GLint64 valData64_v;

    for(int i=0; i<ARRAY_NUM(factors); i++) {
        for(int j=0; j<ARRAY_NUM(types); j++) {
            glGetBufferParameteri64v(factors[i], types[j], &params64);
	    LOGI("glGetBufferParameteri64v(%s, %s): params64 = 0x%0x\n",get_enum_name(factors[i]), get_enum_name(types[j]) ,params64);
        }
    }
    glGetMultisamplefv(GL_SAMPLE_POSITION, 4, &val);
    LOGI("glGetMultisamplefv(index = 4): val = %f\n", val);

    glGetInteger64v(GL_MAX_ELEMENT_INDEX, &valData64);
    LOGI("glGetInteger64v(pname = GL_MAX_ELEMENT_INDEX): valData64 =%lld\n", valData64);
    glGetInteger64i_v(GL_MAX_ELEMENT_INDEX , 1 , &valData64_v);
    LOGI("glGetInteger64i_v(pname = GL_MAX_ELEMENT_INDEX , index = 1): valData64 =%lld\n", valData64_v);
}

bool setupGraphics(int width, int height)
{
    GLfloat *mapArray;
    GLubyte *mapElement;

    glGenBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices1), triangleVertices1);
    mapArray = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    LOGI("glMapBuffer(GL_ARRAY_BUFFER)=%f\n", *mapArray);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    mapElement = (GLubyte *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    *mapElement = 2;
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

    getdata();
    GLboolean isBuffer = glIsBuffer(buffers[0]);
    LOGI("glIsBuffer(buffers[0])=%s\n", GET_BOOL(isBuffer));
    isBuffer = glIsBuffer(buffers[1]);
    LOGI("glIsBuffer(buffers[1])=%s\n", GET_BOOL(isBuffer));

    glViewport(0, 0, width, height);

    /* Set clear screen color. */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepthf(1.0f);

    return true;
}

void renderFrame(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(0.0, 1.0, 0.0, 0.0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glFlush();
    glDeleteBuffers(2, buffers);
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