#ifndef joystick_component_cpp
#define joystick_component_cpp

#include <virtual_keyboard.cpp>
#include <mouse_controller.cpp>
namespace pce {

struct Joystick {
  JoystickReport keyboard_report; 
  mouse::MouseReport mouse_report;
};

}

#endif /* joystick_component_cpp */
