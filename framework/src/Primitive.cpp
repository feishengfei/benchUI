/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include "Primitive.h"

#include <cstdio>
#include <cstdlib>

namespace BotsonSDK
{
    void Primitive::drawRectCustom(GLfloat *vert, GLfloat *color, GLfloat *tex, GLfloat *norm)
    {
        GLint progID = 0;
        GLint iLocPos = -1;
        GLint iLocColor = -1;
        GLint iLocNorm = -1;
        GLint iLocTex = -1;

#if (GL_VERSION < 13)
        GL_CHECK(glBegin(GL_TRIANGLE_STRIP));
        for(int i=0; i<4; i++) {
            if (norm != NULL) 
                GL_CHECK(glNormal3f(*(norm+i*3), *(norm+i*3+1), *(norm+i*3+2)));
            if (tex != NULL) 
                GL_CHECK(glTexCoord2f(*(tex+i*2), *(tex+i*2+1)));
            GL_CHECK(glColor4f(*(color+i*4), *(color+i*4+1), *(color+i*4+2), *(color+i*4+3)));
            GL_CHECK(glVertex4f(*(vert+i*4), *(vert+i*4+1), *(vert+i*4+2), *(vert+i*4+3)));
        }
        GL_CHECK(glEnd());
#elif (ES_VERSION > 11)
        if(tex != NULL && norm == NULL)
            Shader program("es20-baseTex.vert","es20-baseTex.frag");
        else if (tex == NULL && norm != NULL) 
            Shader program("es20-baseNorm.vert","es20-baseNorm.frag");
        else if (tex != NULL && norm != NULL) 
            Shader program("es20-baseNormTex.vert","es20-baseNormTex.frag");
        else
            Shader program("es20-base.vert","es20-base.frag");
        
        progID = program.createProgram();

        iLocPos = GL_CHECK(glGetAttribLocation(progID, "a_v4Pos"));
        if(iLocPos == -1)
        {
            LOGE("Attribute(a_v4Pos) not found!\n");
            return false;
        }

        if(norm ！= NULL) {
            iLocNorm = GL_CHECK(glGetAttribLocation(progID, "a_v3Norm"));
            if(iLocNorm == -1)
            {
                LOGE("Attribute(a_v3Norm) not found!\n");
                return false;
            }           
            GL_CHECK(glVertexAttribPointer(iLocNorm, 3, GL_FLOAT, GL_FALSE, 0, norm));
            GL_CHECK(glEnableVertexAttribArray(iLocNorm));
        }

        if(tex != NULL) {
            iLocTex = GL_CHECK(glGetAttribLocation(progID, "a_v2Tex"));
            if(iLocNorm == -1)
            {
                LOGE("Attribute(a_v2Tex) not found!\n");
                return false;
            }
            GL_CHECK(glVertexAttribPointer(iLocTex, 2, GL_FLOAT, GL_FALSE, 0, tex));
            GL_CHECK(glEnableVertexAttribArray(iLocTex));
            iLocSample = GL_CHECK(glGetUniformLocation(progID, "u_sample2D"));
            if(iLocSample == -1)
            {
                LOGE("Uniform(u_sample2D) not found!\n");
                return false;
            }
            GL_CHECK(glUniform1i(iLocSample, 0));
        } else {        
            iLocColor = GL_CHECK(glGetAttribLocation(progID, "a_v4Color"));
            if(iLocColor == -1)
            {
                LOGE("Attribute(a_v4Color) not found!\n");
                return false;
            }
        }
        GL_CHECK(glVertexAttribPointer(iLocPos, 4, GL_FLOAT, GL_FALSE, 0, vert));
        GL_CHECK(glEnableVertexAttribArray(iLocPos));
        GL_CHECK(glVertexAttribPointer(iLocColor, 4, GL_FLOAT, GL_FALSE, 0, color));
        GL_CHECK(glEnableVertexAttribArray(iLocColor));
        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
#else
        GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
        GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
        GL_CHECK(glVertexPointer(4, GL_FLOAT, 0, vert));
        GL_CHECK(glColorPointer(4, GL_FLOAT, 0, color));
        if(NULL != tex){
            GL_CHECK(glEnableClientState(GL_TEXCOORD_ARRAY));
            GL_CHECK(glTexcoordPointer(2, GL_FLOAT, 0, tex));
        }
        if(NULL != norm){
            GL_CHECK(glEnableClientState(GL_NORMAL_ARRAY));
            GL_CHECK(glNormalPointer(3, GL_FLOAT, 0, norm));
        }
        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
#endif
    }

    void Primitive::drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
    {
        float verts[4][4];
        float colors[4][4] = {
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
        };

        verts[0][0] = x;
        verts[0][1] = y;
        verts[0][2] = 0.0;
        verts[0][3] = 1.0;
        verts[1][0] = x + w;
        verts[1][1] = y;
        verts[1][2] = 0.0;
        verts[1][3] = 1.0;
        verts[2][0] = x;
        verts[2][1] = y + h;
        verts[2][2] = 0.0;
        verts[2][3] = 1.0;
        verts[3][0] = x + w;
        verts[3][1] = y + h;
        verts[3][2] = 0.0;
        verts[3][3] = 1.0;
        drawRectCustom(verts, colors, NULL, NULL);
    }
    void Primitive::drawRectZ(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h)
    {
        float verts[4][4];
        float colors[4][4] = {
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
        };

        verts[0][0] = x;
        verts[0][1] = y;
        verts[0][2] = z;
        verts[0][3] = 1.0;
        verts[1][0] = x + w;
        verts[1][1] = y;
        verts[1][2] = z;
        verts[1][3] = 1.0;
        verts[2][0] = x;
        verts[2][1] = y + h;
        verts[2][2] = z;
        verts[2][3] = 1.0;
        verts[3][0] = x + w;
        verts[3][1] = y + h;
        verts[3][2] = z;
        verts[3][3] = 1.0;
        drawRectCustom(verts, colors, NULL, NULL);
    }
    void Primitive::drawRectTex(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
    {
        float verts[4][4];
        float colors[4][4] = {
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
        };
        float tex[4][2] = {
            {0.0, 0.0},
            {1.0, 0.0},
            {0.0, 1.0},
            {1.0, 1.0},
        };

        verts[0][0] = x;
        verts[0][1] = y;
        verts[0][2] = z;
        verts[0][3] = 1.0;
        verts[1][0] = x + w;
        verts[1][1] = y;
        verts[1][2] = z;
        verts[1][3] = 1.0;
        verts[2][0] = x;
        verts[2][1] = y + h;
        verts[2][2] = z;
        verts[2][3] = 1.0;
        verts[3][0] = x + w;
        verts[3][1] = y + h;
        verts[3][2] = z;
        verts[3][3] = 1.0;
        drawRectCustom(verts, colors, NULL, tex);
    }
    void Primitive::drawRectNorm(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
    {
        float verts[4][4];
        float colors[4][4] = {
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
        };
        float norm[4][3] = {
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0},
        };

        verts[0][0] = x;
        verts[0][1] = y;
        verts[0][2] = z;
        verts[0][3] = 1.0;
        verts[1][0] = x + w;
        verts[1][1] = y;
        verts[1][2] = z;
        verts[1][3] = 1.0;
        verts[2][0] = x;
        verts[2][1] = y + h;
        verts[2][2] = z;
        verts[2][3] = 1.0;
        verts[3][0] = x + w;
        verts[3][1] = y + h;
        verts[3][2] = z;
        verts[3][3] = 1.0;
        drawRectCustom(verts, colors, norm, NULL);
    }
    void Primitive::drawRectNormTex(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
    {
        float verts[4][4];
        float colors[4][4] = {
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
        };
        float tex[4][2] = {
            {0.0, 0.0},
            {1.0, 0.0},
            {0.0, 1.0},
            {1.0, 1.0},
        };
        float norm[4][3] = {
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0},
        };

        verts[0][0] = x;
        verts[0][1] = y;
        verts[0][2] = z;
        verts[0][3] = 1.0;
        verts[1][0] = x + w;
        verts[1][1] = y;
        verts[1][2] = z;
        verts[1][3] = 1.0;
        verts[2][0] = x;
        verts[2][1] = y + h;
        verts[2][2] = z;
        verts[2][3] = 1.0;
        verts[3][0] = x + w;
        verts[3][1] = y + h;
        verts[3][2] = z;
        verts[3][3] = 1.0;
        drawRectCustom(verts, colors, norm, tex);
    }
/*
    void Primitive::GBtest_draw_triangle(GBtest_Vertex3 vetex[])
    {
        glBegin(GL_TRIANGLES);
        glColor3f(vetex[0].color.r, vetex[0].color.g, vetex[0].color.b); //
        glVertex3f(vetex[0].pos.x, vetex[0].pos.y, vetex[0].pos.z);
        glColor3f(vetex[1].color.r, vetex[1].color.g, vetex[1].color.b); //
        glVertex3f(vetex[1].pos.x, vetex[1].pos.y, vetex[1].pos.z);
        glColor3f(vetex[2].color.r, vetex[2].color.g, vetex[2].color.b); //
        glVertex3f(vetex[2].pos.x, vetex[2].pos.y, vetex[2].pos.z);
        glEnd();
    }

    void Primitive::GBtest_draw_quad(GBtest_Vertex3 vetex[])
    {
        glBegin(GL_TRIANGLES);
        glColor3f(vetex[0].color.r, vetex[0].color.g, vetex[0].color.b); //
        glVertex3f(vetex[0].pos.x, vetex[0].pos.y, vetex[0].pos.z);
        glColor3f(vetex[1].color.r, vetex[1].color.g, vetex[1].color.b); //
        glVertex3f(vetex[1].pos.x, vetex[1].pos.y, vetex[1].pos.z);
        glColor3f(vetex[2].color.r, vetex[2].color.g, vetex[2].color.b); //
        glVertex3f(vetex[2].pos.x, vetex[2].pos.y, vetex[2].pos.z);
        glColor3f(vetex[3].color.r, vetex[3].color.g, vetex[3].color.b); //
        glVertex3f(vetex[3].pos.x, vetex[3].pos.y, vetex[3].pos.z);
        glEnd();
    }
*/

    float * Primitive::getNormal(float *vertice, int n)
    {
      int i;
      float *normal = (float *)malloc(n*sizeof(float));

      for(i=0; i<n;) {
        float xa = vertice[i+3] - vertice[i+0];
        float ya = vertice[i+4] - vertice[i+1];
        float za = vertice[i+5] - vertice[i+2];

        float xb = vertice[i+6] - vertice[i+0];
        float yb = vertice[i+7] - vertice[i+1];
        float zb = vertice[i+8] - vertice[i+2];

        normal[i+0] = normal[i+3] = normal[i+6] = ya*zb - yb*za;
        normal[i+1] = normal[i+4] = normal[i+7] = za*xb - zb*xa;
        normal[i+2] = normal[i+5] = normal[i+8] = xa*yb - xb*ya;
        i=i+9;
      }
      return normal;
    }
    void Primitive::genvertex2(int num, GLfloat *vertex, GLfloat *color, float Radius)
    {
      float V,U;
      for(int i=0; i<num ;i++)
      {
        V = sin(2*PI*i/num);
        U = cos(2*PI*i/num);
        *vertex++ = Radius * V;
        *vertex++ = Radius * U;
        *color++ = (2 + 1.14*V)/4;
        *color++ = (2 - 0.394*U - 0.581*V)/4;
        *color++ = (2 + 2*U)/4;
      }
    }
}
