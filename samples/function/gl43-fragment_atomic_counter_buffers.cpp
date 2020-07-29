
#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID;

GLint max_acb;
GLuint VertexArrayName;
GLuint abo, ebo;

GLfloat vertices[]={
        -0.8, 0.8, 0.0,
        -0.8, -0.8, 0.0,
        0.8, -0.8, 0.0,
        0.8, 0.8, 0.0
};

GLuint indices[]={
        0, 1, 2, 2, 3, 0
};

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource = 
    const GLchar* vertexShaderSource =
        "\n#version 430 core\n\n"
        "layout(location=0) in vec3 position;\n\n"
        "out gl_PerVertex{\n"
        "    vec4 gl_Position;\n"
        "};\n\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position, 1.0);\n"
        "}\n\0";


   std::string fragmentShaderSource0 =
        "\n#version 430 core\n\n";

    std::string fragmentShaderSource_s;
    std::string fragmentShaderSource_uni;
    std::string fragmentShaderSource_col;
    std::string fragmentShaderSource_col1="float r =";
    std::string fragmentShaderSource_col2;

    for(int i=0; i<max_acb; i++){
        fragmentShaderSource_uni.append("layout(binding="+std::to_string(i)+") uniform atomic_uint red"+std::to_string(i)+";\n");
        fragmentShaderSource_col.append("float r"+std::to_string(i)+"=atomicCounterIncrement(red"+std::to_string(i)+")*fPixel;\n");
        std::string temp;
        fragmentShaderSource_col2.append("r"+std::to_string(i));
        if(i<max_acb-1){
            temp="+";} else {
            temp=" ;\n\0 ";
        }
        fragmentShaderSource_col2.append(temp);
    }
    fragmentShaderSource_col1.append(fragmentShaderSource_col2);
    std::string fragmentShaderSource_1=
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "float fPixel = 1.0/(480*320);\n";
    std::string fragmentShaderSource_3=
        "if(r>1.0){\n"
        "    r=r-1.0;\n"
        "}\n"
        "    FragColor = vec4(r, 0.0, 0.0, 1.0);\n"
    "}\n\0";
    fragmentShaderSource_s.append(fragmentShaderSource0);
    fragmentShaderSource_s.append(fragmentShaderSource_uni);
    fragmentShaderSource_s.append(fragmentShaderSource_1);
    fragmentShaderSource_s.append(fragmentShaderSource_col);
    fragmentShaderSource_s.append(fragmentShaderSource_col1);
    fragmentShaderSource_s.append(fragmentShaderSource_3);
    LOGI("fragmentShaderSource = %s\n", fragmentShaderSource_s.c_str());
    const GLchar* fragmentShaderSource = fragmentShaderSource_s.c_str();

    programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success); 
    if (!success) { 
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}

bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, &max_acb));
    LOGI("GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS = %d\n", max_acb);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VertexArrayName));
    GL_CHECK(glBindVertexArray(VertexArrayName));

    GL_CHECK(glGenBuffers(1, &abo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, abo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GLuint aco[max_acb];
    for(int i=0; i<max_acb; i++){
        GL_CHECK(glGenBuffers(1, &aco[i]));
        GL_CHECK(glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, aco[i]));
        GL_CHECK(glBufferStorage(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_MAP_WRITE_BIT));
        GLuint Data = 0;
        GL_CHECK(glClearBufferSubData(GL_ATOMIC_COUNTER_BUFFER, GL_RGBA8, 0, sizeof(GLuint),
                                      GL_RGBA, GL_UNSIGNED_BYTE, &Data));
        GL_CHECK(glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, i, aco[i]));

    }

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
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
