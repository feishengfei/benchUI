/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file getprogramInterfaceiv.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for getprogramInterfaceiv related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
//#include <GLES3/gl31.h>

using std::string;
using namespace BotsonSDK;
using namespace std;

float vertices_data[] = {
	-0.8, -0.8,
	 0.8, -0.8,
	-0.8,  0.8,
	 0.8,  0.8,
};

unsigned short indices_data[] = {
	0, 1, 2, 3,
};

GLuint indirect_data[] = {
	4,		/* count */
	4,		/* primcount */
	0,		/* first index */
	0,		/* base vertex */
	0,		/* mbz */
};

GLuint programID;

GLint iLocPosition = -1;
GLuint vao;

/*uniform block*/
GLuint uboHandle;
GLuint uboIndex;
GLint uboSize;
GLvoid *buffer;

/*transform feedback*/
GLuint tfbuffer;
GLuint tfobj;

/*atomic counter buffer*/
/*GLuint m_atomicbuffer;
GLuint *userCounters;

/*atomic counter buffer*/
/*void atomic()
{
	glGenBuffers(1,&m_atomicbuffer);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER,m_atomicbuffer);
	glBufferData(GL_ATOMIC_COUNTER_BUFFER,sizeof(GLuint)*3,NULL,GL_DYNAMIC_DRAW);
	userCounters = (GLuint*)glMapBufferRange(GL_ATOMIC_COUNTER_BUFFER,0,sizeof(GLuint)*3,GL_MAP_WRITE_BIT|GL_MAP_UNSYNCHRONIZED_BIT);
	memset(userCounters,0,sizeof(GLuint)*3);
}

/*transform feedback buffer*/
void TFFB_buffer()
{
	glGenBuffers(1,&tfbuffer);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER,tfbuffer);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER,1024*1024,NULL,GL_STATIC_READ);
	glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER,0,tfbuffer,0,1024*1024);
}

/*transform feedback object*/
void TFFB_object() {
	GLfloat data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
	GLuint  vbo;
	//TFFB_buffer();
	GLfloat feeback[5];
	glGenTransformFeedbacks(1, &tfobj);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfobj);
	//glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER);
	/*creste input VBO adn vertex format*/
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	GLint inputAttrib = glGetAttribLocation(programID, "inValue");
	glEnableVertexAttribArray(inputAttrib);
	glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);
/*creat transform feedback buffer*/
	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), NULL, GL_STATIC_READ);
	/*creat transform feedback buffer*/
	glEnable(GL_RASTERIZER_DISCARD);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, 5);
	glEndTransformFeedback();
	glDisable(GL_RASTERIZER_DISCARD);
	glFlush();
	glBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feeback), feeback);
	LOGI("%f\n %f\n %f\n %f\n %f\n", feeback[0], feeback[1], feeback[2], feeback[3],
		 feeback[4], feeback[5]);

}



/* uniform block/buffer*/
void Uniformblock()
{

	uboIndex = glGetUniformBlockIndex(programID,"Uniforms");
	glGetActiveUniformBlockiv(programID,uboIndex,GL_UNIFORM_BLOCK_DATA_SIZE,&uboSize);
	buffer = malloc(uboSize);
	if(buffer == NULL){
		LOGE("malloc fail for uniformbuffer!");
		exit(EXIT_FAILURE);	
	}
	else
	{
		enum {A,B};
		float a = 0;
		float b = 1;
		const char * names[2] = {
			"a",
			"b"
		};
		GLuint indices[2];
		GLint size[2];
		GLint offset[2];
		GLint type[2];
		glGetUniformIndices(programID,2,names,indices);
		glGetActiveUniformsiv(programID,2,indices,GL_UNIFORM_OFFSET,offset);
		glGetActiveUniformsiv(programID,2,indices,GL_UNIFORM_SIZE,size);
		glGetActiveUniformsiv(programID,2,indices,GL_UNIFORM_TYPE,type);

		memcpy(buffer + offset[0], &a, sizeof(float));
		memcpy (buffer + offset[1], &b, sizeof(float));
		glGenBuffers(1, &uboHandle);
		glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
		glBufferData(GL_UNIFORM_BUFFER,uboSize,buffer,GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER,uboIndex,uboHandle);
	}
}

typedef struct {
	GLuint count;
	GLuint instanceCount;
	GLuint first;
	GLuint reservedMustBeZero;
} DrawArraysIndirectCommand;

bool setupGraphics(int width, int height)
{
	string vertexShaderPath = (string)GLSL_PATH + "DrawArrayInstance.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "DrawArrayInstance.frag";


        GLuint vertexID=-1, fragmentID=-1;
       
 
         Shader::processShader(&vertexID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
         Shader::processShader(&fragmentID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
         programID = GL_CHECK(glCreateProgram());
         if (!programID)
         {
             LOGE("Could not create program.");
             return false;
         }
         GL_CHECK(glAttachShader(programID, vertexID));
         GL_CHECK(glAttachShader(programID, fragmentID));
         const GLchar* feedbackVaryings[] = {"outValue"};
	 glTransformFeedbackVaryings(programID, 1 , feedbackVaryings,GL_INTERLEAVED_ATTRIBS);
       	 GL_CHECK(glLinkProgram(programID));
	 GL_CHECK(glUseProgram(programID));
	
	GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));

	GL_CHECK(glViewport(0, 0, width, height));

	GLuint vertices_bo;
	GLuint indices_bo;
	GLuint indirect_bo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertices_bo);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_bo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(iLocPosition);
	glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &indices_bo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_bo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_data), indices_data, GL_STATIC_DRAW);

	glGenBuffers(1, &indirect_bo);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_bo);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(indirect_data), indirect_data, GL_STATIC_DRAW);
	/*creat UNIFORM BUFFER*/
	
	

	glBindVertexArray(0);

	return true;
}

void renderFrame()
{
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);
	GL_CHECK(glUseProgram(programID));
	Uniformblock();
	//atomic();

	glDrawElementsIndirect(GL_LINE_STRIP, GL_UNSIGNED_SHORT, (GLvoid const *)0);
    GLint actNUM;

  glGetProgramInterfaceiv(programID,GL_UNIFORM,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_UNIFORM,GL_ACTIVE_RESOURCES) = %d\n",actNUM);
     
    glGetProgramInterfaceiv(programID,GL_UNIFORM_BLOCK,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_UNIFORM_BLOCK,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

    glGetProgramInterfaceiv(programID,GL_ATOMIC_COUNTER_BUFFER,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_ATOMIC_COUNTER_BUFFER,GL_ACTIVE_RESOURCES) = %d\n",actNUM);   

    glGetProgramInterfaceiv(programID,GL_PROGRAM_INPUT,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_PROGRAM_INPUT,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

    glGetProgramInterfaceiv(programID,GL_PROGRAM_OUTPUT,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_PROGRAM_OUTPUT,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

    glGetProgramInterfaceiv(programID,GL_TRANSFORM_FEEDBACK_VARYING,GL_ACTIVE_RESOURCES,&actNUM);
    LOGI("glGetProgramInterfaceiv(GL_TRANSFORM_FEEDBACK_VARYING,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

    glGetProgramInterfaceiv(programID,GL_BUFFER_VARIABLE,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_BUFFER_VARIABLE,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

    glGetProgramInterfaceiv(programID,GL_SHADER_STORAGE_BLOCK,GL_ACTIVE_RESOURCES,&actNUM);
    LOGI("glGetProgramInterfaceiv(GL_SHADER_STORAGE_BLOCK,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

    glGetProgramInterfaceiv(programID,GL_TRANSFORM_FEEDBACK_BUFFER,GL_ACTIVE_RESOURCES,&actNUM);//
    LOGI("glGetProgramInterfaceiv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_ACTIVE_RESOURCES) = %d\n",actNUM);

	GLint f = glGetUniformLocation(programID, "resourcet_1");	
	glProgramUniform1f(programID, f, 1.0);
	LOGI("resourcet_1 index get from glGetUniformLocation = %d\n",f);

	GLint m = glGetUniformLocation(programID, "resourcet_2");	
	glProgramUniform1f(programID, m, 1.0);
	LOGI("resourcet_1 index get from glGetUniformLocation = %d\n",m);	

	const char * names[] ={"resourcet_1","resourcet_2","Uniforms","inValue","FragColor","outValue","inValue"};

	/*glGetProgramResourceIndex*/
	GLuint uniform_t1 = glGetProgramResourceIndex(programID,GL_UNIFORM,names[0]);
	LOGI("resourcet_1 index get from glGetProgramResourceIndex = %d\n",uniform_t1);

	GLuint uniform_t2 = glGetProgramResourceIndex(programID,GL_UNIFORM,names[1]);
	LOGI("resourcet_2 index get from glGetProgramResourceIndex = %d\n",uniform_t2);

	GLuint uniform__block = glGetProgramResourceIndex(programID,GL_UNIFORM_BLOCK,names[2]);
	LOGI("uniform__block index get from glGetProgramResourceIndex = %d\n",uniform__block);

	GLuint input = glGetProgramResourceIndex(programID,GL_PROGRAM_INPUT,names[3]);
	LOGI("input index get from glGetProgramResourceIndex = %d\n",input);

	GLuint output = glGetProgramResourceIndex(programID,GL_PROGRAM_OUTPUT,names[4]);
	LOGI("output index get from glGetProgramResourceIndex = %d\n",output);
	
	GLuint transVarying = glGetProgramResourceIndex(programID,GL_TRANSFORM_FEEDBACK_VARYING,names[5]);
	LOGI("transVarying index get from glGetProgramResourceIndex = %d\n",transVarying);
	
	GLuint transBuffer = glGetProgramResourceIndex(programID,GL_TRANSFORM_FEEDBACK_BUFFER,names[6]);
	LOGI("transBuffer index get from glGetProgramResourceIndex = %d\n",transBuffer);
	/*glGetProgramResourceName*/
	GLchar name_prn[64];
	int i =0;
	glGetProgramResourceName(programID,GL_UNIFORM,2,sizeof(name_prn),NULL,name_prn);
	LOGI("the name of uniform which index is 2 is = %s\n",name_prn);
	memset(name_prn,0,64);
	glGetProgramResourceName(programID,GL_PROGRAM_INPUT,1,sizeof(name_prn),NULL,name_prn);
	LOGI("the name of INput which index is 2 is = %s\n",name_prn);
	
	memset(name_prn,0,64);
	glGetProgramResourceName(programID,GL_PROGRAM_OUTPUT,0,sizeof(name_prn),NULL,name_prn);
	LOGI("the name of GL_PROGRAM_OUTPUT which index is 2 is = %s\n",name_prn);	

	memset(name_prn,0,64);
	glGetProgramResourceName(programID,GL_UNIFORM_BLOCK,0,sizeof(name_prn),NULL,name_prn);
	LOGI("the name of GL_UNIFORM_BLOCK which index is 2 is = %s\n",name_prn);
	
	memset(name_prn,0,64);
	glGetProgramResourceName(programID,GL_TRANSFORM_FEEDBACK_VARYING,0,sizeof(name_prn),NULL,name_prn);
	LOGI("the name of GL_TRANSFORM_FEEDBACK_VARYING which index is 2 is = %s\n",name_prn);

	/*glGetprogramResourceiv*/
	GLint params[64];
	GLenum props[] = {GL_TYPE,GL_ARRAY_SIZE,GL_REFERENCED_BY_VERTEX_SHADER,GL_REFERENCED_BY_FRAGMENT_SHADER,GL_REFERENCED_BY_COMPUTE_SHADER,GL_LOCATION,GL_NAME_LENGTH};
	//GLenum props_1[] = {GL_ARRAY_SIZE};		

	glGetProgramResourceiv(programID,GL_PROGRAM_INPUT,0,7,props,64,NULL,params);
	
	LOGI("glGetProgramResourceiv GL_TYPE is = %d\n",params[0]);
	LOGI("glGetProgramResourceiv GL_ARRAY_SIZE is = %d\n",params[1]);
	LOGI("glGetProgramResourceiv GL_REFERENCED_BY_VERTEX_SHADER is = %d\n",params[2]);
	LOGI("glGetProgramResourceiv GL_REFERENCED_BY_FRAGMENT_SHADER is = %d\n",params[3]);
	LOGI("glGetProgramResourceiv GL_REFERENCED_BY_COMPUTE_SHADER is = %d\n",params[4]);
	LOGI("glGetProgramResourceiv GL_LOCATION is = %d\n",params[5]);
	LOGI("glGetProgramResourceiv GL_NAME_LENGTH is = %d\n \n",params[6]);
	memset(params,0,64);

	GLenum uprops[] = {GL_OFFSET,GL_BLOCK_INDEX,GL_ARRAY_STRIDE,GL_MATRIX_STRIDE,GL_IS_ROW_MAJOR,GL_ATOMIC_COUNTER_BUFFER_INDEX,GL_BUFFER_BINDING,GL_BUFFER_DATA_SIZE,GL_NUM_ACTIVE_VARIABLES,GL_ACTIVE_VARIABLES};
	glGetProgramResourceiv(programID,GL_UNIFORM,0,10,uprops,64,NULL,params);
	for(i=0;i<10;i++){
	LOGI("glGetProgramResourceiv GL_UNIFORM is = %d\n",params[i]);
	}
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	renderFrame();
	string bmp_file  = filename + ".bmp";
	LOGI("bmp_file=%s", bmp_file.c_str());
	save2bmp(bmp_file.c_str());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

//int main(int argc, char **argv)
//{
//    string file = "es31-getprogramresourceiv";
//
//    GBtest_init(&argc,argv,file);
//    Platform * platform = Platform::getInstance();
//    platform->createWindow(WINDOW_W, WINDOW_H);
//    EGLRuntime::initializeEGL(EGLRuntime::OPENGLES31);
//    EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
//    setupGraphics(WINDOW_W, WINDOW_H);
//#ifndef DUMP
//    while(1) {
//#endif
//        renderFrame();
//        string filename = file + ".bmp";
//        EGLRuntime::pixelsToPicture(filename.c_str());
//	    eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
//#ifndef DUMP
//    }
//#endif
//    EGLRuntime::terminateEGL();
//    platform->destroyWindow();
//    delete platform;
//    GBtest_deinit();
//
//    return 0;
//}
//