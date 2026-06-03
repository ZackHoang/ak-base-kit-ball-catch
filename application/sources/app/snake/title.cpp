#include "title.h"

int options[2] = {50, 57};

static int curr_opt = 0;
static int curr_screen = 0;

void change_menu_cursor(ak_msg_t* msg) {
	switch (msg->sig) {
		case CURSOR_UP: {
			if (curr_opt > 0) {
				curr_opt--;
				curr_screen--;
			}
		}	break;
		case CURSOR_DOWN: {
			if (curr_opt < 1) {
				curr_opt++;
				curr_screen++;
			}
		}	break;
		default:
			break;
	}
}

void item_render() {
	view_render.setCursor(5, 24);
	view_render.setTextSize(2);
  view_render.print("BALL CATCH");
	view_render.drawBitmap(45, 15, image_volleyball_bits, 20, 20, WHITE);
	view_render.setCursor(32, 48);
	view_render.setTextSize(1);
	view_render.print("Start");
	view_render.setCursor(32, 56);
	view_render.print("Options");
	view_render.drawBitmap(18, options[curr_opt], image_arrow_right_bits, 7, 5, WHITE);
}

view_dynamic_t dyn_view_scr_title = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	item_render,
};

view_screen_t scr_title = {
	&dyn_view_scr_title,
	ITEM_NULL,
	ITEM_NULL,
	.focus_item = 0,
};

void screen_manager() {
	switch (curr_screen) {
		case 0: {
			timer_set(TASK_UPDATE_POS, CHANGE_POS, 100, TIMER_PERIODIC);
			// timer_set(TASK_INCREASE_BALL, INCREASE_BALL, 1000, TIMER_PERIODIC);
			SCREEN_TRAN(task_game, &scr_game);
		}
	}
}

void change_screen(ak_msg_t* msg) {
	switch (msg->sig) {
		case CHANGE_SCREEN: {
			screen_manager();
		}
	}
}


void handle_scr_title(ak_msg_t* msg) {}

void task_title(ak_msg_t *msg) {}