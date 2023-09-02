#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ewmh.h"

void init_ewmh(xcb_connection_t *c,xcb_ewmh_connection_t ewmh){
    if(!xcb_ewmh_init_atoms_replies(&ewmh,xcb_ewmh_init_atoms(c,&ewmh),NULL)) {
        fprintf(stderr,"\033[31mERR\033[0m: unable to initialize ewmh atoms (skill issue)");
        xcb_ewmh_connection_wipe(&ewmh);
        xcb_disconnect(c);
        exit(1);
    }
}

void wipe_ewmh(xcb_ewmh_connection_t ewmh){
    xcb_ewmh_connection_wipe(&ewmh);
}


