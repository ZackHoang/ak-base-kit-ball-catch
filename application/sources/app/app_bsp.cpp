#include "button.h"

#include "sys_dbg.h"

#include "app.h"
#include "app_bsp.h"
#include "app_dbg.h"
#include "app_if.h"

#include "task_list.h"
#include "task_list_if.h"

button_t btn_mode;
button_t btn_up;
button_t btn_down;

void btn_mode_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_PRESSED\n");
		task_post_pure_msg(TASK_CHANGE_SCREEN, CHANGE_SCREEN);
		task_post_pure_msg(TASK_CONFIRM_GAME_OVER_CURSOR, CONFIRM_GAME_OVER);
		task_post_pure_msg(TASK_CONFIRM_OPTION, CONFIRM_OPTION_CHOICE);
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_RELEASED\n");
		task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_MODE_RELEASED);
	}
		break;

	default:
		break;
	}
}

void btn_up_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		APP_DBG("[btn_up_callback] BUTTON_SW_STATE_PRESSED\n");
		task_post_pure_msg(TASK_CHANGE_CURSOR, CURSOR_UP);
		task_post_pure_msg(TASK_MOVE_BAR_RIGHT, MOVE_RIGHT);
		task_post_pure_msg(TASK_CHANGE_GAME_OVER_CURSOR, GAME_OVER_CURSOR_UP);
		task_post_pure_msg(TASK_CHANGE_OPTION_CURSOR, CHANGE_OPTIONS_UP);
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		APP_DBG("[btn_up_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		APP_DBG("[btn_up_callback] BUTTON_SW_STATE_RELEASED\n");
		task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_UP_RELEASED);
	}
		break;

	default:
		break;
	}
}

void btn_down_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		APP_DBG("[btn_down_callback] BUTTON_SW_STATE_PRESSED\n");
		task_post_pure_msg(TASK_CHANGE_CURSOR, CURSOR_DOWN);
		task_post_pure_msg(TASK_MOVE_BAR_LEFT, MOVE_LEFT);
		task_post_pure_msg(TASK_CHANGE_GAME_OVER_CURSOR, GAME_OVER_CURSOR_DOWN);
		task_post_pure_msg(TASK_CHANGE_OPTION_CURSOR, CHANGE_OPTIONS_DOWN);
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		APP_DBG("[btn_down_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		APP_DBG("[btn_down_callback] BUTTON_SW_STATE_RELEASED\n");
		task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_DOWN_RELEASED);
	}
		break;

	default:
		break;
	}
}
