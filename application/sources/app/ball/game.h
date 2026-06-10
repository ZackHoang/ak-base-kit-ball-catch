#ifndef __SCR_GAME_H__
#define __SCR_GAME_H__
#endif

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

// #include <math.h>
#include "app_dbg.h"

#include "bitmap.h"

#include "eeprom.h"

#include "buzzer.h"

#include "scr_game_over.h"

#define WIDTH 128
#define HEIGHT 64
#define X_SPEED 2
#define Y_SPEED 5
#define BALL_RADIUS 2
#define BAR_HEIGHT 3
#define BAR_WIDTH 30
#define MAX_BALL 5

extern void render_game_screen();
extern view_screen_t scr_game;
extern view_dynamic_t dyn_view_scr_game;
extern void task_game(ak_msg_t *msg);
extern void task_draw_snake(ak_msg_t *msg);
extern void init_game();
extern uint8_t max_speed;
extern bool game_over;
