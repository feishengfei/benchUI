#include "Sample.h"
#include "Timer.h"
#include <string>

const static int          FRAMES_NUM = 10;
const static unsigned int VERTEX_NUM = 30000;
GLuint indices[VERTEX_NUM*6/5-1];
float                     vertices[VERTEX_NUM * 2];
float                     colors[VERTEX_NUM * 3];
GLuint                    vao, vbo, programID;
double                    flopstime  = 0.0;
#define BUFFER_OFFSET(x)  ((const void*) (x))

const GLchar *vertexShaderSource =
                     "#version 430 core\n"
                     "layout(location=0) in vec2 position;\n"
                     "layout(location=1) in vec3 vcolor;\n"
                     "out vec4 color;\n\n"
                     "void main()\n"
                     "{\n"
                     "    gl_Position = vec4(position, 0.0, 1.0);\n"
                     "    color = vec4(vcolor, 1.0);\n"
                     "}\n\0";

const GLchar *fragmentShaderSource =
                     "#version 430 core\n"
                     "in vec4 color;\n"
                     "out vec4 fcolor;\n\n"
                     "void main()\n"
                     "{\n"
                     "    fcolor = color;\n"
                     "}\n\0";

    bool
    initProgram() {
        GLint success;
        GLchar infoLog[512];

        programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            LOGI("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
        }
        glClearColor(0.0, 0.0, 0.0, 1.0);
        return true;
    }

    void
    initData() {
        for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
            vertices[i] = ((float)(rand() % 100)) / 50 - 1;
        }
        for(int j=0; j<VERTEX_NUM*6/5-1; j++){
            if(j<5){
                indices[j]=j;
            }else if(j%6==5){
                indices[j]=0xFFFF;
            }else{
                indices[j]=indices[j-6]+5;
            }
        }
        for (int k=0; k<sizeof(colors) / sizeof(colors[0]); k++) {
            colors[k] = ((float)(rand() % 10)) / 10;
        }
        GL_CHECK(glGenVertexArrays(1, &vao));
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glGenBuffers(1, &vbo));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+ sizeof(colors), NULL, GL_STATIC_DRAW));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
        GL_CHECK(glEnableVertexAttribArray(0));
        GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(1));
        GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void
    renderFrame() {
        GL_CHECK(glUseProgram(programID));
        GL_CHECK(glEnable(GL_PRIMITIVE_RESTART));
        GL_CHECK(glPrimitiveRestartIndex(0xFFFF));
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glDrawElements(GL_TRIANGLE_FAN, VERTEX_NUM, GL_UNSIGNED_INT, indices));
    }

    void
    cleanUp() {
        glDeleteProgram(programID);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void Sample::test() {
        Timer *time = new Timer();
        for(int j=0; j<FRAMES_NUM; j++){
            time->reset();
            initProgram();
            initData();
            renderFrame();
            glFlush();
            flopstime = flopstime + time->getTime();
            string bmp_file = filename + ".bmp";
            save2bmp(bmp_file.c_str());
            SwapBuffers();
            cleanUp();
        }
        double ave_time = flopstime / FRAMES_NUM;
        LOGI("restart One frame average time:--%f\n", ave_time);
    }

    int main(int argc, char **argv) {
        Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

        sample.test();

        return 0;
    }
