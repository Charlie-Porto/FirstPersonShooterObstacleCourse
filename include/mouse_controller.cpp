#ifndef mouse_controller_cpp
#define mouse_controller_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
struct & class to track the mouse
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include "../src/SDL_core/simulation_manager.cpp"


namespace pce {
namespace mouse {

struct MouseReport{
  int x_position;
  int y_position;
  int prev_x_pos;
  int prev_y_pos;
  bool left_clicked;
  bool right_clicked;
};

class VirtualMouse {
public:


  VirtualMouse() {
    mouse_report_.x_position = 0.0;
    mouse_report_.y_position = 0.0;
    mouse_report_.left_clicked = false;
    mouse_report_.right_clicked = false;
  }

  MouseReport& PollMouse() {
    prev_mouse_x = mouse_x;
    prev_mouse_y = mouse_y;
    mouse_report_.prev_x_pos = prev_mouse_x;
    mouse_report_.prev_y_pos = prev_mouse_y;
    buttons_ = SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse_report_.x_position = mouse_x;
    mouse_report_.y_position = mouse_y;

    if ((buttons_ & SDL_BUTTON_LMASK) != 0) {
      mouse_report_.left_clicked = true;
    }
    if ((buttons_ & SDL_BUTTON_LMASK) == 0) {
      mouse_report_.left_clicked = false;
    }
    if ((buttons_ & SDL_BUTTON_RMASK) != 0) {
      mouse_report_.right_clicked = true;
    }
    if ((buttons_ & SDL_BUTTON_RMASK) == 0) {
      mouse_report_.right_clicked = false;
    }

    return mouse_report_;
  }


private:
  MouseReport mouse_report_;
  int mouse_x;
  int mouse_y;
  int prev_mouse_x;
  int prev_mouse_y;
  uint32_t buttons_;
};

}
}


#endif /* mouse_controller_cpp */
