
#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;

GLint max_output_components;
GLint max_total_output_components;
GLfloat vertices[]={
        0.0, 0.0, 0.0, 1.0
};

void loadShader(void) {
    GLint  success;
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource = 
    const GLchar *vertexShaderSource =
                         "#version 430 core\n"
                         "layout(location=0) in vec4 position;\n"
                         "layout(location=1) in vec4 color;\n"

                         "void main()\n"
                         "{\n"
                         "    gl_Position = position;\n"
                         "}\n\0";


    std::string geometryShaderSource0 =
                        "#version 430 core\n"
                        "layout(points) in;\n"
                        "layout(points, max_vertices=1) out;\n"

                        "out GS_OUT {\n";

    std::string color_component;
    std::string color_component_add;
    std::string color_component_out;
    for (int    i                     = 0; i < max_output_components / 4; i++) {
        color_component.append("vec4 color" + std::to_string(i) + ";\n");
        color_component_out.append(
                "gs_out.color" + std::to_string(i) + " = vec4(4.0/"+std::to_string(max_output_components)+", 0.0, 0.0, 1.0);\n");
        color_component_add.append("fs_in.color" + std::to_string(i));
        std::string temp;
        if (i < max_output_components / 4 - 1) {
            temp = " + ";
        } else {
            temp = ";\n";
        }
        color_component_add.append(temp);
    }

    std::string geometryShaderSource_main1 =
                        "}gs_out;\n"
                        "void main()\n"
                        "{\n"
                        "gl_Position = gl_in[0].gl_Position;\n";
    std::string geometryShaderSource_main2 =
                        "EmitVertex();\n"
                        "EndPrimitive();\n}";


    std::string geometryShaderSource_s;
    geometryShaderSource_s.append(geometryShaderSource0);
    geometryShaderSource_s.append(color_component);
    geometryShaderSource_s.append(geometryShaderSource_main1);
    geometryShaderSource_s.append(color_component_out);
    geometryShaderSource_s.append(geometryShaderSource_main2);
    LOGI("geometryShaderSource = %s\n", geometryShaderSource_s.c_str());
    const GLchar *geometryShaderSource = geometryShaderSource_s.c_str();

    std::string fragmentShaderSource_s;
    std::string fragmentShaderSource0 =
        "#version 430 core\n"
        "out vec4 FragColor;\n"
        "in GS_OUT {\n";
    std::string fragmentShaderSource1 =
        "}fs_in;\n"
        "void main()\n"
        "{\n"
        "    FragColor = " + color_component_add +
        "}\n\0";

    fragmentShaderSource_s.append(fragmentShaderSource0);
    fragmentShaderSource_s.append(color_component);
    fragmentShaderSource_s.append(fragmentShaderSource1);
    LOGI("fragmentShaderSource = %s\n", fragmentShaderSource_s.c_str());
    const GLchar *fragmentShaderSource = fragmentShaderSource_s.c_str();


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
    GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, &max_output_components));
    LOGI("GL_MAX_GEOMETRY_OUTPUT_COMPONENTS = %d\n", max_output_components);
    GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &max_total_output_components));
    LOGI("GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS = %d\n", max_total_output_components);

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
    GL_CHECK(glPointSize(40.0));
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
