/**
 * @file gl32-ProvokingVertex.cpp
 * @testpoint glProvokingVertex
 *
 * funName : glProvokingVertex
 * funParam : GL_FIRST_VERTEX_CONVENTION | GL_LAST_VERTEX_CONVENTION
 * funDescriptor :Specifies the vertex to be used as the source of data for flat shaded varyings.  
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

static const GLenum factors[] = { 
        GL_POINTS,
        GL_LINE_STRIP,
        GL_LINE_LOOP,
        GL_LINES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
        GL_TRIANGLES,
        GL_QUAD_STRIP,
        GL_QUADS,
        GL_POLYGON 
};

static const GLenum types[] = {
        GL_FIRST_VERTEX_CONVENTION,
        GL_LAST_VERTEX_CONVENTION
};

GLfloat vertices[] = { 
	-1.0f, 0.5f, 0.0f,
	-0.6f, -0.5f, 0.0f,
	-0.2f, 0.5f, 0.0f,
        0.2f, -0.5, 0.0f,
        0.6f, 0.5f, 0.0f,
        1.0f, -0.5f, 0.0f
}; 

GLfloat colors[] = { 
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
}; 


GLuint programID, VAOs, Buffers;


void setupGraphics()
{
         /*load shader*/
    string vertexShaderPath = (string)GLSL_PATH + "Sync.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "Sync.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
} 

void renderFrame(GLenum mode, GLenum type)
{
    GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f)); 
    GL_CHECK(glProvokingVertex(type));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT)); 
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttrib1f(1, 1.0));
    GL_CHECK(glDrawArrays(mode, 0, 6)); 
    GL_CHECK(glFlush());
}

void Sample::test() {
    //for (int i = 0; i < ARRAY_NUM(factors); i++) {
    //    for (int j = 0; j < ARRAY_NUM(types); j++) {
    //        string src_name  = get_primitives_name(factors[i]);
    //        string type_name = get_enum_name(types[j]);
    //        string bmp_file  = filename + "-" + src_name + "-" + type_name.c_str() + ".bmp";
    //        LOGI("[]: filename=%s\n", bmp_file.c_str());
    //        setupGraphics();
    //        renderFrame(factors[i], types[j]);
    //        save2bmp(bmp_file.c_str());
    //        SwapBuffers();
    //    }
    //}
    string bmp_file  = filename + "bmp";
    LOGI("filename=%s\n", bmp_file.c_str());
    setupGraphics();
    renderFrame(factors[5], types[0]);
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}