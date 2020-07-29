/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

#include "SquareModel.h"
#include "Platform.h"
#include "Mathematics.h"

#include <cstdlib>
#include <cmath>
#include <cassert>

namespace BotsonSDK
{
    int SphereModel::genSquareGrid ( int size, GLfloat **vertices, GLuint **indices )
    {
       int i, j;
       int numIndices = ( size - 1 ) * ( size - 1 ) * 2 * 3;

       // Allocate memory for buffers
       if ( vertices != NULL )
       {
          int numVertices = size * size;
          float stepSize = ( float ) size - 1;
          *vertices = ( GLfloat *) malloc ( sizeof ( GLfloat ) * 3 * numVertices );

          for ( i = 0; i < size; ++i ) // row
          {
             for ( j = 0; j < size; ++j ) // column
             {
                ( *vertices ) [ 3 * ( j + i * size )     ] = i / stepSize;
                ( *vertices ) [ 3 * ( j + i * size ) + 1 ] = j / stepSize;
                ( *vertices ) [ 3 * ( j + i * size ) + 2 ] = 0.0f;
             }
          }
       }

       // Generate the indices
       if ( indices != NULL )
       {
          *indices = ( GLuint *)malloc ( sizeof ( GLuint ) * numIndices );

          for ( i = 0; i < size - 1; ++i )
          {
             for ( j = 0; j < size - 1; ++j )
             {
                // two triangles per quad
                ( *indices ) [ 6 * ( j + i * ( size - 1 ) )     ] = j + ( i )   * ( size )    ;
                ( *indices ) [ 6 * ( j + i * ( size - 1 ) ) + 1 ] = j + ( i )   * ( size ) + 1;
                ( *indices ) [ 6 * ( j + i * ( size - 1 ) ) + 2 ] = j + ( i + 1 ) * ( size ) + 1;

                ( *indices ) [ 6 * ( j + i * ( size - 1 ) ) + 3 ] = j + ( i )   * ( size )    ;
                ( *indices ) [ 6 * ( j + i * ( size - 1 ) ) + 4 ] = j + ( i + 1 ) * ( size ) + 1;
                ( *indices ) [ 6 * ( j + i * ( size - 1 ) ) + 5 ] = j + ( i + 1 ) * ( size )    ;
             }
          }
       }

       return numIndices;
    }
}