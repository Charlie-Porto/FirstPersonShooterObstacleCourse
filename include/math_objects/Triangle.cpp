#ifndef Triangle_cpp
#define Triangle_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
triangle struct.
-----------------------------------------------------------------*/

#include <glm/vec2.hpp>
#include <ezprint.cpp>

namespace pce {
namespace math_objs {

struct Triangle {
  std::vector<glm::dvec2> points;
};

}}



#endif /* Triangle_cpp */
