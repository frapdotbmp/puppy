#include <xcb/xcb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include "puppy.h"

xcb_connection_t *dpy;
xcb_screen_t     *scr;

xcb_window_t     root;

int initwm() {
    dpy = xcb_connect(NULL,NULL);
    if(xcb_connection_has_error(dpy)){
        return 1;
    }
    return 0;
}

void closewm() {
    if((dpy) != NULL){
        xcb_disconnect(dpy);
    }
    exit(1);
}

int initscreen() {
    scr = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;
    if(!(scr)){
        return 1;
    }
    return 0;
}

int checkforwm(){
    root = scr->root;

    xcb_intern_atom_cookie_t net_wm_name_cookie;
    net_wm_name_cookie = xcb_intern_atom(dpy,0,
        strlen("_NET_WM_NAME"),"_NET_WM_NAME");

    xcb_intern_atom_cookie_t net_supp_wm_check_cookie;
    net_supp_wm_check_cookie = xcb_intern_atom(dpy,0,
        strlen("_NET_SUPPORTING_WM_CHECK"),
        "_NET_SUPPORTING_WM_CHECK");

    xcb_intern_atom_reply_t *net_wm_name_reply;
    net_wm_name_reply = xcb_intern_atom_reply(dpy,net_wm_name_cookie,NULL);

    xcb_intern_atom_reply_t *net_supporting_wm_check_reply;
    net_supporting_wm_check_reply = xcb_intern_atom_reply(dpy,
        net_supp_wm_check_cookie,NULL);

    xcb_get_property_cookie_t name_cookie;
    name_cookie = xcb_get_property(dpy,0,
        root,net_wm_name_reply->atom,XCB_ATOM_STRING,0,1024);

    xcb_get_property_cookie_t supporting_wm_cookie;
    supporting_wm_cookie = xcb_get_property(dpy,0,root,
        net_supporting_wm_check_reply->atom,
         XCB_ATOM_WINDOW,0,1);

    xcb_get_property_reply_t *name_reply = xcb_get_property_reply(dpy,name_cookie,NULL);
    xcb_get_property_reply_t *supporting_wm_reply = xcb_get_property_reply(dpy,supporting_wm_cookie,NULL);

    if (name_reply && xcb_get_property_value_length(name_reply) > 0) {
        free(name_reply);
        free(supporting_wm_reply);
        return 1;
    } 
    else if (supporting_wm_reply && xcb_get_property_value_length(supporting_wm_reply) > 0) {
        free(name_reply);
        free(supporting_wm_reply);
        return 1;
    }
    return 0;
}
