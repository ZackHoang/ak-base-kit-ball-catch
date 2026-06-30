#include "scr_game.h"

game_data_t game_data;

void render_game() {
	view_render.drawRect(game_data.bar.x, game_data.bar.y, BAR_WIDTH,
						 BAR_HEIGHT, WHITE);
	view_render.setCursor(60, 10);
	view_render.setTextSize(1);
	view_render.drawRect(12, 3, 104, 55, WHITE);
	snprintf(game_data.score_display_buffer,
			 sizeof(game_data.score_display_buffer), "Score: %d",
			 game_data.score);
	view_render.print(game_data.score_display_buffer);
	for (int i = 16; i <= 115; i += 5) {
		view_render.drawLine(i, 52, i, 57, WHITE);
	}
	for (int i = 0; i <= game_data.ball_counter; i++) {
		view_render.drawCircle(game_data.balls[i].x, game_data.balls[i].y,
							   BALL_RADIUS, WHITE);
	}
	if (game_data.game_over == true) {
		view_render.drawBitmap(game_data.ball_lost_x - 10,
							   game_data.ball_lost_y - 10, image_boom_bits, 20,
							   20, WHITE);
	}
}

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

void init_game() {
	game_data.score							= 0;
	game_data.read_score					= 0;
	game_data.target_score					= 5;
	game_data.ball_counter					= 0;
	game_data.bar							= bar_t{54, 45};
	game_data.balls[game_data.ball_counter] = {
		ball_t{(uint8_t)((rand() % 12) + 92), (uint8_t)((rand() % 15) + 20),
			   (int8_t)(rand() % game_data.max_speed + 1),
			   game_data.max_speed}
	   };
	game_data.game_over = false;
	timer_set(TASK_BALL_CATCH, CHANGE_POS, BALL_CATCH_RENDER_AND_PROCESS_TICK,
			  TIMER_PERIODIC);
	timer_set(AC_TASK_DISPLAY_ID, RENDER_GAME,
			  BALL_CATCH_RENDER_AND_PROCESS_TICK, TIMER_PERIODIC);
}

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
	if (ball.y + BALL_RADIUS >= game_data.bar.y - BAR_HEIGHT &&
		ball.y - BALL_RADIUS <= game_data.bar.y + BAR_HEIGHT &&
		ball.x >= game_data.bar.x && ball.x <= game_data.bar.x + BAR_WIDTH &&
		ball.y_speed > 0 && game_data.game_over == false) {
		BUZZER_PlayTones(tones_bang);
		ball.y_speed = -ball.y_speed;
		ball.y		 = game_data.bar.y - BALL_RADIUS - 1;
		game_data.score++;
	}
}

void is_game_over(ball_t &ball) {
	if (ball.y - BALL_RADIUS > HEIGHT - 10) {
		game_data.game_over = true;
		BUZZER_PlayTones(tone_game_over);
		timer_remove_attr(TASK_BALL_CATCH, CHANGE_POS);
		timer_remove_attr(TASK_BALL_CATCH, RENDER_GAME);
		if (eeprom_read(0, (uint8_t *)&game_data.read_score,
						sizeof(game_data.read_score) == 0)) {
			if (game_data.read_score < game_data.score) {
				eeprom_write(0, (uint8_t *)&game_data.score,
							 sizeof(game_data.score));
			}
		}
		game_data.ball_lost_x = ball.x;
		game_data.ball_lost_y = ball.y;
		timer_set(TASK_BALL_CATCH, GAME_OVER, BALL_CATCH_GAME_OVER_TICK,
				  TIMER_ONE_SHOT);
	}
}

void is_ball_spawning() {
	if (game_data.score == game_data.target_score &&
		game_data.ball_counter < MAX_BALL - 1) {
		game_data.ball_counter++;
		game_data.target_score += 5;
		game_data.balls[game_data.ball_counter] = {
			(uint8_t)((rand() % 12) + 92), (uint8_t)((rand() % 10) + 20),
			(int8_t)(rand() % game_data.max_speed + 1), game_data.max_speed};
	}
}

void change_ball_coords() {
	for (int i = 0; i <= game_data.ball_counter; i++) {
		if (game_data.game_over == false) {
			game_data.balls[i].x += game_data.balls[i].x_speed;
			game_data.balls[i].y += game_data.balls[i].y_speed;
			is_game_over(game_data.balls[i]);
		}
		is_touching_side_wall(game_data.balls[i]);
		is_touching_ceiling(game_data.balls[i]);
		is_touching_bar(game_data.balls[i]);
		is_ball_spawning();
	}
}

void task_game_screen(ak_msg_t *msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
			init_game();
		} break;

		case AC_DISPLAY_BUTTON_UP_PRESSED: {
			if (game_data.bar.x <= 80 && game_data.game_over == false) {
				game_data.bar.x += 10;
			}
		} break;

		case AC_DISPLAY_BUTTON_DOWN_PRESSED: {
			if (game_data.bar.x >= 20 && game_data.game_over == false) {
				game_data.bar.x -= 10;
			}
		} break;

		case CHANGE_POS: {
			change_ball_coords();
		} break;
		case RENDER_GAME: {
		} break;

		case GAME_OVER: {
			SCREEN_TRAN(task_game_over_screen, &scr_game_over);
		} break;

		default: {
		} break;
	}
}