/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include <cstdlib>
#include <sys/fcntl.h>
#include <sys/unistd.h>

#include "LinuxFbdevPlatform.h"

namespace BotsonSDK
{
    Platform* LinuxFbdevPlatform::instance = NULL;

    LinuxFbdevPlatform::LinuxFbdevPlatform(void)
    {
    }

    Platform* LinuxFbdevPlatform::getInstance(void)
    {
        if (instance == NULL)
        {
            instance = new LinuxFbdevPlatform();
        }
        return instance;
    }

    void LinuxFbdevPlatform::createWindow(int width, int height)
    {
        window = (fbdev_window *)calloc(1, sizeof(fbdev_window));
        if(window == NULL)
        {
            printf("Out of memory at %s:%i\n", __FILE__, __LINE__);
            exit(1);
        }
        window->width = width;
        window->height = height;
    }

    void LinuxFbdevPlatform::destroyWindow(void)
    {
        free(window);
    }

    Platform::WindowStatus LinuxFbdevPlatform::checkWindow(void)
    {
        return Platform::WINDOW_IDLE;
    }

    EGLDisplay LinuxFbdevPlatform::getDisplay()
    {
        return eglGetDisplay(EGL_DEFAULT_DISPLAY);
    }

    void LinuxFbdevPlatform::getWindowSize(unsigned int *width, unsigned int *height)
    {
    }
}
