/**
 ** @file max-uniform-block.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2020-05-15, create file
 ** @par TestPoints:
 **   GL_MAX_VERTEX_UNIFORM_BLOCKS
 */

#include "Sample.h"
#include "Shader.h"
#include <string>
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = { 
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
}; 

GLfloat colors[] = { 
	0.1f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.1f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.1f, 0.0f
}; 

GLuint fragmentShader;
GLuint programID, VAOs, Buffers;
GLint uboSize;
GLint posLocation, colorLocation;

GLint my_uniform_blocks;
GLint iLocu;
GLuint indices;
GLint getlength;
GLchar uniformBlockName[20] = {};

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    std::string vertexShaderSource0 = 
        "#version 430 core\n"
        "in vec3 position;\n"
        "in vec4 acolor;\n"
        "out vec4 vcolor;\n\0";

    std::string UniformBlock_n = "";
    std::string UniformBlock_temp ;

    std::string vertex[my_uniform_blocks];
    for(int i = 1 ; i < my_uniform_blocks ; i++)
    {
        UniformBlock_temp = "uniform ";
        UniformBlock_temp.append("UniformBlock" + std::to_string(i));
        UniformBlock_temp.append("{   vec4 u4f_v;  vec4 u4f_c; } uni_" + std::to_string(i) + ";\n" ); 
        UniformBlock_n.append(UniformBlock_temp);
    }

    std::string vertexShaderSource_main1 = 
        "void main()\n"
        "{\n"
        "    vcolor = acolor + \0";

    std::string vertexShaderSource_main2 = 
        "    gl_Position = vec4(position, 1.0) + \0";

    std::string vertexShaderSource_temp1;
    std::string vertexShaderSource_temp2;
    for(int i = 1 ; i < my_uniform_blocks ; i++)
    {
        std::string temp;
        vertexShaderSource_temp1.append("uni_" + std::to_string(i) +".u4f_c ");
        if(i < (my_uniform_blocks - 1))
        {
            temp = " + ";
        }
        else
        {
            temp = " ;\n\0 ";
        }
        vertexShaderSource_temp1.append(temp);

        vertexShaderSource_temp2.append("uni_" + std::to_string(i) +".u4f_v ");        
        vertexShaderSource_temp2.append(temp);
    }

    std::string vertexShaderSource_main = "";
    vertexShaderSource_main.append(vertexShaderSource_main1);
    vertexShaderSource_main.append(vertexShaderSource_temp1);
    vertexShaderSource_main.append(vertexShaderSource_main2);
    vertexShaderSource_main.append(vertexShaderSource_temp2 + "}\0");
//    LOGI("vertexShaderSource_main = %s\n", vertexShaderSource_main.c_str());

    vertexShaderSource0.append(UniformBlock_n);
    vertexShaderSource0.append(vertexShaderSource_main);
    const GLchar* vertexShaderSource = vertexShaderSource0.c_str();

    LOGI("vertexShaderSource = \n %s \n", vertexShaderSource);

    const GLchar* fragmentShaderSource = "#version 430 core\n"
        "in vec4 vcolor;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vcolor;\n"
        "}\n\0";

    programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
    GL_CHECK(posLocation = glGetAttribLocation(programID, "position"));
    GL_CHECK(colorLocation = glGetAttribLocation(programID, "acolor"));
    printf("Atrrib Location: v=%d, c=%d\n", posLocation, colorLocation);
}

bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &my_uniform_blocks));
    LOGI("GL_MAX_VERTEX_UNIFORM_BLOCKS = %d\n", my_uniform_blocks);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
    GL_CHECK(glEnableVertexAttribArray(posLocation));
    GL_CHECK(glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(colorLocation));
    GL_CHECK(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glEnableVertexAttribArray(posLocation));
    GL_CHECK(glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    GLuint *max_ubo = (GLuint *)malloc(my_uniform_blocks);
    GLuint *max_uboIndex = (GLuint *)malloc(my_uniform_blocks);
    float *max_uniformBuffer = (float *)malloc(my_uniform_blocks * 8);
     
    for(int i = 1 ; i < my_uniform_blocks; i++)
    {
        std::string shaderName = "UniformBlock" + std::to_string(i);
        max_uboIndex[i] = GL_CHECK(glGetUniformBlockIndex(programID, shaderName.c_str()));
        LOGI("glGetUniformBlockIndex : uboIndex: %d\n", max_uboIndex[i]);

        for(int j = i ; j < (i+8); j++)
        {
            max_uniformBuffer[j] = {0.05};
        }

        GL_CHECK(glGenBuffers(1, &max_ubo[i]));
        GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, max_ubo[i]));
        GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), static_cast<void*> (&max_uniformBuffer[i]), GL_STATIC_DRAW));
        GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, max_uboIndex[i], max_ubo[i]));
    }

    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    glFlush();
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
