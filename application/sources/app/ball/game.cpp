#include "game.h"
// #include "stdlib.h"

// TODO:
// Title screen: smaller option text and arrow + icon next to game title
// Game play: instead of saws, could consider either straight lines or triangles as thorns
// Boom effect: a boom bitmap should be drawn when a ball comes in contact with thorns (maybe sound effect too?)

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

static uint8_t score;
static uint8_t read_score;
static uint8_t target_score;
static uint8_t ball_counter;
static bar_t bar;
// static char game_over_buffer[50];
static char score_display_buffer[25];
bool game_over;
static ball_t balls[MAX_BALL];
uint8_t max_speed = 1;
// static uint8_t game_over_cursor[2] = {40, 50};
// static uint8_t game_over_cursor_opt = 0;

void init_game() {
	score = 0;
	read_score = 0;
	target_score = 5;
	ball_counter = 0;
	bar = bar_t{54, 50};
	game_over = false;
	balls[ball_counter] = {ball_t{(uint8_t)((rand() % 12) + 92), (uint8_t)((rand() % 15) + 20), max_speed, max_speed}};
	timer_set(TASK_UPDATE_POS, CHANGE_POS, 100, TIMER_PERIODIC);
}

void show_boom() {
	view_render.drawBitmap(0, 0, image_boom_bits, 128, 64, WHITE);
}

view_dynamic_t dyn_view_scr_boom = {
	{
		.item_type = ITEM_TYPE_DYNAMIC
	},
	show_boom
};

view_screen_t scr_boom = {
		&dyn_view_scr_boom,
		ITEM_NULL,
		ITEM_NULL,
		.focus_item = 0,
};

void task_show_boom(ak_msg_t* msg) {}


// void task_confirm_game_over_choice(ak_msg_t* msg) {
// 	switch (msg->sig)
// 	{
// 	case CONFIRM_GAME_OVER:
// 		if (game_over_cursor_opt == 0) {
// 			game_over = false;
// 			current_screen = SCREEN_GAME_ACTIVE;
// 			init_game();
// 			SCREEN_TRAN(task_game, &scr_game);
// 		} else if (game_over_cursor_opt == 1) {
// 			game_over = false;
// 			current_screen = SCREEN_TITLE;
// 			SCREEN_TRAN(handle_scr_title, &scr_title);
// 		}
// 		break;

// 	default:
// 		break;
// 	}
// }

// void task_change_game_over_cursor(ak_msg_t* msg) {
// 	switch (msg->sig)
// 	{
// 	case GAME_OVER_CURSOR_UP:
// 		if (game_over == true && game_over_cursor_opt > 0) {
// 			game_over_cursor_opt--;
// 		}
// 		break;

// 	case GAME_OVER_CURSOR_DOWN:
// 		if (game_over == true && game_over_cursor_opt < 1) {
// 			game_over_cursor_opt++;
// 		}
// 		break;
// 	}
// }

// void render_game_over() {
// 	view_render.clear();
// 	view_render.drawBitmap(10, 20, image_cry_dolph_bits, 55, 52, WHITE);
// 	view_render.setCursor(65, 30);
// 	view_render.setTextSize(1);
// 	view_render.print("GAME OVER!");
// 	view_render.setCursor(10, 5);
// 	eeprom_read(0, (uint8_t *)&read_score, sizeof(read_score));
// 	snprintf(game_over_buffer, sizeof(game_over_buffer), "Best Score: %d", read_score);
// 	view_render.print(game_over_buffer);
// 	view_render.drawBitmap(80, game_over_cursor[game_over_cursor_opt], image_arrow_right_bits, 7, 5, WHITE);
// 	view_render.setCursor(92, 40);
// 	view_render.print("Retry");
// 	view_render.setCursor(92, 50);
// 	view_render.print("Quit");
// }

// view_dynamic_t dyn_view_scr_game_over = {
// 		{
// 				.item_type = ITEM_TYPE_DYNAMIC,
// 		},
// 		render_game_over,
// };

// view_screen_t scr_game_over = {
// 		&dyn_view_scr_game_over,
// 		ITEM_NULL,
// 		ITEM_NULL,
// 		.focus_item = 0,
// };

void is_touching_side_wall(ball_t &ball) {
	if (ball.x > WIDTH - BALL_RADIUS - 20 || ball.x < BALL_RADIUS + 20) {
		BUZZER_PlayTones(tones_bang);
		ball.x_speed = -ball.x_speed;
	}
}

void is_touching_ceiling(ball_t &ball) {
	if (ball.y - BALL_RADIUS <= 10) {
		BUZZER_PlayTones(tones_bang);
		ball.y_speed = -ball.y_speed;
	}
}

void is_touching_bar(ball_t &ball) {
	if (ball.y + BALL_RADIUS >= bar.y - BAR_HEIGHT && ball.y - BALL_RADIUS <= bar.y + BAR_HEIGHT && ball.x >= bar.x && ball.x <= bar.x + BAR_WIDTH && game_over == false) {
		BUZZER_PlayTones(tones_bang);
		ball.y_speed = -ball.y_speed;
		score++;
	}
}

void is_game_over(ball_t &ball) {
	if (ball.y - BALL_RADIUS > HEIGHT - 15) {
		timer_remove_attr(TASK_UPDATE_POS, CHANGE_POS);
		if (eeprom_read(0, (uint8_t *)&read_score, sizeof(read_score) == 0))
		{
			xprintf("read score before: %d\n", read_score);
			if (read_score < score)
			{
				eeprom_write(0, (uint8_t *)&score, sizeof(score));
			}
			xprintf("read score after: %d\n", read_score);
		}
		game_over = true;
		current_screen = SCREEN_GAME_OVER;
		view_render.drawBitmap(ball.x - 10, ball.y - 10, image_boom_bits, 20, 20, WHITE);
		timer_set(TASK_GAME_OVER, GAME_OVER, 2000, TIMER_ONE_SHOT);
	}
}

void is_ball_spawning() {
	if (score == target_score && ball_counter < MAX_BALL - 1 && game_over == false) {
		ball_counter++;
		target_score += 5;
		balls[ball_counter] = {(uint8_t)((rand() % 12) + 92), (uint8_t)((rand() % 10) + 20), max_speed, max_speed};
	}
}

void render_game() {
	view_render.drawRect(bar.x, bar.y, BAR_WIDTH, BAR_HEIGHT, WHITE);
	view_render.setCursor(60, 15);
	view_render.setTextSize(1);
	view_render.drawRect(12, 8, 104, 55, WHITE);
	snprintf(score_display_buffer, sizeof(score_display_buffer), "Score: %d", score);
	view_render.print(score_display_buffer);
	for (int i = 14; i <= 115; i += 5) {
		view_render.drawLine(i, 52, i, 62, WHITE);
	}
	for (int i = 0; i <= ball_counter; i++)
	{
		xprintf("ball x: %d, ball y: %d", balls[i].x, balls[i].y);
		view_render.drawCircle(balls[i].x, balls[i].y, BALL_RADIUS, WHITE);
		if (game_over == false) {
			balls[i].x += balls[i].x_speed;
			balls[i].y += balls[i].y_speed;
			is_game_over(balls[i]);
		}
		is_touching_side_wall(balls[i]);
		is_touching_ceiling(balls[i]);
		is_touching_bar(balls[i]);
	}
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
	if (bar.x <= 80 && game_over == false) {
		bar.x += 10;
		xprintf("\nbar.x: %d\n", bar.x);
	}
}

void move_bar_left() {
	if (bar.x >= 20 && game_over == false) {
		bar.x -= 10;
		xprintf("\nbar.y: %d\n", bar.y);
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

// void render_game_screen()
// {
// 	draw_game();
// }

view_dynamic_t dyn_view_scr_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	render_game,
};

view_screen_t scr_game = {
	&dyn_view_scr_game,
	ITEM_NULL,
	ITEM_NULL,
	.focus_item = 0,
};

void task_game(ak_msg_t* msg) {}

void task_show_game_over(ak_msg_t* msg) {}

void task_game_over(ak_msg_t* msg) {
	switch (msg->sig)
	{
	case GAME_OVER:
		SCREEN_TRAN(task_show_game_over, &scr_game_over);
		break;

	default:
		break;
	}
}