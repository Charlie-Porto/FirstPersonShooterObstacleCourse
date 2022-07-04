#ifndef PlayerMovementSystem_cpp
#define PlayerMovementSystem_cpp


#include <ezprint.cpp>
#include <vezprint.cpp>

#include "playerMovementFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class PlayerMovementSystem : public ISystem {
public:

PlayerMovementSystem() {
  current_time_ = 0.0;
  time_change_ = 0.0;
  if_mouse_moved = false;
}

void UpdateEntities(double sdl_time) {
  time_change_ = sdl_time - current_time_;
  current_time_ = sdl_time;

  for (auto const& entity : entities) {
    auto const& joystick = control.GetComponent<pce::Joystick>(entity);
    auto& motion = control.GetComponent<pce::Motion>(entity);
    auto& orientation = control.GetComponent<pce::Orientation>(entity);
    orientation.previous_position = orientation.position;
    pce::motion::updatePositionBasedOnJoystickReport(joystick.keyboard_report, orientation, motion);

    /* control for mouse re-centering */
    if (!if_mouse_moved) {
      if_mouse_moved = pce::motion::updateViewDirectionViaMouseReport(joystick.mouse_report, orientation);
    } else {
      if_mouse_moved = false;
    }
    
  }
}

private:
  double current_time_;
  double time_change_;
  bool if_mouse_moved;
  
 
};
}
#endif /* PlayerMovementSystem_cpp */
