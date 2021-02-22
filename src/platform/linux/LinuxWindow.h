#ifndef VANADIUM_LINUXWINDOW_H
#define VANADIUM_LINUXWINDOW_H

#include "../../core/Window.h"

class LinuxWindow : public Window
{
public:
    LinuxWindow(const std::string &title, uint32_t width, uint32_t height):
        Window(title, width, height)
    {

    }
};


#endif //VANADIUM_LINUXWINDOW_H
