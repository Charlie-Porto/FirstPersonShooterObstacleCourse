#ifndef vec2_functions_cpp
#define vec2_functions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|

-----------------------------------------------------------------*/

#include <cmath>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <ezprint.cpp>


namespace v2func {
double calcAngleBetweenVector2s(glm::dvec2 A, glm::dvec2 B) {
  // this function assumes both vectors originate at the origin. 
  // should be fine -- unless I find out it's not.
  return acos(glm::dot(A, B) / (sqrt(glm::dot(A, A)) * sqrt(glm::dot(B, B))));
}


}



#endif /* vec2_functions_cpp */
