#ifndef simpleDrawingFunctions_cpp
#define simpleDrawingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
simple drawing functions to assist the ray trace system
-----------------------------------------------------------------*/
#include <vector>
#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <drawing_functions.cpp>
#include <render_functions.cpp>
#include "../../../SDL_core/simulation_manager.cpp"
#include "../../../constants/static_variables.cpp"

namespace pce {
namespace quickdraw {

std::vector<glm::dvec2> ConvertGroupCartesianPointstoSDL(const std::vector<glm::dvec2>& points) {
  std::vector<glm::dvec2> sdl_points;
  for (auto const& point : points) {
    const int sdl_x = point.x + int(global_const::screen_x/2);
    const int sdl_y = -point.y + int(global_const::screen_y/2);
    sdl_points.push_back(glm::dvec2(sdl_x, sdl_y));
  }
  return sdl_points;
}


glm::vec2 ConvertCartesianCoordinatesToSDL(glm::vec2 point) {
  const int sdl_x = point.x + int(global_const::screen_x/2);
  const int sdl_y = -point.y + int(global_const::screen_y/2);
  return glm::vec2(sdl_x, sdl_y);
}

void drawLine(glm::dvec2 point_a_transform, glm::dvec2 point_b_transform) {
  SDL_SetRenderDrawColor(Simulation::renderer, 255, 202, 170, 255);
  glm::dvec2 a_sdl_coordinates = ConvertCartesianCoordinatesToSDL(
                                                point_a_transform);
  glm::dvec2 b_sdl_coordinates = ConvertCartesianCoordinatesToSDL(
                                                point_b_transform);
  SDL_RenderDrawLine(
    Simulation::renderer,
    a_sdl_coordinates.x, a_sdl_coordinates.y,
    b_sdl_coordinates.x, b_sdl_coordinates.y
  );                                           
  SDL_SetRenderDrawColor(Simulation::renderer, 0, 0, 0, 255);
}


const std::vector<int> rcolor = {250, 10, 100, 255};
void drawListOfPixels(const std::vector<glm::dvec2>& pixels) {
  std::vector<glm::dvec2> sdl_pixels{};
  for (int i = 0; i < pixels.size(); ++i) {
    sdl_pixels.push_back(ConvertCartesianCoordinatesToSDL(pixels[i]));
  }
  pce::render::renderVec2PixelList(sdl_pixels, rcolor, Simulation::renderer);
}

void drawPixelAtVec2(glm::vec2 pixel, const std::vector<int>& color) {
  const glm::vec2 sdl_transform = ConvertCartesianCoordinatesToSDL(pixel);
  // ezp::print_item("drawing pixel at Vec2");
  // vezp::print_dvec2(pixel);
  drawPixelVec2(sdl_transform, color, Simulation::renderer);
}

void drawSmallCircleAtVec2(const glm::vec2& point, const std::vector<int>& color) {
  // ezp::print_item("drawing circle at Vec2");
  // vezp::print_dvec2(point);
  const glm::vec2 sdl_transform = ConvertCartesianCoordinatesToSDL(point);
  drawCircle(sdl_transform.x, sdl_transform.y, 10, color, Simulation::renderer);
}

// const std::vector<int> mcolor = {100, 160, 50, 255};
void drawCircleAtVec2(const glm::vec2& point, const std::vector<int>& color, double radius) {
  // ezp::print_item("drawing circle at Vec2");
  // vezp::print_dvec2(point);
  const glm::vec2 sdl_transform = ConvertCartesianCoordinatesToSDL(point);
  drawCircle(sdl_transform.x, sdl_transform.y, int(radius), color, Simulation::renderer);
}

const std::vector<glm::dvec2> crosshair_points = {
  glm::dvec2(0, 0),
  glm::dvec2(0, 1),
  glm::dvec2(0, -1),
  glm::dvec2(0, 2),
  glm::dvec2(0, -2),
  glm::dvec2(0, 3),
  glm::dvec2(0, -3),
  glm::dvec2(1, 0),
  glm::dvec2(-1, 0),
  glm::dvec2(2, 0),
  glm::dvec2(-2, 0),
  glm::dvec2(3, 0),
  glm::dvec2(-3, 0),
};

const std::vector<glm::dvec2> crosshair_SDL_points = ConvertGroupCartesianPointstoSDL(crosshair_points);

void DrawCrossHairs() {
  pce::render::renderVec2PixelList(crosshair_SDL_points, {255, 255, 255, 255}, Simulation::renderer);
}

}
}

#endif /* simpleDrawingFunctions_cpp */
