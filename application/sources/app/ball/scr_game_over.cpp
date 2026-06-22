#include "scr_game_over.h"

void render_game_over();

struct game_over_data_t {
	uint8_t read_score;
	char game_over_buffer[50];
	uint8_t game_over_options[2] = {RETRY, QUIT};
	uint8_t game_over_cursor	 = 0;
} game_over_data;

view_dynamic_t dyn_view_scr_game_over = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	 },
	render_game_over,
};

view_screen_t scr_game_over = {
	&dyn_view_scr_game_over,
	ITEM_NULL,
	ITEM_NULL,
	.focus_item = 0,
};

void task_game_over_screen(ak_msg_t *msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY:
			break;

		case AC_DISPLAY_BUTTON_UP_PRESSED:
			if (game_over_data.game_over_cursor > 0) {
				game_over_data.game_over_cursor--;
			}
			break;

		case AC_DISPLAY_BUTTON_DOWN_PRESSED:
			if (game_over_data.game_over_cursor < 1) {
				game_over_data.game_over_cursor++;
			}
			break;

		case AC_DISPLAY_BUTTON_MODE_PRESSED:
			if (game_over_data.game_over_cursor == 0) {
				SCREEN_TRAN(task_game_screen_move_bar, &scr_game);
			}
			else if (game_over_data.game_over_cursor == 1) {
				SCREEN_TRAN(task_title_screen, &scr_title);
			}
			break;

		default:
			break;
	}
}

void render_game_over() {
	view_render.clear();
	view_render.drawBitmap(10, 20, image_cry_dolph_bits, 55, 52, WHITE);
	view_render.setCursor(65, 30);
	view_render.setTextSize(1);
	view_render.print("GAME OVER!");
	view_render.setCursor(10, 5);
	eeprom_read(0, (uint8_t *)&game_over_data.read_score,
				sizeof(game_over_data.read_score));
	snprintf(game_over_data.game_over_buffer,
			 sizeof(game_over_data.game_over_buffer), "Best Score: %d",
			 game_over_data.read_score);
	view_render.print(game_over_data.game_over_buffer);
	view_render.drawBitmap(
		80, game_over_data.game_over_options[game_over_data.game_over_cursor],
		image_arrow_right_bits, 7, 5, WHITE);
	view_render.setCursor(92, 40);
	view_render.print("Retry");
	view_render.setCursor(92, 50);
	view_render.print("Quit");
}