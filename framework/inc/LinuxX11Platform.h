/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */
 
#ifndef LINUX_X11_PLATFORM_H
#define LINUX_X11_PLATFORM_H

#include <cstdlib>

#ifdef API_ES
#include <EGL/egl.h>
#include <EGL/egl.h>
#endif

#include "Platform.h"

namespace BotsonSDK
{
    /**
     * \brief Platform specific functions for a Desktop Linux platform.
     */
    class LinuxX11Platform : public Platform
    {


    private:
        /**
         * \brief The width of the window (in pixels).
         */
        int windowWidth;
        /**
         * \brief The height of the window (in pixels).
         */
        int windowHeight;

        /**
         * \brief An X11 ColorMap.
         *
         * See X11 documentation for more details.
         */
        Colormap colormap;

        /**
         * \brief An X11 XVisualInfo.
         *
         * See X11 documentation for more details.
         */
        XVisualInfo *visual;

        /**
         * \brief The only instance of this class.
         */
        static Platform* instance;
        /**
         * \brief Default constructor.
         */
        LinuxX11Platform(void);
        /**
         * \brief Callback for X11 events.
         *
         * Waits for map notification.
         */
        static Bool wait_for_map(Display *display, XEvent *event, char *windowPointer);
    public:
        /**
         * \brief Get the singleton instance of this class.
         *
         * If the instance does not exist, it is created.
         * \return The only instance of this class.
         */
        static Platform* getInstance(void);
        virtual void createWindow(int width, int height);
        virtual void destroyWindow(void);
        virtual WindowStatus checkWindow(void);
        virtual EGLDisplay getDisplay(void);
        virtual void getWindowSize(unsigned int *width, unsigned int *height);
        /**
         * \brief Create an X11 window.
         *
         * It is used by EGLRuntime::initializeEGL, and can be called
         * only after having initialized the EGL display.
         */
        bool createX11Window(void);

    };
}
#endif /* __LINUX_X11_PLATFORM_H__ */
