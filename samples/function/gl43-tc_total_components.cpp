#include "Sample.h"
#include "Shader.h"
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLint patch_vertices;
GLint total_components;

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];
    GLint num=total_components/(4*patch_vertices);
    //const GLchar* vertexShaderSource = 
    const GLchar* vertexShaderSource =
        "\n#version 430 core\n"
        "layout(location=0) in vec2 position;\n"
        "layout(location=1) in vec2 col;\n"
        "out vec4 color;\n\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position, 0.0, 1.0);\n"
        "    color = vec4(col, 0.0, 1.0);\n"
        "}\n\0";


    std::string tcShaderSource0 =
        "#version 430 core\n\n";
    std::string tcShaderSource1;
    tcShaderSource1.append("layout(vertices="+std::to_string(patch_vertices)+") out;\n");
    std::string tcShaderSource2 =
    "in vec4 color[];\n"
    "out TCS_OUT {\n";

    std::string tcShaderSourceMain0 =
    "}tcs_out[];\n\n"
    "\nvoid main() {\n"
    "    gl_TessLevelOuter[0] = 16.0;\n"
    "    gl_TessLevelOuter[1] = 16.0;\n"
    "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n";

    std::string tcShaderSource3;
    std::string tcShaderSource_main1;
    for(int i=0; i<num; i++) {
        tcShaderSource3.append("vec4 colors" + std::to_string(i) + ";\n");
        tcShaderSource_main1.append("tcs_out[gl_InvocationID].colors" + std::to_string(i)+"=color[gl_InvocationID]/"
                                +std::to_string(num)+";\n");
    }


    std::string tcShaderSource_s;
    tcShaderSource_s.append(tcShaderSource0);
    tcShaderSource_s.append(tcShaderSource1);
    tcShaderSource_s.append(tcShaderSource2);
    tcShaderSource_s.append(tcShaderSource3);
    tcShaderSource_s.append(tcShaderSourceMain0);
    tcShaderSource_s.append(tcShaderSource_main1+"}\n");
    LOGI("tcShaderSource = %s\n", tcShaderSource_s.c_str());
    const GLchar* tcShaderSource = tcShaderSource_s.c_str();

    const GLchar* teShaderSource =
         "\n#version 430 core\n"
         "layout(isolines, equal_spacing) in;\n"
         "layout(location=0) uniform int verts;\n"
         "vec4 quad_bezier(vec4 A, vec4 B, vec4 C, float t){\n"
         "    vec4 D = mix(A, B, t);\n"
         "    vec4 E = mix(B, C, t);\n"
         "    return mix(D, E, t);\n"
         "}\n\n"
         "vec4 cube_bezier(vec4 A, vec4 B, vec4 C, vec4 D, float t){\n"
         "    vec4 E = mix(A, B, t);\n"
         "    vec4 F = mix(B, C, t);\n"
         "    vec4 G = mix(C, D, t);\n"
         "    return quad_bezier(E, F, G, t);\n"
         "}\n\n"
         "vec4 cube_bezier3(vec4 A, vec4 B, vec4 C, vec4 D, vec4 E, float t){\n"
         "    vec4 I = mix(A, B, t);\n"
         "    vec4 J = mix(B, C, t);\n"
         "    vec4 K = mix(C, D, t);\n"
         "    vec4 L = mix(D, E, t);\n"
         "    return cube_bezier(I, J, K, L, t);\n"
         "}\n\n"
         "vec4 cube_bezier2(vec4 A, vec4 B, vec4 C, vec4 D, vec4 E, vec4 F, float t){\n"
         "    vec4 I = mix(A, B, t);\n"
         "    vec4 J = mix(B, C, t);\n"
         "    vec4 K = mix(C, D, t);\n"
         "    vec4 L = mix(D, E, t);\n"
         "    vec4 M = mix(E, F, t);\n"
         "    return cube_bezier3(I, J, K, L, M, t);\n"
         "}\n\n"
         "vec4 cube_bezier1(vec4 A, vec4 B, vec4 C, vec4 D, vec4 E, vec4 F, vec4 G, float t){\n"
         "    vec4 I = mix(A, B, t);\n"
         "    vec4 J = mix(B, C, t);\n"
         "    vec4 K = mix(C, D, t);\n"
         "    vec4 L = mix(D, E, t);\n"
         "    vec4 M = mix(E, F, t);\n"
         "    vec4 N = mix(F, G, t);\n"
         "    return cube_bezier2(I, J, K, L, M, N, t);\n"
         "}\n\n"
         "vec4 cube_bezier0(vec4 A, vec4 B, vec4 C, vec4 D, vec4 E, vec4 F, vec4 G, vec4 H, float t){\n"
         "    vec4 I = mix(A, B, t);\n"
         "    vec4 J = mix(B, C, t);\n"
         "    vec4 K = mix(C, D, t);\n"
         "    vec4 L = mix(D, E, t);\n"
         "    vec4 M = mix(E, F, t);\n"
         "    vec4 N = mix(F, G, t);\n"
         "    vec4 O = mix(G, H, t);\n"
         "    return cube_bezier1(I, J, K, L, M, N, O, t);\n"
         "}\n\n"
         "vec4 evaluate_patch2(vec2 at){\n"
         "    vec4 P[2];\n"
         "    int i;\n"
         "    for(i = 0; i < 2; i++){\n"
         "        P[i] = cube_bezier(gl_in[i + 0].gl_Position, gl_in[i + 4].gl_Position,\n"
         "                           gl_in[i + 8].gl_Position, gl_in[i + 12].gl_Position, at.y);\n"
         "    }\n"
         "    return mix(P[0], P[1], at.x);\n"
         "}\n\n"
         "vec4 evaluate_patch4(vec2 at){\n"
         "    vec4 P[4];\n"
         "    int i;\n"
         "    for(i = 0; i < 4; i++){\n"
         "        P[i] = cube_bezier(gl_in[i + 0].gl_Position, gl_in[i + 4].gl_Position,\n"
         "                           gl_in[i + 8].gl_Position, gl_in[i + 12].gl_Position, at.y);\n"
         "    }\n"
         "    return cube_bezier(P[0], P[1], P[2], P[3], at.x);\n"
         "}\n\n"
         "vec4 evaluate_patch8(vec2 at){\n"
         "    vec4 P[8];\n"
         "    int i;\n"
         "    for(i = 0; i < 8; i++){\n"
         "        P[i] = cube_bezier(gl_in[i + 0].gl_Position, gl_in[i + 8].gl_Position,\n"
         "                           gl_in[i + 16].gl_Position, gl_in[i + 24].gl_Position, at.y);\n"
         "    }\n"
         "    return cube_bezier0(P[0], P[1], P[2], P[3], P[4], P[5], P[6], P[7], at.x);\n"
         "}\n\n"
    "void main(){\n"
    "    vec4 p1;\n"
    "    if(verts==32){\n"
    "    p1 = evaluate_patch8(gl_TessCoord.xy);\n"
    "    }else if(verts==16){\n"
    "    p1 = evaluate_patch4(gl_TessCoord.xy);\n"
    "    }else if(verts==8){\n"
    "    p1 = evaluate_patch2(gl_TessCoord.xy);\n"
    "    }else if(verts==4){\n"
    "    p1 = cube_bezier(gl_in[0].gl_Position, gl_in[1].gl_Position,\n"
    "        gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);}\n"
    "    gl_Position =  p1;\n"
    "}\n";

    const GLchar* fragmentShaderSource =
        "\n#version 430 core\n"
        "layout(location=0) uniform int verts;\n"
        "out vec4 FragColor;"
        "void main()\n"
        "{\n"
        "    if(verts==32){\n"
        "    FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "    }else if(verts==16){\n"
        "    FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "    }else if(verts==8){\n"
        "    FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
        "    }else if(verts==4){\n"
        "    FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
        "    }\n"
        "}\n";



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
    GL_CHECK(glGetIntegerv(GL_MAX_PATCH_VERTICES, &patch_vertices));
    LOGI("GL_MAX_PATCH_VERTICES = %d\n", patch_vertices);
    GL_CHECK(glGetIntegerv(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS, &total_components));
    LOGI("GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS = %d\n", total_components);

    float vertices[patch_vertices*2];

    int row=patch_vertices/8;
    float rowadd=16.0/patch_vertices;
    for(int i=0; i<row; i++){
        for(int j=0; j<16; j++){

            if((i==0 && j==0) || (i==0 && j==1)){
                vertices[16*i+j]=-0.9;
            }else if(i==0 && j>1 && j%2==1){
                vertices[16*i+j]=vertices[16*i+j-2];
            }else if(i==0 && j>1 && j%4==2){
                vertices[16*i+j]=vertices[16*i+j-2]+0.35;
            }else if(i==0 && j>1 && j%4==0){
                vertices[16*i+j]=vertices[16*i+j-2]+0.1;
            }else if((16*i+j)%2==1) {
                vertices[16*i+j]=vertices[16*i+j-16]+rowadd;
            }else if((16*i+j)%2==0) {
                vertices[16*i+j]=vertices[16*i+j-16];
            }
        }
    }
    for(int m=0; m<patch_vertices*2; m++){
        if(m%16==0)
            printf("\n");
        printf("%f   ", vertices[m]);


    }
    float colors[patch_vertices*2];
    for(int i=0; i<row; i++) {
        for (int j = 0; j < 16; j++) {
            if ((i * 16 + j) % 4 == 0 || (i * 16 + j) % 4 == 3) {
                colors[i * 16 + j] = 1.0;
            } else {
                colors[i * 16 + j] = 0.0;
            }
            printf("%f\n", colors[16*i+j]);
        }
    }
        loadShader();
        GL_CHECK(glGenVertexArrays(1, &VAOs));
        GL_CHECK(glBindVertexArray(VAOs));
        GL_CHECK(glGenBuffers(1, &Buffers));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
        GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
        GL_CHECK(glEnableVertexAttribArray(0));
        GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
        GL_CHECK(glEnableVertexAttribArray(1));

        GL_CHECK(glViewport(0, 0, w, h));

        return true;
    }

void renderFrame() {
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glUniform1i(0, patch_vertices));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, patch_vertices));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, patch_vertices));
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
