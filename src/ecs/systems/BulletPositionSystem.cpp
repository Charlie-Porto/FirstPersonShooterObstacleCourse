#ifndef BulletPositionSystem_cpp
#define BulletPositionSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|

-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include <vezprint.cpp>


#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class BulletPositionSystem : public ISystem {
public:
  void RemoveDeadBullets(){
    for (auto const& entity : dead_bullets_) {
      control.DestroyEntity(entity);
    }
  }

  void UpdateEntities() {
    dead_bullets_ = {};
    for (auto const& entity : entities) {
      auto const& orientation = control.GetComponent<pce::Orientation>(entity);
      auto& position = control.GetComponent<pce::Position>(entity);
      position.actual = orientation.position;
      

      auto const& motion = control.GetComponent<pce::Motion>(entity);
      if (motion.time_airborne >= .5) {
        dead_bullets_.push_back(entity);
      }
    }
    RemoveDeadBullets();
  }

private:
  std::vector<Entity> dead_bullets_;
};
}
#endif /* BulletPositionSystem_cpp */
