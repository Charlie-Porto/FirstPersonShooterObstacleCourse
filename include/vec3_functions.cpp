#ifndef vec3_functions_cpp
#define vec3_functions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to manipulate vector3s
-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <cmath>
#include <iostream>

#include <ezprint.cpp>

namespace v3func {

double calculateMagnitude(glm::dvec3 v) {
  return glm::dot(v, v);
}

double calculateDistanceBetweenPosition3Vectors(glm::dvec3 A, glm::dvec3 B) {
  const glm::dvec3 D = A - B;
  return glm::dot(D, D);
}



}



#endif /* vec3_functions_cpp */
