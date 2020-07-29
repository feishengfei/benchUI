#ifndef __BMP_H__
#define __BMP_H__

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int loadObj(string filename, float * vertex, float * texcoord, float * normal, float *face);
static float[] getCrossProduct(float x1,float y1,float z1,float x2,float y2,float z2);
static float[] vectorNormal(float[] vector);

#endif