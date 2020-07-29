#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint output_components;
GLint input_components;

GLfloat vertices[]={ -0.9f, -0.9f,    0.9f, -0.9f,     0.9f, 0.9f,    -0.9f, 0.9f,
                     1.0, 0.0, 0.0,    0.0, 1.0, 0.0,  0.0, 0.0, 1.0, 0.0, 1.0, 1.0
};

void loadShader(void)
{
    GLint success;
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource =
    const GLchar* vertexShaderSource =
        "\n#version 430 core\n"
        "layout(location=0) in vec4 position;\n\n"
        "layout(location=1) in vec4 VsIncolor;\n"
        "out vec4 color;\n\n"
        "void main()\n"
        "{\n"
        "    gl_Position = position;\n"
        "    color = VsIncolor;\n"
        "}\n\0";


    std::string tcShaderSource0 =
        "#version 430 core\n"
        "layout(vertices=4) out;\n"
        "in vec4 color[];\n"
        "out TCS_OUT {\n";

    std::string tcShaderSource1;
    std::string tcShaderSource_main1;
    std::string teShaderSource1;
    std::string teShaderColor0="vec4 TCcolora=";
    std::string teShaderColor1="vec4 TCcolorb=";
    std::string teShaderColor2="vec4 TCcolorc=";
    std::string teShaderColor3="vec4 TCcolord=";
    std::string teShaderAdd0;
    std::string teShaderAdd1;
    std::string teShaderAdd2;
    std::string teShaderAdd3;
    std::string teShaderSource_main1;

    for(int i=0; i<output_components/4; i++){
        tcShaderSource1.append("vec4 TCcolor"+std::to_string(i)+";\n");
        tcShaderSource_main1.append("tcs_out[gl_InvocationID].TCcolor"+std::to_string(i)+"=color[gl_InvocationID]/("+std::to_string(output_components)+"/4);\n");
        std::string temp;
        teShaderAdd0.append("tes_in[0].TCcolor"+std::to_string(i));
        teShaderAdd1.append("tes_in[1].TCcolor"+std::to_string(i));
        teShaderAdd2.append("tes_in[2].TCcolor"+std::to_string(i));
        teShaderAdd3.append("tes_in[3].TCcolor"+std::to_string(i));
        if(i<output_components/4-1){
            temp="+";
            } else {
            temp=" ;\n\0 ";
            }
        teShaderAdd0.append(temp);
        teShaderAdd1.append(temp);
        teShaderAdd2.append(temp);
        teShaderAdd3.append(temp);
    }
    teShaderColor0.append(teShaderAdd0);
    teShaderColor1.append(teShaderAdd1);
    teShaderColor2.append(teShaderAdd2);
    teShaderColor3.append(teShaderAdd3);
    teShaderSource_main1.append(teShaderColor0);
    teShaderSource_main1.append(teShaderColor1);
    teShaderSource_main1.append(teShaderColor2);
    teShaderSource_main1.append(teShaderColor3);

    std::string tcShaderSource_main2;
    tcShaderSource_main2.append("gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n}");


    std::string tcShaderSource_main0 =
        "}tcs_out[];\n"
        "\nvoid main()\n"
        "{\n"
        "gl_TessLevelOuter[0] = 4.0;\n"
        "gl_TessLevelOuter[1] = 3.0;\n";

    std::string tcShaderSource_s;

    tcShaderSource_s.append(tcShaderSource0);
    tcShaderSource_s.append(tcShaderSource1);
    tcShaderSource_s.append(tcShaderSource_main0);
    tcShaderSource_s.append(tcShaderSource_main1);
    tcShaderSource_s.append(tcShaderSource_main2);

    LOGI("tcShaderSource = %s\n", tcShaderSource_s.c_str());
    const GLchar* tcShaderSource = tcShaderSource_s.c_str();

    std::string teShaderSource0 =
                        "\n#version 430 core\n"
                        "layout(isolines, equal_spacing) in;\n"
                        "flat out vec4 color;\n"
                        "in TCS_OUT {\n";


    std::string teShaderSource_main0=
        "}tes_in[];\n"
        "void main()\n"
        "{\n"
        "float u = gl_TessCoord.x;\n"
        "float um = 1 - u;\n"
        "float v = gl_TessCoord.y;\n"
        "float vm = 1 - v;\n"

        "gl_Position = (um*vm * gl_in[0].gl_Position\n"
        "               + u*vm * gl_in[1].gl_Position\n"
        "              + u * v * gl_in[2].gl_Position\n"
        "               + um * v * gl_in[3].gl_Position);\n";

    std::string teShaderSource_main2=
        "color = (TCcolora*um*vm+TCcolorb*u*vm\n"
               " + TCcolorc*v * u + TCcolord*um * v);\n"
               "}";


    std::string teShaderSource_main;
    std::string teShaderSource_s;
    teShaderSource_main.append(teShaderSource_main0);
    teShaderSource_main.append(teShaderSource_main1);
    teShaderSource_main.append(teShaderSource_main2);

    teShaderSource_s.append(teShaderSource0);
    teShaderSource_s.append(tcShaderSource1);
    teShaderSource_s.append(teShaderSource_main);
    LOGI("teShaderSource = %s\n", teShaderSource_s.c_str());
    const GLchar* teShaderSource = teShaderSource_s.c_str();


    const GLchar* fragmentShaderSource =
                        "\n#version 430 core\n"
                        "flat in vec4 color;\n"
                        "out vec4 FragColor;\n"
                        "void main()\n"
                        "{\n"
                        "    FragColor = color;\n"
                        "}\n\0";


    programID = Shader::createProgramFromString(vertexShaderSource, tcShaderSource, teShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
}


bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS, &output_components));
    LOGI("GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS = %d\n", output_components);
    GL_CHECK(glGetIntegerv(GL_MAX_TESS_CONTROL_INPUT_COMPONENTS, &input_components));
    LOGI("GL_MAX_TESS_CONTROL_INPUT_COMPONENTS = %d\n", input_components);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float)*2*4)));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glViewport(0, 0, w, h));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 4));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, 4));
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
