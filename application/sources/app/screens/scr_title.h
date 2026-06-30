#ifndef __SCR_TITLE_H__
#define __SCR_TITLE_H__

#include "view_render.h"
#include "bitmap.h"
#include "scr_game.h"
#include "scr_settings.h"

#define START			45
#define SETTINGS		52
#define START_CURSOR	0
#define SETTINGS_CURSOR 1

extern view_screen_t scr_title;
extern void task_title_screen(ak_msg_t *msg);

#endif	  // __SCR_TITLE_H__
