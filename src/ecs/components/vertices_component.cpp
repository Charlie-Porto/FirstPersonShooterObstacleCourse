#ifndef vertices_component_cpp
#define vertices_component_cpp


#include <utility>
#include <vector>
#include <unordered_map>
#include <glm/vec3.hpp>

namespace pce {

struct Vertices {
  std::unordered_map<uint32_t, glm::dvec3> original_positions; // numbered 1-4
  std::unordered_map<uint32_t, glm::dvec3> transformed_positions;
  std::vector<std::pair<uint32_t, uint32_t>> edges;
};

}

#endif /* vertices_component_cpp */
