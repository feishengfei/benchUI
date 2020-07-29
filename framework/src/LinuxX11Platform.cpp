/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include <stdlib.h>

#include "LinuxX11Platform.h"


namespace BotsonSDK
{
    Platform* LinuxX11Platform::instance = NULL;

    LinuxX11Platform::LinuxX11Platform(void)
    {

    }

    Platform* LinuxX11Platform::getInstance(void)
    {
        if (instance == NULL)
        {
            instance = new LinuxX11Platform();
        }
        return instance;
    }

    /**
     * A window is not actually created by this function.
     * Call createX11Window after the EGL display has been initialized to get a window.
     */
    void LinuxX11Platform::createWindow(int width, int height)
    {
        windowWidth = width;
        windowHeight = height;
    }

    bool LinuxX11Platform::createX11Window(void)
    {
        XSetWindowAttributes windowAttributes;
        XSizeHints sizeHints;
        XEvent event;
        XVisualInfo visualInfoTemplate;

        unsigned long mask;
        long screen;

        int visualID, numberOfVisuals;

        display = XOpenDisplay(NULL);

        screen = DefaultScreen(display);

        eglGetConfigAttrib(EGLRuntime::display, EGLRuntime::config, EGL_NATIVE_VISUAL_ID, &visualID);
        visualInfoTemplate.visualid = visualID;
        visual = XGetVisualInfo(display, VisualIDMask, &visualInfoTemplate, &numberOfVisuals);

        if (visual == NULL)
        {
            LOGE("Couldn't get X visual info\n");
            return false;
        }

        colormap = XCreateColormap(display, RootWindow(display, screen), visual->visual, AllocNone);

        windowAttributes.colormap = colormap;
        windowAttributes.background_pixel = 0xFFFFFFFF;
        windowAttributes.border_pixel = 0;
        windowAttributes.event_mask = StructureNotifyMask | ExposureMask;

        mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

	if(windowWidth <=0 || windowHeight <= 0) {
		windowWidth = XDisplayWidth(display, screen);
		windowHeight = XDisplayHeight(display, screen);
		windowAttributes.override_redirect = true;
		mask = mask | CWOverrideRedirect;
	}

        window = XCreateWindow(display, RootWindow(display, screen), 0, 0, windowWidth, windowHeight,
            0, visual->depth, InputOutput, visual->visual, mask, &windowAttributes);
        sizeHints.flags = USPosition;
        sizeHints.x = 10;
        sizeHints.y = 10;

        XSetStandardProperties(display, window, "Botson OpenGL ES SDK", "", None, 0, 0, &sizeHints);
        XMapWindow(display, window);
        XIfEvent(display, &event, wait_for_map, (char*)&window);
        XSetWMColormapWindows(display, window, &window, 1);
        XFlush(display);

        XSelectInput(display, window, KeyPressMask | ExposureMask | EnterWindowMask
                     | LeaveWindowMask | PointerMotionMask | VisibilityChangeMask | ButtonPressMask
                     | ButtonReleaseMask | StructureNotifyMask);

        return true;
    }

    void LinuxX11Platform::destroyWindow(void)
    {
        XDestroyWindow(display, window);
        XFreeColormap(display, colormap);
        XFree(visual);
        XCloseDisplay(display);
    }

    Platform::WindowStatus LinuxX11Platform::checkWindow(void)
    {
        XEvent event;

        while (XPending(display) > 0)
        {
            XNextEvent(display, &event);

            if (event.type == ButtonPress)
            {
                return Platform::WINDOW_CLICK;
            }
        }
        return Platform::WINDOW_IDLE;
    }

    Bool LinuxX11Platform::wait_for_map(Display *display, XEvent *event, char *windowPointer)
    {
        return (event->type == MapNotify && event->xmap.window == (*((Window*)windowPointer)));
    }

    EGLDisplay LinuxX11Platform::getDisplay()
    {
        EGLDisplay egldpy;
        display = XOpenDisplay(NULL);

	if (display == NULL) {
		printf("X11 open file\n");
	}

        egldpy = eglGetDisplay(display);
        return egldpy;
    }

    void LinuxX11Platform::getWindowSize(unsigned int *width, unsigned int *height)
    {
        *width = windowWidth;
        *height = windowHeight;
    }
}


