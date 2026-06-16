#ifndef __SCR_TITLE_H__
#define __SCR_TITLE_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"
#include "sys_ctrl.h"
#include "sys_dbg.h"
#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"
#include "buzzer.h"
#include "app_dbg.h"
#include "bitmap.h"
#include "scr_game.h"
#include "scr_options.h"

#define START	  50
#define OPTIONS 57

extern view_screen_t scr_title;
extern void task_title_screen(ak_msg_t *msg);

#endif	  // __SCR_TITLE_H__
