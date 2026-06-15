#include "scr_options.h"

int options_cursor[3] = {SOUND, BALL_SPEED, BACK};
int current_cursor = 0;
int sound_on = SOUND_ON;

view_dynamic_t dyn_view_scr_options{
    {.item_type = ITEM_TYPE_DYNAMIC},
    render_options,
};

view_screen_t scr_options{
    &dyn_view_scr_options,
    ITEM_NULL,
    ITEM_NULL,
    .focus_item = 0,
};

void render_options()
{
  view_render.drawBitmap(15, options_cursor[current_cursor], image_arrow_right_bits, 7, 5, WHITE);
  view_render.setCursor(20, 15);
  view_render.setTextSize(2);
  view_render.print("OPTIONS");
  view_render.setTextSize(1);
  view_render.setCursor(30, 35);
  view_render.print("Sound");
  view_render.setCursor(65, 35);
  view_render.print(sound_on == SOUND_ON ? "On" : "Off");
  view_render.setCursor(30, 45);
  view_render.print("Ball speed");
  view_render.setCursor(110, 45);
  view_render.print(game_data.max_speed);
  view_render.setCursor(30, 55);
  view_render.print("Back");
}

void task_options_screen(ak_msg_t *msg)
{
  switch (msg->sig)
  {
  case AC_DISPLAY_BUTTON_UP_PRESSED:
    if (current_cursor > 0)
    {
      current_cursor--;
    }
    break;

  case AC_DISPLAY_BUTTON_DOWN_PRESSED:
    if (current_cursor < 2)
    {
      current_cursor++;
    }
    break;

  case AC_DISPLAY_BUTTON_MODE_PRESSED:
    if (current_cursor == 0)
    {
      sound_on == SOUND_ON ? sound_on = SOUND_OFF : sound_on = SOUND_ON;
      BUZZER_Sleep(sound_on);
    }
    if (current_cursor == 1)
    {
      game_data.max_speed++;
      if (game_data.max_speed > 5)
      {
        game_data.max_speed = 1;
      }
    }
    if (current_cursor == 2)
    {
      current_cursor = 2;
      SCREEN_TRAN(task_title_screen, &scr_title);
    }
    break;

  default:
    break;
  }
}