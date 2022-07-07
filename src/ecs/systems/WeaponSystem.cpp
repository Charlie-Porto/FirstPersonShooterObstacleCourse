#ifndef WeaponSystem_cpp
#define WeaponSystem_cpp


#include <ezprint.cpp>

#include "../System.cpp"
#include "weaponFunctions.cpp"
#include "../../constants/static_variables.cpp"

extern ControlPanel control;

namespace pce{
class WeaponSystem : public ISystem {
public:

  void FireWeapon(const Orientation& orientation) {

    const math_objs::LineVectorForm start_pos_and_dir 
        = weapon::calculateBulletStartOrientation(orientation);
    Entity bullet = control.CreateEntity();
    control.AddComponent(bullet, Orientation{
      .position = orientation.position,
      .previous_position = -start_pos_and_dir.origin,
      .view_direction = -start_pos_and_dir.direction,
    });
    control.AddComponent(bullet, Motion{
      .is_airborne = true,
      .speed = 100,
      .travel_direction = -start_pos_and_dir.direction,
      .initial_velocity = 80.0 * -start_pos_and_dir.direction,
      .time_airborne = .01
    });
    control.AddComponent(bullet, Radar{});
    control.AddComponent(bullet, Position{
      .actual = start_pos_and_dir.origin
    });
  }
  

  void UpdateEntities() {
    for (auto const& entity : entities) {
      auto const& joystick = control.GetComponent<pce::Joystick>(entity);     
      if (joystick.mouse_report.left_clicked) {
        auto const& orientation = control.GetComponent<pce::Orientation>(entity);     
        FireWeapon(orientation);
      }
    }
  }

private:


};
}
#endif /* WeaponSystem_cpp */
