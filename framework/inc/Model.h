/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */
#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include "VectorTypes.h"
#include "Matrix.h"

namespace BotsonSDK
{
    /**
     * \brief Functions for generating cube shapes.
     */
    class Model
    {
    public:
        /**
         * \brief Compute coordinates of points which make up a cube.
         *
         * \param[in] scalingFactor Scaling factor indicating size of a cube.
         * \param[out] numberOfCoordinates  Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getCubeTriangleRepresentation(float scalingFactor, int* numberOfCoordinates, float** coordinates);

        /**
         * \brief Create normals for a cube which was created with getTriangleRepresentation() function.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] normals Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getCubeNormals(int* numberOfCoordinates, float** normals);

        /**
         * \brief Get coordinates of points which make up a plane. The plane is located in XZ space.
         *
         * Triangles are made up of 4 components per vertex.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getPlaneTriangleRepresentation(int* numberOfCoordinates, float** coordinates);

        /**
         * \brief Get U/V 2D texture coordinates that can be mapped onto a plane generated from this class.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] uvCoordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getPlaneTriangleRepresentationUVCoordinates(int* numberOfCoordinates, float** uvCoordinates);

        /**
         * \brief Get normals for plane placed in XZ space.
         *
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] normals Deref will be used to store generated normals. Cannot be null.
         */
        static void getPlaneNormals(int* numberOfCoordinates, float** normals);

        /**
         * \brief Transform a plane by a matrix.
         *
         * \param[in] transform The transformation Matrix to apply to the plane.
         * \param[in] numberOfCoordinates Number of coordinates which make up the plane.
         * \param[in, out] coordinates Pointer to the verticies to be transformed. The transformed verticies will be returned in the same memory. Cannot be null.
         */
        static void transformPlane(Matrix transform, int numberOfCoordinates, float** coordinates);

    private:
        /**
         * \brief Compute coordinates of points which make up a sphere.
         *
         * \param[in] radius Radius of a sphere. Has to be greater than zero.
         * \param[in] numberOfSamples Sphere consists of numberOfSamples circles and numberOfSamples points lying on one circle. Has to be greater than zero.
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getSpherePointRepresentation(const float radius, const int numberOfSamples, int* numberOfCoordinates, float** coordinates);
    public:
        /**
         * \brief Create triangular representation of a sphere.
         *
         * For each point of each circle (excluding last circle) there are two triangles created according to rule described in example below:
         *
         *                A2___________.B2
         *                . \       .  / |
         *                |. \   .    /  |
         *                | . A1____B1   |
         *                |  . |     |.  |
         *                |   D1____C1 . |
         *                |  /    .   \ .|
         *                | /  .       \ .
         *               D2 .___________C2
         *
         * Points named A1, B1, C1 and D1 create a first circle of sphere and points named A2, B2, C2 and D2 create the second one
         * (if numberOfSamples is equal to 4). For each loop iteration, for each point lying at one circle of sphere there are 2 triangles created:
         * for point A1:  A1 B1 B2,   A1 B2 A2
         * for point B1:  B1 C1 C2,   B1 C2 B2
         * for point C1:  C1 D1 D2,   C1 D2 C2
         * for point D1:  D1 A1 A2,   D1 A2 D2
         *
         * \param[in] radius Radius of a sphere. Has to be greater than zero.
         * \param[in] numberOfSamples A sphere consists of numberOfSamples circles and numberOfSamples points lying on one circle. Has to be greater than zero.
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] coordinates Deref will be used to store generated coordinates. Cannot be null.
         */
        static void getSphereTriangleRepresentation(const float radius, const int numberOfSamples, int* numberOfCoordinates, float** coordinates);

        /**
          * \brief Compute normal vector of a super ellipsoid.
          *
          * Whole shape lies at the centre of a box of dimension (-1, 1) on every axis.
          *
          * \param[in] xyAngle XY angle for which we compute a vertex.
          * \param[in] xzAngle XZ angle for which we compute a vertex.
          * \param[in] n1 The "squareness" of our figure - property that tells how rounded the geometry will be in XZ space.
          * \param[in] n2 The "squareness" of our figure - property that tells how rounded the geometry will be in XY space.
          * \param[in] scale Scale factor applied to the object.
          *
          * \return The normal vector of the super ellipsoid.
          */
        inline static Vec3f calculateSuperNormal(float xyAngle, float xzAngle, float n1, float n2, float scale);

        /**
         * \brief Compute vertex of a super ellipsoid.
         *
         * Whole shape lies at the centre of a box of dimension (-1, 1) on every axis.
         *
         * \param[in] xyAngle XY angle for which we compute a vertex.
         * \param[in] xzAngle XZ angle for which we compute a vertex.
         * \param[in] n1 The "squareness" of our figure - property that tells how rounded the geometry will be in XZ space.
         * \param[in] n2 The "squareness" of our figure - property that tells how rounded the geometry will be in XY space.
         * \param[in] scale Scale factor applied to the object.
         *
         * \return point of the super ellipsoid.
         */
        inline static Vec3f sampleSuper(float xyAngle, float xzAngle, float n1, float n2, float scale);

        /**
         * \brief Put vertex and normal vector values into vertex array and normal vector array.
         *
         * We modify vertexIndex and normalVectorIndex inside this function in order to simplify
         * algorithm in the createSuperEllipsoid function.
         *
         * \param[in] vertex Vertex that will be saved in vertex array.
         * \param[in] normalVector Normal vector that will be saved in normal vector array.
         * \param[in] vertexIndex Vertex array index where new coordinate should be saved.
         * \param[out] normalVectorIndex Normal vector array index where new coordinate should be saved.
         * \param[out] roundedCubeCoordinates Pointer to an array that holds rounded cube's coordinates.
         * \param[out] roundedCubeNormalVectors Pointer to an array that holds rounded cube's normal vectors.
         */
        inline static void storeSuperVertexAndNormalVectorInArray(const Vec3f& vertex, const Vec3f& normalVector, int& vertexIndex, int& normalVectorIndex, float* roundedCubeCoordinates, float* roundedCubeNormalVectors);

    public:
        /**
         * \brief Function that generates vertices and normal vectors of rounded cube.
         *
         * It creates an "unit"-size ellipsoid (-1 to 1) at the origin.
         * This function generates vertices of superellipsoid, a versatile primitive that is controlled
         * by two parameters - n1 and n2. It can represent a sphere,
         * square box, and closed cylindrical can. The parameter samples determine the accuracy of
         * this primitive (if it has sharp or smooth edges). It should be noted that there are
         * some numerical issues with both very small or very large values of n1 and n2
         * parameters. Typically, for safety, they should be in the range of 0.1 to 5.0.
         * After using this function user should deallocate memory reserved for roundedCubeCoordinates and roundedCubeNormalVectors.
         *
         * \param[in] samples The number of triangles that will create super ellipsoid.
         * \param[in] n1 The "squareness" of our figure - property that tells how rounded the geometry will be in XZ space.
         * \param[in] n2 The "squareness" of our figure - property that tells how rounded the geometry will be in XY space.
         * \param[in] scale Scale factor applied to the object.
         * \param[out] roundedCubeCoordinates Pointer to an array that holds rounded cube's coordinates.
         * \param[out] roundedCubeNormalVectors Pointer to an array that holds rounded cube's normal vectors.
         * \param[out] numberOfVertices Number of generated vertices.
         * \param[out] numberOfCoordinates Number of generated coordinates.
         * \param[out] numberOfNormals Number of generated normal vectors.
         */
        static void createSuper(int samples, float n1, float n2, float scale, float** roundedCubeCoordinates, float** roundedCubeNormalVectors, int* numberOfVertices, int* numberOfCoordinates, int* numberOfNormals);

    public:
        /**
         * \brief Generates torus's normal vectors.
         *
         * \param[in] circlesCount Number of circles in torus model.
         * \param[in] pointsPerCircleCount Number of points in one circle.
         * \param[out] normals Deref will be used to store normal vectors.
         */
        static void generateTorusNormals(unsigned int circlesCount, unsigned int pointsPerCircleCount, float* normals);

        /**
         * \brief Determines indices for DrawElements() call for shaded torus drawn in triangle strip mode.
         *
         * \param[in] circlesCount Number of circles in torus model.
         * \param[in] pointsPerCircleCount Number of points in one circle.
         * \param[out] indices Deref will be used to store calculated indices.
         */
        static void calculateTorusTriangleStripIndices(unsigned int circlesCount, unsigned int pointsPerCircleCount, unsigned int* indices);

        /**
         * \brief Generate vertices of the torus model.
         *
         * The vertices are grouped in circlesCount circles, where each circle consists of pointsPerCircleCount vertices.
         *
         * \param[in] torusRadius Distance between the center of torus and the center of its tube.
         * \param[in] circleRadius Radius of circles that model the tube.
         * \param[in] circlesCount Number of circles in torus model.
         * \param[in] pointsPerCircleCount Number of points in one circle.
         * \param[out] vertices Deref will be used to store generated vertices. Cannot be null.
         */
        static void generateTorusVertices(float torusRadius, float circleRadius, unsigned int circlesCount, unsigned int pointsPerCircleCount, float* vertices);

        /**
         * \brief Determines an array of indices defining a mesh of control points for instanced torus patches.
         *
         * To simplify mathemathics, it is assumed that torus model consists of 12 circles, each built of
         * 12 points, so it is easy to divide each circle into 4 quadrants and define Bezier surfaces
         * approximating perfectly round torus.
         *
         * \param[in] patchDimension Number of control points in one dimension for a patch.
         * \param[in] patchInstancesCount Number of instances needed to draw the whole torus.
         * \param[in] controlPointsIndicesCount Number of indices needed to create a control mesh.
         * \param[out] controlPointsIndices Deref will be used to store control points indices. Cannot be null.
         */
        static void calculateTorusControlPointsIndices(unsigned int patchDimension, unsigned int patchInstancesCount, unsigned int controlPointsIndicesCount, unsigned int* controlPointsIndices);

        /**
         * \brief Determines patch data for an instanced torus model.
         *
         * \param[in] patchDensity Number of vertices in one edge of a patch.
         * \param[out] patchVertices Deref will be used to store patch vertices. Cannot be null.
         * \param[out] patchTriangleIndices Deref will be used to store indices of triangle vertices. Cannot be null.
         */
        static void calculateTorusPatchData(unsigned int patchDensity, float* patchVertices, unsigned int* patchTriangleIndices);

        /**
         * \brief Determines indices for glDrawElements() call for wireframed torus.
         *
         * \param[in] circlesCount Number of circles in torus model.
         * \param[in] pointsPerCircleCount Number of points in one circle.
         * \param[out] indices Deref will be used to store calculated indices.
         */
        static void calculateTorusWireframeIndices(unsigned int circlesCount, unsigned int pointsPerCircleCount, unsigned int* indices);


        /**
         * \brief Generate torus vertices applying distortions to some of them.
         *
         * The distortions in control mesh are needed for proper construction of Bezier surface patches.
         * It is assumed that each patch consists of 4 control rows and columns.
         * Hence, in each column and each row, we can distinguish 2 middle control points
         * and 2 edge control points, which are shared between patches. The middle control points have to be moved
         * in such a way that C1 continuity between patches is satisfied.
         * Implemented algorithm assumes that each construction circle contains 12 points and the torus model consists
         * of 12 circles.
         *
         * \param[in] torusRadius Distance between the center of torus and the center of its tube.
         * \param[in] circleRadius Radius of circles that model the tube.
         * \param[out] vertices Deref will be used to sotre generated vertices. Cannot be null.
         */
        static void generateTorusBezierVertices(float torusRadius, float circleRadius, float* vertices);
    };
}
#endif
