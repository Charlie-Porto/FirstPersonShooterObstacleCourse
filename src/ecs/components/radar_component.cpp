#ifndef radar_component_cpp
#define radar_component_cpp

#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace pce {

struct Radar {
  glm::dvec3 view_sphere_hitpoint;
  glm::dvec2 hitpoint_corresponding_pixel; 
  double distance_from_player;
  std::unordered_map<uint32_t, glm::dvec2> vertices_corresponding_pixels;
};

}

#endif /* radar_component_cpp */
