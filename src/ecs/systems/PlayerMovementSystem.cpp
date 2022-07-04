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
    pce::motion::updateViewDirectionViaMouseReport(joystick.mouse_report, orientation);
    // vezp::print_labeled_dvec3("position: ", orientation.position);
    
  }
}

private:
  double current_time_;
  double time_change_;
  
 
};
}
#endif /* PlayerMovementSystem_cpp */
