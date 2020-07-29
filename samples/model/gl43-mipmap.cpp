
#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

GLuint programID;

float vertices1[] =
			  {
					  -1.0f, -0.7f, 0.0f,        1.0f, 0.0f, 0.0f,        1.0f, 1.0f,
					  -1.0f, 0.7f, 0.0f,       0.0f, 1.0f, 0.0f,        1.0f, 0.0f,
					  0.4f,  0.7f, 0.0f,      0.0f, 0.0f, 1.0f,        0.0f, 0.0f,
					  0.4f, -0.7f, 0.0f,       1.0f, 1.0f, 0.0f,        0.0f, 1.0f
			  };

float vertices2[] =
			  {
					  0.5f, -0.25f, 0.0f,        1.0f, 0.0f, 0.0f,        1.0f, 1.0f,
					  0.5f, 0.25f, 0.0f,       0.0f, 1.0f, 0.0f,        1.0f, 0.0f,
					  1.0f, 0.25f, 0.0f,      0.0f, 0.0f, 1.0f,        0.0f, 0.0f,
					  1.0f, -0.25f, 0.0f,       1.0f, 1.0f, 0.0f,        0.0f, 1.0f
			  };

static const unsigned int indices[] =
								  {
										  0, 1, 3, 1, 2, 3
								  };

float fcolor[] = {0.0, 0.0, 0.0};
int icolor[] = {0, 0, 0 };

TexData image_png;

unsigned int VBO, VAO, EBO;
unsigned int texture1, texture2;
GLint params;

GLboolean initProgram(void)
{
	string vertexShaderPath = (string)GLSL_PATH + "Samplers.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "Samplers.frag";

	programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
	if (!programID) {
		LOGE("Could not create program.");
		return false;
	}
	GL_CHECK(glUseProgram(programID));
    return GL_TRUE;
}

bool setupGraphics()
{
	
	GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
	GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GL_CHECK(glClearDepthf(1.0f));

	return true;
}

void initTexture(float vertices[], int length)
{
	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glGenBuffers(1, &VBO));
	GL_CHECK(glGenBuffers(1, &EBO));

	GL_CHECK(glBindVertexArray(VAO));

	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW));

	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0));

	GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(1));

	GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(2));

	string PictureName = (string)PICTURE_PATH + "cat.jpg";
	image_png.file_name = (char *)PictureName.c_str();

	printf("loadTexturePNG: %s\n",image_png.file_name);
	read_jpeg(&image_png);

	LOGI("mage_png.height  = %d\n",image_png.height);
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3));

	GLint valData;
	GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &valData));
	LOGI("glGetInteger64v(pname = GL_MAX_ELEMENT_INDEX): valData64 =%lld\n", valData);
}

void renderFrame()
{
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));

	initTexture(vertices1, sizeof(vertices1));
	GL_CHECK(glGenTextures(1, &texture1));

	GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, image_png.width, image_png.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1 , GL_RGB, image_png.width/2, image_png.height/2, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 2 , GL_RGB, image_png.width/4, image_png.height/4, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 3 , GL_RGB, image_png.width/8, image_png.height/8, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0));

	initTexture(vertices2, sizeof(vertices2));
	GL_CHECK(glGenTextures(1, &texture2));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture2));

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 2));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, image_png.width, image_png.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1 , GL_RGB, image_png.width/2, image_png.height/2, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 2 , GL_RGB, image_png.width/4, image_png.height/4, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
	GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
	GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0));

	free(image_png.data);
}

void Sample::test() {
	setupGraphics();
    renderFrame();
	string bmp_file1 = filename + ".bmp";
	save2bmp(bmp_file1.c_str());
	SwapBuffers();
}

int main(int argc, char **argv){
	Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
	sample.test();
	return 0;
}
