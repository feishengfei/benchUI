/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef SPHERE_MODEL_H
#define SPHERE_MODEL_H

#include "VectorTypes.h"

namespace BotsonSDK
{
    class SquareModel
    {
    public:
        int genSquareGrid ( int size, GLfloat **vertices, GLuint **indices );
    };
}

#endif /* SPHERE_MODEL_H */
