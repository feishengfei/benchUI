

#include "Platform.h"

#include <cstdio>
#include <cstdarg>

namespace BotsonSDK
{
    Platform* Platform::getInstance(void)
    {
        return LinuxX11Platform::getInstance();
    }
}
