/**
 ** @file max-vertex-uniform-components.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-05-15, create file
 ** @par TestPoints:
 **   GL_MAX_VERTEX_UNIFORM_COMPONENTS 
 */

#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint max_uniform_components;

GLfloat vertices[]={
        -0.8, -0.8, 0.0, 1.0,
         0.0,  0.8, 0.0, 1.0,
         0.8, -0.8, 0.0, 1.0
};

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    const GLchar* vertexShaderSource0 =
        "#version 430 core\n"
        "in vec4 position;\n\0";

    std::string vertexShaderSource_uniform0;
    vertexShaderSource_uniform0.append("layout(location=0) uniform mat4 rotation;\n");
    std::string vertexShaderSource_uniform1;
    std::string vertexShaderSource_main2;
    std::string vertexShaderSource_main3;
    std::string vertexShaderSource_main4="mat4 scaling =";
    for(int i=1; i< max_uniform_components/16; i++){
       vertexShaderSource_uniform1.append("layout(location="+std::to_string(i)+
        ") uniform mat4 scaling"+std::to_string(i)+";\n");
       std::string temp;
       vertexShaderSource_main2.append("scaling"+std::to_string(i));
       if(i < max_uniform_components/16 - 1){
           temp="*";} else {
           temp=" ;\n\0 ";
       }
        vertexShaderSource_main2.append(temp);
    }

    vertexShaderSource_main3.append("gl_Position = scaling*rotation*position;\n\n");
    vertexShaderSource_main4.append(vertexShaderSource_main2);


    std::string vertexShaderSource_main1 =
        "void main()\n"
        "{\n";

    std::string vertexShaderSource_main;
    std::string vertexShaderSource_s;

    vertexShaderSource_main.append(vertexShaderSource_main1);
    vertexShaderSource_main.append(vertexShaderSource_main4);
    vertexShaderSource_main.append(vertexShaderSource_main3+"}\n\0");
    vertexShaderSource_s.append(vertexShaderSource0);
    vertexShaderSource_s.append(vertexShaderSource_uniform0);
    vertexShaderSource_s.append(vertexShaderSource_uniform1);
    vertexShaderSource_s.append(vertexShaderSource_main);
    LOGI("vertexShaderSource = %s\n", vertexShaderSource_s.c_str());
    const GLchar* vertexShaderSource = vertexShaderSource_s.c_str();

    const GLchar* fragmentShaderSource = "#version 430 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}\n\0";

    programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}

bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &max_uniform_components));
    LOGI("GL_MAX_VERTEX_UNIFORM_COMPONENTS = %d\n", max_uniform_components);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    Matrix rotation = Matrix::createRotationX(45.0);
    Matrix scale0    = Matrix::createScaling(1.0f, 1.0f, 1.0f);
    Matrix scale1    = Matrix::createScaling(0.3f, 1.0f, 1.0f);
    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, rotation.getAsArray()));
    for(int i=1; i<max_uniform_components/16-1; i++){
        GL_CHECK(glUniformMatrix4fv(i, 1, GL_FALSE, scale0.getAsArray()));
    }
    GL_CHECK(glUniformMatrix4fv((max_uniform_components/16-1), 1, GL_FALSE, scale1.getAsArray()));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    glFlush();
}

void Sample::test() {
    string bmp_file = filename + ".bmp";
    LOGI("[]: filename=%s\n", bmp_file.c_str());
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();
    return 0;
}
