#ifndef triangle_raster_functions_cpp
#define triangle_raster_functions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to rasterize triangles
-----------------------------------------------------------------*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <triangle_render_functions.cpp>
#include <ezprint.cpp>
#include <vezprint.cpp>
#include <vec2_functions.cpp>
#include <sign.cpp>


namespace pce {
namespace rast {
const double PI = 3.1415965;

void printVec3StdVector(const std::vector<glm::dvec2> points) {
  vezp::print_labeled_dvec2("highest point: ", points[0]);
  vezp::print_labeled_dvec2("middle point: ", points[1]);
  vezp::print_labeled_dvec2("lowest point: ", points[2]);
}

void fastRenderFilledTriangleTopHalf(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer,
                                 double inscribed_block_height, const std::vector<int>& color) {
   
}

void renderFilledTriangleTopHalf(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer,
                                 double inscribed_block_height, const std::vector<int>& color) {

  /* currently successfully renders top half of triangles */
  // ezp::print_item("------------------------");
  std::vector<glm::dvec2> points = pce::triangle::sortTriangleVerticesHighestToLowest(triangle.points);
  if (points[0].y == points[1].y) {
    ++points[0].y;
  }
  if (points[1].y == points[2].y) {
    --points[2].y;
  }
  // printVec3StdVector(points);
  const glm::dvec2 height_uvec = glm::dvec2(0, 1);
  const double height = points[0].y - points[2].y;
  const glm::dvec2 height_vector_bottom_point = glm::dvec2(points[0].x, points[2].y);
  glm::dvec2 prince_vector = points[0];

  // (TEMP) draw height vector
  // pce::triangle::drawLine(points[0], height_vector_bottom_point, renderer);

  /* get side vector */
  const glm::dvec2 long_side = points[0] - points[2];
  const glm::dvec2 short_side = points[0] - points[1];
  /* calculate side vectors' angle with the height vector */
  const double long_angle_sign = pce::math::sign((points[2].x - points[0].x));
  const double short_angle_sign = pce::math::sign((points[1].x - points[0].x));

  const double t_long_side_angle = v2func::calcAngleBetweenVector2s(
    height_uvec * points[0].y, long_side);
  const double t_short_side_angle = v2func::calcAngleBetweenVector2s(
    height_uvec * points[0].y, short_side);
  // ezp::print_labeled_item("t_long side angle: ", (t_long_side_angle / PI * 180.0));
  // ezp::print_labeled_item("t_short side angle: ", (t_short_side_angle / PI * 180.0));
  double crawl_long_x = double(inscribed_block_height) * tan(t_long_side_angle * long_angle_sign);
  double crawl_short_x = double(inscribed_block_height) * tan(t_short_side_angle * short_angle_sign);
  double crawl_num = 0;
  for (int i = 0; i <= int(points[2].y+height - (points[1].y)); i += int(inscribed_block_height)) {
    /* now the crawl points */
    const glm::dvec2 crawl_long_a = glm::dvec2((prince_vector.x + (crawl_long_x * crawl_num) * pce::math::sign(points[0].y)), prince_vector.y);
    const glm::dvec2 crawl_short_a = glm::dvec2((prince_vector.x + (crawl_short_x * crawl_num) * pce::math::sign(points[0].y)), prince_vector.y);
    pce::triangle::drawLine(crawl_long_a, crawl_short_a, color, renderer);
    prince_vector.y -= inscribed_block_height;
    ++crawl_num;
  }


}

void renderFilledTriangleLowerHalf(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer,
                                   double inscribed_block_height, const std::vector<int>& color) {
  
  /* currently successfully renders top half of triangles */
  // ezp::print_item("------------------------");
  std::vector<glm::dvec2> points = pce::triangle::sortTriangleVerticesHighestToLowest(triangle.points);
  if (points[0].y != points[1].y) {
    glm::dvec2 temp = points[0];
    points[0] = points[2];
    points[2] = temp;
    // printVec3StdVector(points);
    const glm::dvec2 height_uvec = glm::dvec2(0, -1);
    const double height = points[0].y - points[2].y;
    const glm::dvec2 height_vector_top_point = glm::dvec2(points[0].x, points[2].y);
    glm::dvec2 prince_vector = points[0];

    // (TEMP) draw height vector
    // pce::triangle::drawLine(points[0], height_vector_top_point, renderer);

    /* get side vector */
    const glm::dvec2 long_side = points[0] - points[2];
    const glm::dvec2 short_side = points[0] - points[1];
    const double long_angle_sign = pce::math::sign((points[2].x - points[0].x));
    const double short_angle_sign = pce::math::sign((points[1].x - points[0].x));

    const double t_long_side_angle = v2func::calcAngleBetweenVector2s(
    height_uvec * points[0].y, long_side);
    const double t_short_side_angle = v2func::calcAngleBetweenVector2s(
    height_uvec * points[0].y, short_side);

    /* now the crawl points */
    double crawl_long_x = double(inscribed_block_height) * tan(t_long_side_angle * long_angle_sign);
    double crawl_short_x = double(inscribed_block_height) * tan(t_short_side_angle * short_angle_sign);
    double crawl_num = 0;

    for (int i = 0; i <= -int(points[2].y+height - (points[1].y)); i += int(inscribed_block_height)) {
      // double crawl_long_x = double(i) * tan(t_long_side_angle * long_angle_sign);
      // double crawl_short_x = double(i) * tan(t_short_side_angle * short_angle_sign);
      const glm::dvec2 crawl_long_a = glm::dvec2((prince_vector.x + (crawl_long_x * crawl_num) * pce::math::sign(points[0].y)), prince_vector.y);
      const glm::dvec2 crawl_short_a = glm::dvec2((prince_vector.x + (crawl_short_x * crawl_num) * pce::math::sign(points[0].y)), prince_vector.y);
      pce::triangle::drawLine(crawl_long_a, crawl_short_a, color, renderer);
      prince_vector.y += inscribed_block_height;
      ++crawl_num;
    }
  }
}



void renderFilledTriangle(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer,
                          double inscribed_block_height, const std::vector<int>& color) {
  pce::rast::renderFilledTriangleTopHalf(triangle, renderer, inscribed_block_height, color);
  pce::rast::renderFilledTriangleLowerHalf(triangle, renderer, inscribed_block_height, color);

}

}
}



#endif /* triangle_raster_functions_cpp */
