/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include "VectorTypes.h"
#include "Mathematics.h"
#include "Platform.h"
#include <vector>

namespace BotsonSDK
{
    /**
     * \brief Functions for generating cube shapes.
     */
    class CubeModel
    {
    public:
        typedef std::vector<float> coordinates_array;

    private:
        /**
         * \brief Appends content of appendee to target
         *
         * \param      target   Container to append data to
         * \param[out] appendee Container to append data from
         */
        static void append(coordinates_array& target, coordinates_array& appendee);

    public:
        /**
         * \brief Compute coordinates of points which make up a cube.
         *
         * \param[in] scalingFactor Scaling factor indicating size of a cube.
         * \param[out] coordinates Container will be used to store generated coordinates. Cannot be null.
         */
        static void getTriangleRepresentation(float scalingFactor, coordinates_array& coordinates);

       /**
        * \brief Compute coordinates of points which make up a ube shape.
        *
        * \param coordinatesPtrPtr      Deref will be used to store generated coordinates.
        *                               Cannot be null.
        * \param numberOfCoordinatesPtr Number of generated coordinates.
        * \param scalingFactor          Scaling factor indicating size of a cube.
        */
        static void getTriangleRepresentation(float** coordinatesPtrPtr,
                                              int*    numberOfCoordinatesPtr,
                                              float   scalingFactor);

        static void getTriangleRepresentation(float scalingFactor, 
                                              int* numberOfCoordinates, 
                                              float** coordinates);

        /**
         * \brief Create normals for a cube which was created with getTriangleRepresentation() function.
         *
         * \param[out] normals Container will be used to store generated normal vectors. Cannot be null.
         */
        static void getNormals(coordinates_array& normals);

        /** 
         * \brief Create normals for a cube which was created with getTriangleRepresentation() function.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] normals Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getNormals(int* numberOfCoordinates, float** normals);

       /**
        * \brief Create normals for a cube.
        *
        * \param normalsPtrPtr          Deref will be used to store generated coordinates.
        *                               Cannot be null.
        * \param numberOfCoordinatesPtr Number of generated coordinates.
        */
        static void getNormals(float** normalsPtrPtr, int* numberOfCoordinatesPtr);


    };
}
#endif /* CUBE_MODEL_H */
