#include "game.h"
#include <math.h>
#include <vector>

using namespace std;

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

struct snake_coords {
	uint32_t x;
	uint32_t y;
	Direction dir;
};

struct {
	uint8_t x;
	uint8_t y;
} health_pos;

// static int score = 0;
static uint8_t snake_pos = 50;
static uint8_t snake_length = 50;
static vector<snake_coords> snake_coordinates;

void init_snake_coords() {
	for (uint8_t i = 0; i <= snake_length; i++) {
		snake_coordinates[i] = {i, 10, RIGHT};
		xprintf("\nsnake_coordinates[%d]=>x, y, dir: %d %d %d\n", i, snake_coordinates[i].x, snake_coordinates[i].y, snake_coordinates[i].dir);
	}
}

void rotate_snake_clock_wise(snake_coords &coord) {
	switch(coord.dir) {
		case UP: {
			coord.dir = RIGHT;
			coord.x += 1;
			break;
		}
		case RIGHT: {
			coord.dir = DOWN;
			coord.y -= 1;
			break;
		}
		case DOWN: {
			coord.dir = LEFT;
			coord.x -= 1;
			break;
		}
		case LEFT: {
			coord.dir = UP;
			coord.y -= 1;
			break;
		}
	}
}

void rotate_snake_counter_clock_wise(snake_coords &coord) {
	switch (coord.dir) {
		case UP: {
			coord.dir = LEFT;
			coord.x -= 1;
			break;
		}
		case RIGHT: {
			coord.dir = UP;
			coord.y -= 1;
		}
		case DOWN: {
			coord.dir = RIGHT;
			coord.x += 1;
		};
		case LEFT: {
			coord.dir = DOWN;
			coord.y += 1;
		}
		default:
			break;
	}
}

void render_game_over()
{
	view_render.drawBitmap(8, 6, image_cry_dolph_bits, 55, 32, WHITE);
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

void randomize_health() {
	health_pos.x = rand() % 129;
	health_pos.y = rand() % 65;
}

void draw_snake() {
	if (snake_pos > 128) {
		SCREEN_TRAN(task_game_over, &scr_game_over);
	}
	// for (int i = 0; i <= (uint8_t)snake_coordinates.size(); i++)
	// {
	// 	view_render.drawPixel(snake_coordinates[i].x, snake_coordinates[i].y, BLACK);
	// }
	// for (int i = 0; i <= (uint8_t)snake_coordinates.size(); i++) {
	// 	snake_coordinates[i].x += 5;
	// }
	for (int i = 0; i < (uint8_t)snake_coordinates.size(); i++) {
		view_render.drawPixel(snake_coordinates[i].x, snake_coordinates[i].y, WHITE);
	}
}

void task_draw_snake(ak_msg_t* msg) {
	switch (msg->sig) {
		case (CHANGE_POS): {
			view_render_screen(&scr_game);
		}
	}
}

void render_game_screen()
{
	init_snake_coords();
	draw_snake();
	timer_set(TASK_UPDATE_POS, CHANGE_POS, 1000, TIMER_PERIODIC);
	view_render.drawBitmap(20, 50, image_health, health_pos.x, health_pos.y, WHITE);
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