/**
 ** @file max_inout_components.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2020-05-15, create file
 ** @par TestPoints:
 **    GL_MAX_VERTEX_OUTPUT_COMPONENTS
 **    GL_MAX_FRAGMENT_INPUT_COMPONENTS
 */

#include "Sample.h"
#include <string>
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};
 
GLfloat colors[] = { 
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
}; 


GLuint programID, VAOs, Buffers;;
const GLuint uniformIndices = 0;
const GLuint uniformIndices1 = 1;
GLint params;
GLint params1;
GLint length;
GLchar uniformName;
GLuint indices;
GLint my_finput_components;
GLint my_foutput_components;

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    std::string SvertexShaderSource =
        "#version 430 core\n"
        "layout(location=0) in vec3 position;\n"
        "layout(location=1) in vec4 acolor;\n";   
 
    std::string vertex_n1 = ""; 
    std::string vertex_n2 = ""; 
    std::string vertex_temp1 ;
    std::string vertex_temp2 ;

    for(int i = 1 ; i < my_foutput_components ; i++)
    {   
        vertex_temp1.append("out vec4 vcolor" + std::to_string(i) + ";\n");
        vertex_n1.append(vertex_temp1);
        
        vertex_temp2.append("    vcolor" + std::to_string(i) + " = vec4(acolor.r, 0." + std::to_string(i) + ", 0.0, 0.0);\n");
        vertex_n2.append(vertex_temp2);
    }   

    SvertexShaderSource.append(vertex_temp1 + "void main() \n{\n" + vertex_temp2 + "    gl_Position = vec4(position, 1.0);\n}");
    LOGI("vertexShaderSource = \n %s\n", SvertexShaderSource.c_str());
    const GLchar* vertexShaderSource = SvertexShaderSource.c_str();

    std::string SfragmentShaderSource =
       "#version 430 core\n";

    std::string fragment_n = "";
    std::string fragment_temp ;

    for(int i = 1 ; i < my_foutput_components ; i++)
    {
        fragment_temp.append("in vec4 vcolor" + std::to_string(i) + ";\n");
        fragment_n.append(vertex_temp1);
    }

    std::string SfragmentShaderSource_end =
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vcolor1;\n"
        "}\n\0";

    SfragmentShaderSource.append(fragment_temp + SfragmentShaderSource_end);
    LOGI("SfragmentShaderSource = \n %s\n", SfragmentShaderSource.c_str());
    const GLchar* fragmentShaderSource = SfragmentShaderSource.c_str();

    programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success); 
    if (!success) { 
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}


bool setupGraphics()
{
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &my_foutput_components));
    LOGI("GL_MAX_VERTEX_OUTPUT_COMPONENTS = %d\n", my_foutput_components);
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS , &my_finput_components));
    LOGI("GL_MAX_FRAGMENT_INPUT_COMPONENTS = %d\n", my_finput_components);

    loadShader();

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

    return true;
} 

void renderFrame(void)
{
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glBindVertexArray(VAOs));

        GLint max_viewports;

        GL_CHECK(glViewport(0 , 0 , WINDOW_W , WINDOW_H )); 
        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GL_CHECK(glFlush());
}

void Sample::test() {
	string bmp_file = filename + ".bmp";
	LOGI("[]: filename=%s\n", bmp_file.c_str());
	setupGraphics();
        renderFrame();
	save2bmp(bmp_file.c_str());
	SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
