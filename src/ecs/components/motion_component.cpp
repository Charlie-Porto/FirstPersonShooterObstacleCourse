#ifndef motion_component_cpp
#define motion_component_cpp

#include <glm/vec3.hpp>

namespace pce {

struct Motion {
  bool is_airborne;
  bool is_jumping;
  double speed;
  glm::dvec3 travel_direction;
  glm::dvec3 initial_velocity;
  glm::dvec3 previous_ground_position;
  double time_airborne;

  bool in_flight_mode;
};

}

#endif /* motion_component_cpp */
