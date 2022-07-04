#ifndef static_variables_cpp
#define static_variables_cpp


/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
to store static consts used in the project
-----------------------------------------------------------------*/

namespace global_const {

// screen
const int screen_x = 1000;
const int screen_y = 672;

// lens
const double lense_curve_index = 0.03;

// pixel mapping
const double pixel_angle_in_3space = .014;
const double pixel_squish_ratio = 2.0;

// entities
const double block_side_length = 1.0;

// camera static
// const double view_sphere_radius = 10.0;
// const double view_sphere_radius = 1.0;
const double view_sphere_radius = .1;

// camera movement
const double movement_speed = 0.3/view_sphere_radius;
const double view_movement_angle = 1.5;

// player physics (camera movement)
const double player_mass = 100.0; // kilos
const double jump_velocity = 5.0; // meters per second jumping
const double player_block_height = 1.0; // distance between camera and 'feet' 

}


#endif /* static_variables_cpp */
