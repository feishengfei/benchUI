
#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;

GLint max_input_components;

GLfloat vertices[]={
        -1.0, -1.0, 0.0, 1.0,
        -1.0,  0.0, 0.0, 1.0,
         0.0, -1.0, 0.0, 1.0
};

void loadShader(void)
{
    GLint success;
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource =
    std::string vertexShaderSource_s;
    std::string vertexShaderSource_mv;
    std::string vertexShaderSource_mv_in_mian;
    std::string vertexShaderSource1;
    std::string vertexShaderSource3;
    std::string geometryShaderSourceg0;
    std::string geometryShaderSourceg1;
    std::string geometryShaderSourceg2;
    std::string geometryShaderSource30;
    std::string geometryShaderSource31;
    std::string geometryShaderSource32;
    std::string vertexShaderSource0 =
        "#version 430 core\n"
        "layout(location=0) in vec4 position;\n"
        "out VS_OUT {\n";
    vertexShaderSource_s.append(vertexShaderSource0);
    for(int i=0; i<max_input_components/4; i++){
        vertexShaderSource1 = "vec4 mov"+std::to_string(i)+";\n";
        vertexShaderSource_mv.append(vertexShaderSource1);
        vertexShaderSource3 = "vs_out.mov"+std::to_string(i)+"=vec4(4.0/"+std::to_string(max_input_components)+", 0.0, 0.0, 0.0);\n";
        vertexShaderSource_mv_in_mian.append(vertexShaderSource3);
        geometryShaderSourceg0="gs_in[0].mov"+std::to_string(i);
        geometryShaderSourceg1="gs_in[1].mov"+std::to_string(i);
        geometryShaderSourceg2="gs_in[2].mov"+std::to_string(i);
        std::string temp;
        if(i<max_input_components/4-1){
            temp=" + ";
        }else{
            temp=";\n";
        }
        geometryShaderSource30.append(geometryShaderSourceg0);
        geometryShaderSource30.append(temp);
        geometryShaderSource31.append(geometryShaderSourceg1);
        geometryShaderSource31.append(temp);
        geometryShaderSource32.append(geometryShaderSourceg2);
        geometryShaderSource32.append(temp);
    }

    vertexShaderSource_s.append(vertexShaderSource_mv);
    std::string vertexShaderSource2=
        "}vs_out;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = position;\n";
    vertexShaderSource_s.append(vertexShaderSource2);
    vertexShaderSource_s.append(vertexShaderSource_mv_in_mian);
    std::string vertexShaderSource4=
        "}\n\0";
    vertexShaderSource_s.append(vertexShaderSource4);
    LOGI("vertexShaderSource = %s\n", vertexShaderSource_s.c_str());
    const GLchar* vertexShaderSource = vertexShaderSource_s.c_str();

    std::string geometryShaderSource_s;
    std::string geometryShaderSource0 =
        "#version 430 core\n"
        "layout(triangles) in;\n"
        "layout(triangle_strip, max_vertices=3) out;\n\n"
        "in VS_OUT {\n";
    geometryShaderSource_s.append(geometryShaderSource0);
    geometryShaderSource_s.append(vertexShaderSource_mv);
    std::string geometryShaderSource1=
        "}gs_in[3];\n"
        "void main()\n\n"
        "{\n";
    std::string geometryShaderSourcepos0="gl_Position=gl_in[0].gl_Position + "+geometryShaderSource30+"\n EmitVertex();\n";
    std::string geometryShaderSourcepos1="gl_Position=gl_in[1].gl_Position + "+geometryShaderSource31+"\n EmitVertex();\n";
    std::string geometryShaderSourcepos2="gl_Position=gl_in[2].gl_Position + "+geometryShaderSource32+"\n EmitVertex();\nEndPrimitive();}\n\n";
    geometryShaderSource_s.append(geometryShaderSource1);
    geometryShaderSource_s.append(geometryShaderSourcepos0);
    geometryShaderSource_s.append(geometryShaderSourcepos1);
    geometryShaderSource_s.append(geometryShaderSourcepos2);
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
    GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS, &max_input_components));
    LOGI("GL_MAX_GEOMETRY_INPUT_COMPONENTS = %d\n", max_input_components);

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
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
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
