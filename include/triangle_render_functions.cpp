#ifndef triangle_render_functions_cpp
#define triangle_render_functions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
triangle rendering functions 
-----------------------------------------------------------------*/
#include <cmath>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

// #include <render_functions.cpp>
#include <drawing_functions.cpp>
#include <ezprint.cpp>
#include <math_objects/Triangle.cpp>
#include <sign.cpp>
// #include "constants/static_variables.cpp"

namespace pce {
namespace triangle {


std::vector<glm::dvec2> ConvertGroupCartesianPointstoSDL(const std::vector<glm::dvec2>& points) {
  std::vector<glm::dvec2> sdl_points;
  for (auto const& point : points) {
    const int sdl_x = point.x + int(1000/2.0);
    const int sdl_y = -point.y + int(672/2.0);
    sdl_points.push_back(glm::dvec2(sdl_x, sdl_y));
  }
  return sdl_points;
}



std::vector<glm::dvec2> sortTriangleVerticesHighestToLowest(const std::vector<glm::dvec2>& points) {
  
  auto sorted_points = points;
  while (true) {
    if (sorted_points[0].y >= sorted_points[1].y && sorted_points[1].y >= sorted_points[2].y){
      return sorted_points;
    } else {
      for (int i = 0; i < 2; ++i) { 
        if (sorted_points[i].y < sorted_points[i+1].y) {
          glm::dvec2 temp = sorted_points[i];
          sorted_points[i] = sorted_points[i+1];
          sorted_points[i+1] = temp;
        }
      }
    }
  }
  return sorted_points;
}


void renderTriangleVertices(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer) {
  std::vector<glm::dvec2> vertices = ConvertGroupCartesianPointstoSDL(triangle.points);
  for (auto const& vertex : vertices) {
    drawCircle(vertex.x, vertex.y, 10, {230, 10, 200, 255}, renderer);
  }
}


double calculateAngleBetweenVector2s(const glm::dvec2 A, const glm::dvec2 B) {
  return acos(
    (glm::dot(A, B) / (glm::dot(A, A) * glm::dot(B, B)))
  );
}


void drawLine(const glm::dvec2& A, const glm::dvec2& B, const std::vector<int>& color, SDL_Renderer* renderer) {
  const std::vector<glm::dvec2> vertices = ConvertGroupCartesianPointstoSDL({A, B});
  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
  SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y,
                               vertices[1].x, vertices[1].y);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
}


void drawPoint(const glm::dvec2 point, SDL_Renderer* renderer) {
  const int sdl_x = point.x + int(1000/2.0);
  const int sdl_y = -point.y + int(672/2.0);
  drawCircle(sdl_x, sdl_y, 5.0, {200, 100, 40, 255}, renderer);
}



void renderTriangleSides(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer) {
  const std::vector<glm::dvec2> vertices = ConvertGroupCartesianPointstoSDL(triangle.points);
  SDL_SetRenderDrawColor(renderer, 25, 244, 170, 255);

  SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y,
                               vertices[1].x, vertices[1].y);
  SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y,
                               vertices[2].x, vertices[2].y);
  SDL_RenderDrawLine(renderer, vertices[2].x, vertices[2].y,
                               vertices[1].x, vertices[1].y);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
}


// void renderFilledTriangle(const pce::math_objs::Triangle& triangle, SDL_Renderer* renderer,
//                           double inscribed_block_height) {
//   std::vector<glm::dvec2> sorted_vertices = sortTriangleVerticesHighestToLowest(triangle.points);
//   for (auto const& vertex : sorted_vertices) {
//     vezp::print_labeled_dvec2("vertex", vertex);
//   }

//   // approach from top 
//   glm::dvec2 prince_point = sorted_vertices[0] - glm::dvec2(0, inscribed_block_height);
//   drawLine(sorted_vertices[0], prince_point, renderer);
//   const glm::dvec2 side_a_vec = normalize((sorted_vertices[0] - sorted_vertices[2]));
//   const glm::dvec2 side_b_vec = normalize((sorted_vertices[0] - sorted_vertices[1]));
//   const double side_a_angle = calculateAngleBetweenVector2s(glm::dvec2(0, 1), side_a_vec)
//                             * -pce::math::sign(sorted_vertices[0].x - side_a_vec.x);
//   const double side_b_angle = calculateAngleBetweenVector2s(side_b_vec, glm::dvec2(0, 1))
//                             * -pce::math::sign(sorted_vertices[0].x - side_b_vec.x);
//   // vezp::print_labeled_dvec2("angle-comparison vector:", side_a_vec);
//   ezp::print_labeled_item("side_a_angle: ", (side_a_angle * 180.0 / 3.14159));
//   ezp::print_labeled_item("side_b_angle: ", (side_b_angle * 180.0 / 3.14159));

//   ezp::print_item("---------");
//   while (prince_point.y >= sorted_vertices[1].y) {
//     // vezp::print_labeled_dvec2("prince_point", prince_point);
//     glm::dvec2 crawl_a_1 = prince_point;

//     ezp::print_labeled_item("prince_point.y: ", prince_point.y);
//     crawl_a_1.x = crawl_a_1.y * tan(side_a_angle * 2.0);
//                 // * -pce::math::sign(sorted_vertices[0].x - side_a_vec.x);
//     ezp::print_labeled_item("crawl_a_1.x: ", crawl_a_1.x);
    
//     const double side_b_radius = (sorted_vertices[0].y - crawl_a_1.y)/sin(side_b_angle);
//     // ezp::print_labeled_item("side b radius: ", side_b_radius);
//     glm::dvec2 crawl_b_1 = sorted_vertices[0] - side_b_vec * side_b_radius; 
//     crawl_b_1.y = crawl_a_1.y;
//     // vezp::print_labeled_dvec2("vec a", side_a_vec);
//     // vezp::print_labeled_dvec2("vec b", side_b_vec);
//     // vezp::print_labeled_dvec2("crawl a", crawl_a_1);
//     // vezp::print_labeled_dvec2("crawl b", crawl_b_1);
//     drawLine(crawl_a_1, crawl_b_1, renderer); 
//     prince_point.y -= inscribed_block_height;
//   }

//   // // approach from bottom
//   // prince_point = sorted_vertices[2] + glm::dvec2(0, inscribed_block_height);
//   // drawLine(sorted_vertices[2], prince_point, renderer);
//   // const glm::dvec2 side_c_vec = normalize((sorted_vertices[2] - sorted_vertices[1]));
//   // const glm::dvec2 side_d_vec = normalize((sorted_vertices[2] - sorted_vertices[0]));
//   // const double side_c_angle = calculateAngleBetweenVector2s(side_c_vec, glm::dvec2(0, -1))
//   //                           * pce::math::sign(sorted_vertices[2].x - side_c_vec.x);
//   // const double side_d_angle = calculateAngleBetweenVector2s(side_d_vec, glm::dvec2(0, -1))
//   //                           * pce::math::sign(sorted_vertices[2].x - side_d_vec.x);
//   // // vezp::print_labeled_dvec2("angle-comparison vector:", side_a_vec);
//   // ezp::print_labeled_item("side_c_angle: ", (side_c_angle * 180.0 / 3.14159));
//   // ezp::print_labeled_item("side_d_angle: ", (side_d_angle * 180.0 / 3.14159));

//   // ezp::print_item("---------");
//   // while (prince_point.y <= sorted_vertices[1].y) {
//   //   // vezp::print_labeled_dvec2("prince_point", prince_point);
//   //   glm::dvec2 crawl_c_1 = prince_point;
//   //   const double side_d_radius = (sorted_vertices[2].y + crawl_c_1.y)/sin(side_d_angle);
//   //   // ezp::print_labeled_item("side d radius: ", side_d_radius);
//   //   glm::dvec2 crawl_d_1 = sorted_vertices[2] + side_d_vec * side_d_radius; 
//   //   crawl_d_1.y = crawl_c_1.y;
//   //   // vezp::print_labeled_dvec2("vec c", side_c_vec);
//   //   // vezp::print_labeled_dvec2("vec d", side_d_vec);
//   //   // vezp::print_labeled_dvec2("crawl c", crawl_c_1);
//   //   // vezp::print_labeled_dvec2("crawl d", crawl_d_1);
//   //   drawLine(crawl_c_1, crawl_d_1, renderer); 
//   //   prince_point.y += inscribed_block_height;
// }



// }
}
}





#endif /* triangle_render_functions_cpp */
