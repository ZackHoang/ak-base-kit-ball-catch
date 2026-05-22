#ifndef __SCR_GAME_H__
#define __SCR_GAME_H__

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

extern void render_game_screen();
extern view_screen_t scr_game;
extern view_dynamic_t dyn_view_scr_game;
extern void task_game(ak_msg_t *msg);
extern void task_draw_snake(ak_msg_t *msg);
extern void init_snake_coords();

#endif