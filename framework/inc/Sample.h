/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef SAMPLE_H
#define SAMPLE_H

#include "Platform.h"
#include "Matrix.h"

using std::string;
using namespace BotsonSDK;

///
// Defines
//

namespace BotsonSDK
{
    class Sample
    {
      private:
        string filename;
        Platform * platform;
      public:
        Sample(string file, int argc, char **argv);
        Sample(string file, int window_w = WINDOW_W, int window_h = WINDOW_H);
        Sample(string file, unsigned int mode, int argc, char **argv);
        ~Sample();
        void SwapBuffers(void);
        virtual void test(void);
    };
}

#endif
