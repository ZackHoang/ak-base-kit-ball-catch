#include "title.h"

int options[2] = {48, 56};

static int curr_opt = 0;
static int curr_screen = 0;

void change_menu_cursor(ak_msg_t* msg) {
	switch (msg->sig) {
		case CURSOR_UP: {
			if (curr_opt > 0) {
				curr_opt--;
				curr_screen--;
				xprintf("Current screen: %d", curr_screen);
			}
		}	break;
		case CURSOR_DOWN: {
			if (curr_opt < 1) {
				curr_opt++;
				curr_screen++;
				xprintf("Current screen: %d", curr_screen);
			}
		}	break;
		default:
			break;
	}
}

void item_render() {
	view_render.setCursor(32, 24);
	view_render.setTextSize(2);
  view_render.print("SNAKE");
	view_render.setCursor(32, 48);
	view_render.setTextSize(1);
	view_render.print("Start");
	view_render.setCursor(32, 56);
	view_render.print("Options");
	view_render.drawBitmap(20, options[curr_opt], image_arrow_right_bits, 11, 8, WHITE);
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
			init_snake_coords();
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