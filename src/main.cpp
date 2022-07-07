
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constants/static_variables.cpp"
#include "SDL_core/simulation_manager.cpp"

#include "ecs/ControlPanel.cpp"

/* components */
#include "ecs/components/map_array_component.cpp"
#include "ecs/components/position_component.cpp"
#include "ecs/components/radar_component.cpp"
#include "ecs/components/neighbors_component.cpp"
#include "ecs/components/block_component.cpp"
#include "ecs/components/orientation_component.cpp"
#include "ecs/components/bullet_component.cpp"
#include "ecs/components/entity_type_component.cpp"
#include "ecs/components/motion_component.cpp"
#include "ecs/components/joystick_component.cpp"
#include "ecs/components/weapon_component.cpp"

/* systems */
#include "ecs/systems/PlayerMovementSystem.cpp"
#include "ecs/systems/PhysicsSystem.cpp"
#include "ecs/systems/JoystickSystem.cpp"
#include "ecs/systems/CameraOperatorSystem.cpp"
#include "ecs/systems/ObjectPositionTransformerSystem.cpp"
#include "ecs/systems/RadarSystem.cpp"
#include "ecs/systems/MapBuilderSystem.cpp"
#include "ecs/systems/BlockRenderSystem.cpp"
#include "ecs/systems/ScreenMapSystem.cpp"
#include "ecs/systems/WeaponSystem.cpp"
#include "ecs/systems/WeaponRenderSystem.cpp"
#include "ecs/systems/BulletPositionSystem.cpp"

/* factories */
#include "ecs/entity_factories/BlockFactory.cpp"

// make sure to add framerate timer to include folder
#include <simple_framerate_timer.cpp>


/*---------- screen dimensions ----------*/
const int screenx = global_const::screen_x;
const int screeny = global_const::screen_y;
/*---------------------------------------*/
ControlPanel control;
int main(int argc, const char * argv[]) {
    /*------------------------- SDL setup ----------------------------*/ 
    /* set up time and frames */
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;    
    int frameStart;
    int frameTime;
    
    /* create simulation class instance */ 
    Simulation* simulation = new Simulation;
    simulation->init("PineconeEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenx, screeny, false);
    std::cout << "SDL Simulation successfully initialized." << std::endl;

    /* set randomness seed */
    // set_srand();

    /* Ordinary Setup items */
    // TODO: move control to separate file? 
    control.Init();

    /* Register Components */
    control.RegisterComponent<pce::MapArray>();
    control.RegisterComponent<pce::Position>();
    control.RegisterComponent<pce::Radar>();
    control.RegisterComponent<pce::Orientation>();
    control.RegisterComponent<pce::Motion>();
    control.RegisterComponent<pce::Joystick>();
    control.RegisterComponent<pce::Neighbors>();
    control.RegisterComponent<pce::Weapon>();
    control.RegisterComponent<pce::EntityType>();
    control.RegisterComponent<pce::Block>();
    control.RegisterComponent<pce::Bullet>();


    /* Register Systems */
    auto camera_system = control.RegisterSystem<pce::CameraOperatorSystem>();
    Signature camera_sig;
    camera_sig.set(control.GetComponentType<pce::Orientation>());
    control.SetSystemSignature<pce::CameraOperatorSystem>(camera_sig);
    camera_system->Init();

    auto player_movement_system = control.RegisterSystem<pce::PlayerMovementSystem>();
    Signature player_mvmt_sig;
    player_mvmt_sig.set(control.GetComponentType<pce::Motion>());
    player_mvmt_sig.set(control.GetComponentType<pce::Orientation>());
    player_mvmt_sig.set(control.GetComponentType<pce::Joystick>());
    control.SetSystemSignature<pce::PlayerMovementSystem>(player_mvmt_sig);

    auto physics_system = control.RegisterSystem<pce::PhysicsSystem>();
    Signature physics_sig; physics_sig.set(control.GetComponentType<pce::Motion>());
    physics_sig.set(control.GetComponentType<pce::Orientation>());
    control.SetSystemSignature<pce::PhysicsSystem>(physics_sig);

    auto joystick_system = control.RegisterSystem<pce::JoystickSystem>();
    Signature joystick_sig;
    joystick_sig.set(control.GetComponentType<pce::Joystick>());
    control.SetSystemSignature<pce::JoystickSystem>(joystick_sig);

    auto position_transform_system = control.RegisterSystem<pce::ObjectPositionTransformerSystem>();
    Signature position_transform_sig;
    position_transform_sig.set(control.GetComponentType<pce::Position>());
    control.SetSystemSignature<pce::ObjectPositionTransformerSystem>(position_transform_sig);

    auto radar_system = control.RegisterSystem<pce::RadarSystem>();
    Signature radar_sig;
    radar_sig.set(control.GetComponentType<pce::Position>());
    radar_sig.set(control.GetComponentType<pce::Radar>());
    radar_sig.set(control.GetComponentType<pce::EntityType>());
    control.SetSystemSignature<pce::RadarSystem>(radar_sig);

    auto block_render_system = control.RegisterSystem<pce::BlockRenderSystem>();
    Signature block_render_sig;
    block_render_sig.set(control.GetComponentType<pce::Position>());
    block_render_sig.set(control.GetComponentType<pce::Radar>());
    block_render_sig.set(control.GetComponentType<pce::Block>());
    control.SetSystemSignature<pce::BlockRenderSystem>(block_render_sig);

    auto screen_map_system = control.RegisterSystem<pce::ScreenMapSystem>();
    Signature screen_map_sig;
    screen_map_sig.set(control.GetComponentType<pce::Orientation>());
    screen_map_sig.set(control.GetComponentType<pce::Weapon>());
    control.SetSystemSignature<pce::ScreenMapSystem>(screen_map_sig);

    auto weapon_system = control.RegisterSystem<pce::WeaponSystem>();
    Signature weapon_sig;
    weapon_sig.set(control.GetComponentType<pce::Joystick>());
    weapon_sig.set(control.GetComponentType<pce::Orientation>());
    control.SetSystemSignature<pce::WeaponSystem>(weapon_sig);
 
    auto weapon_render_system = control.RegisterSystem<pce::WeaponRenderSystem>();
    Signature weapon_render_sig;
    weapon_render_sig.set(control.GetComponentType<pce::Position>());
    weapon_render_sig.set(control.GetComponentType<pce::Orientation>());
    weapon_render_sig.set(control.GetComponentType<pce::Radar>());
    control.SetSystemSignature<pce::WeaponRenderSystem>(weapon_render_sig);

    auto bullet_position_system = control.RegisterSystem<pce::BulletPositionSystem>();
    Signature bullet_position_sig;
    bullet_position_sig.set(control.GetComponentType<pce::Position>());
    bullet_position_sig.set(control.GetComponentType<pce::Orientation>());
    bullet_position_sig.set(control.GetComponentType<pce::Motion>());
    control.SetSystemSignature<pce::BulletPositionSystem>(bullet_position_sig);




    auto map_builder_system = pce::MapBuilderSystem();
    map_builder_system.CreateMapArray();
    map_builder_system.AssignEntityNeighbors();
    // map_builder_system.PrintMapArray();



    Entity player = control.CreateEntity();
    // glm::dvec3 start_position = glm::dvec3(-15, 20.6, 30);
    glm::dvec3 start_position = glm::dvec3(0, 20.6, 0);
    control.AddComponent(player, pce::Motion{
        .is_airborne = true,
        .is_jumping = false,
        .speed = 1.0,
        .travel_direction = glm::dvec3(0, 0, 0),
        .initial_velocity = glm::dvec3(0, 0, 0),
        .previous_ground_position = start_position,
        .time_airborne = 0.0,
        .in_flight_mode = false
    });
    control.AddComponent(player, pce::Orientation{
        .position = start_position,
        .previous_position = start_position,
        .view_direction = glm::dvec3(0, 0, -1.0),
        .xz_view_angle = 180.0,
        .y_view_angle = 0.0
    });
    control.AddComponent(player, pce::Joystick{});
    control.AddComponent(player, pce::Weapon{});
    
    /* Create Entities */
    // auto block_factory = pce::BlockFactory();
    // block_factory.CreateBlock(glm::dvec3(0, 0, -10));

    simple_framerate_timer simple_timer = simple_framerate_timer();

    /*----------Main Loop---------------------*/
    while (simulation->running()) {
        
        /* SDL events and updating */ 
        int frameStart = SDL_GetTicks();       
        simulation->handleEvents();
        simulation->update();
        simulation->clearRenderer();
        

        double t = frameStart/1000.0;

        // update timer 
        int time = int(t);
        simple_timer.update_timer(time);


        /*~~~~~~~~~------------- Do Stuff and Update ----------------*/
        auto cam_transform_vector = camera_system->ProvideCamTransformVector(); 
        auto cam_versor = camera_system->ProvideCamVersor(); 
        auto cam_pos = camera_system->ProvideCamPosition();

        double ticks = (SDL_GetTicks()/1000.0);
        // joystick_system->UpdateEntities(ticks);
        std::thread thread_a([ticks, joystick_system, player_movement_system,
                              weapon_system, physics_system, camera_system](){
            joystick_system->UpdateEntities(ticks);
            weapon_system->UpdateEntities();
            player_movement_system->UpdateEntities(ticks);
            physics_system->UpdateEntities(ticks);
            camera_system->UpdateCamera();
        });

        /*~~~~~~~~~-------------- Detect, Draw and Render --------------------*/
        std::thread thread_b([cam_versor, cam_pos, cam_transform_vector,
                              position_transform_system, radar_system, block_render_system,
                              weapon_render_system]() {
            position_transform_system->UpdateEntities(cam_transform_vector, cam_versor, cam_pos);
            radar_system->UpdateEntities();
            block_render_system->UpdateEntities(cam_transform_vector, cam_versor);
            weapon_render_system->UpdateEntities();
        });
        thread_a.join();
        thread_b.join();

        std::thread thread_bullet([bullet_position_system]() {
            bullet_position_system->UpdateEntities();
        });
        std:thread thread_screen_map([screen_map_system]() {
            screen_map_system->UpdateEntities();
        });

        thread_bullet.join();
        thread_screen_map.join();

        /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
        simulation->render();
        /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
        /* Clear events list */
        simulation->clear_frame_events();

        /* check how much time has passed during frame */
        frameTime = SDL_GetTicks() - frameStart;

        /* if frame too fast, delay the frame */ if ( frameDelay > frameTime )
        {
            SDL_Delay( frameDelay - frameTime );
        }
    }

    simulation->clean();

    delete simulation;
    
    return 0;
}

