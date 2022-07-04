#ifndef BlockFactory_cpp
#define BlockFactory_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
factory for blocks
-----------------------------------------------------------------*/

#include <ezprint.cpp>

extern ControlPanel control;

namespace pce {

class BlockFactory {
public:
  uint32_t CreateBlock(const glm::dvec3& position) {
    uint32_t entity = control.CreateEntity(); 
    control.AddComponent(entity, pce::Position{.actual = position, .rotated = position});
    control.AddComponent(entity, Radar{});
    return entity;
  }

private:
};
}




#endif /* BlockFactory_cpp */
