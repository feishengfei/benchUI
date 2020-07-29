/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN 1
#endif /* WIN32_LEAN_AND_MEAN */

#include "Platform.h"

#include <windows.h>

namespace BotsonSDK
{
    /**
     * \brief Platform specific functions for the Microsoft Windows platform.
     */
    class WindowsPlatform : public Platform
    {
    private:
        MSG message;
        
        /**
         * \brief The only instance of this class.
         */
        static Platform* instance;
        
        /**
         * \brief Default constructor.
         */
        WindowsPlatform(void);
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
        
        /**
         * \brief Process callbacks to the window.
         */
        static LRESULT CALLBACK processWindow(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    };
}
#endif /* WINDOWSPLATFORM_H */