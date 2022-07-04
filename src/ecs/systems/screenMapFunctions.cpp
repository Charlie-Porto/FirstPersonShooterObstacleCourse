#ifndef screenMapFunctions_cpp
#define screenMapFunctions_cpp


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <SDL_cartesian_conversion.cpp>
#include <ezprint.cpp>
#include "subsystems/simpleDrawingFunctions.cpp"


namespace pce {
namespace screen_map {

const double map_width = 100.0;
const glm::dvec2 map_start_pos = glm::dvec2(5, 567);
const glm::dvec2 map_origin = map_start_pos + (map_width/2 * glm::dvec2(1, 1));
const glm::dvec2 map_origin_cartesian = pce::convert::convertSDLCoordinatesToCartesian(map_origin);
const glm::dvec2 map_transf_vec = map_origin_cartesian;

void drawMapCenter() {
  vezp::print_labeled_dvec2("map origin: ", map_origin);
  vezp::print_labeled_dvec2("cartesian map origin: ", map_origin_cartesian);
  pce::quickdraw::drawCircleAtRawVec2(map_origin, {255, 255, 255, 255}, 1.0);
}

glm::dvec2 convertActualCoordinatesToScreenMap(const glm::dvec3& coordinates) {
  auto const raw_xz_coordinates = glm::dvec2(coordinates.x, (coordinates.z - 10.0));
  return glm::dvec2(raw_xz_coordinates * 1.7) + map_transf_vec;
}



}
}


#endif /* screenMapFunctions_cpp */
