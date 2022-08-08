#include "Sample.h"
#include "Timer.h"
#include "VectorTypes.h"
#include <GL/glcorearb.h>
#include <string.h>

using std::string;
using namespace BotsonSDK;

#define BUFFER_OFFSET(x)  ((const void*) (x))

static const GLfloat patch_init[] = {
         -1.0f, -1.0f, 0.0f,
        -0.33f, -1.0f, 0.0f,
         0.33f, -1.0f, 0.0f,
          1.0f, -1.0f, 0.0f,

         -1.0f,-0.33f, 0.0f,
        -0.33f,-0.33f, 0.0f,
         0.33f,-0.33f, 0.0f,
          1.0f,-0.33f, 0.0f,

         -1.0f, 0.33f, 0.0f,
        -0.33f, 0.33f, 0.0f,
         0.33f, 0.33f, 0.0f,
          1.0f, 0.33f, 0.0f,

         -1.0f,  1.0f, 0.0f,
        -0.33f,  1.0f, 0.0f,
         0.33f,  1.0f, 0.0f,
          1.0f,  1.0f, 0.0f
};

static const GLushort indices[] = {
        0, 1, 1, 2, 2, 3,
        4, 5, 5, 6, 6, 7,
        8, 9, 9,10,10,11,
       12,13,13,14,14,15,

        0, 4, 4, 8, 8,12,
        1, 5, 5, 9, 9,13,
        2, 6, 6,10,10,14,
        3, 7, 7,11,11,15
};

GLuint tess_programID;
GLuint draw_programID;
GLuint vao;
GLuint vbo;
GLuint ebo;

Timer this_one;

bool setupGraphics(int width, int height) {

    ShaderInfo  tess_shaders[] = {
            {GL_VERTEX_SHADER, "cubezier.vert", },
            {GL_TESS_CONTROL_SHADER, "cubezier.tcs", },
            {GL_TESS_EVALUATION_SHADER, "cubezier.tes", },
            {GL_FRAGMENT_SHADER, "cubezier.frag", },
            {GL_NONE,NULL},
    };
    tess_programID = Shader::LoadShaders(tess_shaders);

    ShaderInfo  draw_shaders[] = {
            {GL_VERTEX_SHADER, "cubezier_draw.vert", },
            {GL_FRAGMENT_SHADER, "cubezier_draw.frag", },
            {GL_NONE,NULL},
    };
    draw_programID = Shader::LoadShaders(draw_shaders);

    GL_CHECK(glClearColor(0.1, 0.1, 0.1, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));

    return true;
}

void renderFrame(void) {
    static float last_time = 0.0;
    static float total_time = 0.0;
    float life_time = this_one.getTime();
    total_time += (life_time - last_time);
    last_time = life_time;
    float t = total_time;

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(patch_init), NULL, GL_STATIC_DRAW));
    Vec3f *p = (Vec3f *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(patch_init),
            GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(p, patch_init, sizeof(patch_init));
    for(int i = 0; i < 16; i++){
        float fi = (float)i / 16.0f;
        p[i].z = sinf(t * (0.2f + fi * 0.3f));
    }
    GL_CHECK(glUnmapBuffer(GL_ARRAY_BUFFER));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 16));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W / (float)WINDOW_H, 1.0f, 100.0f);
    Matrix translate = Matrix::createTranslation(0.0f, 0.0f, -4.0f);
    Matrix rotateX = Matrix::createRotationX(t * 17.0f);
    Matrix rotateY = Matrix::createRotationY(t * 10.0f);
    Matrix rotate = rotateY * rotateX;
    Matrix mv_matrix = translate * rotate;
    Matrix mvp_matrix = perspective * mv_matrix;

    
    GL_CHECK(glUseProgram(tess_programID));
    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, mv_matrix.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(1, 1, GL_FALSE, perspective.getAsArray()));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, 16));

    GL_CHECK(glUseProgram(draw_programID));
    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, mvp_matrix.getAsArray()));
    GL_CHECK(glUniform4f(1, 0.2, 0.7, 0.9, 1.0));
    GL_CHECK(glPointSize(9.0));
    GL_CHECK(glDrawElements(GL_LINES, 48, GL_UNSIGNED_SHORT, NULL));

}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    this_one.reset();
    //bool end = false;
    //while(!end)
    for (int i = 0; i < 20; i++) {
        float fFPS = this_one.getFPS();
        if (this_one.isTimePassed(1.0f)) {
            printf("FPS:\t%.1f\n", fFPS);
        }
        renderFrame();
        char ss[3];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();
    return 0;
}
