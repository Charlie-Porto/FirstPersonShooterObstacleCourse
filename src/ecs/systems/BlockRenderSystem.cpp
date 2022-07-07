#ifndef BlockRenderSystem_cpp
#define BlockRenderSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
system to render them blocks using some algorithmz
-----------------------------------------------------------------*/

#include <ezprint.cpp>
// #include "blockRenderFunctions.cpp"
#include "../System.cpp"
#include "subsystems/squareDrawingFunctions.cpp"

extern ControlPanel control;

namespace pce{ 
class BlockRenderSystem : public ISystem {
public:

  void UpdateEntities(const glm::dvec3& transform_vector, const glm::dquat& versor) {
    for (auto const& entity : entities) {
      // if (entity < 30) {
      auto const& radar = control.GetComponent<pce::Radar>(entity);
      auto const& neighbors = control.GetComponent<pce::Neighbors>(entity);      
      
      /* only render blocks within certain range to save compute resources */
      if (radar.distance_from_player <= 50) {
        auto const neighbor_entities = neighbors.entities;
        for (auto const& neighbor : neighbor_entities) {
          auto const& neighbor_radar = control.GetComponent<pce::Radar>(neighbor);
          pce::draw::drawLineWithDistanceColor(radar.hitpoint_corresponding_pixel, 
                                              neighbor_radar.hitpoint_corresponding_pixel,
                                              radar.distance_from_player);
        }
      
      }

      // } /* dev if backet */

    }
  }

private:
};
}
#endif /* BlockRenderSystem_cpp */
