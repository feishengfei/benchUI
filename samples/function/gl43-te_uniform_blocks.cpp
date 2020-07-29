#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint max_uniform_blocks;

GLfloat vertices[]={ -0.9f, -0.9f,    0.9f, -0.9f,     0.0f, 0.9f,
                 1.0, 0.0, 0.0,    0.0, 1.0, 0.0,  0.0, 0.0, 1.0
};

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource = 
    const GLchar* vertexShaderSource =
        "\n#version 430 core\n"
        "layout(location=0) in vec4 position;\n"
        "layout(location=1) in vec4 vcolor;\n"
        "out vec4 color;\n\n"
        "void main()\n"
        "{\n"
        "    gl_Position = position;\n"
        "    color = vcolor;\n"
        "}\n\0";


    const GLchar*  tcShaderSource =
        "#version 430 core\n"
        "layout(vertices=3) out;\n"
        "in vec4 color[];\n"
        "out vec4 TCcolor[];\n"
        "void main()\n"
        "{\n"
        "gl_TessLevelInner[0] = 3.0;\n"
        "gl_TessLevelOuter[0] = 3.0;\n"
        "gl_TessLevelOuter[1] = 3.0;\n"
        "gl_TessLevelOuter[2] = 3.0;\n\n"
        "gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"
        "TCcolor[gl_InvocationID] = color[gl_InvocationID];\n}";


    std::string teShaderSource0 =
                        "#version 430 core\n"
                        "layout(triangles) in;\n"
                        "out vec4 color;\n"
                        "in vec4 TCcolor[];\n";
    std::string teShaderSource_uniform0;
    std::string teShaderSource_main2;
    std::string teShaderSource_main3;
    std::string teShaderSource_main4="mat4 scaling =";
    for(int i=0; i<max_uniform_blocks; i++){
       teShaderSource_uniform0.append("layout(std140, binding="+std::to_string(i)+") uniform MVP"+std::to_string(i)+
       "{\nmat4 scaling"+std::to_string(i)+";\n}ubo"+std::to_string(i)+";\n");
        std::string temp;
       teShaderSource_main2.append("ubo"+std::to_string(i)+".scaling"+std::to_string(i));
       if(i<max_uniform_blocks-1){
           temp="*";} else {
           temp=" ;\n\0 ";
       }
        teShaderSource_main2.append(temp);
    }

       teShaderSource_main4.append(teShaderSource_main2);


    std::string teShaderSource_main0 =
        "void main(){\n";

    std::string teShaderSource_main1 =
        "float u = gl_TessCoord.x;\n"
        "float v = gl_TessCoord.y;\n"
        "float w = gl_TessCoord.z;\n"
        "gl_Position = scaling*(u * gl_in[0].gl_Position+ v * gl_in[1].gl_Position + w * gl_in[2].gl_Position);"
        "color = (TCcolor[0]*(1.0-v)+TCcolor[1]*(1.0-u)+TCcolor[2]*(1.0-w));\n"
        "}";

    std::string teShaderSource_main;
    std::string teShaderSource_s;

    teShaderSource_main.append(teShaderSource_main0);
    teShaderSource_main.append(teShaderSource_main4);
    teShaderSource_main.append(teShaderSource_main1);
    teShaderSource_s.append(teShaderSource0);
    teShaderSource_s.append(teShaderSource_uniform0);
    teShaderSource_s.append(teShaderSource_main);
    LOGI("teShaderSource = %s\n", teShaderSource_s.c_str());
    const GLchar* teShaderSource = teShaderSource_s.c_str();

    const GLchar* fragmentShaderSource =
        "\n#version 430 core\n"
        "in vec4 color;\n"
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
    GL_CHECK(glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, &max_uniform_blocks));
    LOGI("GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS = %d\n", max_uniform_blocks);

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
    Matrix scale0    = Matrix::createScaling(1.0f, 1.0f, 1.0f);
    Matrix scale1    = Matrix::createScaling(0.3f, 1.0f, 1.0f);
    GLuint  buf[max_uniform_blocks];
    GLint blockSize;
    GL_CHECK(glGetActiveUniformBlockiv(programID, 0, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize));
    LOGI("uniform block size is %d\n", blockSize);

    GLubyte *blockBuffer[max_uniform_blocks];

    for(int i=0; i<max_uniform_blocks; i++) {
        blockBuffer[i] = (GLubyte *)malloc(blockSize);
        if (i < max_uniform_blocks - 1) {
            memcpy(blockBuffer[i],  scale0.getAsArray(), 16 * sizeof(float));
        } else {
            memcpy(blockBuffer[i],  scale1.getAsArray(), 16 * sizeof(float));
        }
        GL_CHECK(glGenBuffers(1, &buf[i]));
        GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, buf[i]));
        GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer[i], GL_DYNAMIC_COPY));
        GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, i, buf[i]));

    }
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 3));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, 3));
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
