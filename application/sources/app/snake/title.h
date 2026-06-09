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

#include <math.h>
#include <vector>
#include "app_dbg.h"

#include "bitmap.h"
#include "game.h"
#include "options.h"

#define SCREEN_TITLE (0)
#define SCREEN_GAME_ACTIVE (1)
#define SCREEN_GAME_OVER (2)
#define SCREEN_OPTIONS (3)

// screen
extern view_screen_t scr_title;
extern void handle_scr_title(ak_msg_t *msg);
extern int current_screen;
extern int curr_opt;
extern bool game_state;

// task

#endif //__SCR_TITLE_H__
