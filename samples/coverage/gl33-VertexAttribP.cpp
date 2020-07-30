/**
 * @file gl33-VertexAttrib.cpp
 * @testpoint
 *
 *   glVertexAttribP3ui
 *   glVertexAttribP3uiv
 *   glVertexAttribP4ui
 *   glVertexAttribP4uiv
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
const float Vertices[] =
{
    -0.8, 0.7, 0.0,  0.0, 0.7, 0.0,  -0.4, 0.8, 0.0,
    -0.8, 0.5, 0.0,  0.0, 0.5, 0.0,  -0.4, 0.6, 0.0,
    -0.8, 0.3, 0.0,  0.0, 0.3, 0.0,  -0.4, 0.4, 0.0,
    -0.8, 0.1, 0.0,  0.0, 0.1, 0.0,  -0.4, 0.2, 0.0,
    -0.8,-0.1, 0.0,  0.0,-0.1, 0.0,  -0.4, 0.0, 0.0,
    -0.8,-0.3, 0.0,  0.0,-0.3, 0.0,  -0.4,-0.2, 0.0,
    -0.8,-0.5, 0.0,  0.0,-0.5, 0.0,  -0.4,-0.4, 0.0,
    -0.8,-0.7, 0.0,  0.0,-0.7, 0.0,  -0.4,-0.6, 0.0,

    0.0, 0.7, 0.0,  0.8, 0.7, 0.0,  0.4, 0.8, 0.0,
    0.0, 0.5, 0.0,  0.8, 0.5, 0.0,  0.4, 0.6, 0.0,
    0.0, 0.3, 0.0,  0.8, 0.3, 0.0,  0.4, 0.4, 0.0,
    0.0, 0.1, 0.0,  0.8, 0.1, 0.0,  0.4, 0.2, 0.0,
    0.0,-0.1, 0.0,  0.8,-0.1, 0.0,  0.4, 0.0, 0.0,
    0.0,-0.3, 0.0,  0.8,-0.3, 0.0,  0.4,-0.2, 0.0,
    0.0,-0.5, 0.0,  0.8,-0.5, 0.0,  0.4,-0.4, 0.0,
    0.0,-0.7, 0.0,  0.8,-0.7, 0.0,  0.4,-0.6, 0.0 
};
uint32_t Color[]={0x0, 0x0, 0x0, 0x0};
const GLubyte indices1[] = {0,1,2};
const GLubyte indices2[] = {3,4,5};
const GLubyte indices3[] = {6,7,8};
const GLubyte indices4[] = {9,10,11};
const GLubyte indices5[] = {12,13,14};
const GLubyte indices6[] = {15,16,17};
const GLubyte indices7[] = {18,19,20};
const GLubyte indices8[] = {21,22,23};

const GLubyte indices9[] = {24,25,26};
const GLubyte indices10[] = {27,28,29};
const GLubyte indices11[] = {30,31,32};
const GLubyte indices12[] = {33,34,35};
const GLubyte indices13[] = {36,37,38};
const GLubyte indices14[] = {39,40,41};
const GLubyte indices15[] = {42,43,44};
const GLubyte indices16[] = {45,46,47};

GLuint programID, VAOs, Buffers;

void setupGraphics(int w, int h)
{
    string vertexShaderPath = (string)GLSL_PATH + "gl33basic.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "gl33basic.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Color), Color));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_INT_2_10_10_10_REV, GL_TRUE, 0, BUFFER_OFFSET(sizeof(Vertices))));

    glViewport(0, 0, w, h);
} 

void renderFrame()
{
    GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f)); 
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT)); 
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDisableVertexAttribArray(1));

    uint32_t color1 = {0x0000ff00};
    GL_CHECK(glVertexAttribP1ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color1));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices1));
    GL_CHECK(glVertexAttribP1ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color1));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices9));

    const uint32_t color2[] = {0x0000ffc0, 0x0, 0x0, 0x0};
    GL_CHECK(glVertexAttribP1uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color2));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices2));
    GL_CHECK(glVertexAttribP1uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color2));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices10));

    uint32_t color3 = {0x00ffff00};
    GL_CHECK(glVertexAttribP2ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color3));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices3));
    GL_CHECK(glVertexAttribP2ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color3));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices11));

    const uint32_t color4[] = {0x00ff0000, 0x0, 0x0, 0x0};
    GL_CHECK(glVertexAttribP2uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color4));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices4));
    GL_CHECK(glVertexAttribP2uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color4));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices12));

    uint32_t color5 = {0xffc00000};
    GL_CHECK(glVertexAttribP3ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color5));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices5));
    GL_CHECK(glVertexAttribP3ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color5));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices13));

    const uint32_t color6[] = {0x0ff00000, 0x0, 0x0, 0x0};
    GL_CHECK(glVertexAttribP3uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color6));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices6));
    GL_CHECK(glVertexAttribP3uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color6));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices14));

    uint32_t color7 = {0xffc00000};
    GL_CHECK(glVertexAttribP4ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color7));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices7));
    GL_CHECK(glVertexAttribP4ui(1, GL_INT_2_10_10_10_REV, GL_TRUE, color7));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices15));

    const uint32_t color8[] ={0xff00ff00, 0x00, 0x00, 0x00};
    GL_CHECK(glVertexAttribP4uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color8));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices8));
    GL_CHECK(glVertexAttribP4uiv(1, GL_INT_2_10_10_10_REV, GL_TRUE, color8));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices16));

    glFlush();
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