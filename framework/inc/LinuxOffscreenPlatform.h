/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef __LINUX_OFFSCREEN_PLATFORM_H__
#define __LINUX_OFFSCREEN_PLATFORM_H__

#include <cstdlib>

#include "Platform.h"

namespace BotsonSDK
{
    /**
     * \brief Platform specific functions for a Desktop Linux platform.
     */
    class LinuxOffscreenPlatform : public Platform
    {
    private:
        /**
         * \brief The only instance of this class.
         */
        static Platform* instance;

        /**
         * \brief Default constructor.
         */
        LinuxOffscreenPlatform(void);
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
    };
}
#endif /* __LINUX_OFFSCREEN_PLATFORM_H__ */

