
#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;

GLint max_output_vertices;
GLint max_uniform_components;

GLfloat vertices[]={
        -1.0, -1.0, 0.0, 1.0
};

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource = 
    const GLchar* vertexShaderSource =
        "#version 430 core\n"
        "layout(location=0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = position;\n"
        "}\n\0";


    std::string geometryShaderSource0 =
        "#version 430 core\n"
        "layout(points) in;\n"
        "layout(points, max_vertices=\0";

    geometryShaderSource0.append(std::to_string(max_output_vertices)+") out;\n");

    std::string geometryShaderSource_uniform;
    std::string geometryShaderSource_main2;
    std::string geometryShaderSource_main3;
     for(int i=0; i<max_output_vertices; i++){
        geometryShaderSource_main3.append("gl_Position = vec4(gl_in[0].gl_Position.x + 2.0*" +
         std::to_string(i)+"/"+std::to_string(max_output_vertices)+", gl_in[0].gl_Position.x + 2.0*"
        +std::to_string(i)+"/"+std::to_string(max_output_vertices)+", 0.0, 1.0);\n"
       +"EmitVertex();\n EndPrimitive();\n\n");}



    std::string geometryShaderSource_main1 =
        "void main()\n"
        "{\n";

    std::string geometryShaderSource_main;
    std::string geometryShaderSource_s;
    geometryShaderSource_main.append(geometryShaderSource_main1);
  //  geometryShaderSource_main.append(geometryShaderSource_main2);
    geometryShaderSource_main.append(geometryShaderSource_main3+"}\n\0");
    geometryShaderSource_s.append(geometryShaderSource0);
    geometryShaderSource_s.append(geometryShaderSource_main);
    LOGI("geometryShaderSource = %s\n", geometryShaderSource_s.c_str());
    const GLchar* geometryShaderSource = geometryShaderSource_s.c_str();

    const GLchar* fragmentShaderSource = "#version 430 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}\n\0";


    programID = Shader::createProgramFromString(vertexShaderSource, geometryShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success); 
    if (!success) { 
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}


bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &max_output_vertices));
    LOGI("GL_MAX_GEOMETRY_OUTPUT_VERTICES = %d\n", max_output_vertices);
    GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &max_uniform_components));
    LOGI("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS = %d\n", max_uniform_components);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glPointSize(5.0));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 1));
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
