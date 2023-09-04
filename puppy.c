/*
 *  hiya there! I just wanted to warn you before you start
 *  using my unstable and (possibly unsafe) window manager..
 *
 *  D:
 *
 *  keep in mind i'm only 13 and I don't have much experi-
 *  ence with C either.
 *
 */

#include <xcb/xcb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "puppy.h"

int main(){
    if(initwm()){
        fprintf(stderr,"\033[31mERR\033[0m: unable to access display\n");
        closewm();

    } else if(initscreen()){
        fprintf(stderr,"\033[31mERR\033[0m: unable to fetch screen information");
        closewm();

    } else if(checkforwm()){
        fprintf(stderr,"\033[31mERR\033[0m: another window manager is already running\n");
        closewm();
    }
    closewm();
}
