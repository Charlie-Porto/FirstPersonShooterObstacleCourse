#ifndef SDL_cartesian_conversion_cpp
#define SDL_cartesian_conversion_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to convert SDL coordinates to cartesian coordinates, and vice versa.
-----------------------------------------------------------------*/

#include <glm/vec2.hpp>
#include <ezprint.cpp>

namespace pce {
namespace convert {

glm::vec2 convertCartesianCoordinatesToSDL(glm::vec2 point) {
  const int sdl_x = point.x + int(global_const::screen_x/2);
  const int sdl_y = -point.y + int(global_const::screen_y/2);
  return glm::vec2(sdl_x, sdl_y);
}


glm::vec2 convertSDLCoordinatesToCartesian(glm::vec2 point) {
  const int cart_x = point.x - int(global_const::screen_x/2);
  const int cart_y = -point.y + int(global_const::screen_y/2);
  return glm::vec2(cart_x, cart_y);
}

}
}




#endif /* SDL_cartesian_conversion_cpp */
