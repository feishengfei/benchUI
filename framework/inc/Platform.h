/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include "Util.h"
#include "Shader.h"
#include <cstdio>

#include "EGLRuntime.h"


namespace BotsonSDK
{
    /**
     * \brief Abstract class to hide the complexity of multiple build targets.
     */
    class Platform
    {

    public:
        /**
         * \brief An enum to define the status of a window.
         */
        enum WindowStatus {/** Window has nothing to report */
                           WINDOW_IDLE,
                           /** The window has been closed by the user */
                           WINDOW_EXIT,
                           /** The user has clicked on the window */
                           WINDOW_CLICK};
        //Vec2 mouseClick;
        /*
         * The following variables are platform specific handles/pointers to
         * displays/devices/windows. Used to create and manage the window
         * to which OpenGL ES 2.0 graphics are rendered.
         */

        Window window;
        Display *display;
        /**
         * \brief Create a native window on the target device.
         * \param[in] width The required width of the window.
         * \param[in] height The required height of the window.
         */
        virtual void createWindow(int width, int height) = 0;

        /**
         * \brief Check status of the window.
         * \return The status of the window.
         */
        virtual WindowStatus checkWindow(void) = 0;
        /**
         * \brief Close and clean-up the native window.
         */
        virtual void destroyWindow(void) = 0;
        /**
         * Get the instance of Platform specific to the target.
         * \return An instance of a subclass of Platform which will work on the target platform.
         */
        static Platform* getInstance(void);

        virtual EGLDisplay getDisplay(void) = 0;

        virtual void getWindowSize(unsigned int *width, unsigned int *height) = 0;
    };
}

#include "LinuxX11Platform.h"

#define ASSERT(x, s)                                                    \
    if (!(x))                                                           \
    {                                                                   \
        LOGE("Assertion failed at %s:%i\n%s\n", __FILE__, __LINE__, s); \
        exit(1);                                                        \
    }

#endif /* PLATFORM_H */
