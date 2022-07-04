#ifndef CameraOperatorSystem_cpp
#define CameraOperatorSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
Camera Operator System: manages the camera
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <eye_camera.cpp>
#include <camera_functions.cpp>

#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class CameraOperatorSystem : public ISystem {
public:
  CameraOperatorSystem (){
  }
  
  void Init() {
    camera_.position = glm::dvec3(0, 0, 0);
    camera_.view_direction = normalize(glm::dvec3(0, -1, 1));
    camera_.xz_angle = 0.0;
    camera_.y_angle = 0.0;
    camera_.rotation_versor = {1.0, 0.0, 0.0, 0.0};
    camera_.transformation_vector = {0, 0, 0};
    camera_.flight_mode_activated = false;
  }

  const glm::dquat ProvideCamVersor() const {
    return camera_.rotation_versor;
  }
  const glm::dvec3 ProvideCamTransformVector() const {
    return -camera_.position;
  }
  const glm::dvec3 ProvideCamPosition() const {
    return camera_.position;
  }


  void UpdateCamera() {
    int limiter = 1;
    for (auto const& entity : entities) {
    // update camera rotation versor
      auto const& orientation = control.GetComponent<pce::Orientation>(entity);
      const glm::dquat vert_rot_versor = cam_func::getCameraVerticalRotationVersor(-orientation.y_view_angle);
      const glm::dquat horiz_rot_versor = cam_func::getCameraHorizontalRotationVersor(orientation.xz_view_angle);
      camera_.rotation_versor = horiz_rot_versor * vert_rot_versor;
      camera_.position = orientation.position;
      camera_.transformation_vector = -orientation.position;
      // ensure camera is updated once
      --limiter;
      if (limiter == 0) {break;}
    }
  }

private:
  EyeCamera camera_;
  

};
}
#endif /* CameraOperatorSystem_cpp */
