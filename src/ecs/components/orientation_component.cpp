#ifndef orientation_component_cpp
#define orientation_component_cpp

#include <glm/vec3.hpp>

namespace pce {

struct Orientation {
  glm::dvec3 position;  
  glm::dvec3 previous_position;  
  glm::dvec3 view_direction;
  double xz_view_angle;
  double y_view_angle;
};

}

#endif /* orientation_component_cpp */
