#ifndef MapBuilderSystem_cpp
#define MapBuilderSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
psuedo-system that makes the map
^^ not an actual system; not inherited from ISystem
-----------------------------------------------------------------*/

#include <vector>
#include <assert.h>

#include <orca_array.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>


extern ControlPanel control;

namespace pce{

const int map_width_x = 41;
const int map_height_y = 5;
const int map_depth_z = 41;


class MapBuilderSystem {
public:
MapBuilderSystem() {
  origin_index_ = glm::dvec3(double(map_width_x - 1.0)/2.0,
                             0.0, 
                             double(map_depth_z - 1.0)/2.0);
  // origin_index_ = glm::dvec3(double(map_width_x), double(map_height_y), double(map_depth_z));
  // vezp::print_labeled_dvec3("origin_index_", origin_index_);
  ezp::print_item("constructing MapBuilderSystem");
}

Entity CreateBlockEntity(glm::ivec3 index) {

  Entity block = control.CreateEntity();

    const glm::dvec3 start_position = glm::dvec3(index) - glm::dvec3(0, 0, 10) - origin_index_;
    control.AddComponent(block, pce::MapArray{.index = index});
    control.AddComponent(block, pce::Position{
      .actual = start_position
    });
    control.AddComponent(block, pce::Radar{});
  // ezp::print_labeled_item("entity start position for entity: ", block);
  // vezp::print_dvec3(start_position);
  return block;
}


void CreateMapArray() {
  auto null_entity_ = control.CreateEntity();
  // currently, this function creates a 5x5 floor
  for (int i = 0; i < map_width_x; ++i) {
    for (int j = 0; j < map_height_y; ++j) {
      for (int k = 0; k < map_depth_z; ++k) {
        if (j == 0) {
          auto entity = CreateBlockEntity(glm::ivec3(i, j, k));
          map_array_.at(i, j, k) = entity;
        } else {
          map_array_.at(i, j, k) = 0;
        }
      }
    }
  }
}

void AssignEntityNeighbors() {
  std::unordered_map<int, std::vector<int>> directions;
  directions[1] = {1, 0};
  directions[-1] = {0, 1};

  int dir = 1;
  for (int i = 0; i < map_width_x; ++i) {
    for (int k = 0; k < map_depth_z; ++k) {
      // if (i == 0 || k == 0 || i == map_width_x-1 || k == map_depth_z-1) {
        // control.AddComponent(map_array_.at(i, 0, k), Neighbors{});
      // }
      std::vector<int> this_dir = directions[dir];

      uint32_t nentity_a = map_array_.at(i+this_dir[0], 0, k+this_dir[1]);
      uint32_t nentity_b = map_array_.at(i-this_dir[0], 0, k-this_dir[1]);
 
      if (nentity_a == 0) { nentity_a = nentity_b; }
      if (nentity_b == 0) { nentity_b = nentity_a; }
      ezp::print_labeled_item("entity neighbor a: ", nentity_a);
      ezp::print_labeled_item("entity neighbor b: ", nentity_b);
       
      control.AddComponent(map_array_.at(i, 0, k), Neighbors{
        .entities = {
          nentity_a,
          nentity_b
        } 
      });
      dir *= -1;
    }

  }
}


void PrintMapArray() {
  for (int i = 0; i < map_width_x; ++i) {
    for (int j = 0; j < map_height_y; ++j) {
      // ezp::print_item(MapArray[i][j]);
      for (int k = 0; k < map_depth_z; ++k) {
        ezp::print_item(map_array_.at(i, j, k));
      }
    }
  }
}

static glm::dvec3 origin_index_;
static orca_array::array3d<uint32_t> map_array_;

private:
  Entity null_entity;
};

glm::dvec3 MapBuilderSystem::origin_index_;
orca_array::array3d<uint32_t> MapBuilderSystem::map_array_(map_width_x, map_height_y, map_width_x);


}
#endif /* MapBuilderSystem_cpp */
