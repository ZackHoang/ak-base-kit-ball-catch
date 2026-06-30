#ifndef __SCR_SETTINGS_H__
#define __SCR_SETTINGS_H__

#include "view_render.h"
#include "bitmap.h"
#include "scr_game.h"

#define SOUND			  32
#define BALL_SPEED		  42
#define BACK			  52
#define SOUND_ON		  1
#define SOUND_OFF		  0
#define SOUND_CURSOR	  0
#define BALL_SPEED_CURSOR 1
#define BACK_CURSOR		  2

extern view_dynamic_t dyn_view_scr_options;
extern view_screen_t scr_options;
extern void task_settings_screen(ak_msg_t *msg);

#endif	  // __SCR_SETTINGS_H__