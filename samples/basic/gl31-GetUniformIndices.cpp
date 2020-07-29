/* =================================================================
 ** Copyright (c) 2019 Botson Corp
 ** Botson Confidential and Proprietary
 ** =================================================================
 **/

/**
 ** @file gl31-GetUniformIndices.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-04-15, create file
 ** @par TestPoints:
 **
 **  glGetUniformIndices
 **  glUniformBlockBinding
 **  glGetActiveUniformBlockName
 **  glGetActiveUniformBlockiv
 */

#include "Sample.h"
#include "Shader.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLfloat vertices[] = { 
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
}; 
GLfloat colors[] = { 
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
}; 

GLuint programID, VAOs, Buffers;

GLint uboSize;
GLuint uboIndex;
GLint posLocation, colorLocation;

GLint iLocu;
GLuint indices;
GLuint ubo;
GLint getlength;
GLchar uniformBlockName[20] = {};
const GLchar* names[] = {
        "u1f",
        "u2f",
        "u3f",
        "u4f"
};

bool setupGraphics(int w, int h)
{
   /*load shader*/
    string vertexShaderPath =(string)GLSL_PATH + "GetUniformIndices.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "GetUniformIndices.frag";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    GL_CHECK(posLocation = glGetAttribLocation(programID, "position"));
    GL_CHECK(colorLocation = glGetAttribLocation(programID, "acolor"));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
    GL_CHECK(glEnableVertexAttribArray(posLocation));
    GL_CHECK(glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(colorLocation));
    GL_CHECK(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void getData()
{
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_BINDING, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_BINDING) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_DATA_SIZE) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_NAME_LENGTH, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_NAME_LENGTH) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER) : uboSize: %d\n", uboSize);
    glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, &uboSize);
    LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER) : uboSize: %d\n", uboSize);
}

void renderFrame(void) {
    int i = 0;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
    float uniformBuffer[] = {0.1,
                             0.1, 0.1,
                             0.1, 0.1, 0.1,
                             0.0, 1.0, 0.0, 0.0};

    uboIndex = glGetUniformBlockIndex(programID, "UniformBlock");
    LOGI("glGetUniformBlockIndex : uboIndex: %d\n", uboIndex);
    GL_CHECK(glGetActiveUniformBlockName(programID, uboIndex, sizeof(uniformBuffer), &getlength, uniformBlockName));
    LOGI("glGetActiveUniformBlockName : length = %d, uniformBlockName = %s \n", getlength, uniformBlockName);

    GL_CHECK(iLocu = glGetUniformLocation(programID, "UniformBlock"));

    GL_CHECK(glGenBuffers(1, &ubo));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, ubo));
    GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformBuffer), uniformBuffer, GL_STATIC_DRAW));
    GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo));

    GL_CHECK(glGetUniformIndices(programID, 1, names, &indices));
    LOGI("glGetUniformIndices: indices = %d \n", indices);

    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    glFlush();
}

void Sample::test() {
    string bmp_file = filename + ".bmp";
    LOGI("[]: filename=%s\n", bmp_file.c_str());
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    getData();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}