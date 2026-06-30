#ifndef _WRE_STRUCTS_HPP_
#define _WRE_STRUCTS_HPP_

#include <ncurses.h>

struct WindowInfo {
    WINDOW* win;
    int width;
    int height;
};

#endif
