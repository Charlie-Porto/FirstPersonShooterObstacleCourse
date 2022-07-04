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

const int map_width_x = 51;
const int map_height_y = 5;
const int map_depth_z = 51;


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
    // control.AddComponent(block, pce::Block{.type_index = 1});
    control.AddComponent(block, pce::MapArray{.index = index});
    control.AddComponent(block, pce::Position{
      .actual = start_position
    });
    control.AddComponent(block, pce::Radar{});
    control.AddComponent(block, pce::OpenBlockFace{});
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
        // if (j == 0 || j == map_height_y-1) {
          auto entity = CreateBlockEntity(glm::ivec3(i, j, k));
          map_array_.at(i, j, k) = entity;
        } else if ((i == 5 && k == 5 && j < 2)
                || (i == 5 && k == 6 && j < 2)
                || (i == 6 && k == 6 && j < 2)
                || (i == 6 && k == 5 && j < 2)
                || (i == 4 && k == 13 && j < 2)) {
          auto entity = CreateBlockEntity(glm::ivec3(i, -j, k));
          map_array_.at(i, j, k) = entity;
        // } else if (k == (map_depth_z-2)){
          // auto entity = CreateBlockEntity(glm::ivec3(i, j, k));
        // } else if (i == 0 || i == map_width_x-1){
          // auto entity = CreateBlockEntity(glm::ivec3(i, j, k));
        } else {
          map_array_.at(i, j, k) = 0;
        }
      }
    }
  }
}


void assignAllOpenBlockFaceComponents() {
  for (int i = 0; i < map_width_x; ++i) {
    for (int j = 0; j < map_height_y; ++j) {
      for (int k = 0; k < map_depth_z; ++k) {
        auto entity = map_array_.at(i, j, k);
        auto& open_faces = control.GetComponent<pce::OpenBlockFace>(entity);
        if (open_faces.open_faces.size() >= 6 || entity == 0) {
          continue;
        }

        // check for block below
        if (j > 0) {
          if (map_array_.at(i, j-1, k) == 0) {
            open_faces.open_faces.push_back(glm::dvec3(0, -0.5, 0));
          }
        }

        // check for block above
        if (j < map_height_y) {
          if (map_array_.at(i, j+1, k) == 0) {
            open_faces.open_faces.push_back(glm::dvec3(0, 0.5, 0));
          }
        }
        
        // check for block to the left
        if (i > 0)  {
          if (map_array_.at(i+1, j, k) == 0) {
            open_faces.open_faces.push_back(glm::dvec3(-0.5, 0, 0));
          }
        }

        // check for block to the right
        if (i < map_width_x)  {
          if (map_array_.at(i-1, j, k) == 0) {
            open_faces.open_faces.push_back(glm::dvec3(0.5, 0, 0));
          }
        }
                
        // check for block behind
        if (k > 0)  {
          if (map_array_.at(i, j, k+1) == 0) {
            open_faces.open_faces.push_back(glm::dvec3(0, 0, -0.5));
          }
        }
        
        // check for block in front
        if (k < map_depth_z)  {
          if (map_array_.at(i, j, k-1) == 0) {
            open_faces.open_faces.push_back(glm::dvec3(0, 0, 0.5));
          }
        }
        

      }
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
