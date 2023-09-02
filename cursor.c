#include <xcb/xcb.h>
#include <xcb/xcb_cursor.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cursor.h"

void create_cursor(xcb_connection_t *c,xcb_font_t font,xcb_cursor_t cursor){
    font = xcb_generate_id(c);
    xcb_open_font(c,font,strlen("cursor"),"cursor");

    cursor = xcb_generate_id(c);
    xcb_create_glyph_cursor(c,cursor,font,font,
                            58,58 + 1,
                            0, 0, 0,
                            0, 0, 0);
}

void free_cursor(xcb_connection_t *c,xcb_cursor_t cursor){
    xcb_free_cursor(c,cursor);
}
