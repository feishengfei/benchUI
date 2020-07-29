/**
 * @file uniformf.cpp
 * @testpoint glUniform1/2/3/4fv
 *
 */

#include "Sample.h"
#include "Matrix.h"
#define FBO_WIDTH    256
#define FBO_HEIGHT    256
using namespace BotsonSDK;

Matrix projection;
Matrix projectionFBO;
Matrix translation;
Matrix rotationX;
Matrix rotationY;
Matrix rotationZ;
//Matrix translation;
Matrix modelView;

static float angleX = 0;
static float angleY = 0;
static float angleZ = 0;

/* Shader variables. */
GLint iLocPosition = -1;
GLint iLocTextureMix = -1;
GLint iLocTexture = -1;
GLint iLocFillColor = -1;
GLint iLocTexCoord = -1;
GLint iLocProjection = -1;
GLint iLocModelview = -1;

/* Application textures. */
GLuint iFBOTex = 0;
GLuint iFBO = 0;

unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;
GLuint vertexShaderID = -1;
GLuint fragmentShaderID = -1;
GLuint programID = -1;
int windowWidth = -1;
int windowHeight = -1;
static const float cubeTextureCoordinates[] =
{
    /* Front. */
    0.0f, 0.0f, /* 0 */
    1.0f, 0.0f, /* 1 */
    0.0f, 1.0f, /* 2 */
    1.0f, 1.0f, /* 3 */

    /* Right. */
    0.0f, 0.0f, /* 4 */
    1.0f, 0.0f, /* 5 */
    0.0f, 1.0f, /* 6 */
    1.0f, 1.0f, /* 7 */

    /* Back. */
    0.0f, 0.0f, /* 8 */
    1.0f, 0.0f, /* 9 */
    0.0f, 1.0f, /* 10 */
    1.0f, 1.0f, /* 11 */

    /* Left. */
    0.0f, 0.0f, /* 12 */
    1.0f, 0.0f, /* 13 */
    0.0f, 1.0f, /* 14 */
    1.0f, 1.0f, /* 15 */

    /* Top. */
    0.0f, 0.0f, /* 16 */
    1.0f, 0.0f, /* 17 */
    0.0f, 1.0f, /* 18 */
    1.0f, 1.0f, /* 19 */

    /* Bottom. */
    0.0f, 0.0f, /* 20 */
    1.0f, 0.0f, /* 21 */
    0.0f, 1.0f, /* 22 */
    1.0f, 1.0f, /* 23 */

};


static const float cubeColors[] =
{
    /* Front. */
    0.0f, 0.0f, 0.0f, 1.0f, /* 0 */
    1.0f, 0.0f, 0.0f, 1.0f, /* 1 */
    0.0f, 1.0f, 0.0f, 1.0f, /* 2 */
    1.0f, 1.0f, 0.0f, 1.0f, /* 3 */

    /* Right. */
    1.0f, 0.0f, 0.0f, 1.0f, /* 4 */
    0.0f, 0.0f, 1.0f, 1.0f, /* 5 */
    1.0f, 1.0f, 0.0f, 1.0f, /* 6 */
    0.0f, 1.0f, 1.0f, 1.0f, /* 7 */

    /* Back. */
    0.0f, 0.0f, 1.0f, 1.0f, /* 8 */
    1.0f, 0.0f, 1.0f, 1.0f, /* 9 */
    0.0f, 1.0f, 1.0f, 1.0f, /* 10 */
    1.0f, 1.0f, 1.0f, 1.0f, /* 11 */

    /* Left. */
    1.0f, 0.0f, 1.0f, 1.0f, /* 12 */
    0.0f, 0.0f, 0.0f, 1.0f, /* 13 */
    1.0f, 1.0f, 1.0f, 1.0f, /* 14 */
    0.0f, 1.0f, 0.0f, 1.0f, /* 15 */

    /* Top. */
    0.0f, 1.0f, 0.0f, 1.0f, /* 16 */
    1.0f, 1.0f, 0.0f, 1.0f, /* 17 */
    1.0f, 1.0f, 1.0f, 1.0f, /* 18 */
    0.0f, 1.0f, 1.0f, 1.0f, /* 19 */

    /* Bottom. */
    1.0f, 0.0f, 1.0f, 1.0f, /* 20 */
    0.0f, 0.0f, 1.0f, 1.0f, /* 21 */
    0.0f, 0.0f, 0.0f, 1.0f, /* 22 */
    1.0f, 0.0f, 0.0f, 1.0f, /* 23 */
};

static const float cubeVertices[] =
{
    /* Front. */
    -0.5f, -0.5f,  0.5f, /* 0 */
     0.5f, -0.5f,  0.5f, /* 1 */
    -0.5f,  0.5f,  0.5f, /* 2 */
     0.5f,  0.5f,  0.5f, /* 3 */

    /* Right. */
     0.5f, -0.5f,  0.5f, /* 4 */
     0.5f, -0.5f, -0.5f, /* 5 */
     0.5f,  0.5f,  0.5f, /* 6 */
     0.5f,  0.5f, -0.5f, /* 7 */

    /* Back. */
     0.5f, -0.5f, -0.5f, /* 8 */
    -0.5f, -0.5f, -0.5f, /* 9 */
     0.5f,  0.5f, -0.5f, /* 10 */
    -0.5f,  0.5f, -0.5f, /* 11 */

    /* Left. */
    -0.5f, -0.5f, -0.5f, /* 12 */
    -0.5f, -0.5f,  0.5f, /* 13 */
    -0.5f,  0.5f, -0.5f, /* 14 */
    -0.5f,  0.5f,  0.5f, /* 15 */

    /* Top. */
    -0.5f,  0.5f,  0.5f, /* 16 */
     0.5f,  0.5f,  0.5f, /* 17 */
    -0.5f,  0.5f, -0.5f, /* 18 */
     0.5f,  0.5f, -0.5f, /* 19 */

    /* Bottom. */
    -0.5f, -0.5f, -0.5f, /* 20 */
     0.5f, -0.5f, -0.5f, /* 21 */
    -0.5f, -0.5f,  0.5f, /* 22 */
     0.5f, -0.5f,  0.5f, /* 23 */
};

GLfloat colors[] = { 
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
}; 
const float triangleColors2[] =
{
    1.0, 0.0,
    0.0, 1.0,
    0.0, 1.0
};
static const GLubyte cubeIndices[] =
{
    0, 1, 2, 3,   3, 4,   4, 5, 6, 7,   7, 8,   8, 9, 10, 11,   11, 12,   12, 13, 14, 15,   15, 16,   16, 17, 18, 19,   19, 20,   20, 21, 22, 23,
};
static const GLenum factors[] = {
    GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,
    GL_VERTEX_ATTRIB_ARRAY_ENABLED,
    GL_VERTEX_ATTRIB_ARRAY_SIZE,
    GL_VERTEX_ATTRIB_ARRAY_STRIDE,
    GL_VERTEX_ATTRIB_ARRAY_TYPE,
    GL_VERTEX_ATTRIB_ARRAY_INTEGER,
    GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
    GL_CURRENT_VERTEX_ATTRIB
};

GLuint vertexShader, vertexShaderi;
GLuint fragmentShader;
//GLuint programID;
GLint posLocation, colorLocation;
GLint vertexattribP = 0;

bool setupGraphics(int w, int h)
{
	//loadShader();
         /*load shader*/
    string vertexShaderPath = (string)GLSL_PATH + "FramebufferTexture.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "FramebufferTexture.frag";
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));

	glUseProgram(programID); 
	glViewport(0, 0, w, h);
	/* Initialize matrices. */
	projection = Matrix::matrixPerspective(45.0f, windowWidth/(float)windowHeight, 0.01f, 100.0f);
        projectionFBO = Matrix::matrixPerspective(45.0f, (FBO_WIDTH / (float)FBO_HEIGHT), 0.01f, 100.0f);
        /* Move cube 2 further away from camera. */
        translation = Matrix::createTranslation(0.0f, 0.0f, -2.0f);
        /* Initialize OpenGL. */
        GL_CHECK(glEnable(GL_CULL_FACE));
        GL_CHECK(glCullFace(GL_BACK));
        GL_CHECK(glEnable(GL_DEPTH_TEST));
        GL_CHECK(glEnable(GL_BLEND));
        
	/* Should do src * (src alpha) + dest * (1-src alpha). */
        GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	/* Initialize FBO texture. */
	GL_CHECK(glGenTextures(1, &iFBOTex));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, iFBOTex));
	/* Set filtering. */
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FBO_WIDTH, FBO_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
	/* Initialize FBOs. */
	GL_CHECK(glGenFramebuffers(1, &iFBO));

	/* Render to framebuffer object. */
	/* Bind our framebuffer for rendering. */
	GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, iFBO));

	/* Attach texture to the framebuffer. */
	GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, iFBOTex, 0));

	/* Check FBO is OK. */
	GLenum iResult = GL_CHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER));
	if(iResult != GL_FRAMEBUFFER_COMPLETE)
	{
	    LOGI("Framebuffer incomplete at %s:%i\n", __FILE__, __LINE__);
	    return false;
	}
	/* Unbind framebuffer. */
        GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	/* Set up shaders. */
	//loadShader();
	glUseProgram(programID); 	

	/* Vertex positions. */
	iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
	if(iLocPosition == -1)
	{
	LOGI("Attribute not found at %s:%i\n", __FILE__, __LINE__);
	return false;
	}
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));

	/* Texture mix. */
	iLocTextureMix = GL_CHECK(glGetUniformLocation(programID, "u_fTex"));
	if(iLocTextureMix == -1)
	{
	LOGI("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
	}
	else 
	{
	GL_CHECK(glUniform1f(iLocTextureMix, 0.0));
	}

	/* Texture. */
	iLocTexture = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
	if(iLocTexture == -1)
	{
	LOGI("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
	}
	else 
	{
	GL_CHECK(glUniform1i(iLocTexture, 0));
	}

	/* Vertex colors. */
	iLocFillColor = GL_CHECK(glGetAttribLocation(programID, "a_v4FillColor"));
	if(iLocFillColor == -1)
	{
	LOGI("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
	}
	else 
	{
	GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
	}

	/* Texture coords. */
	iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
	if(iLocTexCoord == -1)
	{
	LOGI("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
	}
	else 
	{
	GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
	}

	/* Projection matrix. */
	iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
	if(iLocProjection == -1)
	{
	LOGI("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
	}
	else 
	{
	GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, projection.getAsArray()));
	}

	/* Modelview matrix. */
	iLocModelview = GL_CHECK(glGetUniformLocation(programID, "u_m4Modelview"));
	if(iLocModelview == -1)
	{
	LOGI("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
	}
	/* We pass this for each object, below. */

	return true;
} 


void renderFrame(void)
{
    /* Both main window surface and FBO use the same shader program. */
    GL_CHECK(glUseProgram(programID));

    /* Both drawing surfaces also share vertex data. */
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices));

    /* Including color data. */
    if(iLocFillColor != -1)
    {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, cubeColors));
    }

    /* And texture coordinate data. */
    if(iLocTexCoord != -1)
    {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, cubeTextureCoordinates));
    }

    /* Bind the FrameBuffer Object. */
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, iFBO));

    /* Set the viewport according to the FBO's texture. */
    GL_CHECK(glViewport(0, 0, FBO_WIDTH, FBO_HEIGHT));

    /* Clear screen on FBO. */
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    /* Create rotation matrix specific to the FBO's cube. */
    rotationX = Matrix::createRotationX(-angleZ);
    rotationY = Matrix::createRotationY(-angleY);
    rotationZ = Matrix::createRotationZ(-angleX);

    /* Rotate about origin, then translate away from camera. */
    modelView = translation * rotationX;
    modelView = modelView * rotationY;
    modelView = modelView * rotationZ;

    /* Load FBO-specific projection and modelview matrices. */
    GL_CHECK(glUniformMatrix4fv(iLocModelview, 1, GL_FALSE, modelView.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, projectionFBO.getAsArray()));

    /* The FBO cube doesn't get textured so zero the texture mix factor. */
    if(iLocTextureMix != -1)
    {
        GL_CHECK(glUniform1f(iLocTextureMix, 0.0));
    }

    /* Now draw the colored cube to the FrameBuffer Object. */
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(cubeIndices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, cubeIndices));

    /* And unbind the FrameBuffer Object so subsequent drawing calls are to the EGL window surface. */
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER,0));

    /* Reset viewport to the EGL window surface's dimensions. */
    GL_CHECK(glViewport(0, 0, windowWidth, windowHeight));

    /* Clear the screen on the EGL surface. */
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    /* Construct different rotation for main cube. */
    rotationX = Matrix::createRotationX(angleX);
    rotationY = Matrix::createRotationY(angleY);
    rotationZ = Matrix::createRotationZ(angleZ);

    /* Rotate about origin, then translate away from camera. */
    modelView = translation * rotationX;
    modelView = modelView * rotationY;
    modelView = modelView * rotationZ;

    /* Load EGL window-specific projection and modelview matrices. */
    GL_CHECK(glUniformMatrix4fv(iLocModelview, 1, GL_FALSE, modelView.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, projection.getAsArray()));

    /* For the main cube, we use texturing so set the texture mix factor to 1. */
    if(iLocTextureMix != -1)
    {
        GL_CHECK(glUniform1f(iLocTextureMix, 1.0));
    }

    /* Ensure the correct texture is bound to texture unit 0. */
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, iFBOTex));

    /* And draw the cube. */
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(cubeIndices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, cubeIndices));


    /* Update cube's rotation angles for animating. */
    angleX += 3;
    angleY += 20;
    angleZ += 1;

    if(angleX >= 360) angleX -= 360;
    //if(angleY >= 360) angleY -= 360;
    if(angleZ >= 360) angleZ -= 360;
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