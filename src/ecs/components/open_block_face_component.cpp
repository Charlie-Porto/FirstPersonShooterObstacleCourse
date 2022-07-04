#ifndef open_block_face_component_cpp
#define open_block_face_component_cpp

#include <vector>
#include <glm/vec3.hpp>

namespace pce {

struct OpenBlockFace {
  std::vector<glm::dvec3> open_faces;
};

}

#endif /* open_block_face_component_cpp */
