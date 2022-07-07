#ifndef weaponFunctions_cpp
#define weaponFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the weapons system
-----------------------------------------------------------------*/

#include <math_objects/LineVectorForm.cpp>
#include <ezprint.cpp>

namespace pce {
namespace weapon {

math_objs::LineVectorForm calculateBulletStartOrientation(const Orientation& orientation) {
  const glm::dvec3 direction = orientation.view_direction;
  const glm::dvec3 start_position = orientation.position + 2.0 * orientation.view_direction;
  return math_objs::LineVectorForm{.direction=direction, .origin=start_position};
}


}
}



#endif /* weaponFunctions_cpp */
