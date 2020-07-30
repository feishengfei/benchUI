
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
};
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
};

const unsigned int SRC_WIDTH = 480;
const unsigned int SRC_HEIGHT = 320;

GLenum glCheckError_(const char *file, int line){
    GLenum errorCode;
    while((errorCode = glGetError()) != GL_NO_ERROR){
        char* error;
        switch(errorCode){
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        printf("%s - %s - %d\n", error, file, line);
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__);

void APIENTRY glDebugOutPut(GLenum source, GLenum type, GLuint id, GLenum severity,
                            GLsizei length, const GLchar *message, const void *userParam){
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    printf("--------------------------------------------\n");
    printf("Debug message(%d):%s\n", id, message);

    switch(source){
    case GL_DEBUG_SOURCE_API:
        printf("Source:API");
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        printf("Source:Window System");
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        printf("Source:Shader Compiler");
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        printf("Source:Third Party");
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        printf("Source:Application");
        break;
    case GL_DEBUG_SOURCE_OTHER:
        printf("Source:Other");
        break;
    }
    printf("\n");

    switch(type){
    case GL_DEBUG_TYPE_ERROR:
        printf("Type:Error");
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        printf("Type:Deprecated Behavior");
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        printf("Type:Undefined Behavior");
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        printf("Type:Portability");
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        printf("Type:Performance");
        break;
    case GL_DEBUG_TYPE_MARKER:
        printf("Type:Marker");
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        printf("Type:Push Group");
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        printf("Type:Pop Group");
        break;
    case GL_DEBUG_TYPE_OTHER:
        printf("Type:Other");
        break;
    }
    printf("\n");

    switch(type){
    case GL_DEBUG_SEVERITY_HIGH:
        printf("Severity:High");
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        printf("Severity:Medium");
        break;
    case GL_DEBUG_SEVERITY_LOW:
        printf("Severity:Low");
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        printf("Severity:Notification");
        break;
    }
    printf("\n");
    printf("\n");
}

void init_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Gears", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window) {
        printf("Failed to open GLFW window\n");
        glfwTerminate();
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    printf("flag = %d\n", flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        printf("debug mode is ok\n");
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "Test Message");
        glDebugMessageCallback(glDebugOutPut, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0X4752414A, GL_DEBUG_SEVERITY_LOW, -1,
                             "Test Message");
        glPopDebugGroup();
    }
}
int main() {
    init_glfw();
   glViewport(0, 0,480, 320);
   glCheckError();
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glCheckError();
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   glCheckError();
}
