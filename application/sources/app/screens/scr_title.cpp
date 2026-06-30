#include "scr_title.h"

uint8_t options[2] = {START, SETTINGS};
uint8_t curr_opt   = START_CURSOR;

void item_render() {
	view_render.setCursor(5, 19);
	view_render.setTextSize(2);
	view_render.print("BALL CATCH");
	view_render.drawBitmap(45, 10, image_volleyball_bits, 20, 20, WHITE);
	view_render.setCursor(45, 43);
	view_render.setTextSize(1);
	view_render.print("Start");
	view_render.setCursor(45, 51);
	view_render.print("Settings");
	view_render.drawBitmap(31, options[curr_opt], image_arrow_right_bits, 7, 5,
						   WHITE);
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

void task_title_screen(ak_msg_t *msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
		} break;
		case AC_DISPLAY_BUTTON_UP_PRESSED: {
			if (curr_opt > 0) {
				curr_opt--;
			}
		} break;

		case AC_DISPLAY_BUTTON_DOWN_PRESSED: {
			if (curr_opt < 1) {
				curr_opt++;
			}
		} break;

		case AC_DISPLAY_BUTTON_MODE_PRESSED: {
			switch (curr_opt) {
				case START_CURSOR: {
					SCREEN_TRAN(task_game_screen, &scr_game);
				} break;
				case SETTINGS_CURSOR: {
					SCREEN_TRAN(task_settings_screen, &scr_options);
				} break;
			}
		} break;
	}
};
