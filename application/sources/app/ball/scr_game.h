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

typedef struct
{
  uint8_t x;
  uint8_t y;
  uint8_t x_speed;
  uint8_t y_speed;
} ball_t;

typedef struct
{
  uint8_t x;
  uint8_t y;
} bar_t;

typedef struct
{
  uint8_t score;
  uint8_t read_score;
  uint8_t target_score;
  uint8_t ball_counter;
  bar_t bar;
  char score_display_buffer[25];
  ball_t balls[MAX_BALL];
  uint8_t max_speed = 2;
} game_data_t;

// extern void render_game_screen();
extern view_screen_t scr_game;
extern view_dynamic_t dyn_view_scr_game;
extern void task_game(ak_msg_t *msg);
extern void task_draw_snake(ak_msg_t *msg);
extern void init_game();
extern game_data_t game_data;

#endif
