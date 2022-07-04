#ifndef squareDrawingFunctions_cpp
#define squareDrawingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to draw squares
-----------------------------------------------------------------*/

#include <vector>
#include <algorithm>

#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <drawing_functions.cpp>
#include <render_functions.cpp>
#include <triangle_raster_functions.cpp>
#include "simpleDrawingFunctions.cpp"
#include "../../../SDL_core/simulation_manager.cpp"
#include "../../../constants/static_variables.cpp"


namespace pce {
namespace draw {

std::vector<int> determineColorAsFunctionOfDistance(double distance) {
  std::vector<int> color = {
    std::max(255 - int(distance/2.0), 0),
    10,
    std::max(200 - int(distance/2.0), 0)
  };
  return color;
}


void drawQuadrilateral(const std::vector<glm::dvec2> points, std::vector<int> color) {
  const std::vector<glm::dvec2> cartesian_points = pce::quickdraw::ConvertGroupCartesianPointstoSDL(points);
  SDL_SetRenderDrawColor(Simulation::renderer, color[0], color[1], color[2], color[3]);
  for (int i = 0; i < cartesian_points.size(); ++i) {
    SDL_RenderDrawLine(
      Simulation::renderer,
      cartesian_points[i].x, cartesian_points[i].y,
      cartesian_points[(i+1) % cartesian_points.size()].x, 
      cartesian_points[(i+1) % cartesian_points.size()].y
    );                                           
  }
  SDL_SetRenderDrawColor(Simulation::renderer, 0, 0, 0, 255);
}


void drawQuadrilateralWithDistanceColor(const std::vector<glm::dvec2> points, double distance) {
  const std::vector<int> color = determineColorAsFunctionOfDistance(distance); 
  drawQuadrilateral(points, color);
}



void drawFilledTriangleWithDistanceColor(const pce::math_objs::Triangle& tri, double distance) {
  const std::vector<int> color = determineColorAsFunctionOfDistance(distance); 
  pce::rast::renderFilledTriangleTopHalf(tri, Simulation::renderer, 13.0, color);
  pce::rast::renderFilledTriangleLowerHalf(tri, Simulation::renderer, 13.0, color);
}

void drawFilledQuadrilateralWithDistanceColor(const std::vector<glm::dvec2> points, double distance) {

}

}
}




#endif /* squareDrawingFunctions_cpp */
