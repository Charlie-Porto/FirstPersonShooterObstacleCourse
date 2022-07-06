#ifndef BlockRenderSystem_cpp
#define BlockRenderSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
system to render them blocks using some algorithmz
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include "blockRenderFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{ 
class BlockRenderSystem : public ISystem {
public:

  void UpdateEntities(const glm::dvec3& transform_vector, const glm::dquat& versor) {
    // ezp::print_item("updating block render system");
    // for (auto const& entity : entities) {
    set<Entity>::iterator itr;
    for (auto const& entity : entities) {
      // if (entity < 30) {
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      auto const& neighbors = control.GetComponent<pce::Neighbors>(entity);      
      
      auto const neighbor_entities = neighbors.entities;
      // ezp::print_item("-------------");
      for (auto const& neighbor : neighbor_entities) {
        // ezp::print_item(neighbor);
        auto const& neighbor_radar = control.GetComponent<pce::Radar>(neighbor);
        pce::quickdraw::drawLine(radar.hitpoint_corresponding_pixel, neighbor_radar.hitpoint_corresponding_pixel);
      }
      // ezp::print_item("-------------");
      
      

      // } /* dev if backet */

    }
  }

private:
};
}
#endif /* BlockRenderSystem_cpp */
