#ifndef blockRenderFunctions_cpp
#define blockRenderFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the block render system
-----------------------------------------------------------------*/
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <quaternion_funktions.cpp>
#include <ezprint.cpp>
#include <sign.cpp>
#include <math_objects/Triangle.cpp>

#include "subsystems/simpleDrawingFunctions.cpp"
#include "subsystems/squareDrawingFunctions.cpp"
#include "../../SDL_core/simulation_manager.cpp"


namespace pce {
namespace brend {

glm::dvec3 getClosestVertexRelativePosition(const glm::dvec3& position) {
  return glm::dvec3(pce::math::sign(position.x) * .05, pce::math::sign(position.y) * .05,
                    pce::math::sign(position.z) * .05);
}


std::vector<glm::dvec3> getBlockFaceVertices(const glm::dvec3 position,
                                             const glm::dvec3& side_to_render) {
  const glm::dvec3 face_center = position - side_to_render;
  const glm::dvec3 absolute_side = glm::dvec3(
    abs(side_to_render.x), abs(side_to_render.y), abs(side_to_render.z)
  );
  const glm::dvec3 vertices_offset_vector = glm::dvec3(0.5, 0.5, 0.5) - absolute_side;
  if (vertices_offset_vector.y == 0) {
    return {
      glm::dvec3(face_center.x + vertices_offset_vector.x, face_center.y, face_center.z + vertices_offset_vector.z),
      glm::dvec3(face_center.x + vertices_offset_vector.x, face_center.y, face_center.z + -vertices_offset_vector.z),
      glm::dvec3(face_center.x + -vertices_offset_vector.x, face_center.y, face_center.z + -vertices_offset_vector.z),
      glm::dvec3(face_center.x + -vertices_offset_vector.x, face_center.y, face_center.z + vertices_offset_vector.z)
    };
  } else if (vertices_offset_vector.x == 0) {
    return {
      glm::dvec3(face_center.x, face_center.y + vertices_offset_vector.y, face_center.z + vertices_offset_vector.z),
      glm::dvec3(face_center.x, face_center.y + vertices_offset_vector.y, face_center.z + -vertices_offset_vector.z),
      glm::dvec3(face_center.x, face_center.y + -vertices_offset_vector.y, face_center.z + -vertices_offset_vector.z),
      glm::dvec3(face_center.x, face_center.y + -vertices_offset_vector.y, face_center.z + vertices_offset_vector.z),
    };
  // } else if (vertices_offset_vector.z == 0) {
  } else {
    return {
      glm::dvec3(face_center.x + vertices_offset_vector.x, face_center.y + vertices_offset_vector.y, face_center.z),
      glm::dvec3(face_center.x + vertices_offset_vector.x, face_center.y +  -vertices_offset_vector.y, face_center.z),
      glm::dvec3(face_center.x + -vertices_offset_vector.x, face_center.y +  -vertices_offset_vector.y, face_center.z),
      glm::dvec3(face_center.x + -vertices_offset_vector.x, face_center.y +  vertices_offset_vector.y, face_center.z),
    };
  }
}


glm::dvec3 transformVertexForRender(const glm::dvec3 point, const glm::dvec3& transform_vector,
                                    const glm::dquat& rotation_versor) {
  const glm::dvec3 transformed_position = point - transform_vector;
  return qfunc::rotateVector3byQuaternion(transformed_position, rotation_versor);
}


void renderVertex(const glm::dvec3& rotated_position) {
  glm::dvec3 view_sphere_hitpoint = glm::normalize((rotated_position));
  glm::dvec2 hitpoint_corresponding_pixel = -pce::pix_map::fastconvertPointOnViewSphereToPixel(
    view_sphere_hitpoint, glm::dvec3(0, 0, 0)
  ) / global_const::pixel_squish_ratio;
}


std::pair<pce::math_objs::Triangle, pce::math_objs::Triangle> 
divideQuadrilateralIntoTwoTriangles(const std::vector<glm::dvec2>& points) {
  auto const tri_a = pce::math_objs::Triangle{
    .points = { points[0], points[1], points[2] }
  };
  auto const tri_b = pce::math_objs::Triangle{
    .points = { points[0], points[2], points[3] }
  };
  auto const tri_pair = std::pair<pce::math_objs::Triangle, pce::math_objs::Triangle>(tri_a, tri_b);
  return tri_pair;
}


void renderCubeFilledFace(const std::vector<glm::dvec2>& points, const double& distance) {
  // ezp::print_item("rendering cube filled face");
  std::pair<pce::math_objs::Triangle, pce::math_objs::Triangle> quad_tris = divideQuadrilateralIntoTwoTriangles(points);
  
  pce::draw::drawFilledTriangleWithDistanceColor(quad_tris.first, distance);
  pce::draw::drawFilledTriangleWithDistanceColor(quad_tris.second, distance);
  
}


void renderCubeSide(const glm::dvec3& position, const glm::dvec3& side_to_render, 
                    const glm::dvec3& transform_vector, const glm::dquat& versor, double distance) {
  std::vector<glm::dvec3> vertices = getBlockFaceVertices(position, side_to_render);
  std::vector<glm::dvec2> pixels;
  for (auto const& vertex : vertices) {
    // vezp::print_labeled_dvec3("vertex", vertex);
    // vezp::print_labeled_dvec3("vertex", vertex);
    const glm::dvec3 transformed_position = transformVertexForRender(vertex, transform_vector, versor);
    pixels.push_back(-pce::pix_map::fastconvertPointOnViewSphereToPixel(
      glm::normalize(transformed_position), glm::dvec3(0, 0, 0)
    ) / global_const::pixel_squish_ratio);
  }
  // pce::draw::drawQuadrilateral(pixels, {200, 0, 100, 255});
  pce::draw::drawQuadrilateralWithDistanceColor(pixels, distance);
  // if (distance < 300.0 && distance < 400.0) {
  // if (distance < 300.0) {
    // renderCubeFilledFace(pixels, distance);
  // }
}


   


}
}



#endif /* blockRenderFunctions_cpp */
