#include "title.h"

int options[2] = {50, 57};
int current_screen = SCREEN_TITLE;
int curr_opt = 0;

void change_menu_cursor(ak_msg_t* msg) {
	switch (msg->sig) {
		case CURSOR_UP: {
			if (curr_opt > 0) {
				curr_opt--;
				xprintf("\ncurr_opt value: %d\n", curr_opt);
			}
		}
		break;
		case CURSOR_DOWN: {
			if (curr_opt < 1) {
				curr_opt++;
				xprintf("\ncurr_opt value: %d\n", curr_opt);
			}
		}
		break;
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

void change_screen(ak_msg_t* msg) {
	switch (msg->sig) {
		case CHANGE_SCREEN: {
			switch (curr_opt) {
				case 0: {
					current_screen = SCREEN_GAME_ACTIVE;
					timer_set(TASK_UPDATE_POS, CHANGE_POS, 100, TIMER_PERIODIC);
					init_game();
					xprintf("\ncurr_opt: %d\n", curr_opt);
					SCREEN_TRAN(task_game, &scr_game);
					break;
				}
				case 1: {
					current_screen = SCREEN_OPTIONS;
					xprintf("\ncurr_opt: %d\n", curr_opt);
					SCREEN_TRAN(task_options, &scr_options);
					break;
				}
			}
		}
	}
}

void handle_scr_title(ak_msg_t * msg){};
void task_title(ak_msg_t * msg){};