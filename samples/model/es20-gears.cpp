/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file aishe.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2020-01-11, create file
 * @par TestPoints:
 *      
 *
 */
#include "Sample.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Timer.h"
#include <vector>
#include <sys/time.h>

#define WINDOW_W_ 512
#define WINDOW_H_ 512

using namespace std;
using std::string;
using namespace BotsonSDK;

/* Shader variables. */
GLuint programID;
GLint iLocPos;
GLint iLocNorm;
GLint iLocMaterial;
GLint iLocModelView;
GLint iLocFrustum;

int windowWidth = -1;
int windowHeight = -1;
GLuint fragmentShaderID, vertexShaderID;

#ifndef M_PI
#define M_PI 3.14159265
#endif

/** Event handler results: */
#define NOP 0
#define EXIT 1
#define DRAW 2

static GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;
static GLfloat angle = 0.0;

static GLboolean fullscreen = GL_FALSE;	/* Create a single fullscreen window */
static GLboolean stereo = GL_FALSE;	/* Enable stereo.  */
static GLint samples = 0;               /* Choose visual with at least N samples. */
static GLboolean animate = GL_TRUE;	/* Animation */
static GLfloat eyesep = 5.0;		/* Eye separation. */
static GLfloat fix_point = 40.0;	/* Fixation point distance.  */
static GLfloat left, right, asp;	/* Stereo frustum params.  */
static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };
static GLfloat red[4] = { 0.8, 0.1, 0.0, 1.0 };
static GLfloat green[4] = { 0.0, 0.8, 0.2, 1.0 };
static GLfloat blue[4] = { 0.2, 0.2, 1.0, 1.0 };

typedef struct {
  float x,y,z;
} vec3f;

vector<vec3f> vertex;
vector<vec3f> normal;
vec3f normal_data;
vec3f vertex_data;
Matrix modelview, MVmat, Frustum;

#define DRAW_ARRAY(X)    \
   glEnableVertexAttribArray(iLocPos); \
   glEnableVertexAttribArray(iLocNorm); \
   glVertexAttribPointer(iLocPos, 3, GL_FLOAT, GL_FALSE, 0, vertex.data()); \
   glVertexAttribPointer(iLocNorm, 3, GL_FLOAT, GL_FALSE, 0, normal.data()); \
   glDrawArrays(X, 0, vertex.size());\
   vertex.clear(); \
   normal.clear(); \
   glDisableVertexAttribArray(iLocPos); \
   glDisableVertexAttribArray(iLocNorm);

static int current_time(void)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return (int)tv.tv_sec;
}

void push_Vertex3f(float x, float y, float z) { 
   vertex_data = {x,y,z};  
   vertex.push_back(vertex_data);                         
}

void push_Normal3f(float x, float y, float z) { 
   normal_data = {x,y,z};  
   normal.push_back(normal_data);                         
}

static void
gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
     GLint teeth, GLfloat tooth_depth)
{
   GLint i;
   GLfloat r0, r1, r2;
   GLfloat angle, da;
   GLfloat u, v, len;

   r0 = inner_radius;
   r1 = outer_radius - tooth_depth / 2.0;
   r2 = outer_radius + tooth_depth / 2.0;

   da = 2.0 * M_PI / teeth / 4.0;

   normal_data = {0.0, 0.0, 1.0};

// draw front face
   for (i = 0; i <= teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;
      push_Vertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      normal.push_back(normal_data);
      if (i < teeth) {
	 push_Vertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
         normal.push_back(normal_data);
	 push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		    width * 0.5);
         normal.push_back(normal_data);
      }
   }
   DRAW_ARRAY(GL_TRIANGLE_STRIP);


//draw front sides of teeth
   for (i = 0; i < teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;

      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
      normal.push_back(normal_data);

      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
      normal.push_back(normal_data);
   }
   DRAW_ARRAY(GL_TRIANGLES);

//draw back face
   normal_data = {0.0, 0.0, -1.0};
   for (i = 0; i <= teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;
      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
      normal.push_back(normal_data);
      if (i < teeth) {
	 push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
         normal.push_back(normal_data);
	 push_Vertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
        normal.push_back(normal_data);
      }
   }
   DRAW_ARRAY(GL_TRIANGLE_STRIP);

// draw back sides of teeth
   da = 2.0 * M_PI / teeth / 4.0;
   for (i = 0; i < teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;

      push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
      normal.push_back(normal_data);

      push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
      normal.push_back(normal_data);
      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
      normal.push_back(normal_data);
   }
   DRAW_ARRAY(GL_TRIANGLES);

// draw outward faces of teeth
   normal.push_back(normal_data);
   normal.push_back(normal_data);
   for (i = 0; i < teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;

      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      push_Vertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
      u = r2 * cos(angle + da) - r1 * cos(angle);
      v = r2 * sin(angle + da) - r1 * sin(angle);
      len = sqrt(u * u + v * v);
      u /= len;
      v /= len;
      push_Normal3f(v, -u, 0.0);
      push_Vertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
      push_Normal3f(v, -u, 0.0);
      push_Vertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
      push_Normal3f(cos(angle), sin(angle), 0.0);
      push_Vertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
      push_Normal3f(cos(angle), sin(angle), 0.0);
      push_Vertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
      u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
      v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
      push_Normal3f(v, -u, 0.0);
      push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
      push_Normal3f(v, -u, 0.0);
      push_Vertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
      push_Normal3f(cos(angle), sin(angle), 0.0);
      push_Normal3f(cos(angle), sin(angle), 0.0);
   }

   push_Vertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
   push_Vertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

   DRAW_ARRAY(GL_TRIANGLE_STRIP);

// draw inside radius cylinder
   for (i = 0; i <= teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;
      push_Normal3f(-cos(angle), -sin(angle), 0.0);
      push_Vertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
      push_Normal3f(-cos(angle), -sin(angle), 0.0);
      push_Vertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
   }
   DRAW_ARRAY(GL_TRIANGLE_STRIP);
}

bool setupGraphics(int width, int height)
{
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    string vertexShaderPath = ((string)GLSL_PATH) + "gears.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "gears.frag";

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    /* Attach shaders and link programID */
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    /* Get attribute locations of non-fixed attributes like colour and texture coordinates. */
    iLocPos = GL_CHECK(glGetAttribLocation(programID, "av3position"));
    iLocNorm = GL_CHECK(glGetAttribLocation(programID, "av3normal"));
    printf("iLocPos = %i\n", iLocPos);
    printf("iLocNorm   = %i\n", iLocNorm);

    /* Get uniform locations */
    iLocModelView = GL_CHECK(glGetUniformLocation(programID, "modelview"));
    iLocFrustum = GL_CHECK(glGetUniformLocation(programID, "frustum"));
    iLocMaterial = GL_CHECK(glGetUniformLocation(programID, "materal"));
    printf("iLocModelView      = %i\n", iLocModelView);
    printf("iLocFrustum      = %i\n", iLocFrustum);
    printf("iLocMaterial      = %i\n", iLocMaterial);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glViewport(0, 0, width, height));

    /* Set clear screen color. */
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    GLfloat h = (GLfloat) height / (GLfloat) width;
    Frustum = Matrix::matrixFrustumgraphic(-1.0, 1.0, -h, h, 5.0, 60.0);
    glUniformMatrix4fv(iLocFrustum, 1, GL_FALSE, Frustum.getAsArray());
    modelview = Matrix::createTranslation(0.0, 0.0, -40.0);

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    Matrix rotateX = Matrix::createRotationX(view_rotx);
    Matrix rotateY = Matrix::createRotationY(view_roty);
    Matrix rotateZ = Matrix::createRotationZ(view_rotz);
    Matrix rotateMat = modelview * rotateX * rotateY * rotateZ;

    Matrix translate = Matrix::createTranslation(-3.0, -2.0, 0.0);
    Matrix rotate = Matrix::createRotationZ(angle);
    MVmat = rotateMat * translate * rotate;
    GL_CHECK(glUniformMatrix4fv(iLocModelView, 1, GL_FALSE, MVmat.getAsArray()));
    glUniform4fv(iLocMaterial, 1, red);
    gear(1.0, 4.0, 1.0, 20, 0.7);

    translate = Matrix::createTranslation(3.1, -2.0, 0.0);
    rotate = Matrix::createRotationZ(-2.0 * angle - 9.0);
    MVmat = rotateMat * translate * rotate;
    glUniformMatrix4fv(iLocModelView, 1, GL_FALSE, MVmat.getAsArray());
    glUniform4fv(iLocMaterial, 1, green);
    gear(0.5, 2.0, 2.0, 10, 0.7);

    translate = Matrix::createTranslation(-3.1, 4.2, 0.0);
    rotate = Matrix::createRotationZ(-2.0 * angle - 25.0);
    MVmat = rotateMat * translate * rotate;
    glUniformMatrix4fv(iLocModelView, 1, GL_FALSE, MVmat.getAsArray());
    glUniform4fv(iLocMaterial, 1, blue);
    gear(1.3, 2.0, 0.5, 10, 0.7);
}

void Sample::test() {
    setupGraphics(300, 300);

    Timer fpsTimer;
    fpsTimer.reset();
    bool end = false;
    while(!end)
    {
        float fFPS = fpsTimer.getFPS();
        if(fpsTimer.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        static int t0 = -1;
        static int frame = 0;
        int t = current_time();
        if(t0 < 0) t0 = t;
        frame++;
        if(t - t0 >= 5.0) {
            float seconds = t -t0;
            float fps = frame / seconds;
            printf("%d frames in %3.1f seconds = %6.3f FPS\n", frame, seconds, fps);
            t0 = t;
            frame = 0;
        }

        angle += 2.0;
        renderFrame();
        eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, 300, 300);

    sample.test();

    return 0;
}

