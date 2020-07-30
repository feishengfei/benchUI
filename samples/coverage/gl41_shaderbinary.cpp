/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 *
 * @file gl41_shaderbinary 
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-11, Init file
 * @par TestPoints:
 *    glShaderBinary
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;

float triangleVertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f,  0.5f
};

float triangleColors[] = {
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0
};
GLenum binaryFormat;

bool getdata() {
    GLint num=0;
    glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &num);
    LOGI("get(GL_NUM_SHADER_BINARY_FORMATS): %d\n", num);
    GLint *formats = new GLint[num];
    glGetIntegerv(GL_SHADER_BINARY_FORMATS, formats);
    for(int i=0; i<num; i++) {
        binaryFormat = formats[i];
        LOGI("get(GL_SHADER_BINARY_FORMATS): %d : 0x%x, %s\n", i+1, formats[i], get_enum_name(formats[i]));
    }
    delete formats;
    if(num == 0) {
        LOGI("No shader binary formats support!");
        return FALSE;
    }
    return TRUE;
}

bool getProgramBinary(const char *vertex, const char *frag, const char *filename)
{
    GLuint vertexID=-1, fragmentID=-1;
    GLint ID;

    FILE *fp = fopen(filename,"rb");
    if(fp == NULL) {
        printf("open file failed!\n");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int len = (int)ftell(fp);
    GLubyte *binary = new GLubyte[len];
    fseek(fp, 0, SEEK_SET);
    fread(binary, len, 1, fp);
    fclose(fp);

    Shader::processShader(&vertexID, vertex, GL_VERTEX_SHADER);
    Shader::processShader(&fragmentID, frag, GL_FRAGMENT_SHADER);
    ID = GL_CHECK(glCreateProgram());
    if (!ID) 
    {
        printf("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(ID, vertexID));
    GL_CHECK(glAttachShader(ID, fragmentID));
    GL_CHECK(glProgramParameteri(ID, GL_PROGRAM_BINARY_RETRIEVABLE_HINT,GL_TRUE));
    GL_CHECK(glLinkProgram(ID));

    GLint linked;
    glGetProgramiv(ID, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        GLsizei len;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &len );

        GLchar* linklog = new GLchar[len+1];
        glGetProgramInfoLog(ID, len, &len, linklog );
        printf("Shader linking failed: %s\n", linklog);
        delete linklog;

        GL_CHECK(glDeleteShader(fragmentID));
        GL_CHECK(glDeleteShader(vertexID));
        
        return false;

    }

    return true;
}

bool setupGraphics(int width, int height) {
    if(getdata()) {
/*        string vertexShaderPath = ((string)GLSL_PATH) + "vert2color4_passby.vert";
        string fragmentShaderPath = ((string)GLSL_PATH) + "color_passby.frag";
        string binaryFile = "binaryProgram.bin";
        getProgramBinary(vertexShaderPath.c_str(), fragmentShaderPath.c_str(), binaryFile.c_str());
        programID = loadBinaryProgram(binaryFile.c_str());
        if (programID <= 0) {
            LOGE("Could not create program.");
            return false;
        }*/
    }
//    GL_CHECK(glViewport(0, 0, width, height));
//    GL_CHECK(glClearColor(0.3f, 0.3f, 0.3f, 0.7f));
    return true;
}

void fileData() {
    GLint iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v2Position"));
    GLint iLocFillColor = GL_CHECK(glGetAttribLocation(programID, "a_v4Color"));

    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors));
    GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    fileData();
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);
//    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("%s\n", bmp_file.c_str());
//    save2bmp(bmp_file.c_str());
//    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
