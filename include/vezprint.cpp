#ifndef vezprint_cpp
#define vezprint_cpp

#include <iostream>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp>

#include <ezprint.cpp>

/*
  Purpose: this module contains functions to speed up the printing of vector3s and quaternions. 
*/

namespace vezp {

void print_dquat(const glm::dquat& q) {
  ezp::print_labeled_item("w: ", q.w);
  ezp::print_labeled_item("x: ", q.x);
  ezp::print_labeled_item("y: ", q.y);
  ezp::print_labeled_item("z: ", q.z);
}

void print_dvec3(const glm::dvec3& v) {
  ezp::print_labeled_item("x: ", v.x);
  ezp::print_labeled_item("y: ", v.y);
  ezp::print_labeled_item("z: ", v.z);
}

void print_labeled_dvec3(const std::string& label, const glm::dvec3& v) {
  std::cout << label << ": " << double(v.x) << ", " << double(v.y) << ", " << double(v.z) << '\n';
}

void print_dvec2(const glm::dvec2& v) {
  ezp::print_labeled_item("x: ", v.x);
  ezp::print_labeled_item("y: ", v.y);
}

void print_labeled_dvec2(const std::string& label, const glm::dvec2& v) {
  std::cout << label << ": " << double(v.x) << ", " << double(v.y) << '\n';
}

}

#endif /* vezprint_cpp */
