#include "game.h"

static uint8_t x = 20;
static uint8_t y = 20;
static uint8_t x_speed = 3;
static uint8_t y_speed = 3;
static uint8_t x_bar = 54;
static uint8_t x2_bar = 74;
static uint8_t y_bar = 60;
static uint8_t score = 0;

void render_game_over()
{
	view_render.drawBitmap(10, 20, image_cry_dolph_bits, 55, 52, WHITE);
	view_render.setCursor(50, 50);
	view_render.setTextSize(1);
	view_render.print("GAME OVER!");
}

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

void touch_bar() {
	if (y + BALL_RADIUS >= y_bar && y - BALL_RADIUS <= y_bar + BAR_HEIGHT && x >= x_bar && x <= x_bar + BAR_WIDTH) {
		BUZZER_Enable(500, 10);
		BUZZER_PlayTones(tones_startup);
		y_speed = -y_speed;
		score++;
	}
}

void draw_game() {
	view_render.drawRect(x_bar, y_bar, BAR_WIDTH, BAR_HEIGHT, WHITE);
	view_render.drawCircle(x, y, BALL_RADIUS, WHITE);
	view_render.setCursor(80, 20);
	view_render.setTextSize(1);
	view_render.print(score);
	x += x_speed;
	y += y_speed;
	if (x > WIDTH - BALL_RADIUS || x < BALL_RADIUS) {
		BUZZER_Enable(500, 10);
		BUZZER_PlayTones(tones_startup);
		x_speed = -x_speed;
	}
	if (y - BALL_RADIUS <= 0) {
		BUZZER_Enable(500, 10);
		BUZZER_PlayTones(tones_startup);
		y_speed = -y_speed;
	}
	touch_bar();
	if (y - BALL_RADIUS > HEIGHT) {
		timer_remove_attr(TASK_UPDATE_POS, CHANGE_POS);
		SCREEN_TRAN(task_game_over, &scr_game_over);
	}
}

void move_bar_right() {
	if (x2_bar < 110) {
		x_bar += 5;
		x2_bar += 5;
		xprintf("x_bar: %d\nx2_bar: %d\n\n", x_bar, x2_bar);
	}
}

void move_bar_left() {
	if (x_bar > 10) {
		x_bar -= 5;
		x2_bar -= 5;
		xprintf("x_bar: %d\nx2_bar: %d\n\n", x_bar, x2_bar);
	}
}

void task_draw_snake(ak_msg_t* msg) {
	switch (msg->sig) {
		case (CHANGE_POS):
			{
				view_render_screen(&scr_game);
			}
	}
}

void task_move_bar_right(ak_msg_t* msg) {
	switch (msg->sig) {
		case (MOVE_RIGHT): {
			move_bar_right();
		}
	}
}

void task_move_bar_left(ak_msg_t* msg) {
	switch (msg->sig) {
		case (MOVE_LEFT): {
			move_bar_left();
		}
	}
}

void render_game_screen()
{
	draw_game();
}

view_dynamic_t dyn_view_scr_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	render_game_screen,
};

view_screen_t scr_game = {
	&dyn_view_scr_game,
	ITEM_NULL,
	ITEM_NULL,
	.focus_item = 0,
};

void task_game(ak_msg_t* msg) {}

void task_game_over(ak_msg_t* msg) {
	switch (msg->sig)
	{
	case GAME_OVER:
		view_render_screen(&scr_game_over);
		break;

	default:
		break;
	}
}