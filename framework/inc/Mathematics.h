/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include "VectorTypes.h"

#include <cmath>
#include <cstdlib>
/**
 * \file framework/inc/Mathematics.h
 * \brief Mathematic functions
 */

/**
 * \brief The value of pi.
 */
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif /* M_PI */
#ifndef PI
#define PI 3.14159265358979323846f
#endif /* PI */

#ifndef NUMBER_OF_CUBE_FACES
    /** \brief Number of faces which make up a cubic shape. */
    #define NUMBER_OF_CUBE_FACES (6)
#endif /* NUMBER_OF_CUBE_FACES */

#ifndef NUMBER_OF_POINT_COORDINATES
    /** \brief Number of coordinates for a point in 3D space. */
    #define NUMBER_OF_POINT_COORDINATES (3)
#endif /* NUMBER_OF_POINT_COORDINATES */

#ifndef NUMBER_OF_TRIANGLE_VERTICES
    /** \brief Number of vertices which make up a traingle shape. */
    #define NUMBER_OF_TRIANGLE_VERTICES (3)
#endif /* NUMBER_OF_TRIANGLE_VERTICES */

#ifndef NUMBER_OF_TRIANGLES_IN_QUAD
   /** \brief Number of triangles which make up a quad. */
    #define NUMBER_OF_TRIANGLES_IN_QUAD (2)
#endif /* NUMBER_OF_TRIANGLES_IN_QUAD */

namespace BotsonSDK
{
    /**
     * \brief Compute Euclidean 2-dimensional distance between two points on XY plane.
     * \param[in] point1 First point.
     * \param[in] point2 Second point.
     * \return Distance between points on XY plane.
     */
    inline float distanceBetweenPoints(const Vec2f& point1, const Vec2f& point2)
    {
	    return sqrtf((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
    }

    /**
     * \brief Get the sign of a number.
     * \param[in] f Value to check the sign of.
     * \return -1.0 if the number's sign is minus, 1.0 if the number's sign is plus and 0.0 if the number's sign is indefinite.
     */
    inline float signum(float f)
    {
	    if (f > 0.0f)
	    {
		    return  1.0f;
	    }

	    if (f < 0.0f)
	    {
		    return -1.0f;
	    }

	    return 0.0f;
    }

    /**
     * \brief Generate random number in the 0.0 to 1.0 range.
     * \return Random number in the range 0.0 to 1.0.
     */
    inline float uniformRandomNumber()
    {
	    return rand() / float(RAND_MAX);
    }

    /**
     * \brief Convert an angle in degrees to radians.
     * \param[in] degrees The angle (in degrees) to convert to radians.
     */
    inline float degreesToRadians(float degrees)
    {
        return M_PI * degrees / 180.0f;
    }
    inline float radiansToDegrees(float degrees)
    {
        return 180.0f * degrees / M_PI;
    }

    /**
    * \brief Calculates the Euclidean distance between two points in 3D space.
    *
    * \param startPoint Coordinates of a start point in 3D space.
    * \param endPoint   Coordinates of an end point in 3D space.
    *
    * \return As per description.
    */
    inline float getDistanceBetweenPointsIn3DSpace(Vec3f startPoint, Vec3f endPoint)
    {
        return sqrt(((startPoint.x - endPoint.x) * (startPoint.x - endPoint.x)) +
                    ((startPoint.y - endPoint.y) * (startPoint.y - endPoint.y)) +
                    ((startPoint.z - endPoint.z) * (startPoint.z - endPoint.z))
                    );;
    }
}
#endif /* MATHEMATICS_H */
