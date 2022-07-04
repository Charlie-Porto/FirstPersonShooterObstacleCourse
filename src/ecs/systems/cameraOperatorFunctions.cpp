#ifndef cameraOperatorFunctions_cpp
#define cameraOperatorFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the CameraOperatorSystem
-----------------------------------------------------------------*/

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp>
#include <camera_functions.cpp>
#include <virtual_keyboard.cpp>
#include <ezprint.cpp>
#include <vezprint.cpp>

namespace pce {
namespace cam_op {

const double PI = 3.14159265;

void updateCameraReverseRotationVersor(EyeCamera& camera) {
  const glm::dquat vert_rot_versor = cam_func::getCameraVerticalRotationVersor(-camera.y_angle);
  const glm::dquat horiz_rot_versor = cam_func::getCameraHorizontalRotationVersor(camera.xz_angle);
  camera.rotation_versor = horiz_rot_versor * vert_rot_versor;
}



}
}



#endif /* cameraOperatorFunctions_cpp */
