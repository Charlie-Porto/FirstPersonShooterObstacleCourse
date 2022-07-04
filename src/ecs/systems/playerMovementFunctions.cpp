#ifndef playerMovementFunctions_cpp
#define playerMovementFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the PlayerMovementSystem class.
-----------------------------------------------------------------*/

#include <cmath>
#include <orca_array.hpp>
#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include <sign.cpp>
#include "../../constants/static_variables.cpp"
#include "MapBuilderSystem.cpp"

extern ControlPanel control;

namespace pce{
namespace motion {

const double GRAVITY = -9.81;
const double PI = 3.14159265;


uint32_t getEntityByPositionFromMapArray(const glm::dvec3& position) {
  const glm::dvec3 index = pce::MapBuilderSystem::origin_index_ - position + glm::dvec3(0, 0, 10);
  return pce::MapBuilderSystem::map_array_.at(int(index.x), int(index.y), int(index.z));
}


void rotateGazeLaterally(pce::Orientation& orientation, const double& direction) {
  orientation.xz_view_angle += global_const::view_movement_angle * direction;
  const double xz_circle_radius = cos(orientation.y_view_angle/180.0 * PI) * global_const::view_sphere_radius;
  orientation.view_direction.x = sin(orientation.xz_view_angle/180.0 * PI) * xz_circle_radius;
  orientation.view_direction.z = cos(orientation.xz_view_angle/180.0 * PI) * xz_circle_radius;
}


void rotateGazeVertically(pce::Orientation& orientation, const double& direction) {
  orientation.y_view_angle += global_const::view_movement_angle * direction;
  orientation.view_direction.y = sin(orientation.y_view_angle/180.0 * PI) * global_const::view_sphere_radius;
  rotateGazeLaterally(orientation, 0.0);
}


void movePlayerLaterally(pce::Orientation& orientation, const glm::dvec3 direction) {
  // ezp::print_item("moving player laterally");
  glm::dvec3 orthogonal_view_direction = glm::normalize(glm::dvec3(orientation.view_direction.z, 0.0,
                                                    -orientation.view_direction.x));
  // vezp::print_labeled_dvec3("direction vector", orientation.view_direction);
  // vezp::print_labeled_dvec3("orthogonal direction vector", orthogonal_view_direction);
  auto const movement_vector = glm::dvec3(
    (direction.x/10.0 * -orthogonal_view_direction.x + 2.0 * direction.z * orientation.view_direction.x),
    0.0,
    (2.0 * direction.z * orientation.view_direction.z + -direction.x/10.0 * orthogonal_view_direction.z)
  ) * global_const::movement_speed;
  const glm::dvec3 potential_position = orientation.position + movement_vector;
  orientation.position += movement_vector;
}

void updateViewDirectionViaMouseReport(const mouse::MouseReport& mouse_report, pce::Orientation& orientation) {
  const double direction_x_shift = pce::math::sign(mouse_report.x_position - mouse_report.prev_x_pos);
  const double direction_y_shift = -pce::math::sign(mouse_report.y_position - mouse_report.prev_y_pos);
  if (direction_x_shift != 0 || direction_y_shift != 0) {
    ezp::print_item("mouse moving");
    ezp::print_labeled_item("direction_x_shift", direction_x_shift);
    ezp::print_labeled_item("direction_y_shift", direction_y_shift);
    rotateGazeLaterally(orientation, direction_x_shift);
    rotateGazeVertically(orientation, direction_y_shift);
  }
}

void updatePositionBasedOnJoystickReport(const JoystickReport& report,
                                         pce::Orientation& orientation,
                                         pce::Motion& motion) {
  if (report.D_pressed) { movePlayerLaterally(orientation, glm::dvec3(-1, 0, 0)); }
  if (report.A_pressed) { movePlayerLaterally(orientation, glm::dvec3(1, 0, 0)); }
  if (report.S_pressed) { movePlayerLaterally(orientation, glm::dvec3(0, 0, -1)); }
  if (report.W_pressed) { movePlayerLaterally(orientation, glm::dvec3(0, 0, 1)); }
  if (report.R_pressed) { rotateGazeLaterally(orientation, 1.0); }
  if (report.L_pressed) { rotateGazeLaterally(orientation, -1.0); }
  if (report.Up_pressed) { rotateGazeVertically(orientation, 1.0); }
  if (report.Down_pressed) { rotateGazeVertically(orientation, -1.0); }
  if (report.SPACE_pressed) { 
    if (!motion.is_airborne){
      motion.is_airborne = true;
      motion.previous_ground_position = orientation.position;
      motion.travel_direction.y = global_const::jump_velocity;
      motion.initial_velocity = glm::dvec3(motion.speed * motion.travel_direction.x, global_const::jump_velocity, 
                                           motion.speed * motion.travel_direction.z);
      vezp::print_labeled_dvec3("initial_velocity", motion.initial_velocity);
    }
  }

}


}
}



#endif /* playerMovementFunctions_cpp */
