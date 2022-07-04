#ifndef ScreenMapSystem_cpp
#define ScreenMapSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
system to produce the screen map (common feature of first person shooters)
-----------------------------------------------------------------*/
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include "../System.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"

extern ControlPanel control;

namespace pce{
class ScreenMapSystem : public ISystem {
public:


void Init() {

}


void DrawScreenMap() {
  pce::quickdraw::drawRect(glm::dvec2(5, 567), 100, 100, {255, 255, 255, 255});
  pce::quickdraw::drawMapSquare(glm::dvec2(5, 567), 100, {20, 20, 20, 255});

}


void UpdateEntities() {
  for (auto const& entity : entities) {
    auto const& orientation = control.GetComponent<pce::Orientation>(entity);

    /* draw 2d-converted position on map */

    DrawScreenMap();
  }
}


private:
  glm::dvec2 player_map_position_;
  std::vector<glm::dvec2> enemy_map_positions_;

};
}
#endif /* ScreenMapSystem_cpp */
