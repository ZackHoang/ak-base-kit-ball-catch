#ifndef __SCR_OPTIONS_H__
#define __SCR_OPTIONS_H__

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

#include <math.h>
#include <vector>
#include "app_dbg.h"

#include "bitmap.h"

#include "eeprom.h"

#include "scr_game.h"

#define SOUND (37)
#define BALL_SPEED (47)
#define BACK (57)
#define SOUND_ON (1)
#define SOUND_OFF (0)

extern void task_options(ak_msg_t *msg);
extern view_dynamic_t dyn_view_scr_options;
extern view_screen_t scr_options;
extern void render_options();

#endif