#include "Sample.h"
#include "Timer.h"
#include <string>

    const static int FRAMES_NUM = 10;
    const static unsigned int  VERTEX_NUM = 30000;
    float vertices[VERTEX_NUM*2];
    float colors[VERTEX_NUM*3];
    GLuint vao, vbo, programID[2];

    #define BUFFER_OFFSET(x)  ((const void*) (x))

const GLchar* vertexShaderSource =
                    "#version 430 core\n"
                    "layout(location=0) in vec2 position;\n"
                    "layout(location=1) in vec3 vcolor;\n"
                    "smooth out vec4 color;\n\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = vec4(position, 0.0, 1.0);\n"
                    "    color = vec4(vcolor, 1.0);\n"
                    "}\n\0";

const GLchar* fragmentShaderSource =
                    "#version 430 core\n"
                    "smooth in vec4 color;\n"
                    "out vec4 fcolor;\n\n"
                    "void main()\n"
                    "{\n"
                    "    fcolor = color;\n"
                    "}\n\0";

const GLchar* vertexShaderSource1 =
                    "#version 430 core\n"
                    "layout(location=0) in vec2 position;\n"
                    "layout(location=1) in vec3 vcolor;\n"
                    "flat out vec4 color;\n\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = vec4(position, 0.0, 1.0);\n"
                    "    color = vec4(vcolor, 1.0);\n"
                    "}\n\0";

const GLchar* fragmentShaderSource1 =
                    "#version 430 core\n"
                    "flat in vec4 color;\n"
                    "out vec4 fcolor;\n\n"
                    "void main()\n"
                    "{\n"
                    "    fcolor = color;\n"
                    "}\n\0";

    bool initProgram()
    {


        programID[0] = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
        
        programID[1] = Shader::createProgramFromString(vertexShaderSource1, fragmentShaderSource1);
        
        return true;
    }
    
    void initData() {
        for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
            vertices[i] = ((float)(rand() % 100)) / 50 - 1;
        }
        for (int j = 0; j < sizeof(colors) / sizeof(colors[0]); j++) {
            colors[j] = ((float)(rand() % 50)) / 50;
        }
        GL_CHECK(glGenVertexArrays(1, &vao));
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glGenBuffers(1, &vbo));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
        GL_CHECK(glEnableVertexAttribArray(0));
        GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(1));
        GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    }

    
    void renderFrame(int i, int j)
    {
        glUseProgram(programID[i]);
        glBindVertexArray(vao);
        switch(j){
        case 0:
            glPointSize(1.0);
            glDrawArrays(GL_POINTS, 0, VERTEX_NUM);
            break;
        case 1:
            glPointSize(5.0);
            glDrawArrays(GL_POINTS, 0, VERTEX_NUM);
            break;
        case 2:
            glLineWidth(1.0);
            glDrawArrays(GL_LINES, 0, VERTEX_NUM);
            break;
        case 3:
            glLineWidth(1.0);
            glDrawArrays(GL_LINE_LOOP, 0, VERTEX_NUM);
            break;
        case 4:
            glLineWidth(1.0);
            glDrawArrays(GL_LINE_STRIP, 0, VERTEX_NUM);
            break;
        case 5:
            glLineWidth(5.0);
            glDrawArrays(GL_LINES, 0, VERTEX_NUM);
            break;
        case 6:
            glLineWidth(5.0);
            glDrawArrays(GL_LINE_LOOP, 0, VERTEX_NUM);
            break;
        case 7:
            glLineWidth(5.0);
            glDrawArrays(GL_LINE_STRIP, 0, VERTEX_NUM);
            break;
        case 8:
            glDrawArrays(GL_TRIANGLES, 0, VERTEX_NUM);
            break;
        case 9:
            glDrawArrays(GL_TRIANGLE_STRIP, 0, VERTEX_NUM);
            break;
        case 10:
            glDrawArrays(GL_TRIANGLE_FAN, 0, VERTEX_NUM);
            break;
        default:
            break;
        }
    }
    
    void cleanUp()
    {
        glDeleteProgram(programID[0]);
        glDeleteProgram(programID[1]);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

void Sample::test() {
    Timer *time = new Timer();
    for(int i=0; i<2; i++) {
        for (int j = 0; j < 11; j++) {
            double flopstime=0.0;
            for(int k=0; k<FRAMES_NUM+1; k++){
                time->reset();
                initProgram();
                initData();
                renderFrame(i, j);
                glFlush();
                if(k>0) {
                    flopstime = flopstime + time->getTime();
                }
                char ss[8];
                sprintf(ss, "%d-%d-%d", i, j);
                string bmp_file = filename + "-" + ss + ".bmp";
                save2bmp(bmp_file.c_str());
                SwapBuffers();
                cleanUp();
            }
            double ave_time = flopstime / FRAMES_NUM;
            LOGI("primi_speed One frame average time:%d-%d--%f\n", i, j, ave_time);
        }
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
