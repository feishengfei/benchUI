/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

//
/// @file Model.cpp
///
/// @brief
///
/// @details
//
/// @date 9/3/19
//
/// @author otto
//-----------------------------------------------------------------------------

#include "Model.h"
#include "Platform.h"
#include "Mathematics.h"

#include <cstdlib>
#include <cmath>
#include <cassert>


namespace BotsonSDK {
    void
    Model::getCubeTriangleRepresentation(float scalingFactor, int *numberOfCoordinates,
                                         float **coordinates) {
        if (coordinates == NULL) {
            LOGE("Cannot use null pointer while calculating coordinates.");
            return;
        }

        /* 6 faces, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeTriangleCoordinates = 6 * 2 * 3 * 3;
        /* Index of an array we will put new point coordinates at. */
        int       currentIndex                    = 0;

        /* Allocate memory for result array. */
        *coordinates = (float *)malloc(numberOfCubeTriangleCoordinates * sizeof(float));

        /* Is allocation successful?. */
        if (*coordinates == NULL) {
            LOGE("Could not allocate memory for result array.");

            return;
        }

        /* Example:
         * Coordinates for cube points:
         * A -1.0f,  1.0f,  1.0f
         * B -1.0f,  1.0f, -1.0f
         * C  1.0f,  1.0f, -1.0f
         * D  1.0f,  1.0f,  1.0f
         * E -1.0f, -1.0f,  1.0f
         * F -1.0f, -1.0f, -1.0f
         * G  1.0f, -1.0f, -1.0f
         * H  1.0f, -1.0f,  1.0f
         * Create 2 triangles for each face of the cube. Vertices are written in clockwise order.
         *       B ________ C
         *      / |     /  |
         *  A ......... D  |
         *    .   |   .    |
         *    .  F|_ _.___ |G
         *    . /     .  /
         *  E ......... H
         */

        /* Fill the array with coordinates. */
        /* Top face. */
        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /* Bottom face. */
        /*E*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*F*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*G*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /*E*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*G*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*H*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /* Back face. */
        /*G*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /*G*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*F*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /* Front face. */
        /*E*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /*E*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*H*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /* Right face. */
        /*H*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /*H*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*G*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /* Left face. */
        /*F*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /*F*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /*E*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /* Calculate size of a cube. */
        for (int i = 0; i < numberOfCubeTriangleCoordinates; i++) {
            (*coordinates)[i] = scalingFactor * (*coordinates)[i];
        }

        if (numberOfCoordinates != NULL) {
            *numberOfCoordinates = numberOfCubeTriangleCoordinates;
        }
    }

    void
    Model::getCubeNormals(int *numberOfCoordinates, float **normals) {
        /* Set the same normals for both triangles from each face.
         * For details: see example for getCubeTriangleRepresentation() function.
         */

        if (normals == NULL) {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 6 faces, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeNormalsCoordinates = 6 * 2 * 3 * 3;
        /* Index of an array we will put new point coordinates at. */
        int       currentIndex                   = 0;

        /* Allocate memory for result array. */
        *normals = (float *)malloc(numberOfCubeNormalsCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*normals == NULL) {
            LOGE("Could not allocate memory for result array.");

            return;
        }

        /* There are 2 triangles for each face. Each triangle consists of 3 vertices. */
        int numberOfCoordinatesForOneFace = 2 * 3;

        /* Top face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++) {
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        /* Bottom face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++) {
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = -1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        /* Back face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++) {
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = -1;
            currentIndex++;
        }

        /* Front face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++) {
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 1;
            currentIndex++;
        }

        /* Right face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++) {
            (*normals)[currentIndex] = 1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        /* Left face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++) {
            (*normals)[currentIndex] = -1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        if (numberOfCoordinates != NULL) {
            *numberOfCoordinates = numberOfCubeNormalsCoordinates;

        }
    }

    void Model::getPlaneTriangleRepresentationUVCoordinates(int* numberOfCoordinates, float** uvCoordinates)
    {
        /* Example:
         *  v   D __________ C
         *  .    |        / |
         * / \   |     /    |
         *  |    |  /       |
         *  |    |/_________|
         *  |   A            B
         *  |----------> u
         */

        if (uvCoordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 2 triangles, 3 points of triangle, 2 coordinates for each point. */
        const int numberOfUVCoordinates = 2 * 3 * 2;

        /* Allocate memory for result array. */
        *uvCoordinates = (float*) malloc (numberOfUVCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*uvCoordinates == NULL)
        {
            LOGE("Could not allocate memory for result array.");
            return;
        }

        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /*** First triangle. ***/
        /* A */
        /* u */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* v */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* B */
        /* u */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* v */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* C */
        /* u */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* v */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /*** Second triangle. ***/
        /* A */
        /* u */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* v */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* C */
        /* u */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* v */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* D */
        /* u */
        (*uvCoordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* v */
        (*uvCoordinates)[currentIndex] = 1.0f;
        currentIndex++;

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfUVCoordinates;
        }
    }

    void Model::getPlaneTriangleRepresentation(int* numberOfCoordinates, float** coordinates)
    {
        /* Example:
         *  z   D __________ C
         *  .    |        / |
         * / \   |     /    |
         *  |    |  /       |
         *  |    |/_________|
         *  |   A            B
         *  |----------> x
         */

        if (coordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 2 triangles, 3 points of triangle, 4 coordinates for each point. */
        const int numberOfSquareCoordinates = 2 * 3 * 4;

        /* Allocate memory for result array. */
        *coordinates = (float*) malloc (numberOfSquareCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*coordinates == NULL)
        {
            LOGE("Could not allocate memory for result array.");
            return;
        }

        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /* First triangle. */
        /* A */
        /* x */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* w */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* B */
        /* x */
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* w */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* C */
        /* x */
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* w */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        /* Second triangle. */
        /* A */
        /* x */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* w */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* C */
        /* x */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* y */
        (*coordinates)[currentIndex] = 0.0f;
        currentIndex++;
        /* z */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* w */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;
        /* D */
        /* x */
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /* y */
        (*coordinates)[currentIndex] =  0.0f;
        currentIndex++;
        /* z */
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /* w */
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfSquareCoordinates;
        }
    }

    void Model::getPlaneNormals(int* numberOfCoordinates, float** normals)
    {
        if (normals == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 2 triangles, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfNormalsCoordinates = 2 * 3 * 3;
        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /* Allocate memory for result array. */
        *normals = (float*) malloc (numberOfNormalsCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*normals == NULL)
        {
            LOGE("Could not allocate memory for result array.");

            return;
        }

        for (int i = 0; i < numberOfNormalsCoordinates; i+=3)
        {
            (*normals)[currentIndex] = 0.0f;
            currentIndex++;
            (*normals)[currentIndex] = 1.0f;
            currentIndex++;
            (*normals)[currentIndex] = 0.0f;
            currentIndex++;
        }

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfNormalsCoordinates;
        }
    }

    void Model::transformPlane(Matrix transform, int numberOfCoordinates, float** squareCoordinates)
    {
        /* Loop through all the coordinates and transform them using the rotation matrix. */
        for (int allCoordinates = 0; allCoordinates < numberOfCoordinates; allCoordinates +=4)
        {
            Vec4f currentVertex = {(*squareCoordinates)[allCoordinates], (*squareCoordinates)[allCoordinates + 1], (*squareCoordinates)[allCoordinates + 2], (*squareCoordinates)[allCoordinates + 3]};

            Vec4f rotatedVertex = Matrix::vertexTransform(&currentVertex, &transform);

            (*squareCoordinates)[allCoordinates] = rotatedVertex.x;
            (*squareCoordinates)[allCoordinates + 1] = rotatedVertex.y;
            (*squareCoordinates)[allCoordinates + 2] = rotatedVertex.z;
            (*squareCoordinates)[allCoordinates + 3] = rotatedVertex.w;
        }
    }

    void Model::getSpherePointRepresentation(const float radius, const int numberOfSamples, int* numberOfCoordinates, float** coordinates)
    {
        /*
         * Sphere vertices are created according to rule:
         * Create a circle at north pole of the sphere, consisting of numberOfSample points.
         * Create following circles, ending at south pole of sphere. The sphere now consists of numberOfSample circles.
         * Theta value (indicating longitude) runs from 0 to 2*M_PI.
         * Radius value (indicating latitude) runs from -radius to radius.
         */

        /* Check if parameters have compatibile values. */
        if (radius <= 0.0f)
        {
            LOGE("radius value has to be greater than zero.");

            return;
        }

        if (numberOfSamples <= 0)
        {
            LOGE("numberOfSamples value has to be greater than zero.");

            return;
        }
        if (coordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* Maximum value of an error (used to compare float values). */
        const float epsilon = 0.001f;
        /* Index of an array we will put new point coordinates at. */
        int indexOfSphereArray = 0;
        /* Maximum longitude. */
        float maxTheta = (2.0f * M_PI);
        /* Value of longitude step. */
        float thetaStep = maxTheta / float(numberOfSamples);
        /* Value of latitude step. */
        float radiusStep = (2 * radius) / float(numberOfSamples-1);
        /* Index of longitude loop. */
        int thetaIndex = 0;
        /* Index of latitude loop. */
        int radiusIndex = 0;
        /* Number of coordinates which a sphere consists of. Each point (which a sphere consists of) consists of 3 coordinates: x, y, z. */
        const int numberOfSphereCoordinates = numberOfSamples * numberOfSamples * 3;

        /* Allocate memory for result array. */
        *coordinates = (float*) malloc (numberOfSphereCoordinates * sizeof(float));

        if (*coordinates == NULL)
        {
            LOGE("Could not allocate memory for result array.");

            return;
        }

        /* Loop through circles from north to south. */
        for (float r = -radius;
                r < radius + epsilon;
                r = -radius + radiusIndex * radiusStep)
        {
            thetaIndex = 0;

            /* Protect against rounding errors.. */
            if (r > radius)
            {
                r = radius;
            }

            /* Loop through all points of the circle. */
            for (float theta = 0.0f;
                    theta < maxTheta;
                    theta = thetaIndex * thetaStep)
            {
                /* Compute x, y and z coordinates for the considered point. */
                float x = sqrt((radius * radius) - (r * r)) * cosf(theta);
                float y = sqrt((radius * radius) - (r * r)) * sinf(theta);
                float z = r;

                (*coordinates)[indexOfSphereArray] = x;
                indexOfSphereArray++;

                (*coordinates)[indexOfSphereArray] = y;
                indexOfSphereArray++;

                (*coordinates)[indexOfSphereArray] = z;
                indexOfSphereArray++;

                thetaIndex ++;
            }

            radiusIndex ++;
        }

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfSphereCoordinates;
        }
    }

    void Model::getSphereTriangleRepresentation(const float radius, const int numberOfSamples, int* numberOfCoordinates, float** coordinates)
    {
        /* Check if parameters have compatibile values. */
        if (radius <= 0.0f)
        {
            LOGE("radius value has to be greater than zero.");

            return;
        }

        if (numberOfSamples <= 0)
        {
            LOGE("numberOfSamples value has to be greater than zero.");

            return;
        }
        if (coordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }
        /* Array holding coordinates of points which a sphere consists of. */
        float* pointCoordinates = NULL;
        /* Current index used for accessing coordinates array. */
        int sphereTriangleCoordinateIndex = 0;
        /* Index of current loop iteration. */
        int iterationIndex = 1;
        /* There are 18 coordinates created in one loop: 3 coordinates * 3 triangle vertices * 2 triangles. */
        int numberOfCoordinatesCreatedInOneLoop = 18;
        /* Number of coordinates of all triangles which a sphere consists of.
        * (numberOfSamples - 1) - for each circle (excluding last one)
        * numberOfSamples - for each point on a single circle
        * 2 - number of triangles that start at given point
        * 3 - number of points that make up a triangle
        * 3 - coordinates per each point.
        */
        const int numberOfSphereTriangleCoordinates = (numberOfSamples - 1) * numberOfSamples * 2 * 3 * 3;

        /* Compute coordinates of points which make up a sphere. */
        getSpherePointRepresentation(radius, numberOfSamples, NULL, &pointCoordinates);

        if (pointCoordinates == NULL)
        {
            LOGE("Could not get coordinates of points which make up a sphere.");
            return;
        }

        *coordinates = (float*) malloc (numberOfSphereTriangleCoordinates * sizeof(float));

        if (*coordinates == NULL)
        {
            LOGE("Could not allocate memory for result array.");
            return;
        }

        /* Each point has 3 coordinates: x, y, z. */
        for (int pointIndex = 0;
                pointIndex < (numberOfSphereTriangleCoordinates / numberOfCoordinatesCreatedInOneLoop) * 3;
                pointIndex += 3)
        {
            /* First triangle. ==> */

            /* Building of a triangle is started from point at index described by pointIndex.
             * Values of x, y and z coordinates are written one after another in pointCoordinates array starting at index of point value.
             */
            /* Coordinate x. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex];
            sphereTriangleCoordinateIndex++;
            /* Coordinate y. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 1];
            sphereTriangleCoordinateIndex++;
            /* Coordinate z. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 2];
            sphereTriangleCoordinateIndex++;

            /* Check if this is the last point of circle. */
            if ((iterationIndex % numberOfSamples) == 0 )
            {
                /* Second point of triangle.
                 * If this is the last point lying on a circle,
                 * second point that makes up a triangle is the point with coordinates taken from the first point lying on current circle.
                 * According to example above: the second point for first triangle starting at point D1 (last point on a current circle) is point A1.
                 * Index (to receive x coordinate): [point - 3 * (numberOfSamples)] stands for x coordinate of point D0 (corresponding point from previous circle),
                 * [+ 3] stands for next point (first point of current circle - A1).
                 */
                /* Coordinate x. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex - 3 * (numberOfSamples) + 3];
                sphereTriangleCoordinateIndex++;
                /* Coordinate y. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex - 3 * (numberOfSamples) + 3 + 1];
                sphereTriangleCoordinateIndex++;
                /* Coordinate z. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex - 3 * (numberOfSamples) + 3 + 2];
                sphereTriangleCoordinateIndex++;

                /* Third point of triangle.
                 * If this is the last point lying on a circle,
                 * third point that makes up a triangle is the point with coordinates taken from the first point lying on next circle.
                 * According to example above: the third point for first triangle starting at point D1 (last point on a current circle) is point A2.
                 * Index (to receive x coordinate): [point + 3] stands for x coordinate of point A2 (first point on next circle).
                 */
                /* Coordinate x. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3];
                sphereTriangleCoordinateIndex++;
                /* Coordinate y. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 + 1];
                sphereTriangleCoordinateIndex++;
                /* Coordinate z. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 + 2];
                sphereTriangleCoordinateIndex++;
            }
            else
            {
                /* Second point of triangle.
                 * If this is not the last point lying on a circle,
                 * second point that makes up a triangle is the point with coordinates taken from the next point lying on current circle.
                 * According to example above: the second point for first triangle starting at (for example) point A1 (not last point on a circle) is point B1.
                 * Index (to receive x coordinate): [point + 3] stands for x coordinate of point B1 (next point in array).
                 */
                /* Coordinate x. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3];
                sphereTriangleCoordinateIndex++;
                /* Coordinate y. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 + 1];
                sphereTriangleCoordinateIndex++;
                /* Coordinate z. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 + 2];
                sphereTriangleCoordinateIndex++;

                /* Third point of triangle.
                 * If this is not the last point lying on a circle,
                 * third point that makes up a triangle is the point with coordinates taken from the next from corresponding point lying on next circle.
                 * According to example above: the third point for first triangle starting at (for example) point A1 (not last point on a circle) is point B2.
                 * Index (to receive x coordinate): [point + numberOfSamples * 3] stands for x coordinate of point A2 (corresponding point lying on next circle),
                 * [+ 3] stands for nex point on that circle - B2.
                 */
                /* Coordinate x. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + numberOfSamples * 3 + 3];
                sphereTriangleCoordinateIndex++;
                /* Coordinate y. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + numberOfSamples * 3 + 3 + 1];
                sphereTriangleCoordinateIndex++;
                /* Coordinate z. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + numberOfSamples * 3 + 3 + 2];
                sphereTriangleCoordinateIndex++;
            }
            /* <== First triangle. */

            /* Second triangle. ==> */

            /* Building of a triangle is started from point at index described by pointIndex.
             * Values of x, y and z coordinates are written one after another in pointCoordinates array starting at index of point value.
             */
            /* Coordinate x. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex];
            sphereTriangleCoordinateIndex++;
            /* Coordinate y. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 1];
            sphereTriangleCoordinateIndex++;
            /* Coordinate z. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 2];
            sphereTriangleCoordinateIndex++;

            /* Check if this is a last point of circle. */
            if ((iterationIndex % numberOfSamples) == 0 )
            {   /* Second point of triangle.
                 * If this is the last point lying on a circle,
                 * second point that makes up a triangle is the point with coordinates taken from the first point lying on next circle.
                 * According to example above: the second point for first triangle starting at point D1 (last point on a current circle) is point A2.
                 * Index (to receive x coordinate): [point + 3] stands for x coordinate of point A2 (first point on next circle).
                 */
                /* Coordinate x. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3];
                sphereTriangleCoordinateIndex++;
                /* Coordinate y. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 + 1];
                sphereTriangleCoordinateIndex++;
                /* Coordinate z. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 + 2];
                sphereTriangleCoordinateIndex++;
            }
            else
            {
                /* Second point of triangle.
                 * If this is not the last point lying on a circle,
                 * second point that makes up a triangle is the point with coordinates taken from the next from corresponding point lying on next circle.
                 * According to example above: the second point for first triangle starting at (for example) point A1 (not last point on a circle) is point B2.
                 * Index (to receive x coordinate): [point + numberOfSamples * 3] stands for x coordinate of point A2 (corresponding point lying on next circle),
                 * [+ 3] stands for nex point on that circle - B2.
                 */
                /* Coordinate x. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 * numberOfSamples + 3];
                sphereTriangleCoordinateIndex++;
                /* Coordinate y. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 * numberOfSamples + 3 + 1];
                sphereTriangleCoordinateIndex++;
                /* Coordinate z. */
                (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 * numberOfSamples + 3 + 2];
                sphereTriangleCoordinateIndex++;
            }

            /* Third point of triangle that makes up a triangle is the point with coordinates taken from the corresponding point lying on next circle.
             * According to example above: the third point for second triangle starting at point A1 (for example) is point A2.
             * Index (to receive x coordinate): [point + 3 * (numberOfSamples)] stands for x coordinate of point A2 (corresponding point from next circle).
             */
            /* Coordinate x. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 * numberOfSamples];
            sphereTriangleCoordinateIndex++;
            /* Coordinate y. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3  *numberOfSamples + 1];
            sphereTriangleCoordinateIndex++;
            /* Coordinate z. */
            (*coordinates)[sphereTriangleCoordinateIndex] = pointCoordinates[pointIndex + 3 * numberOfSamples + 2];
            sphereTriangleCoordinateIndex++;

            /* <== Second triangle. */

            iterationIndex++;
        }

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfSphereTriangleCoordinates;
        }

        /* Deallocate memory. */
        free(pointCoordinates);
        pointCoordinates = NULL;
    }

    void Model::createSuper(int samples, float n1, float n2, float scale, float** roundedCubeCoordinates, float** roundedCubeNormalVectors, int* numberOfVertices, int* numberOfCoordinates, int* numberOfNormals)
    {
        /* Check if samples is different than 0. */
        if (samples == 0)
        {
            LOGE("Number of samples can't be 0.");
            return;
        }

        /*
         * Computation of the numberOfCoordinates results from the algorithm used in this function.
         * In the first "for" loop we can see that this loop iterates samples / 2 times. Then in the second loop
         * we can see that this loop will go samples times.
         * In total, there are samples / 2 * samples iterations.
         * Each iteration produces 6 vertices and each vertex has 4 coordinates.
         */
        *numberOfCoordinates = samples / 2 * samples * 6 * 4;

        /* The number of normals is the same except that each normal only has 3 coordinates. */
        *numberOfNormals = samples / 2 * samples * 6 * 3;

        /* Allocate memory to store rounded cube's coordinates. */
        *roundedCubeCoordinates = new float[*numberOfCoordinates];

        if (roundedCubeCoordinates == NULL)
        {
            LOGE("Pointer roundedCubeCoordinates is NULL.");
            return;
        }

        /* Allocate memory to store rounded cube's normal vectors. */
        *roundedCubeNormalVectors = new float[*numberOfNormals];

        if (roundedCubeNormalVectors == NULL)
        {
            LOGE("Pointer roundedCubeNormalVectors is NULL.");
            return;
        }

        /* Calculate the number of vertices for the rounded cube. */
        *numberOfVertices = *numberOfCoordinates / 4;

        /* Values to store temporarily vertices and normal vectors. */
        Vec3f vertex, normalVector;

        /* Value vertexIndex determines the beginning of array where vertices should be saved. */
        int vertexIndex = 0;

        /* Value normalVectorIndex determines the beginning of array where normal vectors should be saved. */
        int normalVectorIndex = 0;

        /* These values will change xzAngle and xyAngle. */
        float xzAngleDelta = 2.0f * M_PI / samples;
        float xyAngleDelta = 2.0f * M_PI / samples;

        /* Angle used to compute vertices and normal vectors. */
        float xyAngle = -M_PI / 2.0f;

        /* This loop goes samples / 2 times because in each second loop we create 2 triangles. */
        for (int j = 0; j < samples / 2; j++)
        {
            /* Angle used to compute vertices and normal vectors. */
            float xzAngle = -M_PI;

            for (int i = 0; i < samples; i++)
            {
                /* Triangle #1 */
                /* Calculate first vertex and normal vector. */
                vertex       = sampleSuper(xyAngle, xzAngle, n1, n2, scale);
                normalVector = calculateSuperNormal(xyAngle, xzAngle, n1, n2, scale);

                /* Put vertex and normal vector coordinates into array. */
                storeSuperVertexAndNormalVectorInArray(vertex, normalVector, vertexIndex, normalVectorIndex, *roundedCubeCoordinates, *roundedCubeNormalVectors);

                /* Calculate second vertex and normal vector. */
                vertex       = sampleSuper         (xyAngle + xyAngleDelta, xzAngle, n1, n2, scale);
                normalVector = calculateSuperNormal(xyAngle + xyAngleDelta, xzAngle, n1, n2, scale);

                /* Put vertex and normal vector coordinates into array. */
                storeSuperVertexAndNormalVectorInArray(vertex, normalVector, vertexIndex, normalVectorIndex, *roundedCubeCoordinates, *roundedCubeNormalVectors);

                /* Calculate third vertex and normal vector. */
                vertex		 = sampleSuper         (xyAngle + xyAngleDelta, xzAngle + xzAngleDelta, n1, n2, scale);
                normalVector = calculateSuperNormal(xyAngle + xyAngleDelta, xzAngle + xzAngleDelta, n1, n2, scale);

                /* Put vertex and normal vector coordinates into array. */
                storeSuperVertexAndNormalVectorInArray(vertex, normalVector, vertexIndex, normalVectorIndex, *roundedCubeCoordinates, *roundedCubeNormalVectors);

                /* Triangle #2 */
                /* Calculate first vertex and normal vector. */
                vertex		 = sampleSuper         (xyAngle, xzAngle, n1, n2, scale);
                normalVector = calculateSuperNormal(xyAngle, xzAngle, n1, n2, scale);

                /* Put vertex and normal vector coordinates into array. */
                storeSuperVertexAndNormalVectorInArray(vertex, normalVector, vertexIndex, normalVectorIndex, *roundedCubeCoordinates, *roundedCubeNormalVectors);

                /* Calculate second vertex and normal vector. */
                vertex		 = sampleSuper         (xyAngle + xyAngleDelta, xzAngle + xzAngleDelta, n1, n2, scale);
                normalVector = calculateSuperNormal(xyAngle + xyAngleDelta, xzAngle + xzAngleDelta, n1, n2, scale);

                /* Put vertex and normal vector coordinates into array. */
                storeSuperVertexAndNormalVectorInArray(vertex, normalVector, vertexIndex, normalVectorIndex, *roundedCubeCoordinates, *roundedCubeNormalVectors);

                /* Calculate third vertex and normal vector. */
                vertex		 = sampleSuper         (xyAngle, xzAngle + xzAngleDelta, n1, n2, scale);
                normalVector = calculateSuperNormal(xyAngle, xzAngle + xzAngleDelta, n1, n2, scale);

                /* Put vertex and normal vector coordinates into array. */
                storeSuperVertexAndNormalVectorInArray(vertex, normalVector, vertexIndex, normalVectorIndex, *roundedCubeCoordinates, *roundedCubeNormalVectors);

                /* Change xzAngle value. */
                xzAngle += xzAngleDelta;
            }

            /* Change xyAngle value. */
            xyAngle += xyAngleDelta;
        }
    }

    Vec3f Model::calculateSuperNormal(float xyAngle, float xzAngle, float n1, float n2, float scale)
    {
        /* Pre-calculate sine and cosine values for both angles. */
        float cosPhi  = cosf(xyAngle);
        float cosBeta = cosf(xzAngle);
        float sinPhi  = sinf(xyAngle);
        float sinBeta = sinf(xzAngle);

        /*
         * The equations for x, y and z coordinates are:
         * x = 1 / rx * cos^(2 - n1)(xyAngle) * cos^(2 - n2)(xzAngle)
         * y = 1 / ry * sin^(2 - n1)(xyAngle)
         * z = 1 / rz * cos^(2 - n1)(xyAngle) * sin^(2 - n2)(xzAngle)
         *
         * where:
         * -M_PI/2 <= xyAngle <= M_PI/2
         * -M_PI   <= xzAngle <= M_PI
         * 0 < n1, n2 < infinity
         *
         * As for two-dimensional case rx, ry, and rz are scale factors for each axis (axis intercept).
         */

        /* Normal vector to be returned. */
        Vec3f normal;

        normal.x = signum(cosPhi) * powf(fabs(cosPhi), 2 - n1) * signum(cosBeta) * powf(fabs(cosBeta), 2 - n2) / scale;
        normal.y = signum(sinPhi) * powf(fabs(sinPhi), 2 - n1) / scale;
        normal.z = signum(cosPhi) * powf(fabs(cosPhi), 2 - n1) * signum(sinBeta) * powf(fabs(sinBeta), 2 - n2) / scale;

        /* Normalize vector. */
        normal.normalize();

        return normal;
    }

    Vec3f Model::sampleSuper(float xyAngle, float xzAngle, float n1, float n2, float scale)
    {
        /* Pre-calculate sine and cosine values for both angles. */
        const float xyAngleCos = cosf(xyAngle);
        const float xzAngleCos = cosf(xzAngle);
        const float xyAngleSin = sinf(xyAngle);
        const float xzAngleSin = sinf(xzAngle);

        /*
         * The equations for x, y and z coordinates are given below:
         *
         * x = rx * cos^n1(xyAngle) * cos^n2(xzAngle)
         * y = ry * sin^n1(xyAngle)
         * z = rz * cos^n1(xyAngle) * sin^n2(xzAngle)
         *
         * where:
         *
         * -M_PI/2 <= xyAngle <= M_PI/2
         * -M_PI   <= xzAngle <= M_PI
         * 0 < n1, n2 < infinity
         *
         * As for two-dimensional case rx, ry, and rz are scale factors for each axis (axis intercept).
	     */

        /* Vertex to be returned. */
        Vec3f vertex;

        vertex.x = scale * BotsonSDK::signum(xyAngleCos) * powf(fabs(xyAngleCos), n1) * BotsonSDK::signum(xzAngleCos) * powf(fabs(xzAngleCos), n2);
        vertex.y = scale * BotsonSDK::signum(xyAngleSin) * powf(fabs(xyAngleSin), n1);
        vertex.z = scale * BotsonSDK::signum(xyAngleCos) * powf(fabs(xyAngleCos), n1) * BotsonSDK::signum(xzAngleSin) * powf(fabs(xzAngleSin), n2);

        return vertex;
    }

    void Model::storeSuperVertexAndNormalVectorInArray(const Vec3f& vertex, const Vec3f& normalVector, int& vertexIndex, int& normalVectorIndex, float* roundedCubeCoordinates, float* roundedCubeNormalVectors)
    {
        /* Save vertex and increment counter/index. */
        roundedCubeCoordinates[vertexIndex++] = vertex.x;
        roundedCubeCoordinates[vertexIndex++] = vertex.y;
        roundedCubeCoordinates[vertexIndex++] = vertex.z;
        roundedCubeCoordinates[vertexIndex++] = 1.0f;

        /* Save normal vector and increment counter/index. */
        roundedCubeNormalVectors[normalVectorIndex++] = normalVector.x;
        roundedCubeNormalVectors[normalVectorIndex++] = normalVector.y;
        roundedCubeNormalVectors[normalVectorIndex++] = normalVector.z;
    }

    void Model::generateTorusNormals(unsigned int circlesCount, unsigned int pointsPerCircleCount, float* normals)
    {
        unsigned int normalSize = 3;
        unsigned int index = 0;

        for (unsigned int horizontalIndex = 0; horizontalIndex < circlesCount; ++horizontalIndex)
        {
            /* Angle in radians on XZ plane. */
            float phi = (float) horizontalIndex * 2.0f * M_PI / circlesCount;

            Vec3f horizontalTangent = {-sinf(phi), 0.0f, cosf(phi)};

            for (unsigned int verticalIndex = 0; verticalIndex < pointsPerCircleCount; ++verticalIndex)
            {
                /* Angle in radians on XY plane. */
                float theta  = (float) verticalIndex * 2.0f * M_PI / pointsPerCircleCount;

                Vec3f verticalTangent = {-cosf(phi) * sinf(theta), cosf(theta), -sinf(phi) * sinf(theta)};

                assert(index < circlesCount * pointsPerCircleCount * normalSize);

                normals[index++] = horizontalTangent.z * verticalTangent.y - horizontalTangent.y * verticalTangent.z;
                normals[index++] = horizontalTangent.x * verticalTangent.z - horizontalTangent.z * verticalTangent.x;
                normals[index++] = horizontalTangent.y * verticalTangent.x - horizontalTangent.x * verticalTangent.y;
            }
        }
    }

    void Model::calculateTorusControlPointsIndices(unsigned int patchDimension, unsigned int patchInstancesCount, unsigned int controlPointsIndicesCount, unsigned int* controlPointsIndices)
    {
        if (controlPointsIndices == NULL)
        {
            LOGE("Cannot use null pointer while calculating control points indices.");

            return;
        }

        /* Definition of needed constants. Torus continuity cannot be guaranteed with other parameters. */
        const unsigned int pointsPerCircleCount = 12;
        const unsigned int circlesCount         = 12;
        const unsigned int torusVerticesCount   = pointsPerCircleCount * circlesCount;

        /* Index of a vertex from which a patch starts. */
        unsigned int startIndex = 0;
        /* Index of a circle from which vertex indices are currently taken. */
        unsigned int currentCircle = 0;

        /* Index variable. */
        unsigned int index = 0;

        /* Loop that creates patches for each instance of patch primitives. Successive patches wrap around torus horizontally. */
        for (unsigned int instanceIndex = 0; instanceIndex < patchInstancesCount; ++instanceIndex)
        {
            /* Iterate in horizontal axis. */
            for (unsigned int x = 0; x < patchDimension; ++x)
            {
                /* Determine index of current circle from which the vertex indices are taken. */
                currentCircle = startIndex / pointsPerCircleCount;

                /* Iterate in vertical axis. */
                for (unsigned int y = 0; y < patchDimension; ++y)
                {
                    unsigned int currentIndex = startIndex + y;

                    /* Make closing patches end up at the very first vertex of each circle. */
                    if (currentIndex >= pointsPerCircleCount * (currentCircle + 1))
                    {
                        currentIndex -= pointsPerCircleCount;
                    }

                    controlPointsIndices[index++] = currentIndex;

                    assert(index <= controlPointsIndicesCount);
                }

                /* Get indices from the next circle. */
                startIndex += pointsPerCircleCount;

                /* Make closing patches end up at the very first circle. */
                if (startIndex >= torusVerticesCount)
                {
                    startIndex -= torusVerticesCount;
                }
            }

            /* Neighbouring patches always share one edge, so start index of the next patch should start from the last column of the previous patch. */
            startIndex -= pointsPerCircleCount;

            /* When the whole row is finished, move to the next one. */
            if (currentCircle == 0)
            {
                startIndex += patchDimension - 1;
            }
        }
    }
    void Model::calculateTorusPatchData(unsigned int patchDensity, float* patchVertices, unsigned int* patchTriangleIndices)
    {
        if (patchVertices == NULL || patchTriangleIndices == NULL)
        {
            LOGE("Cannot use null pointers while calculating patch data.");

            return;
        }

        /* Total number of components describing a patch (only U/V components are definied). */
        const unsigned int patchComponentsCount = patchDensity * patchDensity * 2;
        /* Number of indices that needs to be defined to draw quads consisted of triangles (6 points per quad needed) over the entire patch. */
        const unsigned int patchTriangleIndicesCount = (patchDensity - 1) * (patchDensity - 1) * 6;

        /* Number of components in a single vertex. */
        const unsigned int uvComponentsCount = 2;
        /* Number of vertices needed to draw a quad as two separate triangles. */
        const unsigned int verticesPerQuadCount = 6;

        /* Current index of a patch vertex. */
        unsigned int uvIndex = 0;
        /* Current index for indices array. */
        unsigned int triangleVertexIndex = 0;

        for (unsigned int x = 0; x < patchDensity; ++x)
        {
            /* Horizontal component. */
            float u = (float) x / (patchDensity - 1);

            for (unsigned int y = 0; y < patchDensity; ++y)
            {
                /* Vertical component. */
                float v = (float) y / (patchDensity - 1);

                patchVertices[uvIndex++] = u;
                patchVertices[uvIndex++] = v;

                assert(uvIndex <= patchComponentsCount);
            }
        }

        /*
         * Indices are determined in the following manner:
         *
         * 0 -> 1 -> 16 -> 16 -> 1 -> 17 -> 1 -> 2 -> 17 -> 17 -> 2 -> 18 -> ...
         *
         * 2----18----34---...
         * |  /  |  /  |
         * | /   | /   |
         * 1----17----33---...
         * |  /  |  /  |
         * | /   | /   |
         * 0----16----32----...
         */
        for (unsigned int x = 0; x < patchDensity - 1; ++x)
        {
            for (unsigned int y = 0; y < patchDensity - 1; ++y)
            {
                patchTriangleIndices[triangleVertexIndex++] = patchDensity *  x      + y;
                patchTriangleIndices[triangleVertexIndex++] = patchDensity *  x      + y + 1;
                patchTriangleIndices[triangleVertexIndex++] = patchDensity * (x + 1) + y;

                patchTriangleIndices[triangleVertexIndex++] = patchDensity * (x + 1) + y;
                patchTriangleIndices[triangleVertexIndex++] = patchDensity *  x      + y + 1;
                patchTriangleIndices[triangleVertexIndex++] = patchDensity * (x + 1) + y + 1;

                assert(triangleVertexIndex <= patchTriangleIndicesCount);
            }
        }
    }

    void Model::calculateTorusWireframeIndices(unsigned int circlesCount, unsigned int pointsPerCircleCount, unsigned int* indices)
    {
        const unsigned int torusVerticesCount = circlesCount * pointsPerCircleCount;

        for (unsigned int i = 0; i < circlesCount; ++i)
        {
            for (unsigned int j = 0; j < pointsPerCircleCount; ++j)
            {
                /* Starting point for vertical and horizontal lines. */
                unsigned int lineStart     = i * pointsPerCircleCount + j;
                /* Horiznotal end of the currently determined line. */
                unsigned int horizontalEnd = (i + 1) * pointsPerCircleCount + j;
                /* Vertical end of the currently determined line. */
                unsigned int verticalEnd   = i * pointsPerCircleCount + j + 1;

                /* From the last circle, horizontal lines go to the first one. */
                if (horizontalEnd >= torusVerticesCount)
                {
                    horizontalEnd -= torusVerticesCount;
                }

                /* From the last point in the circle, vertical lines go to the first one. */
                if (verticalEnd >= (i + 1) * pointsPerCircleCount)
                {
                    verticalEnd -= pointsPerCircleCount;
                }

                /* Determine horizontal line indices. */
                indices[(i * pointsPerCircleCount + j) * 4    ] = lineStart;
                indices[(i * pointsPerCircleCount + j) * 4 + 1] = horizontalEnd;

                /* Determine vertical line indices. */
                indices[(i * pointsPerCircleCount + j) * 4 + 2] = lineStart;
                indices[(i * pointsPerCircleCount + j) * 4 + 3] = verticalEnd;
            }
        }
    }

    void Model::generateTorusVertices(float torusRadius, float circleRadius, unsigned int circlesCount, unsigned int pointsPerCircleCount, float* vertices)
    {
        if (vertices == NULL)
        {
            LOGE("Cannot use null pointer while calculating torus vertices.");

            return;
        }

        /* Index variable. */
        unsigned int componentIndex = 0;

        for (unsigned int horizontalIndex = 0; horizontalIndex < circlesCount; ++horizontalIndex)
        {
            /* Angle in radians on XZ plane. */
            float xyAngle = (float) horizontalIndex * 2.0f * M_PI / circlesCount;

            for (unsigned int verticalIndex = 0; verticalIndex < pointsPerCircleCount; ++verticalIndex)
            {
                /* Angle in radians on XY plane. */
                float theta  = (float) verticalIndex * 2.0f * M_PI / pointsPerCircleCount;

                /* X coordinate. */
                vertices[componentIndex++] = (torusRadius + circleRadius * cosf(theta)) * cosf(xyAngle);
                /* Y coordinate. */
                vertices[componentIndex++] = circleRadius * sinf(theta);
                /* Z coordinate. */
                vertices[componentIndex++] = (torusRadius + circleRadius * cosf(theta)) * sinf(xyAngle);
                /* W coordinate. */
                vertices[componentIndex++] = 1.0f;
            }
        }
    }

    void Model::calculateTorusTriangleStripIndices(unsigned int circlesCount, unsigned int pointsPerCircleCount, unsigned int* indices)
    {
        const unsigned int torusVerticesCount = circlesCount * pointsPerCircleCount;
        const unsigned int torusIndicesCount  = (2 * circlesCount + 1) * pointsPerCircleCount + 1;

        unsigned int counter = 0;
        unsigned int currentIndex = 0;

        indices[counter++] = currentIndex;

        bool isLastStrip = false;

        for (unsigned int stripIndex = 0; stripIndex < pointsPerCircleCount; ++stripIndex)
        {
            assert(currentIndex == stripIndex);

            /* Set initial index for the current strip. */
            currentIndex += 1;

            isLastStrip = currentIndex >= pointsPerCircleCount;

            assert(counter < torusIndicesCount);

            indices[counter++] = isLastStrip ? (currentIndex - pointsPerCircleCount) : currentIndex;

            for (unsigned int circleIndex = 0; circleIndex < circlesCount; ++circleIndex)
            {
                currentIndex = currentIndex + pointsPerCircleCount - 1;

                if (currentIndex >= torusVerticesCount)
                {
                    currentIndex -= torusVerticesCount;
                }

                assert(counter < torusIndicesCount);

                indices[counter++] = currentIndex;

                currentIndex += 1;

                assert(counter < torusIndicesCount);

                indices[counter++] = isLastStrip ? currentIndex - pointsPerCircleCount : currentIndex;
            }
        }
    }

    void Model::generateTorusBezierVertices(float torusRadius, float circleRadius, float* vertices)
    {
        if (vertices == NULL)
        {
            LOGE("Cannot use null pointer while calculating torus vertices.");

            return;
        }

        /* Coefficient relating radius of a circle to the distance between middle patch control point and the closest edge point. */
        const float kappa = 4.0f * (sqrtf(2.0f) - 1.0f) / 3.0f;
        /* Angle between circle radius connecting a patch edge point and a line segment connecting the circle center and a middle patch control point. */
        const float alpha = atanf(kappa);
        /* Length of a line segment connecting circle center and a middle control point. */
        const float distortedCircleRadius = circleRadius * sqrt(1.0f + kappa * kappa);
        /* Length of a line segment connecting torus center and a middle control poin. */
        const float distortedTorusRadius = torusRadius  * sqrt(1.0f + kappa * kappa);
        /* Each circle is divided into 4 quadrants to simplify calculations. */
        const int quadrantsCount = 4;
        /* Number of circles in torus model. */
        const int circlesCount = 12;
        /* Number of points in one circle. */
        const int pointsPerCircleCount = 12;

        /* Angle in horizontal plane XZ, used only to point on edge points. */
        float phi = 0.0f;
        /* Angle in vertical plane XY, used only to point on edge points. */
        float theta = 0.0f;

        /* Index of currently calculated component. */
        unsigned int componentIndex = 0;

        /* Iterate through all circles. */
        for (int horizontalIndex = 0; horizontalIndex < circlesCount; ++horizontalIndex)
        {
            /* Index of a circle in a torus quadrant. */
            const int currentCircleModulo = horizontalIndex % (quadrantsCount - 1);

            /* Temporary variables holding current values of radii and angles. */
            float currentTorusRadius;
            float currentCircleRadius;
            float currentPhi;
            float currentTheta;

            switch (currentCircleModulo)
            {
            case 0:
                /* Edge points take non-distorted parameters. */
                currentTorusRadius = torusRadius;
                currentPhi         = phi;
                break;
            case 1:
                /* 1st middle point. Angle value is related to the angle of preceding edge point. */
                currentTorusRadius = distortedTorusRadius;
                currentPhi         = phi + alpha;
                break;
            case 2:
                /* Second middle point. Angle value is related to the angle of the following edge point. */
                phi                = (float) (horizontalIndex + 1) * M_PI / (2 * (quadrantsCount - 1));
                currentTorusRadius = distortedTorusRadius;
                currentPhi         = phi - alpha;
                break;
            }

            for (int verticalIndex = 0; verticalIndex < pointsPerCircleCount; ++verticalIndex)
            {
                /* Index of a point in a circle quadrant. */
                const int currentPointModulo = verticalIndex   % (quadrantsCount - 1);

                switch (currentPointModulo)
                {
                case 0:
                    /* Edge points take non-distorted parameters. */
                    currentCircleRadius = circleRadius;
                    currentTheta        = theta;
                    break;
                case 1:
                    /* 1st middle point. Angle value is related to the angle of preceding edge point. */
                    currentCircleRadius = distortedCircleRadius;
                    currentTheta        = theta + alpha;
                    break;
                case 2:
                    /* Second middle point. Angle value is related to the angle of the following edge point. */
                    theta               = (float) (verticalIndex + 1) * M_PI / (2 * (quadrantsCount - 1));
                    currentCircleRadius = distortedCircleRadius;
                    currentTheta        = theta - alpha;
                }

                /* Store values in the array. */
                vertices[componentIndex++] = (currentTorusRadius + currentCircleRadius * cosf(currentTheta)) * cosf(currentPhi);
                vertices[componentIndex++] =  currentCircleRadius * sinf(currentTheta);
                vertices[componentIndex++] = (currentTorusRadius + currentCircleRadius * cosf(currentTheta)) * sinf(currentPhi);
                vertices[componentIndex++] = 1.0f;
            }
        }
    }
}