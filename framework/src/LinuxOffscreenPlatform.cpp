/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include <cstdlib>
#include <sys/fcntl.h>
#include <sys/unistd.h>

#include "LinuxOffscreenPlatform.h"

namespace BotsonSDK
{
    Platform* LinuxOffscreenPlatform::instance = NULL;

    LinuxOffscreenPlatform::LinuxOffscreenPlatform(void)
    {
    }

    Platform* LinuxOffscreenPlatform::getInstance(void)
    {
        if (instance == NULL)
        {
            instance = new LinuxOffscreenPlatform();
        }
        return instance;
    }

    void LinuxOffscreenPlatform::createWindow(int width, int height)
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

    void LinuxOffscreenPlatform::destroyWindow(void)
    {
        free(window);
    }

    Platform::WindowStatus LinuxOffscreenPlatform::checkWindow(void)
    {
        return WINDOW_EXIT;
    }

    EGLDisplay LinuxOffscreenPlatform::getDisplay()
    {
        return eglGetDisplay(EGL_DEFAULT_DISPLAY);
    }

	void LinuxOffscreenPlatform::getWindowSize(unsigned int *width, unsigned int *height)
	{
		*width = window->width;
		*height = window->height;
	}
}
