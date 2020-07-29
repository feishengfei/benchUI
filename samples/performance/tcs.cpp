#include "Sample.h"
#include "Timer.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint max_uniform_components;
GLint max_uniform_vectors;
GLint uni_num;
double                    flopstime  = 0.0;
const static int          FRAMES_NUM = 10;
const static unsigned int VERTEX_NUM = 30000;
float                     vertices[VERTEX_NUM * 4];
float                     colors[VERTEX_NUM * 4];

//GLfloat vertices[]={
//        -0.8, -0.8, 0.0, 1.0,
//         0.0,  0.8, 0.0, 1.0,
//         0.8, -0.8, 0.0, 1.0
//};
//
//GLfloat colors[]={
//        1.0,  0.0, 0.0, 1.0,
//        0.0,  1.0, 0.0, 1.0,
//        0.8,  0.0, 1.0, 1.0
//};

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

  //const GLchar* vertexShaderSource =
  // std::string vertexShaderSource0 =
  //     "\n#version 430 core\n"
  //     "layout(location=0) in vec4 position;\n"
  //     "layout(location=1) in vec4 vcolor;\n";
  // std::string vertexShaderSource1 =
  //     "out vec4 color;\n"
  //     "void main()\n"
  //     "{\n";
  // std::string vertexShaderSource2=
  // "    gl_Position = scale*position;\n"
  // "    color = vcolor;\n"
  // "}\n\0";


  // std::string vertexShaderSource_uniform;
  // std::string vertexShaderSource_main0;
  // std::string vertexShaderSource_main1="mat4 scale =";
  // for(int i=0; i<max_uniform_components/16; i++){
  //     vertexShaderSource_uniform.append("\nlayout(location="+std::to_string(i)+
  //     ") uniform mat4 scale"+std::to_string(i)+";\n");
  //    std::string temp;
  //     vertexShaderSource_main0.append("scale"+std::to_string(i));
  //    if(i<max_uniform_components/16-1){
  //        temp="*";} else {
  //        temp=" ;\n\0 ";
  //    }
  //     vertexShaderSource_main0.append(temp);
  // }
  // vertexShaderSource_main1.append(vertexShaderSource_main0);
  // vertexShaderSource0.append(vertexShaderSource_uniform);
  // vertexShaderSource0.append(vertexShaderSource1);
  // vertexShaderSource0.append(vertexShaderSource_main1);
  // vertexShaderSource0.append(vertexShaderSource2);
  // LOGI("vertexShaderSource = %s\n", vertexShaderSource0.c_str());
  // const GLchar* vertexShaderSource = vertexShaderSource0.c_str();

    const GLchar *vertexShaderSource =
        "\n#version 430 core\n"
        "layout(location=0) in vec4 position;\n"
        "layout(location=1) in vec4 vcolor;\n"
        "out vec4 color;\n\n"
        "void main()\n"
        "{\n"
        "    gl_Position=position;\n"
        "    color=vcolor;\n"
        "}\n\0";

    const GLchar*  tcShaderSource =
        "#version 430 core\n"
        "layout(vertices=3) out;\n"
        "layout(location=0) uniform mat4 scale0;\n"
        "layout(location=4) uniform mat4 scale1;\n"
        "layout(location=8) uniform mat4 scale2;\n"
        "layout(location=12) uniform mat4 scale3;\n"
        "layout(location=16) uniform mat4 scale4;\n"
        "layout(location=20) uniform mat4 scale5;\n"
        "layout(location=24) uniform mat4 scale6;\n"
        "layout(location=28) uniform mat4 scale7;\n"
        "layout(location=32) uniform mat4 scale8;\n"
        "layout(location=36) uniform mat4 scale9;\n"
        "layout(location=40) uniform mat4 scale10;\n"
        "layout(location=44) uniform mat4 scale11;\n"
        "layout(location=48) uniform mat4 scale12;\n"
        "layout(location=52) uniform mat4 scale13;\n"
        "layout(location=56) uniform mat4 scale14;\n"
        "layout(location=60) uniform mat4 scale15;\n"
        "layout(location=64) uniform mat4 scale16;\n"
        "layout(location=68) uniform mat4 scale17;\n"
        "layout(location=72) uniform mat4 scale18;\n"
        "layout(location=76) uniform mat4 scale19;\n"
        "layout(location=80) uniform mat4 scale20;\n"
        "layout(location=84) uniform mat4 scale21;\n"
        "layout(location=88) uniform mat4 scale22;\n"
        "layout(location=92) uniform mat4 scale23;\n"
        "layout(location=96) uniform mat4 scale24;\n"
        "layout(location=100) uniform mat4 scale25;\n\n"
        "in vec4 color[];\n"
        "out vec4 TCcolor[];\n"
        "void main()\n"
        "{\n"
        "    mat4 scale=scale0*scale1*scale2*scale3*scale4*scale5\n"
        "               *scale6*scale7*scale8*scale9*scale10*scale11*\n"
        "               scale12*scale13*scale14*scale15*scale17*scale17\n"
        "               *scale18*scale19*scale20*scale21*scale22\n"
        "               *scale23*scale24*scale25;\n"
        "    gl_TessLevelInner[0] = 3.0;\n"
        "    gl_TessLevelOuter[0] = 3.0;\n"
        "    gl_TessLevelOuter[1] = 3.0;\n"
        "    gl_TessLevelOuter[2] = 3.0;\n\n"
        "    gl_out[gl_InvocationID].gl_Position = scale*gl_in[gl_InvocationID].gl_Position;\n"
        "    TCcolor[gl_InvocationID] = color[gl_InvocationID];\n"
        "}";

    const GLchar* teShaderSource =
        "\n#version 430 core\n"
        "layout(triangles) in;\n"
        "in vec4 TCcolor[];\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    float u = gl_TessCoord.x;\n"
        "    float v = gl_TessCoord.y;\n"
        "    float w = gl_TessCoord.z;\n"
        "    gl_Position = (u * gl_in[0].gl_Position+ \n"
        "    v * gl_in[1].gl_Position + w * gl_in[2].gl_Position);\n"
        "    color = (TCcolor[0]*(1.0-v) + \n"
        "    + TCcolor[1]*(1.0-u) + + TCcolor[2]*(1.0-w));\n"
        "}\n\0";

    const GLchar *fragmentShaderSource =
        "#version 430 core\n"
        "in vec4 color;\n"
        "out vec4 fcolor;\n\n"
        "void main()\n"
        "{\n"
        "    fcolor = color;\n"
        "}\n\0";

    programID = Shader::createProgramFromString(vertexShaderSource, tcShaderSource, teShaderSource, fragmentShaderSource);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            LOGI("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}


bool setupGraphics(int w, int h)
{
    for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
        vertices[i] = ((float)(rand() % 100)) / 50 - 1;
    }

    for (int j = 0; j < sizeof(colors) / sizeof(colors[0]); j++) {
        colors[j] = ((float)(rand() % 10)) / 10;
    }

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    Matrix scale0    = Matrix::createScaling(1.0f, 1.0f, 1.0f);
    Matrix scale1    = Matrix::createScaling(0.3f, 1.0f, 1.0f);
    for(int i=0; i<25; i++){
        GL_CHECK(glUniformMatrix4fv(i*4, 1, GL_FALSE, scale0.getAsArray()));
    }
    GL_CHECK(glUniformMatrix4fv(100, 1, GL_FALSE, scale1.getAsArray()));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 3));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, VERTEX_NUM));
}

void
cleanUp() {
    glDeleteProgram(programID);
    glDeleteBuffers(1, &Buffers);
    glDeleteVertexArrays(1, &VAOs);
}

void Sample::test() {
    Timer    *time = new Timer();
    for (int j     = 0; j < FRAMES_NUM; j++) {
        time->reset();
        setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame();
        glFlush();
        flopstime = flopstime + time->getTime();
        string bmp_file = filename + ".bmp";
        save2bmp(bmp_file.c_str());
        SwapBuffers();
        cleanUp();
    }
    double ave_time = flopstime / FRAMES_NUM;
    LOGI("tcs One frame average time:--%f\n", ave_time);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
