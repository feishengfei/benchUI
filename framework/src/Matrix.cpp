/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include "Matrix.h"

namespace BotsonSDK
{
    /* Identity matrix. */
    const float Matrix::identityArray[16] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };

    Matrix Matrix::identityMatrix = Matrix(identityArray);

    Matrix::Matrix(const float* array)
    {
        memcpy(elements, array, 16 * sizeof(float));
    }

    Matrix::Matrix(void)
    {
    }

    float& Matrix::operator[] (unsigned element)
    {

        if (element > 15)
        {
           printf("Matrix only has 16 elements, tried to access element %d", element);
            exit(1);

        }
        return elements[element];
    }

    Matrix Matrix::operator* (Matrix right)
    {
        return multiply(this, &right);
    }

    Matrix& Matrix::operator= (const Matrix &another)
    {
        if(this != &another)
        {
            memcpy(this->elements, another.elements, 16 * sizeof(float));
        }

        return *this;
    }

    float* Matrix::getAsArray(void)
    {
        return elements;
    }

    float Matrix::matrixDeterminant(float *matrix)
    {
        float result = 0.0f;

        result  = matrix[0] * (matrix[4] * matrix[8] - matrix[7] * matrix[5]);
        result -= matrix[3] * (matrix[1] * matrix[8] - matrix[7] * matrix[2]);
        result += matrix[6] * (matrix[1] * matrix[5] - matrix[4] * matrix[2]);

        return result;
    }

    float Matrix::matrixDeterminant(Matrix *matrix)
    {
        float matrix3x3[9];
        float determinant3x3 = 0.0f;
        float result = 0.0f;

        /* Remove (i, j) (1, 1) to form new 3x3 matrix. */
        matrix3x3[0] = matrix->elements[ 5];
        matrix3x3[1] = matrix->elements[ 6];
        matrix3x3[2] = matrix->elements[ 7];
        matrix3x3[3] = matrix->elements[ 9];
        matrix3x3[4] = matrix->elements[10];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[13];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        determinant3x3 = matrixDeterminant(matrix3x3);
        result += matrix->elements[0] * determinant3x3;

        /* Remove (i, j) (1, 2) to form new 3x3 matrix. */
        matrix3x3[0] = matrix->elements[ 1];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 9];
        matrix3x3[4] = matrix->elements[10];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[13];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        determinant3x3 = matrixDeterminant(matrix3x3);
        result -= matrix->elements[4] * determinant3x3;

        /* Remove (i, j) (1, 3) to form new 3x3 matrix. */
        matrix3x3[0] = matrix->elements[ 1];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 5];
        matrix3x3[4] = matrix->elements[ 6];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[13];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        determinant3x3 = matrixDeterminant(matrix3x3);
        result += matrix->elements[8] * determinant3x3;

        /* Remove (i, j) (1, 4) to form new 3x3 matrix. */
        matrix3x3[0] = matrix->elements[ 1];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 5];
        matrix3x3[4] = matrix->elements[ 6];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[ 9];
        matrix3x3[7] = matrix->elements[10];
        matrix3x3[8] = matrix->elements[11];
        determinant3x3 = matrixDeterminant(matrix3x3);
        result -= matrix->elements[12] * determinant3x3;

        return result;
    }

    Matrix Matrix::matrixInvert(Matrix *matrix)
    {
        Matrix result;
        float matrix3x3[9];

        /* Find the cofactor of each element. */
        /* Element (i, j) (1, 1) */
        matrix3x3[0] = matrix->elements[ 5];
        matrix3x3[1] = matrix->elements[ 6];
        matrix3x3[2] = matrix->elements[ 7];
        matrix3x3[3] = matrix->elements[ 9];
        matrix3x3[4] = matrix->elements[10];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[13];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        result.elements[0] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (1, 2) */
        matrix3x3[0] = matrix->elements[ 1];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 9];
        matrix3x3[4] = matrix->elements[10];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[13];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        result.elements[4] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (1, 3) */
        matrix3x3[0] = matrix->elements[ 1];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 5];
        matrix3x3[4] = matrix->elements[ 6];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[13];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        result.elements[8] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (1, 4) */
        matrix3x3[0] = matrix->elements[ 1];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 5];
        matrix3x3[4] = matrix->elements[ 6];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[ 9];
        matrix3x3[7] = matrix->elements[10];
        matrix3x3[8] = matrix->elements[11];
        result.elements[12] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (2, 1) */
        matrix3x3[0] = matrix->elements[ 4];
        matrix3x3[1] = matrix->elements[ 6];
        matrix3x3[2] = matrix->elements[ 7];
        matrix3x3[3] = matrix->elements[ 8];
        matrix3x3[4] = matrix->elements[10];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        result.elements[1] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (2, 2) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 8];
        matrix3x3[4] = matrix->elements[10];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        result.elements[5] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (2, 3) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 4];
        matrix3x3[4] = matrix->elements[ 6];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[14];
        matrix3x3[8] = matrix->elements[15];
        result.elements[9] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (2, 4) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 2];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 4];
        matrix3x3[4] = matrix->elements[ 6];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[ 8];
        matrix3x3[7] = matrix->elements[10];
        matrix3x3[8] = matrix->elements[11];
        result.elements[13] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (3, 1) */
        matrix3x3[0] = matrix->elements[ 4];
        matrix3x3[1] = matrix->elements[ 5];
        matrix3x3[2] = matrix->elements[ 7];
        matrix3x3[3] = matrix->elements[ 8];
        matrix3x3[4] = matrix->elements[ 9];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[13];
        matrix3x3[8] = matrix->elements[15];
        result.elements[2] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (3, 2) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 1];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 8];
        matrix3x3[4] = matrix->elements[ 9];
        matrix3x3[5] = matrix->elements[11];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[13];
        matrix3x3[8] = matrix->elements[15];
        result.elements[6] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (3, 3) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 1];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 4];
        matrix3x3[4] = matrix->elements[ 5];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[13];
        matrix3x3[8] = matrix->elements[15];
        result.elements[10] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (3, 4) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 1];
        matrix3x3[2] = matrix->elements[ 3];
        matrix3x3[3] = matrix->elements[ 4];
        matrix3x3[4] = matrix->elements[ 5];
        matrix3x3[5] = matrix->elements[ 7];
        matrix3x3[6] = matrix->elements[ 8];
        matrix3x3[7] = matrix->elements[ 9];
        matrix3x3[8] = matrix->elements[11];
        result.elements[14] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (4, 1) */
        matrix3x3[0] = matrix->elements[ 4];
        matrix3x3[1] = matrix->elements[ 5];
        matrix3x3[2] = matrix->elements[ 6];
        matrix3x3[3] = matrix->elements[ 8];
        matrix3x3[4] = matrix->elements[ 9];
        matrix3x3[5] = matrix->elements[10];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[13];
        matrix3x3[8] = matrix->elements[14];
        result.elements[3] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (4, 2) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 1];
        matrix3x3[2] = matrix->elements[ 2];
        matrix3x3[3] = matrix->elements[ 8];
        matrix3x3[4] = matrix->elements[ 9];
        matrix3x3[5] = matrix->elements[10];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[13];
        matrix3x3[8] = matrix->elements[14];
        result.elements[7] = matrixDeterminant(matrix3x3);

        /* Element (i, j) (4, 3) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 1];
        matrix3x3[2] = matrix->elements[ 2];
        matrix3x3[3] = matrix->elements[ 4];
        matrix3x3[4] = matrix->elements[ 5];
        matrix3x3[5] = matrix->elements[ 6];
        matrix3x3[6] = matrix->elements[12];
        matrix3x3[7] = matrix->elements[13];
        matrix3x3[8] = matrix->elements[14];
        result.elements[11] = -matrixDeterminant(matrix3x3);

        /* Element (i, j) (4, 4) */
        matrix3x3[0] = matrix->elements[ 0];
        matrix3x3[1] = matrix->elements[ 1];
        matrix3x3[2] = matrix->elements[ 2];
        matrix3x3[3] = matrix->elements[ 4];
        matrix3x3[4] = matrix->elements[ 5];
        matrix3x3[5] = matrix->elements[ 6];
        matrix3x3[6] = matrix->elements[ 8];
        matrix3x3[7] = matrix->elements[ 9];
        matrix3x3[8] = matrix->elements[10];
        result.elements[15] = matrixDeterminant(matrix3x3);

        /* The adjoint is the transpose of the cofactor matrix. */
        matrixTranspose(&result);

        /* The inverse is the adjoint divided by the determinant. */
        result = matrixScale(&result, 1.0f / matrixDeterminant(matrix));

        return result;
    }

    Matrix Matrix::matrixScale(Matrix *matrix, float scale)
    {
        Matrix result;
        for(int allElements = 0; allElements < 16; allElements ++)
        {
            result.elements[allElements] = matrix->elements[allElements] * scale;
        }

        return result;
    }

    Matrix Matrix::scaleM(Matrix *matrix, int offset, float x, float y, float z)
    {
        for(int i = 0; i < 4; i++)
        {
            int mi = offset + i;
            matrix->elements[ mi] *= x;
            matrix->elements[4 + mi] *= y;
            matrix->elements[8 + mi] *= z;
        }
        return matrix->elements;
    }

    Matrix Matrix::matrixTranspose(Matrix *matrix)
    {
        float temp;

        temp = matrix->elements[1];
        matrix->elements[1] = matrix->elements[4];
        matrix->elements[4] = temp;

        temp = matrix->elements[2];
        matrix->elements[2] = matrix->elements[8];
        matrix->elements[8] = temp;

        temp = matrix->elements[3];
        matrix->elements[3] = matrix->elements[12];
        matrix->elements[12] = temp;

        temp = matrix->elements[6];
        matrix->elements[6] = matrix->elements[9];
        matrix->elements[9] = temp;

        temp = matrix->elements[7];
        matrix->elements[7] = matrix->elements[13];
        matrix->elements[13] = temp;

        temp = matrix->elements[11];
        matrix->elements[11] = matrix->elements[14];
        matrix->elements[14] = temp;

        return matrix->elements;
    }

    Matrix Matrix::createScaling(float x, float y, float z)
    {
        Matrix result = identityMatrix;

        result.elements[ 0] = x;
        result.elements[ 5] = y;
        result.elements[10] = z;

        return result;
    }

    Matrix Matrix::createTranslation(float x, float y, float z)
    {
        Matrix result = identityMatrix;


        result.elements[12] = x;
        result.elements[13] = y;
        result.elements[14] = z;

        return result;
    }

    Matrix Matrix::matrixPerspective(float FOV, float ratio, float zNear, float zFar)
    {
        Matrix result = identityMatrix;

        FOV = 1.0f / tan(FOV * 0.5f);

        result.elements[ 0] = FOV / ratio;
        result.elements[ 5] = FOV;
        result.elements[10] = -(zFar + zNear) / (zFar - zNear);
        result.elements[11] = -1.0f;
        result.elements[14] = (-2.0f * zFar * zNear) / (zFar - zNear);
        result.elements[15] = 0.0f;

        return result;
    }

    Matrix Matrix::matrixCameraLookAt(float eyeX, float eyeY, float eyeZ,
			float centerX, float centerY, float centerZ,

			float upX, float upY, float upZ)
	{
		Vec3f eye = {eyeX, eyeY, eyeZ};
		Vec3f center = {centerX, centerY, centerZ};
		Vec3f up = {upX, upY, upZ};
		matrixCameraLookAt(eye, center, up);
	}
    Matrix Matrix::matrixCameraLookAt(Vec3f eye, Vec3f center, Vec3f up)
	{
		Matrix result = identityMatrix;

		Vec3f cameraX, cameraY;

        Vec3f cameraZ = {center.x - eye.x, center.y - eye.y, center.z - eye.z};
        cameraZ.normalize();

        cameraX = Vec3f::cross(cameraZ, up);
        cameraX.normalize();

		cameraY = Vec3f::cross(cameraX, cameraZ);

		/*

         * The final cameraLookAt should look like:
		 *
		 * cameraLookAt[] = { cameraX.x,	cameraY.x,   -cameraZ.x,  0.0f,
		 *					  cameraX.y,	cameraY.y,   -cameraZ.y,  0.0f,
		 *					  cameraX.z,	cameraY.z,   -cameraZ.z,  0.0f,
		 *					 -eye.x,	   -eye.y,		 -eye.z,	  1.0f };
		 */

		result[0]  = cameraX.x;
		result[1]  = cameraY.x;
		result[2]  = -cameraZ.x;

		result[4]  = cameraX.y;
		result[5]  = cameraY.y;
		result[6]  = -cameraZ.y;

		result[8]  = cameraX.z;
		result[9]  = cameraY.z;
		result[10] = -cameraZ.z;

		result[12] = -eye.x;
		result[13] = -eye.y;
		result[14] = -eye.z;

		return result;
	}

    Matrix Matrix::matrixOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        Matrix result = identityMatrix;

        result.elements[ 0] = 2.0f / (right - left);
        result.elements[12] = -(right + left) / (right - left);

        result.elements[ 5] = 2.0f / (top - bottom);
        result.elements[13] = -(top + bottom) / (top - bottom);

        result.elements[10] = -2.0f / (zFar - zNear);
        result.elements[14] = -(zFar + zNear) / (zFar - zNear);

        return result;
    }
    Matrix Matrix::matrixFrustumgraphic(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        Matrix result = identityMatrix;
        float r_width = 1.0f / (right - left);
        float r_height = 1.0f / (top - bottom);
        float r_depth = 1.0f / (zNear - zFar);
        float x = 2.0f * (zNear * r_width);
        float y = 2.0f * (zNear * r_height);
        float A = (right + left) * r_width;
        float B = (top + bottom) * r_height;
        float C = (zNear + zFar) * r_depth;
        float D = 2.0f * (zNear * zFar * r_depth);

        result.elements[ 0] = x;
        result.elements[ 5] = y;
        result.elements[ 8] = A;
        result.elements[ 9] = B;
        result.elements[10] = C;
        result.elements[14] = D;
        result.elements[11] = -1.0f;
        result.elements[1] = 0.0f;
        result.elements[2] = 0.0f;
        result.elements[3] = 0.0f;
        result.elements[4] = 0.0f;
        result.elements[6] = 0.0f;
        result.elements[7] = 0.0f;
        result.elements[12] = 0.0f;
        result.elements[13] = 0.0f;
        result.elements[15] = 0.0f;

        return result;
    }

    Matrix Matrix::createRotationX(float angle)
    {
        Matrix result = identityMatrix;

        result.elements[ 5] = cos(degreesToRadians(angle));
        result.elements[ 9] = -sin(degreesToRadians(angle));
        result.elements[ 6] = sin(degreesToRadians(angle));
        result.elements[10] = cos(degreesToRadians(angle));

        return result;
    }

    Matrix Matrix::createRotationY(float angle)
    {
        Matrix result = identityMatrix;

        result.elements[ 0] = cos(degreesToRadians(angle));
        result.elements[ 8] = sin(degreesToRadians(angle));
        result.elements[ 2] = -sin(degreesToRadians(angle));
        result.elements[10] = cos(degreesToRadians(angle));

        return result;
    }

    Matrix Matrix::createRotationZ(float angle)
    {
        Matrix result = identityMatrix;

        result.elements[0] = cos(degreesToRadians(angle));
        result.elements[4] = -sin(degreesToRadians(angle));
        result.elements[1] = sin(degreesToRadians(angle));
        result.elements[5] = cos(degreesToRadians(angle));

        return result;
    }

    Matrix Matrix::multiply(Matrix *left, Matrix *right)
    {
        Matrix result;

        for(int row = 0; row < 4; row ++)
        {
            for(int column = 0; column < 4; column ++)
            {
                /*result.elements[row * 4 + column]  = left->elements[0 + row * 4] * right->elements[column + 0 * 4];
                result.elements[row * 4 + column] += left->elements[1 + row * 4] * right->elements[column + 1 * 4];
                result.elements[row * 4 + column] += left->elements[2 + row * 4] * right->elements[column + 2 * 4];
                result.elements[row * 4 + column] += left->elements[3 + row * 4] * right->elements[column + 3 * 4];*/
                float accumulator = 0.0f;
                for(int allElements = 0; allElements < 4; allElements ++)
                {
                    accumulator += left->elements[allElements * 4 + row] * right->elements[column * 4 + allElements];
                }
                result.elements[column * 4 + row] = accumulator;
            }
        }

        return result;
    }

    Vec4f Matrix::vertexTransform(Vec4f *vertex, Matrix *matrix)
    {
        Vec4f result;


        result.x  = vertex->x * matrix->elements[ 0];
        result.x += vertex->y * matrix->elements[ 4];
        result.x += vertex->z * matrix->elements[ 8];
        result.x += vertex->w * matrix->elements[12];

        result.y  = vertex->x * matrix->elements[ 1];
        result.y += vertex->y * matrix->elements[ 5];
        result.y += vertex->z * matrix->elements[ 9];
        result.y += vertex->w * matrix->elements[13];

        result.z  = vertex->x * matrix->elements[ 2];
        result.z += vertex->y * matrix->elements[ 6];
        result.z += vertex->z * matrix->elements[10];
        result.z += vertex->w * matrix->elements[14];

        result.w  = vertex->x * matrix->elements[ 3];
        result.w += vertex->y * matrix->elements[ 7];
        result.w += vertex->z * matrix->elements[11];
        result.w += vertex->w * matrix->elements[15];

        return result;
    }

    Vec3f Matrix::vertexTransform(Vec3f *vertex, Matrix *matrix)
    {
        Vec3f result;
        Vec4f extendedVertex;

        extendedVertex.x = vertex->x;
        extendedVertex.y = vertex->y;
        extendedVertex.z = vertex->z;
        extendedVertex.w = 1.0f;

        result.x  = extendedVertex.x * matrix->elements[ 0];
        result.x += extendedVertex.y * matrix->elements[ 4];
        result.x += extendedVertex.z * matrix->elements[ 8];
        result.x += extendedVertex.w * matrix->elements[12];

        result.y  = extendedVertex.x * matrix->elements[ 1];
        result.y += extendedVertex.y * matrix->elements[ 5];
        result.y += extendedVertex.z * matrix->elements[ 9];
        result.y += extendedVertex.w * matrix->elements[13];

        result.z  = extendedVertex.x * matrix->elements[ 2];
        result.z += extendedVertex.y * matrix->elements[ 6];
        result.z += extendedVertex.z * matrix->elements[10];
        result.z += extendedVertex.w * matrix->elements[14];

        return result;
    }

    void Matrix::print(void)
    {
        for(int row = 0; row < 4; row ++)
        {
            for(int column = 0; column < 4; column ++)
            {
                printf("%f ", elements[column * 4 + row]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
