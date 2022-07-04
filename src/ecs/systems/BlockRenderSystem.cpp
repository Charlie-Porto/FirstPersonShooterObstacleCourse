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
    for (auto const& entity : entities) {

      /* the below if statement is just for deving */
      // if (entity > 255 && entity < 257) {
      // if (entity < 1278 && entity >1000) {
      // ezp::print_item("*******");
      // ezp::print_labeled_item("entity: ", entity);
      auto const& position = control.GetComponent<pce::Position>(entity);
      auto const& blockfaces = control.GetComponent<pce::OpenBlockFace>(entity);
      auto const& radar = control.GetComponent<pce::Radar>(entity);

      glm::dvec3 closest_vertex = pce::brend::getClosestVertexRelativePosition(position.rotated);
      for (auto const& face : blockfaces.open_faces) {
        pce::brend::renderCubeSide(position.actual, face, transform_vector, versor, 
                                  radar.distance_from_player);
          
      }

      // } /* dev if backet */

    }
  }

private:
};
}
#endif /* BlockRenderSystem_cpp */
