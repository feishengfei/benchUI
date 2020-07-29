#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))
GLint max_uniform_blocks;
GLuint programID, VAOs, Buffers;


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
        "#version 430 core\n\n"
        "out vec4 FragColor;\n\n";
        

    std::string fragmentShaderSource_uniform1;
    std::string fragmentShaderSource_main2;
    std::string fragmentShaderSource_main3;
    std::string fragmentShaderSource_main4="vec4 color =";
    for(int i=0; i<max_uniform_blocks; i++){
       fragmentShaderSource_uniform1.append("layout(std140, binding="+std::to_string(i)+") uniform MVP"+std::to_string(i)+"{\nvec4 ucolor"+std::to_string(i)+";\n}ubo"+std::to_string(i)+";\n");
       std::string temp;
       fragmentShaderSource_main2.append("ubo"+std::to_string(i)+".ucolor"+std::to_string(i));
       if(i<max_uniform_blocks-1){
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
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &max_uniform_blocks));
    LOGI("GL_MAX_FRAGMENT_UNIFORM_BLOCKS = %d\n", max_uniform_blocks);

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
    float cols=1.0/max_uniform_blocks;
    float per_col[]={cols, 0.0, 0.0, cols};

    GLuint  buf[max_uniform_blocks];
    GLint blockSize;
    GL_CHECK(glGetActiveUniformBlockiv(programID, 0, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize));
    LOGI("uniform block size is %d\n", blockSize);

    GLubyte *blockBuffer[max_uniform_blocks];
    for(int i=0; i<max_uniform_blocks; i++) {
        blockBuffer[i] = (GLubyte *)malloc(blockSize);
        memcpy(blockBuffer[i], per_col, 4*sizeof(float));

        GL_CHECK(glGenBuffers(1, &buf[i]));
        GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, buf[i]));
        GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer[i], GL_DYNAMIC_COPY));
        GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, i, buf[i]));
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
