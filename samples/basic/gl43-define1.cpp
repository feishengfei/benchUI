
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#include "Timer.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
Timer this_one;

GLfloat vertices[] = {
       -0.8, -0.8, 0.0, 1.0,
        0.0,  0.8, 0.0, 1.0,
        0.8, -0.8, 0.0, 1.0
};

GLfloat color[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0
};

GLuint programID, VAOs, Buffers;

bool setupGraphics(int w, int h) {
    ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER,  "define1.vert" },
            { GL_FRAGMENT_SHADER, "define.frag" },
            { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders(shaders);

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
    static float last_time = 0.0;
    static float total_time = 0.0;
    float life_time = this_one.getTime();
    total_time += (life_time - last_time);
    last_time = life_time;
    float t = total_time;

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glUniform1f(0, t));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    this_one.reset();
   // bool end = false;
   // while(!end)
    for(int i=0; i<20; i++)
    {
        float fFPS = this_one.getFPS();
        if(this_one.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        render();
        Sample::SwapBuffers();
    }
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}