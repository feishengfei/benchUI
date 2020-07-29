/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include "CubeModel.h"

#include <cstdlib>

namespace BotsonSDK
{   
    void CubeModel::append(coordinates_array& target, coordinates_array& appendee)
    {
        target.insert(target.end(), appendee.begin(), appendee.end());
    }

    void CubeModel::getTriangleRepresentation(float scalingFactor, coordinates_array& coordinates)
    {
        /* 6 faces, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeTriangleCoordinates = 6 * 2 * 3 * 3;

        /* Allocate memory for result array. */
        coordinates.reserve(numberOfCubeTriangleCoordinates);

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
        /* Scaled cube points */
        const int coordinates_count = 3;
        float vertex_A_coordinates_data[coordinates_count] = {-scalingFactor,  scalingFactor,  scalingFactor};
        float vertex_B_coordinates_data[coordinates_count] = {-scalingFactor,  scalingFactor, -scalingFactor};
        float vertex_C_coordinates_data[coordinates_count] = { scalingFactor,  scalingFactor, -scalingFactor};
        float vertex_D_coordinates_data[coordinates_count] = { scalingFactor,  scalingFactor,  scalingFactor};
        float vertex_E_coordinates_data[coordinates_count] = {-scalingFactor, -scalingFactor,  scalingFactor};
        float vertex_F_coordinates_data[coordinates_count] = {-scalingFactor, -scalingFactor, -scalingFactor};
        float vertex_G_coordinates_data[coordinates_count] = { scalingFactor, -scalingFactor, -scalingFactor};
        float vertex_H_coordinates_data[coordinates_count] = { scalingFactor, -scalingFactor,  scalingFactor};

        coordinates_array vertexA(vertex_A_coordinates_data, vertex_A_coordinates_data + coordinates_count);
        coordinates_array vertexB(vertex_B_coordinates_data, vertex_B_coordinates_data + coordinates_count);
        coordinates_array vertexC(vertex_C_coordinates_data, vertex_C_coordinates_data + coordinates_count);
        coordinates_array vertexD(vertex_D_coordinates_data, vertex_D_coordinates_data + coordinates_count);
        coordinates_array vertexE(vertex_E_coordinates_data, vertex_E_coordinates_data + coordinates_count);
        coordinates_array vertexF(vertex_F_coordinates_data, vertex_F_coordinates_data + coordinates_count);
        coordinates_array vertexG(vertex_G_coordinates_data, vertex_G_coordinates_data + coordinates_count);
        coordinates_array vertexH(vertex_H_coordinates_data, vertex_H_coordinates_data + coordinates_count);

        /* Fill the array with coordinates. */
        /* Top face. */
        /* CBA */
        append(coordinates, vertexC);
        append(coordinates, vertexB);
        append(coordinates, vertexA);

        /* DCA */
        append(coordinates, vertexD);
        append(coordinates, vertexC);
        append(coordinates, vertexA);

        /* Bottom face. */
        /* EFG */
        append(coordinates, vertexE);
        append(coordinates, vertexF);
        append(coordinates, vertexG);

        /* EGH */
        append(coordinates, vertexE);
        append(coordinates, vertexG);
        append(coordinates, vertexH);

        /* Back face. */
        /* BCG */
        append(coordinates, vertexB);
        append(coordinates, vertexC);
        append(coordinates, vertexG);

        /* FBG */
        append(coordinates, vertexF);
        append(coordinates, vertexB);
        append(coordinates, vertexG);

        /* Front face. */
        /* DAE */
        append(coordinates, vertexD);
        append(coordinates, vertexA);
        append(coordinates, vertexE);

        /* HDE */
        append(coordinates, vertexH);
        append(coordinates, vertexD);
        append(coordinates, vertexE);

        /* Right face. */
        /* CDH */
        append(coordinates, vertexC);
        append(coordinates, vertexD);
        append(coordinates, vertexH);

        /* GCH */
        append(coordinates, vertexG);
        append(coordinates, vertexC);
        append(coordinates, vertexH);

        /* Left face. */
        /* ABF */
        append(coordinates, vertexA);
        append(coordinates, vertexB);
        append(coordinates, vertexF);

        /* EAF */
        append(coordinates, vertexE);
        append(coordinates, vertexA);
        append(coordinates, vertexF);
    }

    void CubeModel::getTriangleRepresentation(float** coordinatesPtrPtr, int*    numberOfCoordinatesPtr, float   scalingFactor)
    {
        ASSERT(coordinatesPtrPtr != NULL,
            "Cannot use null pointer while calculating coordinates");

        /* Index of an array we will put new point coordinates at. */
        int       currentIndex                    = 0;
        /* 6 faces of open cube, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeTriangleCoordinates = NUMBER_OF_CUBE_FACES        *
                                                    NUMBER_OF_TRIANGLES_IN_QUAD *
                                                    NUMBER_OF_TRIANGLE_VERTICES *
                                                    NUMBER_OF_POINT_COORDINATES;

        /* Allocate memory for result array. */
        *coordinatesPtrPtr = (float*) malloc(numberOfCubeTriangleCoordinates * sizeof(float));

        /* Is allocation successful?. */
        ASSERT(*coordinatesPtrPtr != NULL,
               "Could not allocate memory for result array.")

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

        const Vec3f pointA = {-1.0f,  1.0f,  1.0f};
        const Vec3f pointB = {-1.0f,  1.0f, -1.0f};
        const Vec3f pointC = { 1.0f,  1.0f, -1.0f};
        const Vec3f pointD = { 1.0f,  1.0f,  1.0f};
        const Vec3f pointE = {-1.0f, -1.0f,  1.0f};
        const Vec3f pointF = {-1.0f, -1.0f, -1.0f};
        const Vec3f pointG = { 1.0f, -1.0f, -1.0f};
        const Vec3f pointH = { 1.0f, -1.0f,  1.0f};

        /* Fill the array with coordinates. */
        /* Top face. */
        /* A */
        (*coordinatesPtrPtr)[currentIndex++] = pointA.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.z;
        /* B */
        (*coordinatesPtrPtr)[currentIndex++] = pointB.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.z;
        /* C */
        (*coordinatesPtrPtr)[currentIndex++] = pointC.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.z;

        /* A */
        (*coordinatesPtrPtr)[currentIndex++] = pointA.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.z;
        /* C */
        (*coordinatesPtrPtr)[currentIndex++] = pointC.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.z;
        /* D */
        (*coordinatesPtrPtr)[currentIndex++] = pointD.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.z;

        /* Bottom face. */
        /* F */
        (*coordinatesPtrPtr)[currentIndex++] = pointF.x;;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.y;;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.z;;
        /* E */
        (*coordinatesPtrPtr)[currentIndex++] = pointE.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.z;
        /* H */
        (*coordinatesPtrPtr)[currentIndex++] = pointH.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.z;

        /* F */
        (*coordinatesPtrPtr)[currentIndex++] = pointF.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.z;
        /* H */
        (*coordinatesPtrPtr)[currentIndex++] = pointH.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.z;
        /* G */
        (*coordinatesPtrPtr)[currentIndex++] = pointG.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.z;

        /* Back face. */
        /* G */
        (*coordinatesPtrPtr)[currentIndex++] = pointG.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.z;
        /* C */
        (*coordinatesPtrPtr)[currentIndex++] = pointC.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.z;
        /* B */
        (*coordinatesPtrPtr)[currentIndex++] = pointB.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.z;

        /* G */
        (*coordinatesPtrPtr)[currentIndex++] = pointG.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.z;
        /* B */
        (*coordinatesPtrPtr)[currentIndex++] = pointB.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.z;
        /* F */
        (*coordinatesPtrPtr)[currentIndex++] = pointF.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.z;

        /* Front face. */
        /* E */
        (*coordinatesPtrPtr)[currentIndex++] = pointE.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.z;
        /* A */
        (*coordinatesPtrPtr)[currentIndex++] = pointA.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.z;
        /* D */
        (*coordinatesPtrPtr)[currentIndex++] = pointD.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.z;

        /* E */
        (*coordinatesPtrPtr)[currentIndex++] = pointE.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.z;
        /* D */
        (*coordinatesPtrPtr)[currentIndex++] = pointD.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.z;
        /* H */
        (*coordinatesPtrPtr)[currentIndex++] = pointH.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.z;

        /* Right face. */
        /* H */
        (*coordinatesPtrPtr)[currentIndex++] = pointH.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.z;
        /* D */
        (*coordinatesPtrPtr)[currentIndex++] = pointD.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointD.z;
        /* C */
        (*coordinatesPtrPtr)[currentIndex++] = pointC.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.z;

        /* H */
        (*coordinatesPtrPtr)[currentIndex++] = pointH.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointH.z;
        /* C */
        (*coordinatesPtrPtr)[currentIndex++] = pointC.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointC.z;
        /* G */
        (*coordinatesPtrPtr)[currentIndex++] = pointG.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointG.z;

        /* Left face. */
        /* F */
        (*coordinatesPtrPtr)[currentIndex++] = pointF.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.z;
        /* B */
        (*coordinatesPtrPtr)[currentIndex++] = pointB.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointB.z;
        /* A */
        (*coordinatesPtrPtr)[currentIndex++] = pointA.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.z;

        /* F */
        (*coordinatesPtrPtr)[currentIndex++] = pointF.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointF.z;
        /* A */
        (*coordinatesPtrPtr)[currentIndex++] = pointA.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointA.z;
        /* E */
        (*coordinatesPtrPtr)[currentIndex++] = pointE.x;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.y;
        (*coordinatesPtrPtr)[currentIndex++] = pointE.z;

        /* Calculate size of a cube. */
        if (scalingFactor != 1.0f)
        {
            for (int i = 0; i < numberOfCubeTriangleCoordinates; i++)
            {
                (*coordinatesPtrPtr)[i] *= scalingFactor;
            }
        }

        if (numberOfCoordinatesPtr != NULL)
        {
            *numberOfCoordinatesPtr = numberOfCubeTriangleCoordinates;
        }
    }
    
    void CubeModel::getTriangleRepresentation(float scalingFactor, int* numberOfCoordinates, float** coordinates)
    {
        if (coordinates == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");
            return;
        }

        /* 6 faces, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeTriangleCoordinates = 6 * 2 * 3 * 3;
        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /* Allocate memory for result array. */
        *coordinates = (float*) malloc (numberOfCubeTriangleCoordinates * sizeof(float));

        /* Is allocation successful?. */
        if (*coordinates == NULL)
        {
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
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;

        /* Bottom face. */
        /*E*/                              
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*F*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*G*/
        (*coordinates)[currentIndex] =  1.0f;
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
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*G*/ 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*H*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;

        /* Back face. */
        /*G*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;

        /*G*/
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++;
        /*B*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
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
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*A*/
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] =  1.0f;
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
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] = 1.0f;
        currentIndex++;  
        (*coordinates)[currentIndex] = 1.0f; 
        currentIndex++;
        (*coordinates)[currentIndex] = 1.0f; 
        currentIndex++;
        /*H*/
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;

        /* Right face. */
        /*H*/                             
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++;
        /*D*/
        (*coordinates)[currentIndex] = 1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] = 1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] = 1.0f; 
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++;

        /*H*/                              
        (*coordinates)[currentIndex] =  1.0f;
        currentIndex++; 
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;
        /*C*/
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++;
        /*G*/
        (*coordinates)[currentIndex] =  1.0f; 
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
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++;
        /*A*/
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f; 
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
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++; 
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;
        /*E*/                            
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++;
        (*coordinates)[currentIndex] = -1.0f; 
        currentIndex++;
        (*coordinates)[currentIndex] =  1.0f; 
        currentIndex++;

        /* Calculate size of a cube. */
        for (int i = 0; i < numberOfCubeTriangleCoordinates; i++)
        {
            (*coordinates)[i] = scalingFactor * (*coordinates)[i];
        }
        
        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfCubeTriangleCoordinates;
        }
    }

    void CubeModel::getNormals(coordinates_array& normals)
    {
        /* Set the same normals for both triangles from each face.
         * For details: see example for getCubeTriangleRepresentation() function.
         */

        /* 6 faces, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeNormalsCoordinates = 6 * 2 * 3 * 3;

        /* Allocate memory for result array. */
        normals.reserve(numberOfCubeNormalsCoordinates);

        /* There are 2 triangles for each face. Each triangle consists of 3 vertices. */
        int numberOfCoordinatesForOneFace = 2 * 3;

        /* Top face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            normals.push_back( 0.0f);
            normals.push_back( 1.0f);
            normals.push_back( 0.0f);
        }

        /* Bottom face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            normals.push_back( 0.0f);
            normals.push_back(-1.0f);
            normals.push_back( 0.0f);
        }

        /* Back face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            normals.push_back( 0.0f);
            normals.push_back( 0.0f);
            normals.push_back(-1.0f);
        }

        /* Front face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            normals.push_back( 0.0f);
            normals.push_back( 0.0f);
            normals.push_back( 1.0f);
        }

        /* Right face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            normals.push_back( 1.0f);
            normals.push_back( 0.0f);
            normals.push_back( 0.0f);
        }

        /* Left face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            normals.push_back(-1.0f);
            normals.push_back( 0.0f);
            normals.push_back( 0.0f);
        }
    }
    void CubeModel::getNormals(int* numberOfCoordinates, float** normals)
    {
        /* Set the same normals for both triangles from each face.
         * For details: see example for getCubeTriangleRepresentation() function. 
         */

        if (normals == NULL)
        {
            LOGE("Cannot use null pointer while calculating coordinates.");

            return;
        }

        /* 6 faces, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
        const int numberOfCubeNormalsCoordinates = 6 * 2 * 3 * 3;
        /* Index of an array we will put new point coordinates at. */
        int currentIndex = 0;

        /* Allocate memory for result array. */
        *normals = (float*) malloc (numberOfCubeNormalsCoordinates * sizeof(float));

        /* Is allocation successfu?. */
        if (*normals == NULL)
        {
            LOGE("Could not allocate memory for result array.");

            return;
        }

        /* There are 2 triangles for each face. Each triangle consists of 3 vertices. */
        int numberOfCoordinatesForOneFace = 2 * 3;

        /* Top face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        /* Bottom face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            (*normals)[currentIndex] =  0;
            currentIndex++;
            (*normals)[currentIndex] = -1;
            currentIndex++;
            (*normals)[currentIndex] =  0;
            currentIndex++;
        }

        /* Back face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            (*normals)[currentIndex] =  0;
            currentIndex++;
            (*normals)[currentIndex] =  0;
            currentIndex++;
            (*normals)[currentIndex] =  -1;
            currentIndex++;
        }

        /* Front face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 1;
            currentIndex++;
        }

        /* Right face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            (*normals)[currentIndex] = 1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        /* Left face. */
        for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
        {
            (*normals)[currentIndex] = -1;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
            (*normals)[currentIndex] = 0;
            currentIndex++;
        }

        if (numberOfCoordinates != NULL)
        {
            *numberOfCoordinates = numberOfCubeNormalsCoordinates;
        
        }
    }

  void CubeModel::getNormals(float** normalsPtrPtr,
                             int*    numberOfCoordinatesPtr)
  {
     /* Set the same normals for both triangles from each face.
      * For details: see example for getCubeTriangleRepresentation() function. */
      ASSERT(normalsPtrPtr != NULL,
             "Cannot use null pointer while calculating coordinates");

      /* Index of an array we will put new point coordinates at. */
      int       currentIndex                   = 0;
      /* 6 faces of open cube, 2 triangles for each face, 3 points of triangle, 3 coordinates for each point. */
      const int numberOfCubeNormalsCoordinates = NUMBER_OF_CUBE_FACES        *
                                                 NUMBER_OF_TRIANGLES_IN_QUAD *
                                                 NUMBER_OF_TRIANGLE_VERTICES *
                                                 NUMBER_OF_POINT_COORDINATES;
      /* There are 2 triangles for each face. Each triangle consists of 3 vertices. */
      const int numberOfCoordinatesForOneFace  = NUMBER_OF_TRIANGLES_IN_QUAD *
                                                 NUMBER_OF_TRIANGLE_VERTICES;

      /* Allocate memory for result array. */
      *normalsPtrPtr = (float*) malloc(numberOfCubeNormalsCoordinates * sizeof(float));

      /* Is allocation successful?. */
      ASSERT(*normalsPtrPtr != NULL,
             "Could not allocate memory for result array");

      /* Top face. */
      for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
      {
          (*normalsPtrPtr)[currentIndex++] = 0;
          (*normalsPtrPtr)[currentIndex++] = 1;
          (*normalsPtrPtr)[currentIndex++] = 0;
      }

      /* Bottom face. */
      for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
      {
          (*normalsPtrPtr)[currentIndex++] =  0;
          (*normalsPtrPtr)[currentIndex++] = -1;
          (*normalsPtrPtr)[currentIndex++] =  0;
      }

      /* Back face. */
      for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
      {
          (*normalsPtrPtr)[currentIndex++] =  0;
          (*normalsPtrPtr)[currentIndex++] =  0;
          (*normalsPtrPtr)[currentIndex++] = -1;
      }

      /* Front face. */
      for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
      {
          (*normalsPtrPtr)[currentIndex++] = 0;
          (*normalsPtrPtr)[currentIndex++] = 0;
          (*normalsPtrPtr)[currentIndex++] = 1;
      }

      /* Right face. */
      for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
      {
          (*normalsPtrPtr)[currentIndex++] = 1;
          (*normalsPtrPtr)[currentIndex++] = 0;
          (*normalsPtrPtr)[currentIndex++] = 0;
      }

      /* Left face. */
      for (int i = 0; i < numberOfCoordinatesForOneFace; i++)
      {
          (*normalsPtrPtr)[currentIndex++] = -1;
          (*normalsPtrPtr)[currentIndex++] =  0;
          (*normalsPtrPtr)[currentIndex++] =  0;
      }

      if (numberOfCoordinatesPtr != NULL)
      {
          *numberOfCoordinatesPtr = numberOfCubeNormalsCoordinates;
      }
  }
}
