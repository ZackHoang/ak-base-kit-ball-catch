#include "options.h"

int options_cursor[3] = {37, 47, 57};
int current_cursor = 0;

void render_options() {
  view_render.drawBitmap(15, options_cursor[current_cursor], image_arrow_right_bits, 7, 5, WHITE);
  view_render.setCursor(20, 15);
  view_render.setTextSize(2);
  view_render.print("OPTIONS");
  view_render.setTextSize(1);
  view_render.setCursor(30, 35);
  view_render.print("Sound");
  view_render.setCursor(30, 45);
  view_render.print("Ball speed");
  view_render.setCursor(30, 55);
  view_render.print("Back");
}

view_dynamic_t dyn_view_scr_options {
    { .item_type = ITEM_TYPE_DYNAMIC} ,
    render_options,
};

view_screen_t scr_options {
  &dyn_view_scr_options,
  ITEM_NULL,
  ITEM_NULL,
  .focus_item = 0,
};

void task_options(ak_msg_t* msg) {
  switch (msg->sig) {
    case CHANGE_OPTIONS_UP:
      if (current_cursor > 0) {
        current_cursor--;
      }
      break;

    case CHANGE_OPTIONS_DOWN:
      if (current_cursor < 2) {
        current_cursor++;
      }
      break;

    default:
      break;
  }
}

void task_confirm_option_choice(ak_msg_t* msg) {
  switch (msg->sig)
  {
  case CONFIRM_OPTION_CHOICE:
    /* code */
    if (current_cursor == 2) {
      current_cursor = 0;
      current_screen = 0;
      curr_opt = 1;
      SCREEN_TRAN(task_title, &scr_title);
    }
    break;

  default:
    break;
  }
}