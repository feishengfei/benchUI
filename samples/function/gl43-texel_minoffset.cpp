
#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint min_offset;
GLuint texture;
#define	iWidth 4
#define	iHeight 4
static GLfloat imagef[iHeight][iWidth][4];

float vertices[] = {
        -1,-1,0,  1,-1,0,  -1,1,0,
        1,-1,0,  -1,1,0,  1,1,0,
};
void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    //const GLchar* vertexShaderSource = 
    const GLchar* vertexShaderSource =
        "#version 430 core\n"
        "layout(location=0) in vec3 position;\n\n"
        "out vec2 texcoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(0.8*position, 1.0);\n"
        "    texcoord = vec2(position.xy);\n"
        "}\n\0";


   std::string fragmentShaderSource_s =
        "#version 430 core\n"
        "in vec2 texcoord;\n"
        "uniform sampler2D sampler;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor=textureOffset(sampler, texcoord, ivec2("+std::to_string(min_offset)+", "+std::to_string(min_offset)+"));\n}";
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

void makeImage(void) {
    int s, t, r;
    for (s = 0; s < iHeight; s++) {
        for (t = 0; t < iWidth; t++) {
            imagef[t][s][0] = (GLfloat)(s * 2);
            imagef[t][s][1] = (GLfloat)(t * 10);
            imagef[t][s][2] = (GLfloat)(s * 17);
            imagef[t][s][3] = (GLfloat)(t * 17);
        }
    }
}


unsigned int loadTexture() {
    unsigned int textureID;
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, iWidth, iHeight, 0, GL_RGBA, GL_FLOAT, imagef));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    return textureID;
}

bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MIN_PROGRAM_TEXEL_OFFSET, &min_offset));
    LOGI("GL_MIN_PROGRAM_TEXEL_OFFSET = %d\n", min_offset);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    makeImage();
    texture=loadTexture();

    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glClearColor (0.5, 0.2, 1.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));

    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
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
