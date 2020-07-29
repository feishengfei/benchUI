#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint max_uniform_components;
GLint max_uniform_vectors;
GLint uni_num;
GLfloat vertices[]={
        -0.8, -0.8, 0.0, 1.0,
         0.0,  0.8, 0.0, 1.0,
         0.8, -0.8, 0.0, 1.0
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


    std::string fragmentShaderSource0 =
        "#version 430 core\n"
        "out vec4 FragColor;\n\n";

    std::string fragmentShaderSource_uniform0;
    std::string fragmentShaderSource_uniform1;
    std::string fragmentShaderSource_main2;
    std::string fragmentShaderSource_main3;
    std::string fragmentShaderSource_main4="vec4 color =";
    for(int i=0; i<max_uniform_vectors; i++){
       fragmentShaderSource_uniform1.append("\nlayout(location="+std::to_string(i)+
        ") uniform vec4 color"+std::to_string(i)+";\n");
       std::string temp;
       fragmentShaderSource_main2.append("color"+std::to_string(i));
       if(i<max_uniform_vectors-1){
           temp="+";} else {
           temp=" ;\n\0 ";
       }
        fragmentShaderSource_main2.append(temp);
    }

        fragmentShaderSource_main3.append("FragColor = color;\n\n");
        fragmentShaderSource_main4.append(fragmentShaderSource_main2);


    std::string fragmentShaderSource_main1 =
        "void main()\n"
        "{\n";

    std::string fragmentShaderSource_main;
    std::string fragmentShaderSource_s;

    fragmentShaderSource_main.append(fragmentShaderSource_main1);
    fragmentShaderSource_main.append(fragmentShaderSource_main4);
    fragmentShaderSource_main.append(fragmentShaderSource_main3+"}\n\0");
    fragmentShaderSource_s.append(fragmentShaderSource0);
    fragmentShaderSource_s.append(fragmentShaderSource_uniform1);
    fragmentShaderSource_s.append(fragmentShaderSource_main);
    LOGI("fragmentShaderSource = %s\n", fragmentShaderSource_s.c_str());
    const GLchar* fragmentShaderSource = fragmentShaderSource_s.c_str();


    programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}


bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &max_uniform_components));
    LOGI("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS = %d\n", max_uniform_components);
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &max_uniform_vectors));
    LOGI("GL_MAX_FRAGMENT_UNIFORM_VECTORS = %d\n", max_uniform_vectors);
    GL_CHECK(glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &max_uniform_vectors));
    LOGI("GL_MAX_FRAGMENT_UNIFORM_VECTORS = %d\n", max_uniform_vectors);
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
    float col_per=1.0/max_uniform_vectors;
    GL_CHECK(glUseProgram(programID));
    for(int i=0; i<max_uniform_vectors; i++){
        GL_CHECK(glUniform4f(i, col_per, 0.0, 0.0, col_per));
    }
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
