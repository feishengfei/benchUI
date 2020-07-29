#include "Sample.h"
#include "Timer.h"
#include <string>

const static int FRAMES_NUM = 10;
const static unsigned int  VERTEX_NUM = 60000;
float vertices0[VERTEX_NUM];
float vertices1[VERTEX_NUM];
float colors[VERTEX_NUM*3];
GLuint vao, vbo, programID;
double flopstime=0.0;
#define BUFFER_OFFSET(x)  ((const void*) (x))

const GLchar* vertexShaderSource =
                    "#version 430 core\n"
                    "layout(location=0) in vec2 position;\n"
                    "layout(location=1) in vec3 vcolor;\n"
                    "out vec4 color;\n\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = vec4(position, 0.0, 1.0);\n"
                    "    color = vec4(vcolor, 1.0);\n"
                    "}\n\0";

const GLchar* fragmentShaderSource =
                    "#version 430 core\n"
                    "in vec4 color;\n"
                    "out vec4 fcolor;\n\n"
                    "void main()\n"
                    "{\n"
                    "    fcolor = color;\n"
                    "}\n\0";

bool initProgram()
    {
        GLint success;
        GLchar infoLog[512];

        programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
        LOGI("PROGRAM = %d\n", programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
        }

        return true;
    }
    
    void initBuffer()
    {
        for(int i = 0; i < sizeof(vertices0)/sizeof(vertices0[0]) ; i++) {
            vertices0[i] = ((float)(rand() % 100)) / 50 - 1;
        }
        for(int k = 0; k < sizeof(vertices1)/sizeof(vertices1[0]) ; k++) {
            vertices1[k] = ((float)(rand() % 100)) / 25 - 2;
        }
        for(int j = 0; j < sizeof(colors)/sizeof(colors[0]) ; j++) {
            colors[j] = ((float)(rand() % 50)) / 50;
        }
        GL_CHECK(glGenVertexArrays(1, &vao));
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glGenBuffers(1, &vbo));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0)+sizeof(vertices1)+sizeof(colors), NULL, GL_STATIC_DRAW));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices0), vertices0));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices0), sizeof(vertices1), vertices1));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices0)+sizeof(vertices1), sizeof(colors), colors));
        GL_CHECK(glEnableVertexAttribArray(0));
        GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(1));
        GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices0)+ sizeof(vertices1))));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
        GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    }

    
    void renderFrame(int i)
    {
        GL_CHECK(glUseProgram(programID));
        GL_CHECK(glBindVertexArray(vao));
        switch(i){
        case 0:
            glDrawArrays(GL_TRIANGLES, 0, VERTEX_NUM);
            break;
        case 1:
            GL_CHECK(glEnable(GL_DEPTH_TEST));
            GL_CHECK(glDepthFunc(GL_ALWAYS));
            glDrawArrays(GL_TRIANGLES, 0, VERTEX_NUM);
            break;
        default:
            break;
        }
    }
    
    void cleanUp()
    {
        glDeleteProgram(programID);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

void Sample::test() {
    Timer *time = new Timer();
    for(int i=0; i<2; i++) {
        for(int j=0; j<FRAMES_NUM; j++) {
            time->reset();
            initProgram();
            initBuffer();
            renderFrame(i);
            glFlush();
            char ss[5];
            sprintf(ss, "%d_%d", i, j);
            string bmp_file  = filename + "-" + ss + ".bmp";
            LOGI("bmp_file=%s\n", bmp_file.c_str());
            save2bmp(bmp_file.c_str());
            flopstime = flopstime + time->getTime();
            SwapBuffers();
            cleanUp();
        }
        double ave_time = flopstime / FRAMES_NUM;
        LOGI("FLOPS :\n One frame average time:%d---%f\n", i, ave_time);
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
