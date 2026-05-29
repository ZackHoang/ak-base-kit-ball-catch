#include "game.h"
#include "stdlib.h"

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t x_speed;
	uint8_t y_speed;
} ball_t;

typedef struct {
	uint8_t x;
	uint8_t y;
} bar_t;

static uint8_t x = 20;
static uint8_t y = 20;
static uint8_t x_speed = 3;
static uint8_t y_speed = 3;
static uint8_t x_bar = 54;
static uint8_t x2_bar = 74;
static uint8_t y_bar = 60;
static uint8_t score = 0;
static uint8_t target_score = 3;
static uint8_t ball_counter = 0;
static bar_t bar {54, 60};
static ball_t balls[3] = { { 20, 20, 2, 2 } };

void render_game_over()
{
	view_render.clear();
	view_render.drawBitmap(10, 20, image_cry_dolph_bits, 55, 52, WHITE);
	view_render.setCursor(65, 30);
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

void play_buzzer() {
	BUZZER_Enable(500, 10);
	BUZZER_PlayTones(tones_startup);
}

void touch_bar() {
	if (y + BALL_RADIUS >= y_bar && y - BALL_RADIUS <= y_bar + BAR_HEIGHT && x >= x_bar && x <= x_bar + BAR_WIDTH) {
		play_buzzer();
		y_speed = -y_speed;
		score++;
	}
}

void is_touching_side_wall(ball_t &ball) {
	if (ball.x > WIDTH - BALL_RADIUS || ball.x < BALL_RADIUS) {
		// play_buzzer();
		ball.x_speed = -ball.x_speed;
	}
}

void is_touching_ceiling(ball_t &ball) {
	if (ball.y - BALL_RADIUS <= 0) {
		// play_buzzer();
		ball.y_speed = -ball.y_speed;
	}
}

void is_touching_bar(ball_t &ball) {
	if (ball.y + BALL_RADIUS >= bar.y && ball.y - BALL_RADIUS <= bar.y + BAR_HEIGHT && ball.x >= bar.x && ball.x <= bar.x + BAR_WIDTH) {
		// play_buzzer();
		ball.y_speed = -ball.y_speed;
		score++;
	}
}

void is_game_over(ball_t &ball) {
	if (ball.y - BALL_RADIUS > HEIGHT) {
		timer_remove_attr(TASK_UPDATE_POS, CHANGE_POS);
		SCREEN_TRAN(task_game_over, &scr_game_over);
	}
}

void is_ball_spawning() {
	if (score == target_score && ball_counter < 2) {
		ball_counter++;
		target_score += 3;
		balls[ball_counter] = {20, 20, 2, 2};
	}
}

void draw_game() {
	view_render.drawRect(bar.x, bar.y, BAR_WIDTH, BAR_HEIGHT, WHITE);
	view_render.setCursor(80, 20);
	view_render.setTextSize(1);
	view_render.print(score);
	for (int i = 0; i <= ball_counter; i++)
	{
		xprintf("ball x: %d, ball y: %d", balls[i].x, balls[i].y);
		view_render.drawCircle(balls[i].x, balls[i].y, BALL_RADIUS, WHITE);
		balls[i].x += balls[i].x_speed;
		balls[i].y += balls[i].y_speed;
		is_touching_side_wall(balls[i]);
		is_touching_ceiling(balls[i]);
		is_touching_bar(balls[i]);
		is_game_over(balls[i]);
	}
	// view_render.drawCircle(x, y, BALL_RADIUS, WHITE);
	// x += x_speed;
	// y += y_speed;
	// if (x > WIDTH - BALL_RADIUS || x < BALL_RADIUS) {
	// 	BUZZER_Enable(500, 10);
	// 	BUZZER_PlayTones(tones_startup);
	// 	x_speed = -x_speed;
	// }
	// if (y - BALL_RADIUS <= 0) {
	// 	BUZZER_Enable(500, 10);
	// 	BUZZER_PlayTones(tones_startup);
	// 	y_speed = -y_speed;
	// }
	// touch_bar();
	// if (y - BALL_RADIUS > HEIGHT) {
	// 	timer_remove_attr(TASK_UPDATE_POS, CHANGE_POS);
	// 	SCREEN_TRAN(task_game_over, &scr_game_over);
	// }
}

void task_increase_ball(ak_msg_t* msg) {
	switch (msg->sig) {
		case (INCREASE_BALL): {
			// if (score % 5 == 0 && score != 0 && ball_counter < 3) {
			// 	balls[ball_counter] = {20, 20, 1, 1};
			// 	ball_counter++;
			// }
		}
	}
}


void move_bar_right() {
	if (bar.x < 110) {
		bar.x += 10;
		xprintf("x_bar: %d\nx2_bar: %d\n\n", x_bar, x2_bar);
	}
}

void move_bar_left() {
	if (bar.x > 10) {
		bar.x -= 10;
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
			is_ball_spawning();
			move_bar_right();
		}
	}
}

void task_move_bar_left(ak_msg_t* msg) {
	switch (msg->sig) {
		case (MOVE_LEFT): {
			is_ball_spawning();
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