#ifndef WeaponRenderSystem_cpp
#define WeaponRenderSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
system for rendering guns, bullets, and other weapons
-----------------------------------------------------------------*/

#include <cmath>
#include <vector>
#include <glm/vec2.hpp>
#include <ezprint.cpp>

#include "../System.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"
#include "subsystems/squareDrawingFunctions.cpp"
#include "../../constants/static_variables.cpp"

extern ControlPanel control;

namespace pce{

const glm::dvec2 gun_point_a = glm::dvec2(150, -160);
const glm::dvec2 gun_point_b = glm::dvec2(170, -150);
const glm::dvec2 gun_point_c = glm::dvec2(400, -global_const::screen_y/2);
const glm::dvec2 gun_point_d = glm::dvec2(300, -global_const::screen_y/2);
const std::vector<int> gun_color = {20, 20, 20, 25};
auto const tri_a = pce::math_objs::Triangle{.points={gun_point_a, gun_point_b, gun_point_c}};
auto const tri_b = pce::math_objs::Triangle{.points={gun_point_a, gun_point_c, gun_point_d}};

class WeaponRenderSystem : public ISystem {
public:

  void UpdateEntities() {
    pce::quickdraw::drawLine(gun_point_a, gun_point_b);
    pce::draw::drawFilledTriangleWithColor(tri_a, gun_color);
    pce::draw::drawFilledTriangleWithColor(tri_b, gun_color);
    for (auto const& entity : entities) {
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      const double radius = 80.0 / radar.distance_from_player;
      pce::quickdraw::drawCircleAtVec2(radar.hitpoint_corresponding_pixel,
                                       {255, 100, 10, 255}, radius);
    }
  }

private:
};
}
#endif /* WeaponRenderSystem_cpp */
