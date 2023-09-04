#ifndef __PUPPY__
#define __PUPPY__
#include <xcb/xcb.h>

extern xcb_connection_t  *dpy;
extern xcb_screen_t      *scr;

extern xcb_window_t      root;

int initwm();
int initscreen();
int checkforwm();

void closewm();

#endif
