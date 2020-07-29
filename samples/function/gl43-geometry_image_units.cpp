
#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;

GLint max_image_units;
GLuint texture[256];
#define	iWidth 4
#define	iHeight 4
static GLfloat imagef_odd[iHeight][iWidth][4];
static GLfloat imagef_eve[iHeight][iWidth][4];

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
        "out VS_OUT {\n"
        "    vec2 texcoord;\n"
        "}vs_out;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(0.8*position, 1.0);\n"
        "    vs_out.texcoord = vec2(position.xy);\n"
        "}\n\0";

    const GLchar* geometryShaderSource =
        "#version 430 core\n"
        "layout(triangles) in;\n"
        "layout(triangle_strip, max_vertices=3) out;\n\n"
        "in VS_OUT {\n"
        "    vec2 texcoord;\n"
        "}gs_in[3];\n\n"
        "out GS_OUT {\n"
        "    vec2 texcoord;\n"
        "}gs_out;\n\n"
        "void main()\n"
        "{\n"
        "    gl_Position = gl_in[0].gl_Position;\n"
        "    gs_out.texcoord = gs_in[0].texcoord;\n"
        "    EmitVertex();\n\n"
        "    gl_Position = gl_in[1].gl_Position;\n"
        "    gs_out.texcoord = gs_in[1].texcoord;\n"
        "    EmitVertex();\n\n"
        "    gl_Position = gl_in[2].gl_Position;\n"
        "    gs_out.texcoord = gs_in[2].texcoord;\n"
        "    EmitVertex();\n\n"
        "    EndPrimitive();\n"
        "}\n\0";

   std::string fragmentShaderSource0 =
        "#version 430 core\n"
        "in GS_OUT {\n"
        "    vec2 texcoord;\n"
        "}fs_in;\n\n";
    std::string fragmentShaderSource_s;
    std::string fragmentShaderSource_uni;
    std::string fragmentShaderSource_col;
    std::string fragmentShaderSource_2;
    for(int i=0; i<max_image_units; i++){
        fragmentShaderSource_uni.append("layout(location="+std::to_string(i)+") uniform sampler2D sampler"+std::to_string(i)+";\n");
        fragmentShaderSource_col.append("vec4 color"+std::to_string(i)+"=texture(sampler"+std::to_string(i)+", fs_in.texcoord);\n");
        fragmentShaderSource_2.append("color0=mix(color0, color"+std::to_string(i)+", 0.5);\n");
    }
    std::string fragmentShaderSource_1=
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n";

    std::string fragmentShaderSource_3=
        "    FragColor = color0;\n"
    "}\n\0";
    fragmentShaderSource_s.append(fragmentShaderSource0);
    fragmentShaderSource_s.append(fragmentShaderSource_uni);
    fragmentShaderSource_s.append(fragmentShaderSource_1);
    fragmentShaderSource_s.append(fragmentShaderSource_col);
    fragmentShaderSource_s.append(fragmentShaderSource_2);
    fragmentShaderSource_s.append(fragmentShaderSource_3);
    LOGI("fragmentShaderSource = %s\n", fragmentShaderSource_s.c_str());
    const GLchar* fragmentShaderSource = fragmentShaderSource_s.c_str();

    programID = Shader::createProgramFromString(vertexShaderSource, geometryShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success); 
    if (!success) { 
            glGetProgramInfoLog(programID, 512, NULL, infoLog); 
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
    }
}

void makeImage_odd(void) {
    int s, t, r;
    for (s = 0; s < iHeight; s++) {
        for (t = 0; t < iWidth; t++) {
            imagef_odd[t][s][0] = (GLfloat)(s * 2);
            imagef_odd[t][s][1] = (GLfloat)(t * 10);
            imagef_odd[t][s][2] = (GLfloat)(s * 17);
            imagef_odd[t][s][3] = (GLfloat)(t * 17);
        }
    }
}

void makeImage_eve(void) {
    int s, t, r;
    for (s = 0; s < iHeight; s++) {
        for (t = 0; t < iWidth; t++) {
            imagef_eve[t][s][0] = (GLfloat)(s * 13);
            imagef_eve[t][s][1] = (GLfloat)(t * 2);
            imagef_eve[t][s][2] = (GLfloat)(s * 17);
            imagef_eve[t][s][3] = (GLfloat)(t * 17);
        }
    }
}

unsigned int loadTexture_eve() {
    unsigned int textureID;
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, iWidth, iHeight, 0, GL_RGBA, GL_FLOAT, imagef_eve));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    return textureID;
}

unsigned int loadTexture_odd() {
    unsigned int textureID;
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, iWidth, iHeight, 0, GL_RGBA, GL_FLOAT, imagef_odd));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    return textureID;
}

bool setupGraphics(int w, int h)
{
    GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &max_image_units));
    LOGI("GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = %d\n", max_image_units);

    loadShader();
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    makeImage_odd();
    makeImage_eve();
    for(int i=0; i<max_image_units; i++){
        if(i%2==0){
           texture[i]=loadTexture_odd();
        }else{
           texture[i]=loadTexture_eve();
        }
    }
    GL_CHECK(glViewport(0, 0, w, h));
    
    return true;
} 

void renderFrame(void) {
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    for(int i=0; i<max_image_units; i++){
        GL_CHECK(glActiveTexture(GL_TEXTURE0+i));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture[i]));
    }
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
