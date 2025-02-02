/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file points.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for points related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

float vertices[] = {
	 0.402940, -0.123799, -0.123799,
	 -0.052273, 0.926691, 0.926691,
	 0.404230, -1.007278, -1.007278,
	 -1.874750, 1.475374, 1.475374,
	 -1.675412, -1.491210, -1.491210,
	 -1.586881, 1.367032, 1.367032,
	 -0.481991, -1.396949, -1.396949,
	 -0.033564, -1.317676, -1.317676,
	 -0.416637, -1.894860, -1.894860,
	 -0.947413, -1.875706, -1.875706,
	 1.332690, 0.427233, 0.427233,
	 -0.530595, -1.525039, -1.525039,
	 -0.999227, 0.779191, 0.779191,
	 1.184732, 0.804441, 0.804441,
	 -0.031963, 1.029028, 1.029028,
	 -1.792508, 1.342148, 1.342148,
	 0.234701, -1.039843, -1.039843,
	 1.782847, 0.826593, 0.826593,
	 0.204928, -1.490043, -1.490043,
	 1.408582, -0.537456, -0.537456,
	 1.831807, -1.104766, -1.104766,
	 0.231233, 0.264639, 0.264639,
	 1.457351, 1.165412, 1.165412,
	 -0.223809, 0.450145, 0.450145,
	 1.470405, -1.481818, -1.481818,
	 -0.226592, -1.374326, -1.374326,
	 1.343444, 0.760375, 0.760375,
	 -0.383470, 0.643222, 0.643222,
	 -1.528059, -1.051850, -1.051850,
	 1.132491, -1.543268, -1.543268,
	 0.017335, -1.611461, -1.611461,
	 1.229412, 0.519773, 0.519773,
	 -0.983550, 0.077124, 0.077124,
	 -0.517321, 1.753315, 1.753315,
	 -1.146651, 1.323720, 1.323720,
	 1.153047, -0.802872, -0.802872,
	 -0.905108, -1.359428, -1.359428,
	 1.696895, 0.157102, 0.157102,
	 -0.574508, 0.529043, 0.529043,
	 1.364045, -0.238466, -0.238466,
	 0.865142, 1.678869, 1.678869,
	 1.161473, 1.008281, 1.008281,
	 -0.177556, -1.875268, -1.875268,
	 1.548827, -0.492589, -0.492589,
	 1.825355, 0.260760, 0.260760,
	 -1.279936, -0.486194, -0.486194,
	 -0.059552, 0.508699, 0.508699,
	 0.021208, 0.305594, 0.305594,
	 -1.154811, 1.631086, 1.631086,
	 -1.482681, 1.095131, 1.095131,
	 -1.453818, 0.060272, 0.060272,
	 -1.136416, -0.678255, -0.678255,
	 1.600758, 1.044189, 1.044189,
	 -1.284943, 0.693016, 0.693016,
	 -0.517329, 0.618370, 0.618370,
	 -0.325995, 1.238434, 1.238434,
	 0.962468, -0.721117, -0.721117,
	 -1.008498, 1.200090, 1.200090,
	 -0.922361, -1.854721, -1.854721,
	 1.592818, -1.437402, -1.437402,
	 -1.830469, -0.991220, -0.991220,
	 -1.674887, -0.227636, -0.227636,
	 1.388976, -0.526877, -0.526877,
	 0.677571, 0.088180, 0.088180,
	 1.373576, 1.470851, 1.470851,
	 0.430341, -0.755144, -0.755144,
	 0.900913, -1.692676, -1.692676,
	 -0.019817, -0.801174, -0.801174,
};
float colors[] = {
	 0.849617, 0.591794, 0.979006, 0.100263,
	 0.519041, 0.188569, 0.240229, 0.483898,
	 0.403807, 0.754497, 0.588825, 0.777659,
	 0.658126, 0.467793, 0.225106, 0.287847,
	 0.178270, 0.695991, 0.674134, 0.948435,
	 0.594350, 0.685662, 0.605514, 0.850556,
	 0.540504, 0.368888, 0.914604, 0.638393,
	 0.814195, 0.274852, 0.642836, 0.626457,
	 0.766646, 0.621842, 0.754048, 0.206318,
	 0.710411, 0.894277, 0.721195, 0.015798,
	 0.648775, 0.310020, 0.814111, 0.229890,
	 0.677813, 0.939217, 0.565963, 0.728981,
	 0.635208, 0.240098, 0.709674, 0.143953,
	 0.825760, 0.315188, 0.995059, 0.295849,
	 0.584077, 0.909662, 0.940818, 0.331413,
	 0.184514, 0.583654, 0.962083, 0.834622,
	 0.205496, 0.716130, 0.136846, 0.795453,
	 0.610408, 0.758042, 0.830126, 0.176869,
	 0.968062, 0.644237, 0.466083, 0.606527,
	 0.583453, 0.932046, 0.401958, 0.131846,
	 0.172144, 0.111632, 0.348219, 0.886561,
	 0.326821, 0.343278, 0.264168, 0.789886,
	 0.252940, 0.204986, 0.209169, 0.263838,
	 0.688640, 0.171252, 0.188614, 0.771263,
	 0.787382, 0.225460, 0.610045, 0.330877,
	 0.883502, 0.440170, 0.556972, 0.835070,
	 0.984407, 0.923055, 0.497438, 0.519845,
	 0.855101, 0.799396, 0.686521, 0.919162,
	 0.811028, 0.934741, 0.825150, 0.042055,
	 0.278018, 0.989319, 0.848747, 0.367731,
	 0.194305, 0.957916, 0.668412, 0.758828,
	 0.129168, 0.757026, 0.577082, 0.796166,
	 0.882486, 0.187126, 0.214339, 0.739986,
	 0.527297, 0.671311, 0.617551, 0.457448,
	 0.594366, 0.114989, 0.979564, 0.388297,
	 0.814385, 0.666085, 0.376713, 0.583792,
	 0.600826, 0.201863, 0.663262, 0.754271,
	 0.191182, 0.512009, 0.209802, 0.206096,
	 0.469925, 0.778214, 0.968432, 0.443437,
	 0.535240, 0.545514, 0.315643, 0.353029,
	 0.632640, 0.429982, 0.183714, 0.066597,
	 0.101294, 0.701264, 0.571640, 0.550733,
	 0.716253, 0.551204, 0.945127, 0.478486,
	 0.217289, 0.321840, 0.156051, 0.686794,
	 0.423704, 0.719313, 0.496959, 0.460984,
	 0.231323, 0.606761, 0.700372, 0.556942,
	 0.384976, 0.668804, 0.100341, 0.800240,
	 0.214318, 0.315984, 0.237942, 0.718843,
	 0.645966, 0.321655, 0.806895, 0.608067,
	 0.922920, 0.378536, 0.242920, 0.599081,
	 0.829740, 0.188047, 0.169810, 0.941143,
	 0.409887, 0.225861, 0.665144, 0.703990,
	 0.845175, 0.162103, 0.248477, 0.973886,
	 0.668864, 0.848849, 0.577746, 0.948710,
	 0.517653, 0.578087, 0.774055, 0.591080,
	 0.794071, 0.911997, 0.378930, 0.377819,
	 0.233652, 0.185826, 0.987297, 0.062857,
	 0.464361, 0.230217, 0.695744, 0.215668,
	 0.318264, 0.765555, 0.241130, 0.586835,
	 0.891416, 0.806274, 0.361742, 0.707323,
	 0.868377, 0.510219, 0.713088, 0.485823,
	 0.359068, 0.290834, 0.491080, 0.751913,
	 0.768921, 0.265135, 0.408693, 0.514436,
	 0.177132, 0.687623, 0.903030, 0.234204,
	 0.773449, 0.890327, 0.367355, 0.153123,
	 0.120544, 0.963099, 0.431912, 0.265342,
	 0.728654, 0.573042, 0.866959, 0.577855,
	 0.379317, 0.228702, 0.356660, 0.164104,
};
float rotate=0.0;

#define NUM 8

float constant[3] = {2.0, 0.0, 0.0};
float linear[3] = {0.0, 0.12, 0.0};
float quadratic[3] = {0.0, 0.0, 0.01};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrthof (-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	else {
		glOrthof (-2.0f*w/h, 2.0f*w/h, -2.0f, 2.0f, -2.0f, 2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getRandv3(float *data) {
        LOGI("float vertices[] = {\n");
    for(int i=0; i<NUM; i++) {
        *(data+(i*2)) = (rand()/(float)RAND_MAX) * 3.8 - 1.9;
        LOGI("\t %f,", *(data+(i*2)));
        *(data+(i*2)+1) = (rand()/(float)RAND_MAX) * 3.8 - 1.9;
        LOGI(" %f,", *(data+(i*2)+1));
        *(data+(i*2)+2) = (rand()/(float)RAND_MAX) * 3.8 - 1.9;
        LOGI(" %f,\n", *(data+(i*2)+1));
    }
        LOGI("\t}\n");
}

void getRandc4(float *data) {
        LOGI("float colors[] = {\n");
    for(int i=0; i<NUM; i++) {
        *(data+(i*4)) = (rand()/(float)RAND_MAX) * 0.9 + 0.1;
        LOGI("\t %f,", *(data+(i*4)));
        *(data+(i*4)+1) = (rand()/(float)RAND_MAX) * 0.9 + 0.1;
        LOGI(" %f,", *(data+(i*4)+1));
        *(data+(i*4)+2) = (rand()/(float)RAND_MAX) * 0.9 + 0.1;
        LOGI(" %f,", *(data+(i*4)+2));
        *(data+(i*4)+3) = (rand()/(float)RAND_MAX) * 1.0;
        LOGI(" %f,\n", *(data+(i*4)+3));
    }
        LOGI("\t}\n");
}


void renderFrame() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CHECK(glEnable(GL_DEPTH_TEST));

	GL_CHECK(glEnable(GL_POINT_SMOOTH));

	GL_CHECK(glEnable(GL_BLEND));
	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GL_CHECK(glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, quadratic));
	GL_CHECK(glPointParameterf(GL_POINT_SIZE_MIN, 2.0));
	GL_CHECK(glPointParameterf(GL_POINT_SIZE_MAX, 20.0));
	GL_CHECK(glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 2.0));

	GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
	GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertices));
	GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
	GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
	GL_CHECK(glDrawArrays(GL_POINTS, 0, NUM));
}

void Sample::test()
{
	setupGraphics(WINDOW_W, WINDOW_H);

    string bmp_file = filename + ".bmp";
    LOGI("filename=%s",bmp_file.c_str());
	renderFrame();
    save2bmp(bmp_file.c_str());
	SwapBuffers();
}

int main(int argc, char **argv)
{
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

