
#include "Timer.h"
#include "Sample.h"
#include <GL/freeglut.h>

using std::string;
using namespace BotsonSDK;

const static int          FRAMES_NUM = 10;
const static unsigned int VERTEX_NUM = 30000;
float                     vertices[VERTEX_NUM * 4];
float                     coords[VERTEX_NUM * 2];
GLuint m_vao, m_vbo, m_ebo, m_fbo, tex, rb;
GLuint programID = 0;
double                    flopstime  = 0.0;
#define BUFFER_OFFSET(x)  ((const void*) (x))

void
initData() {
    for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
        vertices[i] = ((float)(rand() % 100)) / 50 - 1;
    }
    for (int j = 0; j < sizeof(coords) / sizeof(coords[0]); j++) {
        coords[j] = ((float)(rand() % 10)) / 8;
    }
}

bool setupGraphics(int w, int h, int sampleNum) {
    glutSetOption(GLUT_MULTISAMPLE, sampleNum);
    string vertexShaderPath = ((string)GLSL_PATH) + "texstorage2dms.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "texstorage2dms.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));
    initData();
    GL_CHECK(glGenVertexArrays(1, &m_vao));
    GL_CHECK(glBindVertexArray(m_vao));

    GL_CHECK(glGenBuffers(1, &m_vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+ sizeof(coords), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(coords), coords));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glGenFramebuffers(1, &m_fbo));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex));
    GL_CHECK(glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sampleNum, GL_RGB8, w, h, GL_TRUE));

    GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                    GL_TEXTURE_2D_MULTISAMPLE, tex, 0));

    GL_CHECK(glGenRenderbuffers(1, &rb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, rb));
    GL_CHECK(glRenderbufferStorageMultisample(GL_RENDERBUFFER, sampleNum,
                                              GL_DEPTH_COMPONENT24, w, h));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb));

    GLenum status=glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        LOGE("FRAMEBUFFER NOT COMPLETE");
    }

    GLint diffuseLoc = GL_CHECK(glGetUniformLocation(programID, "diffuse"));
    LOGI("diffuse location = %d\n", diffuseLoc);
    GL_CHECK(glUniform1i(diffuseLoc, 1));

    GLint nMsLoc = GL_CHECK(glGetUniformLocation(programID, "nMultiSample"));
    LOGI("nMultiSample location = %d\n", nMsLoc);
    GL_CHECK(glUniform1i(nMsLoc, sampleNum));

    GLenum drawbuffers[] = {GL_COLOR_ATTACHMENT0};
    GL_CHECK(glDrawBuffers(1, drawbuffers));
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    GL_CHECK(glClearDepthf(1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glReadBuffer( GL_COLOR_ATTACHMENT0));

    return true;
}

void renderFrame(int w, int h) {
    GL_CHECK(glBindVertexArray(m_vao));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, rb));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo));
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
    GL_CHECK(glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST));
    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
}

void clean_test(){
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));

    GL_CHECK(glDeleteBuffers(1, &m_vbo));
    GL_CHECK(glDeleteBuffers(1, &m_ebo));
    GL_CHECK(glDeleteProgram(programID));
    GL_CHECK(glDeleteFramebuffers(1, &m_fbo));
    GL_CHECK(glDeleteRenderbuffers(1, &rb));
    GL_CHECK(glDeleteTextures(1, &tex));
    GL_CHECK(glDeleteVertexArrays(1, &m_vao));
}
void Sample::test() {
    Timer *time = new Timer();
    for(int j=0; j<FRAMES_NUM; j++) {
        time->reset();
        glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        GL_CHECK(glEnable(GL_MULTISAMPLE));
        setupGraphics(WINDOW_W, WINDOW_H, 4);
        renderFrame(WINDOW_W, WINDOW_H);
        glFlush();
        char ss[5];
        sprintf(ss, "%d", j);
        string bmp_file = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        flopstime = flopstime + time->getTime();
        SwapBuffers();
        clean_test();
    }
    double ave_time = flopstime / FRAMES_NUM;
    LOGI("FLOPS :\n One frame average time:--%f\n", ave_time);
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_ALPHA | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
