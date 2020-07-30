/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file debugmessage.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for debugmessage related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

#include <vector>
#include <string>

using std::string;
using namespace BotsonSDK;
using namespace std;

	static const int MessageId1 = 101;
	static const char *TestMessage1 = "Piglit Message 1";

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
	4,
	4,
	0,
	0,
	0,
};

GLuint programID;

GLint iLocPosition = -1;
GLuint vao;

GLuint uboHandle;
GLuint uboIndex;
GLint uboSize;
GLvoid *buffer;

GLuint tfbuffer;
GLuint tfobj;

void GetFirstNMessages(GLuint numMsgs) {
    GLint maxMsgLen = 0;
    glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);
    std::vector<GLchar>  msgData(numMsgs * maxMsgLen);
    std::vector<GLenum>  sources(numMsgs);
    std::vector<GLenum>  types(numMsgs);
    std::vector<GLenum>  severities(numMsgs);
    std::vector<GLuint>  ids(numMsgs);
    std::vector<GLsizei> lengths(numMsgs);

    GLuint numFound = glGetDebugMessageLog(numMsgs, lengths.size(), &sources[0], &types[0], &ids[0], &severities[0],
                                           &lengths[0], &msgData[0]);
    LOGI("98787985=%s\n", msgData[0]);
    sources.resize(numFound);
    types.resize(numFound);
    severities.resize(numFound);
    ids.resize(numFound);
    lengths.resize(numFound);

    std::vector<std::string> messages;
    messages.reserve(numFound);

    std::vector<GLchar>::iterator currPos = msgData.begin();
    for (size_t                   msg     = 0; msg < lengths.size(); ++msg) {
        messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
        currPos = currPos + lengths[msg];
    }
    //string GEBG_LOG = currPos;
    LOGI("OQOQOQOQOQOQQO=%s\n", msgData[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", lengths[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", severities[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", ids[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", types[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", sources[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", ids[0]);
    LOGI("OQOQOQOQOQOQQO=%s\n", ids[0]);

}






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
	GL_CHECK(glGenBuffers(1,&tfbuffer));
	GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER,tfbuffer));
	GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER,1024*1024,NULL,GL_STATIC_READ));
	GL_CHECK(glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER,0,tfbuffer,0,1024*1024));
}


/*transform feedback object*/
void TFFB_object()
{
	

	GLfloat data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
	GLuint vbo;

	GLfloat feeback[5];
	GL_CHECK(glGenTransformFeedbacks(1,&tfobj));
	GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK,tfobj));
	GL_CHECK(glGenBuffers(1,&vbo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER,vbo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW));
	
	GLint inputAttrib = glGetAttribLocation(programID,"inValue");
	GL_CHECK(glEnableVertexAttribArray(inputAttrib));
	GL_CHECK(glVertexAttribPointer(inputAttrib,1,GL_FLOAT,GL_FALSE,0,0));

	GLuint tbo;
	GL_CHECK(glGenBuffers(1,&tbo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, tbo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(data),NULL,GL_STATIC_READ));
	GL_CHECK(glEnable(GL_RASTERIZER_DISCARD));
	GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,tbo));
	GL_CHECK(glBeginTransformFeedback(GL_POINTS));
	GL_CHECK(glDrawArrays(GL_POINTS,0,5));
	GL_CHECK(glEndTransformFeedback());
	GL_CHECK(glDisable(GL_RASTERIZER_DISCARD));
	GL_CHECK(glFlush());
	GL_CHECK(glBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER,0,sizeof(feeback),feeback));
	LOGI("%f\n %f\n %f\n %f\n %f\n",feeback[0],feeback[1],feeback[2],feeback[3],feeback[4],feeback[5]);
		
}


/*debug callbcak*/
void callback(GLenum source,GLenum type, GLuint id, GLenum serverity, GLsizei length, const GLchar *message, const GLvoid *userParam)
{
	
	LOGI("source is %d:type is %d[%d](%d): %s\n",source,type,serverity,id,message);
}

/* uniform block/buffer*/
void Uniformblock()
{

	GL_CHECK(uboIndex = glGetUniformBlockIndex(programID,"Uniforms"));
	GL_CHECK(glGetActiveUniformBlockiv(programID,uboIndex,GL_UNIFORM_BLOCK_DATA_SIZE,&uboSize));
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
		GL_CHECK(glGetUniformIndices(programID,2,names,indices));
		GL_CHECK(glGetActiveUniformsiv(programID,2,indices,GL_STATIC_DRAW,offset));
		GL_CHECK(glGetActiveUniformsiv(programID,2,indices,GL_UNIFORM_SIZE,size));
		GL_CHECK(glGetActiveUniformsiv(programID,2,indices,GL_UNIFORM_TYPE,type));

		memcpy(buffer + offset[0], &a, sizeof(float));
		memcpy (buffer + offset[1], &b, sizeof(float));
		GL_CHECK(glGenBuffers(1, &uboHandle));
		GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, uboHandle));
		GL_CHECK(glBufferData(GL_UNIFORM_BUFFER,uboSize,buffer,GL_STATIC_DRAW));
		GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER,uboIndex,uboHandle));
		GLfloat value_nuniform[2];


	}



}




GLubyte *blockBuffer;//block buffer
GLenum factors[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES
};

typedef struct {
	GLuint count;
	GLuint instanceCount;
	GLuint first;
	GLuint reservedMustBeZero;
} DrawArraysIndirectCommand;

bool setupGraphics(int width, int height) {
	GLuint vertexID = -1, fragmentID = -1;

	string vertexShaderPath   = (string)GLSL_PATH + "DrawArrayInstance.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "DrawArrayInstance.frag";
	Shader::processShader(&vertexID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	Shader::processShader(&fragmentID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
	programID       = GL_CHECK(glCreateProgram());
	if (!programID) {
		LOGE("Could not create program.");
		return false;
	}
	GL_CHECK(glAttachShader(programID, vertexID));
	GL_CHECK(glAttachShader(programID, fragmentID));
	const GLchar *feedbackVaryings[] = {"outValue"};
	GL_CHECK(glTransformFeedbackVaryings(programID, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS));
	GL_CHECK(glLinkProgram(programID));
	GL_CHECK(glUseProgram(programID));

	//TFFB_object();	






	GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));

	GL_CHECK(glViewport(0, 0, width, height));

	GLuint vertices_bo;
	GLuint indices_bo;
	GLuint indirect_bo;

	GL_CHECK(glGenVertexArrays(1, &vao));
	GL_CHECK(glBindVertexArray(vao));
	GL_CHECK(glGenBuffers(1, &vertices_bo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertices_bo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));
	GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glGenBuffers(1, &indices_bo));
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_bo));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_data), indices_data, GL_STATIC_DRAW));
	GL_CHECK(glGenBuffers(1, &indirect_bo));
	GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_bo));
	GL_CHECK(glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(indirect_data), indirect_data, GL_STATIC_DRAW));
	/*creat UNIFORM BUFFER*/



	GL_CHECK(glBindVertexArray(0));

	return true;
}

void renderFrame(GLenum factor) {
	GL_CHECK(glClearColor(0, 0, 1, 1));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glBindVertexArray(vao));
	GL_CHECK(glUseProgram(programID));
	Uniformblock();
	//atomic();

	glDrawElementsIndirect(factor, GL_UNSIGNED_SHORT, (GLvoid const *)0);
	GLint actNUM;

	glGetProgramInterfaceiv(programID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_UNIFORM,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_UNIFORM_BLOCK,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_ATOMIC_COUNTER_BUFFER, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_ATOMIC_COUNTER_BUFFER,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_PROGRAM_INPUT,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_PROGRAM_OUTPUT,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_TRANSFORM_FEEDBACK_VARYING, GL_ACTIVE_RESOURCES, &actNUM);
	LOGI("glGetProgramInterfaceiv(GL_TRANSFORM_FEEDBACK_VARYING,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_BUFFER_VARIABLE, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_BUFFER_VARIABLE,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &actNUM);
	LOGI("glGetProgramInterfaceiv(GL_SHADER_STORAGE_BLOCK,GL_ACTIVE_RESOURCES) = %d\n", actNUM);

	glGetProgramInterfaceiv(programID, GL_TRANSFORM_FEEDBACK_BUFFER, GL_ACTIVE_RESOURCES, &actNUM);//
	LOGI("glGetProgramInterfaceiv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_ACTIVE_RESOURCES) = %d\n", actNUM);
	float value_uniform;
	float value_vecunifor[2];
	int   value_int;
	uint  value_uint;
	GLint f = glGetUniformLocation(programID, "resourcet_1");
	glProgramUniform1f(programID, f, 1.0);
	glGetnUniformfv(programID, f, sizeof(float), &value_uniform);
	LOGI("resourcet_1 index get from glGetUniformLocation = %d\n   value!!!!!!!!!!!!! is =%f\n", f, value_uniform);

	GLint q = glGetUniformLocation(programID, "resourcet_3");
	glProgramUniform2f(programID, q, 1.0, 0.5);

	glGetnUniformfv(programID, q, 2 * sizeof(float), value_vecunifor);
	LOGI("resourcet_1 index get from glGetUniformLocation = %d\n   glGetnUniformfv!!!!!!!!!!!!! is =%f    %f\n", q,
		 &value_vecunifor[0], value_vecunifor[1]);

	GLint w = glGetUniformLocation(programID, "valu_int");
	glProgramUniform1i(programID, w, 1);
	LOGI("valu_int index get from glGetUniformLocation = %d\n", w);
	glGetnUniformiv(programID, w, sizeof(int), &value_int);
	LOGI("valu_int index get from glGetUniformLocation = %d\n   glGetnUniformiv!!!!!!!!!!!!! is =%lu \n", w, value_int);

	GLint z = glGetUniformLocation(programID, "valu_ulint");
	glProgramUniform1ui(programID, z, 1);
	LOGI("valu_ulint index get from glGetUniformLocation = %d\n", w);
	glGetnUniformuiv(programID, z, sizeof(uint), &value_uint);
	LOGI("valu_ulint index get from glGetUniformLocation = %d\n   glGetnUniformiv!!!!!!!!!!!!! is =%lu \n", z,
		 value_uint);

	GLint m = glGetUniformLocation(programID, "resourcet_2");
	glProgramUniform1f(programID, m, 1.0);
	LOGI("resourcet_1 index get from glGetUniformLocation = %d\n", m);

	const char *names[] = {"resourcet_1", "resourcet_2", "Uniforms", "inValue", "FragColor", "outValue", "inValue"};

	/*glGetProgramResourceIndex*/
	GLuint uniform_t1 = glGetProgramResourceIndex(programID, GL_UNIFORM, names[0]);
	LOGI("resourcet_1 index get from glGetProgramResourceIndex = %d\n", uniform_t1);

	GLuint uniform_t2 = glGetProgramResourceIndex(programID, GL_UNIFORM, names[1]);
	LOGI("resourcet_2 index get from glGetProgramResourceIndex = %d\n", uniform_t2);

	GLuint uniform__block = glGetProgramResourceIndex(programID, GL_UNIFORM_BLOCK, names[2]);
	LOGI("uniform__block index get from glGetProgramResourceIndex = %d\n", uniform__block);

	GLuint input = glGetProgramResourceIndex(programID, GL_PROGRAM_INPUT, names[3]);
	LOGI("input index get from glGetProgramResourceIndex = %d\n", input);

	GLuint output = glGetProgramResourceIndex(programID, GL_PROGRAM_OUTPUT, names[4]);
	LOGI("output index get from glGetProgramResourceIndex = %d\n", output);

	GLuint transVarying = glGetProgramResourceIndex(programID, GL_TRANSFORM_FEEDBACK_VARYING, names[5]);
	LOGI("transVarying index get from glGetProgramResourceIndex = %d\n", transVarying);

	GLuint transBuffer = glGetProgramResourceIndex(programID, GL_TRANSFORM_FEEDBACK_BUFFER, names[6]);
	LOGI("transBuffer index get from glGetProgramResourceIndex = %d\n", transBuffer);
	/*glGetProgramResourceName*/
	GLchar name_prn[64];
	int    i           = 0;
	glGetProgramResourceName(programID, GL_UNIFORM, 2, sizeof(name_prn), NULL, name_prn);
	LOGI("the name of uniform which index is 2 is = %s\n", name_prn);
	memset(name_prn, 0, 64);
	glGetProgramResourceName(programID, GL_PROGRAM_INPUT, 1, sizeof(name_prn), NULL, name_prn);
	LOGI("the name of INput which index is 2 is = %s\n", name_prn);

	memset(name_prn, 0, 64);
	glGetProgramResourceName(programID, GL_PROGRAM_OUTPUT, 0, sizeof(name_prn), NULL, name_prn);
	LOGI("the name of GL_PROGRAM_OUTPUT which index is 2 is = %s\n", name_prn);

	memset(name_prn, 0, 64);
	glGetProgramResourceName(programID, GL_UNIFORM_BLOCK, 0, sizeof(name_prn), NULL, name_prn);
	LOGI("the name of GL_UNIFORM_BLOCK which index is 2 is = %s\n", name_prn);

	memset(name_prn, 0, 64);
	glGetProgramResourceName(programID, GL_TRANSFORM_FEEDBACK_VARYING, 0, sizeof(name_prn), NULL, name_prn);
	LOGI("the name of GL_TRANSFORM_FEEDBACK_VARYING which index is 2 is = %s\n", name_prn);

	/*glGetprogramResourceiv*/
	GLint  params[64];
	GLenum props[]     = {GL_TYPE, GL_ARRAY_SIZE, GL_REFERENCED_BY_VERTEX_SHADER, GL_REFERENCED_BY_FRAGMENT_SHADER,
						  GL_REFERENCED_BY_COMPUTE_SHADER, GL_LOCATION, GL_NAME_LENGTH};
	//GLenum props_1[] = {GL_ARRAY_SIZE};		

	glGetProgramResourceiv(programID, GL_PROGRAM_INPUT, 0, 7, props, 64, NULL, params);

	LOGI("glGetProgramResourceiv GL_TYPE is = %d\n", params[0]);
	LOGI("glGetProgramResourceiv GL_ARRAY_SIZE is = %d\n", params[1]);
	LOGI("glGetProgramResourceiv GL_REFERENCED_BY_VERTEX_SHADER is = %d\n", params[2]);
	LOGI("glGetProgramResourceiv GL_REFERENCED_BY_FRAGMENT_SHADER is = %d\n", params[3]);
	LOGI("glGetProgramResourceiv GL_REFERENCED_BY_COMPUTE_SHADER is = %d\n", params[4]);
	LOGI("glGetProgramResourceiv GL_LOCATION is = %d\n", params[5]);
	LOGI("glGetProgramResourceiv GL_NAME_LENGTH is = %d\n \n", params[6]);
	memset(params, 0, 64);

	GLenum uprops[] = {GL_OFFSET, GL_BLOCK_INDEX, GL_ARRAY_STRIDE, GL_MATRIX_STRIDE, GL_IS_ROW_MAJOR,
					   GL_ATOMIC_COUNTER_BUFFER_INDEX, GL_BUFFER_BINDING, GL_BUFFER_DATA_SIZE, GL_NUM_ACTIVE_VARIABLES,
					   GL_ACTIVE_VARIABLES};
	glGetProgramResourceiv(programID, GL_UNIFORM, 0, 10, uprops, 64, NULL, params);
	for (i = 0; i < 10; i++) {
		LOGI("glGetProgramResourceiv GL_UNIFORM is = %d\n", params[i]);
	}
}

static void insert_inheritance_messages()
{
	glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,GL_DEBUG_TYPE_MARKER,MessageId1,GL_DEBUG_SEVERITY_NOTIFICATION,-1,TestMessage1);
}


void Sample::test() {
	GLint flags;
	const GLuint *log1;
	GLsizei *bufsize_log = (GLsizei *)malloc(256);
	GLsizei buf_strel = 1024;
	char address[10][10] ;
	GL_CHECK(glEnable(GL_DEBUG_OUTPUT));
	GL_CHECK(glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION,1,-1,"push_pop test"));
	GL_CHECK(glDebugMessageControl(GL_DEBUG_SOURCE_APPLICATION,GL_DEBUG_TYPE_OTHER,GL_DONT_CARE,
                                   256,log1,GL_TRUE));
	GL_CHECK(insert_inheritance_messages());
	GL_CHECK(glPopDebugGroup());
	GL_CHECK(insert_inheritance_messages());

	setupGraphics(WINDOW_W, WINDOW_H);

	GL_CHECK(glGetIntegerv(GL_CONTEXT_FLAGS,&flags));
	LOGI("GL_CONTEXT_FLAGS is=%d\n", flags);
	GL_CHECK(glDebugMessageCallback(callback,NULL));
	GL_CHECK(glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,GL_DEBUG_TYPE_ERROR,1000,GL_DEBUG_SEVERITY_HIGH,-1,"ERROR:MY APPLICATION GENERATED AN ERROR!"));
	GL_CHECK(glGetPointerv(GL_DEBUG_CALLBACK_FUNCTION,(void**)address));
	LOGI("wwwwwwwwwwwwww=%d\n", address[0][0]);
	GetFirstNMessages(5);

	for(int i=0; i<ARRAY_NUM(factors); i++) {
		renderFrame(factors[i]);
		string mode_name = get_enum_name(factors[i]);
		string bmp_file  = filename + mode_name + ".bmp";
		LOGI("bmp_file=%s", bmp_file.c_str());
		save2bmp(bmp_file.c_str());
		Sample::SwapBuffers();
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

//int main(int argc, char **argv)
//{
//    	string file = "es32-debugmessage";
//	GLint flags;
// 	const GLuint *log;
//	GLsizei *bufsize_log = (GLsizei *)malloc(256);
//	GLsizei buf_strel = 1024;
//	char address[10][10] ;
//	glEnable(GL_DEBUG_OUTPUT);
//	glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION,1,-1,"push_pop test");
//
//	glDebugMessageControl(GL_DEBUG_SOURCE_APPLICATION,GL_DONT_CARE,GL_DONT_CARE,256,log,GL_TRUE);
//	insert_inheritance_messages();
//	glPopDebugGroup();
//	insert_inheritance_messages();
//	/*glPush,glPop*/
//
//    	GBtest_init(&argc,argv,file);
//    	Platform * platform = Platform::getInstance();
//    	platform->createWindow(WINDOW_W, WINDOW_H);
//    	EGLRuntime::initializeEGL(EGLRuntime::OPENGLES32);
//    	EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
//    	setupGraphics(WINDOW_W, WINDOW_H);
//    	glGetIntegerv(GL_CONTEXT_FLAGS,&flags);
//	LOGI("GL_CONTEXT_FLAGS is=%d\n", flags);
//	glDebugMessageCallback(callback,NULL);
//	glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,GL_DEBUG_TYPE_ERROR,1000,GL_DEBUG_SEVERITY_HIGH,-1,"ERROR:MY APPLICATION GENERATED AN ERROR!");
//	//glDebugMessageCallback(NULL,NULL);
//	glGetPointerv(GL_DEBUG_CALLBACK_FUNCTION,(void**)address);
//	LOGI("wwwwwwwwwwwwww=%d\n", address[0][0]);
//	GetFirstNMessages(5);
//	//glGetDebugMessageLog(1,buf_strel,&debug_source[0],NULL,NULL,&debug_severities[0],&debug_length[0],&debug_log[0]);
//	//LOGI("OQOQOQOQOQOQQO=%s\n", &debug_log[0]);
//
//#ifndef DUMP
//    while(1) {
//#endif
//        renderFrame(factors[1]);
//        string filename = file + ".bmp";
//        EGLRuntime::pixelsToPicture(filename.c_str());
//	eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
//#ifndef DUMP
//    }
//#endif
//
//    	EGLRuntime::terminateEGL();
//    	platform->destroyWindow();
//    	delete platform;
//    	GBtest_deinit();
//
//    	return 0;
//}
//