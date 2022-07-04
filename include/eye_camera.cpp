#ifndef eye_camera_cpp
#define eye_camera_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
camera struct that resembles the human eye. (experimental)
-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp> 
#include <ezprint.cpp>

namespace pce {
struct EyeCamera {
  glm::dvec3 position;  
  glm::dvec3 view_direction;
  double xz_angle;
  double y_angle;
  glm::dquat rotation_versor;
  glm::dvec3 transformation_vector;
  bool flight_mode_activated;
  bool currently_airborne;
  bool currently_jumping;
  double time_airborne;
};
}



#endif /* eye_camera_cpp */
