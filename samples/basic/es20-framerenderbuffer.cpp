/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file framerenderbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for framerenderbuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"

using std::string;
using namespace BotsonSDK;

#define FBO_WIDTH    256
#define FBO_HEIGHT    256

static const GLubyte cubeIndices[] = {
    0, 1, 2, 3//,   3, 4,   4, 5, 6, 7,   7, 8,   8, 9, 10, 11,   11, 12,   12, 13, 14, 15,   15, 16,   16, 17, 18, 19,   19, 20,   20, 21, 22, 23,
};

static const float cubeVertices[] = {
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,

     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
};

static const float cubeTextureCoordinates[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};

static const float cubeColors[] = {
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
};

GLuint programTextureID=0, programSplashID = 0;
GLint iLocPosition = -1;
GLint iLocDiffuseTexture = -1;
GLint iLocDiffuseSplash = -1;
GLint iLocTexCoord = -1;

GLuint iFBO = 0;
GLuint iRBO = 0;
GLuint iFBOTex = 0;

int window_Width = -1;
int window_Height = -1;

GLsizei ElementCount = 6;
GLsizeiptr ElementSize = ElementCount * sizeof(GLushort);
GLushort ElementData[ElementCount] = {
	0, 1, 2, 
	2, 3, 0
};

struct vec2 {
	float x,y;
};

struct vertex_v2fv2f {
	vec2 Position;
	vec2 Texcoord;
};

GLsizei VertexCount=4;
GLsizeiptr VertexSize = VertexCount * sizeof(vertex_v2fv2f);
vertex_v2fv2f VertexData[VertexCount] = {
	{-1.0f,-1.0f}, {0.0f, 1.0f},
	{ 1.0f,-1.0f}, {1.0f, 1.0f},
	{ 1.0f, 1.0f}, {1.0f, 0.0f},
	{-1.0f, 1.0f}, {0.0f, 0.0f}
};

namespace buffer {
	enum type {
		VERTEX,
		ELEMENT,
		TRANSFORM,
		MAX
	};
}

GLuint BufferName[buffer::MAX];

void InitFBO(void) {
	glGenBuffers(buffer::MAX, &BufferName[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UniformBufferOffset);
	GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4)), UniformBufferOffset);

	glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
	glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return true;
}

bool initTexture() {
	bool Validated=true;

	gli::texture2d Texture(gli::load_dds((getDataDirectory() + TEXTURE_DIFFUSE).c_str()));
	assert(!Texture.empty());

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(texture::MAX, &TextureName[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::DIFFUSE]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(Texture.levels() - 1));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	for(std::size_t Level = 0; Level < Texture.levels(); ++Level) {
		glCompressedTexImage2D(GL_TEXTURE_2D, GLint(Level),
                GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
				GLsizei(Texture[Level].extent().x),
				GLsizei(Texture[Level].extent().y),
				0,
				GLsizei(Texture[Level].size()),
				Texture[Level].data());
	}
	
	glm::ivec2 WindowSize(this->getWindowSize() * this->FramebufferScale);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::COLORBUFFER]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, GLint(0), GL_RGBA8, GLsizei(WindowSize.x), GLsizei(WindowSize.y), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::DEPTHBUFFER]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexImage2D(GL_TEXTURE_2D, GLint(0), GL_DEPTH_COMPONENT24, GLsizei(WindowSize.x), GLsizei(WindowSize.y), 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureName[texture::STENCILBUFFER]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexImage2D(GL_TEXTURE_2D, GLint(0), GL_STENCIL_INDEX8, GLsizei(WindowSize.x), GLsizei(WindowSize.y), 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, nullptr);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return Validated;
}

void LoadShader(void) {
    string vertexTexture = "fbo-depth-stencil-render.vert";
    string fragmentTexture = "fbo-depth-stencil-render.frag";
    string vertexSplash = "fbo-depth-stencil-blit.vert";
    string fragmentSplash = "fbo-depth-stencil-blit.frag";
    string TextureDiffuse = "kueken7_rgb_dxt1_unorm.dds";

    GLuint vertexShaderID = 0, fragmentShaderID = 0;

    string vertexShaderPath = ((string)GLSL_PATH) + vertexTexture; 
    string fragmentShaderPath = ((string)GLSL_PATH) + fragmentTexture;
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(),
                          GL_FRAGMENT_SHADER);
    programTextureID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programTextureID, vertexShaderID));
    GL_CHECK(glAttachShader(programTextureID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programTextureID));

    vertexShaderPath = ((string)GLSL_PATH) + vertexSplash; 
    fragmentShaderPath = ((string)GLSL_PATH) + fragmentSplash;
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(),
                          GL_FRAGMENT_SHADER);
    programSplashID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programSplashID, vertexShaderID));
    GL_CHECK(glAttachShader(programSplashID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programSplashID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programTextureID, "Position"));
    if(iLocPosition == -1) {
        LOGE("Attribute not found at %s:%i\n", __FILE__, __LINE__);
        return;
    }

    iLocTexCoord = GL_CHECK(glGetAttribLocation(programTextureID, "Texcoord"));
    if(iLocTexCoord == -1) {
        LOGW("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
    }

    glUseProgram(programTextureID);
    iLocDiffuseTexture = GL_CHECK(glGetUniformLocation(programTextureID, "Diffuse"));
    if(iLocDiffuseTexture == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniform1i(iLocDiffuseTexture, 0));
    }

    glUseProgram(programSplashID);
    iLocDiffuseSplash = GL_CHECK(glGetUniformLocation(programSplashID, "Diffuse"));
    if(iLocDiffuseSplash == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniform1i(iLocDiffuseSplash, 0));
    }
    GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
}

bool setupGraphics(int width, int height) {
    window_Width = width;
    window_Height = height;

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    InitFBO();
    LoadShader();

    return true;
}

void renderFrame(void) {
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices));

    if(iLocFillColor != -1) {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, cubeColors));
    }

    if(iLocTexCoord != -1) {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, cubeTextureCoordinates));
    }

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, iFBO));
    GL_CHECK(glViewport(0, 0, FBO_WIDTH, FBO_HEIGHT));
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    if(iLocTextureMix != -1) {
        GL_CHECK(glUniform1f(iLocTextureMix, 0.0));
    }

    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(cubeIndices) / sizeof(GLubyte),
                            GL_UNSIGNED_BYTE, cubeIndices));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER,0));

    GL_CHECK(glViewport(0, 0, window_Width, window_Height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    if(iLocTextureMix != -1) {
        GL_CHECK(glUniform1f(iLocTextureMix, 1.0));
    }

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, iFBOTex));
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(cubeIndices) / sizeof(GLubyte),
                            GL_UNSIGNED_BYTE, cubeIndices));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

