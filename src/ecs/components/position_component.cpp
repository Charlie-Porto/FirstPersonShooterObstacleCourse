#ifndef position_component_cpp
#define position_component_cpp

#include <glm/vec3.hpp>

namespace pce {
struct Position {
  glm::dvec3 actual;
  glm::dvec3 rotated;
};

}

#endif /* position_component_cpp */
