#include <xcb/xcb.h>
#include <xcb/xcb_cursor.h>
#include <xcb/xcb_ewmh.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ewmh.h"
#include "puppy.h"

static xcb_connection_t   *dpy;
static xcb_screen_t      *scre;

static xcb_ewmh_connection_t ewmh;

static xcb_window_t    rootwin;
static xcb_window_t        win;

xcb_generic_event_t         *e;

static uint32_t mask = 0;
static uint32_t vals[3];

int main(){
    dpy = xcb_connect(NULL,NULL);

    if (xcb_connection_has_error(dpy)){
        fprintf(stderr,"\033[31mERR\033[0m: unable to access display massive L\n");
        xcb_disconnect(dpy);
        exit(1);
    }
    
    scre = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;
    init(dpy,&scre,&rootwin);
    init_ewmh(dpy,ewmh);

    if(check_for_wm(dpy,&scre,rootwin)){
        fprintf(stderr,"\033[31mERR\033[0m: another window manager is already running stupid\n");
        wipe_ewmh(ewmh);
        xcb_disconnect(dpy);
        exit(1);
    }

    uint32_t val;
    xcb_get_geometry_reply_t *wingeometry;

    xcb_flush(dpy);

    while ((e = xcb_wait_for_event(dpy))){
        switch(e->response_type & ~0x80){
            case XCB_EXPOSE:
                xcb_flush(dpy);
            default:
               break;
        }
        free(e);
    }
    
    wipe_ewmh(ewmh);
    xcb_disconnect(dpy);
}
