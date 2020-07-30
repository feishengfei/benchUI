/**
 * @file gl31-GetActiveUniformName.cpp
 * @testpoint glGetActiveUniformsiv
 * @testpoint glGetActiveUniformName
 * @testpoint glGetUniformBlockIndex
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};
 
GLfloat colors[] = { 
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
}; 


GLuint programID, VAOs, Buffers;;

const GLuint uniformIndices = 0;
const GLuint uniformIndices1 = 1;

GLint params;
GLint params1;

static const GLenum factors[] = {
    GL_UNIFORM_TYPE,
    GL_UNIFORM_SIZE,
    GL_UNIFORM_NAME_LENGTH,
    GL_UNIFORM_BLOCK_INDEX,
    GL_UNIFORM_OFFSET,
    GL_UNIFORM_ARRAY_STRIDE,
    GL_UNIFORM_MATRIX_STRIDE,
    GL_UNIFORM_IS_ROW_MAJOR,
    GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX
};

GLint length;
GLchar uniformName;
GLuint indices;
const char*names = {"u1f"};

void getdata(void)
{
	GLfloat paramf[4];
	GLsizei length;
	GLint size;
	GLenum type;
	GLchar name[5];
        GLuint uboIndex;
        GLint uboSize;

        uboIndex = glGetUniformBlockIndex(programID, "3");
        LOGI("glGetUniformBlockIndex uboIndex: %d\n", uboIndex);
        glGetActiveUniformBlockiv(programID, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
        LOGI("glGetUniformBlockIndex uboSize: %d\n", uboSize);

	glGetUniformfv(programID, 3, paramf);
	LOGI("glGetUniformfv: %f, %f, %f, %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetActiveUniform(programID, 3, 4, &length, &size, &type, name);
	LOGI("GetActiveUniform(3): length=%d, size=%d, type=%s, name=%s\n", length, size, get_enum_name(type), name);
        
        glGetUniformIndices(programID, 1, &names, &indices);
        LOGI("glGetUniformIndices: indices = %d \n", indices);

        glGetActiveUniformsiv(programID, 4*sizeof(float), &uniformIndices, 3, &params);
        LOGI("glGetActiveUniformsiv: uniformIndices = %d, params = %d \n", uniformIndices, params);
      
        for(int typeNum=0; typeNum < ARRAY_NUM(factors); typeNum++) { 
            glGetActiveUniformsiv(programID, sizeof(float), &uniformIndices1, factors[typeNum], &params1);
            LOGI("glGetActiveUniformsiv (%s): uniformIndices = %d, params = %d \n",get_enum_name(factors[typeNum]), uniformIndices1, params1);
        }

        glGetActiveUniformName(programID, 3, 4*sizeof(float), &length, &uniformName);
        LOGI("glGetActiveUniformName: params: length = %d, uniformName = %c\n", length, uniformName);
}

bool setupGraphics(int w, int h)
{
    /*load shader*/
    string vertexShaderPath =(string)GLSL_PATH + "GetActiveUniformName.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "GetActiveUniformName.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));

	GL_CHECK(glGenVertexArrays(1, &VAOs));
	GL_CHECK(glBindVertexArray(VAOs));

	GL_CHECK(glGenBuffers(1, &Buffers));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

	glViewport(0, 0, w, h);
    return true;
} 

void renderFrame(void)
{
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glUniform1f(0, 0.1f));
	GL_CHECK(glUniform2f(1, 0.1, 0.1));
	GL_CHECK(glUniform3f(2, 0.1, 0.1, 0.1));
	GL_CHECK(glUniform4f(3, 0.0, 1.0, 0.0, 0.0));
	GL_CHECK(glBindVertexArray(VAOs));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
	GL_CHECK(glFlush());
}

void Sample::test() {
	string bmp_file = filename + ".bmp";
	LOGI("[]: filename=%s\n", bmp_file.c_str());
	setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame();
	getdata();
	save2bmp(bmp_file.c_str());
	SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}