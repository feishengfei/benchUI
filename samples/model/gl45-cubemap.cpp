#include "Sample.h"
#include "Texture.h"
#include "Timer.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))
const static int          FRAMES_NUM = 10;
double flopstime=0.0;
string cubemap[]={
        "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
};

string texpath[6];

GLfloat vertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

GLuint programID, VAOs, Buffers, texture1;

bool setupGraphics(int w, int h) {
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "cubemap.vert"},
            {GL_FRAGMENT_SHADER, "cubemap.frag"},
            {GL_NONE, NULL}
    };

    programID = Shader::LoadShaders(shaders);

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glClearColor(0.2, 0.2, 0.6, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render() {
    GL_CHECK(glUseProgram(programID));
    static float angleX      = 0, angleY = 0, angleZ = 0;
    Matrix       translate   = Matrix::createTranslation(0.0, 0.0, 0.0);
    Matrix       rotationX   = Matrix::createRotationX(angleX);
    Matrix       rotationY   = Matrix::createRotationY(angleY);
    Matrix       perspective = Matrix::matrixPerspective(45.0f,
                                                         WINDOW_W / (float)WINDOW_H, 0.01f, 100.0f);
    Matrix       modelView   = perspective * translate * rotationY * rotationX;

    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, modelView.getAsArray()));

    angleX += 0.0;
    angleY += 10;
    angleZ += 0.0;

    if (angleX >= 360)
        angleX -= 360;
    if (angleX < 0)
        angleX += 360;
    if (angleY >= 360)
        angleY -= 360;
    if (angleY < 0)
        angleY += 360;
    if (angleZ >= 360)
        angleZ -= 360;
    if (angleZ < 0)
        angleZ += 360;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenTextures(1, &texture1));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture1));
    TexData  image_jpg;
    for (int i = 0; i < 6; i++) {
        texpath[i] = ((string)PICTURE_PATH) + cubemap[i];
        image_jpg.file_name = (char *)texpath[i].c_str();
        read_jpeg(&image_jpg);
        GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, image_jpg.width, image_jpg.height,
                              0, GL_RGB, GL_UNSIGNED_BYTE, image_jpg.data));
    }
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
    GL_CHECK(glDeleteTextures(1, &texture1));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
}

void Sample::test() {
    int fcnt = 0;
    Timer    *time    = new Timer();
    while (fcnt < FRAMES_NUM) {
        time->reset();
        setupGraphics(WINDOW_W, WINDOW_H);
        for (int i = 0; i < 36; i++) {
            render();
            glFlush();
            flopstime = flopstime + time->getTime();
            Sample::SwapBuffers();
        }
        fcnt++;
    }
    double ave_time = flopstime / FRAMES_NUM;
    printf("FLOPS :\n One frame average time:%f\n", ave_time);
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
