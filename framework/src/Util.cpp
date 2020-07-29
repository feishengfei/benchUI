/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include "Util.h"
#include "bmp.h"


using std::string;
using namespace BotsonSDK;


#define ES_PI  (3.14159265f)

namespace BotsonSDK
{
    void btx_init(string file)
    {
        windowWidth = WINDOW_W;
        windowHeight = WINDOW_H;
        string filename = file + ".log";
        printf("log filename: %s\nfile: %s\n",filename.c_str(), file.c_str());
        fp_log = fopen(filename.c_str(), "wt");
        if(fp_log == NULL) {
      	    printf("file open failed\n");
    	      return;
        }
    }

    void btx_deinit(void)
    {
        fclose(fp_log);
    }

   void log(const char* format, ...)
   {
       va_list vp;
       va_start(vp,format);
       vfprintf(fp_log,format,vp);
       va_end(vp);
       fflush(fp_log);
   }


    char * getTime()
    {
        static char t[30];
        struct timeb tb;
        ftime(&tb);
        sprintf(t ,"%s:%d",__TIME__, tb.millitm);

        return t;
    }


    GLboolean check_gl_error_(GLenum expected_error, const char *file, unsigned line)
    {
        GLenum actual_error;

        actual_error = glGetError();
        if (actual_error == expected_error) {
            return GL_TRUE;
        }

        LOGE("Unexpected GL error: %s 0x%x\n", get_error_name(actual_error), actual_error);
        LOGE("(Error at %s:%u)\n", file, line);

        if (expected_error != GL_NO_ERROR) {
            LOGE("Expected GL error: %s 0x%x\n", get_error_name(expected_error), expected_error);
        }

        return GL_FALSE;
    }


    string getFileName(string file)
    {
        string::size_type pos = file.find_last_of('/')+1;
        return file.substr(pos, file.length() - pos);
    }

    void save2bmp(string filename)
    {
        unsigned int *readPixelBuffer;
        readPixelBuffer = (unsigned int *)malloc(windowWidth * windowHeight * sizeof(unsigned int));
        glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, readPixelBuffer);
        struct bmp_data bmp_data;
        bmp_data.width = windowWidth;
        bmp_data.height = windowHeight;
        bmp_data.image_size = windowWidth * windowHeight;
        bmp_data.rgb.red = (unsigned char *)malloc(windowWidth * windowHeight);
        bmp_data.rgb.green = (unsigned char *)malloc(windowWidth * windowHeight);
        bmp_data.rgb.blue = (unsigned char *)malloc(windowWidth * windowHeight);
        bmp_data.rgb.alpha = (unsigned char *)malloc(windowWidth * windowHeight);
        stream_to_rgba((unsigned int *)readPixelBuffer, bmp_data);
        write_bmp(filename.c_str(), bmp_data);
    }

    int  genSphere ( int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
                       GLfloat **texCoords, GLuint **indices )
    {
        int i;
        int j;
        int numParallels = numSlices / 2;
        int numVertices = ( numParallels + 1 ) * ( numSlices + 1 );
        int numIndices = numParallels * numSlices * 6;
        float angleStep = ( 2.0f * ES_PI ) / ( ( float ) numSlices );

        // Allocate memory for buffers
        if ( vertices != NULL )
        {
            *vertices = ( GLfloat *)malloc ( sizeof ( GLfloat ) * 3 * numVertices );
        }

        if ( normals != NULL )
        {
            *normals = ( GLfloat *)malloc ( sizeof ( GLfloat ) * 3 * numVertices );
        }

        if ( texCoords != NULL )
        {
            *texCoords = ( GLfloat *)malloc ( sizeof ( GLfloat ) * 2 * numVertices );
        }

        if ( indices != NULL )
        {
            *indices = ( GLuint *)malloc ( sizeof ( GLuint ) * numIndices );
        }

        for ( i = 0; i < numParallels + 1; i++ )
        {
            for ( j = 0; j < numSlices + 1; j++ )
            {
                int vertex = ( i * ( numSlices + 1 ) + j ) * 3;

                if ( vertices )
                {
                    ( *vertices ) [vertex + 0] = radius * sinf ( angleStep * ( float ) i ) *
                                                 sinf ( angleStep * ( float ) j );
                    ( *vertices ) [vertex + 1] = radius * cosf ( angleStep * ( float ) i );
                    ( *vertices ) [vertex + 2] = radius * sinf ( angleStep * ( float ) i ) *
                                                 cosf ( angleStep * ( float ) j );
                }

                if ( normals )
                {
                    ( *normals ) [vertex + 0] = ( *vertices ) [vertex + 0] / radius;
                    ( *normals ) [vertex + 1] = ( *vertices ) [vertex + 1] / radius;
                    ( *normals ) [vertex + 2] = ( *vertices ) [vertex + 2] / radius;
                }

                if ( texCoords )
                {
                    int texIndex = ( i * ( numSlices + 1 ) + j ) * 2;
                    ( *texCoords ) [texIndex + 0] = ( float ) j / ( float ) numSlices;
                    ( *texCoords ) [texIndex + 1] = ( 1.0f - ( float ) i ) / ( float ) ( numParallels - 1 );
                }
            }
        }

        // Generate the indices
        if ( indices != NULL )
        {
            GLuint *indexBuf = ( *indices );

            for ( i = 0; i < numParallels ; i++ )
            {
                for ( j = 0; j < numSlices; j++ )
                {
                    *indexBuf++  = i * ( numSlices + 1 ) + j;
                    *indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + j;
                    *indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );

                    *indexBuf++ = i * ( numSlices + 1 ) + j;
                    *indexBuf++ = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );
                    *indexBuf++ = i * ( numSlices + 1 ) + ( j + 1 );
                }
            }
        }

        return numIndices;
    }

    int  genCube ( float scale, GLfloat **vertices, GLfloat **normals,
                     GLfloat **texCoords, GLuint **indices )
    {
        int i;
        int numVertices = 24;
        int numIndices = 36;

        GLfloat cubeVerts[] =
                        {
                                -0.5f, -0.5f, -0.5f,
                                -0.5f, -0.5f,  0.5f,
                                0.5f, -0.5f,  0.5f,
                                0.5f, -0.5f, -0.5f,
                                -0.5f,  0.5f, -0.5f,
                                -0.5f,  0.5f,  0.5f,
                                0.5f,  0.5f,  0.5f,
                                0.5f,  0.5f, -0.5f,
                                -0.5f, -0.5f, -0.5f,
                                -0.5f,  0.5f, -0.5f,
                                0.5f,  0.5f, -0.5f,
                                0.5f, -0.5f, -0.5f,
                                -0.5f, -0.5f, 0.5f,
                                -0.5f,  0.5f, 0.5f,
                                0.5f,  0.5f, 0.5f,
                                0.5f, -0.5f, 0.5f,
                                -0.5f, -0.5f, -0.5f,
                                -0.5f, -0.5f,  0.5f,
                                -0.5f,  0.5f,  0.5f,
                                -0.5f,  0.5f, -0.5f,
                                0.5f, -0.5f, -0.5f,
                                0.5f, -0.5f,  0.5f,
                                0.5f,  0.5f,  0.5f,
                                0.5f,  0.5f, -0.5f,
                        };

        GLfloat cubeNormals[] =
                        {
                                0.0f, -1.0f, 0.0f,
                                0.0f, -1.0f, 0.0f,
                                0.0f, -1.0f, 0.0f,
                                0.0f, -1.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, -1.0f,
                                0.0f, 0.0f, -1.0f,
                                0.0f, 0.0f, -1.0f,
                                0.0f, 0.0f, -1.0f,
                                0.0f, 0.0f, 1.0f,
                                0.0f, 0.0f, 1.0f,
                                0.0f, 0.0f, 1.0f,
                                0.0f, 0.0f, 1.0f,
                                -1.0f, 0.0f, 0.0f,
                                -1.0f, 0.0f, 0.0f,
                                -1.0f, 0.0f, 0.0f,
                                -1.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 0.0f,
                        };

        GLfloat cubeTex[] =
                        {
                                0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f,
                                1.0f, 0.0f,
                                1.0f, 0.0f,
                                1.0f, 1.0f,
                                0.0f, 1.0f,
                                0.0f, 0.0f,
                                0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f,
                                1.0f, 0.0f,
                                0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f,
                                1.0f, 0.0f,
                                0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f,
                                1.0f, 0.0f,
                                0.0f, 0.0f,
                                0.0f, 1.0f,
                                1.0f, 1.0f,
                                1.0f, 0.0f,
                        };

        // Allocate memory for buffers
        if ( vertices != NULL )
        {
            *vertices = ( GLfloat *)malloc ( sizeof ( GLfloat ) * 3 * numVertices );
            memcpy ( *vertices, cubeVerts, sizeof ( cubeVerts ) );

            for ( i = 0; i < numVertices * 3; i++ )
            {
                ( *vertices ) [i] *= scale;
            }
        }

        if ( normals != NULL )
        {
            *normals = ( GLfloat *)malloc ( sizeof ( GLfloat ) * 3 * numVertices );
            memcpy ( *normals, cubeNormals, sizeof ( cubeNormals ) );
        }

        if ( texCoords != NULL )
        {
            *texCoords = ( GLfloat *)malloc ( sizeof ( GLfloat ) * 2 * numVertices );
            memcpy ( *texCoords, cubeTex, sizeof ( cubeTex ) ) ;
        }


        // Generate the indices
        if ( indices != NULL )
        {
            GLuint cubeIndices[] =
                           {
                                   0, 2, 1,
                                   0, 3, 2,
                                   4, 5, 6,
                                   4, 6, 7,
                                   8, 9, 10,
                                   8, 10, 11,
                                   12, 15, 14,
                                   12, 14, 13,
                                   16, 17, 18,
                                   16, 18, 19,
                                   20, 23, 22,
                                   20, 22, 21
                           };

            *indices = ( GLuint *)malloc ( sizeof ( GLuint ) * numIndices );
            memcpy ( *indices, cubeIndices, sizeof ( cubeIndices ) );
        }

        return numIndices;
    }

    int  genSquareGrid ( int size, GLfloat **vertices, GLuint **indices )
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
