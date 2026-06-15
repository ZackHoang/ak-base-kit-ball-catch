#ifndef __SCR_GAME_OVER_H__
#define __SCR_GAME_VER_H__

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
#include "app_dbg.h"
#include "bitmap.h"
#include "eeprom.h"
#include "buzzer.h"
#include "scr_title.h"

#define RETRY (40)
#define QUIT (50)

void render_game_over();
extern view_screen_t scr_game_over;
extern view_dynamic_t dyn_view_scr_game;
extern void task_game_over_screen(ak_msg_t *msg);
extern struct game_over_data_t game_over_data;

#endif
