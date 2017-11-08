#include <allegro5/allegro.h>

#include <math.h>

#include "world.h"
#include "utils.h"

SpaceObject space_objects[100] = {0};

char* static_planets[] = {
   //"res/planet3.png",
   "res/double-ringed-orb.png",
   "res/jupiter.png",
   "res/sun.png",
   "res/orbit.png",
   "res/planet-core.png",
   "res/world.png"};

void draw_space_object(Context* context, SpaceObject* space_object, double time)
{
   int object_width = al_get_bitmap_width(space_object->resource);
   int object_height = al_get_bitmap_height(space_object->resource);

   if (is_in_the_box(
      space_object->center_x,
      space_object->center_y,
      context->current_x - (screen_width / 2) - (object_width / 2) - (space_object->move_span / 2), 
      context->current_y - (screen_height / 2) - (object_height / 2) - (space_object->move_span / 2),
      screen_width  + object_width + space_object->move_span,
      screen_height + object_height + space_object->move_span))
   {
      double x_skew = 0;
      double y_skew = 0;

      switch(space_object->move_type){
         case MOVE_TYPE_STATIC: 
            break;         
         case MOVE_TYPE_CIRCLE: 
            x_skew = cos(time) * space_object->move_span;
            y_skew = sin(time) * space_object->move_span;
            break;
         case MOVE_TYPE_HORIZONTAL: 
            x_skew = cos(time) * space_object->move_span;
            break;
         case MOVE_TYPE_VERTICAL: 
            y_skew = sin(time) * space_object->move_span;
            break;
         default: 
            return;
      }

      al_draw_scaled_rotated_bitmap(
            space_object->resource,
            object_width / 2, 
            object_height / 2, 
            space_object->center_x - context->current_x + (screen_width / 2) + (int)x_skew, 
            space_object->center_y - context->current_y + (screen_height / 2) + (int)y_skew, 
            space_object->scale_factor, 
            space_object->scale_factor,
            space_object->initial_angle + (space_object->is_rotating ? time : 0), 
            0);
   }
}

void draw_world(Context* context)
{

   double time = al_get_time();

   for (int i = 0; i < sizeof(space_objects) / sizeof(SpaceObject); i++)
   {
      if (space_objects[i].resource == NULL)
      {
         break;
      }

      draw_space_object(context, &space_objects[i], time);
   }
}

void load_world()
{

   SpaceObject boring_planet;
   boring_planet.center_x = 178223;
   boring_planet.center_y = 101241;
   boring_planet.mass = 150000000;
   boring_planet.resource = al_load_bitmap("res/planet3.png");
   boring_planet.move_type = MOVE_TYPE_STATIC;
   boring_planet.scale_factor = 0.3;
   boring_planet.move_span = 0;
   boring_planet.initial_angle = -M_PI_4;
   boring_planet.is_rotating = 0;
   space_objects[0] = boring_planet;

   SpaceObject boring_planet_2;
   boring_planet_2.center_x = 177223;
   boring_planet_2.center_y = 101241;
   boring_planet_2.mass = 150000000;
   boring_planet_2.resource = al_load_bitmap("res/planet3.png");
   boring_planet_2.move_type = MOVE_TYPE_STATIC;
   boring_planet_2.scale_factor = 0.3;
   boring_planet_2.move_span = 0;
   boring_planet_2.initial_angle = -M_PI_4;
   boring_planet_2.is_rotating = 0;
   space_objects[1] = boring_planet_2;

   SpaceObject spoutnik;
   spoutnik.center_x = 177223;
   spoutnik.center_y = 101441;
   spoutnik.mass = 100000;
   spoutnik.resource = al_load_bitmap("res/spoutnik.png");
   spoutnik.move_type = MOVE_TYPE_CIRCLE;
   spoutnik.scale_factor = 0.4;
   spoutnik.move_span = 200;
   spoutnik.initial_angle = M_PI_2 + M_PI_4 + M_PI_2;
   spoutnik.is_rotating = 1;
   space_objects[2] = spoutnik;

   SpaceObject weird_ship;
   weird_ship.center_x = 178203;
   weird_ship.center_y = 100421;
   weird_ship.mass = 100000;
   weird_ship.resource = al_load_bitmap("res/ship.png");
   weird_ship.move_type = MOVE_TYPE_HORIZONTAL;
   weird_ship.scale_factor = 0.1;
   weird_ship.move_span = 500;
   weird_ship.initial_angle = 0;
   weird_ship.is_rotating = 0;
   space_objects[3] = weird_ship;

   SpaceObject weird_planet;
   weird_planet.center_x = 179203;
   weird_planet.center_y = 101321;
   weird_planet.mass = 15000000;
   weird_planet.resource = al_load_bitmap("res/planet3.png");
   weird_planet.move_type = MOVE_TYPE_VERTICAL;
   weird_planet.scale_factor = 0.2;
   weird_planet.move_span = 400;
   weird_planet.initial_angle = 0;
   weird_planet.is_rotating = 1;
   space_objects[4] = weird_planet;

   int num_of_random_planets = 3;
   for (int i = 0; i < num_of_random_planets; i++)
   {
      size_t res_size = sizeof(static_planets) / sizeof(char*);
      char* res = static_planets[rand() % res_size];
      int spread = 5000;
      
      SpaceObject planet;
      planet.center_x = 178223 + (rand() % spread) - (spread / 2);
      planet.center_y = 101241 + (rand() % spread) - (spread / 2);;
      planet.mass = 150000000 + (rand() % 50000000 - 25000000);
      planet.resource = al_load_bitmap(res);
      planet.move_type = MOVE_TYPE_STATIC;
      planet.scale_factor = 0.3;
      planet.move_span = 0;
      planet.initial_angle = 0;
      planet.is_rotating = 0;
      space_objects[5+i] = planet;
   }
}

