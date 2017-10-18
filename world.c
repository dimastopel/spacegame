   #include <allegro5/allegro.h>

#include <math.h>

#include "world.h"
#include "utils.h"

typedef enum {
   MOVE_TYPE_STATIC,
   MOVE_TYPE_CIRCLE,
   MOVE_TYPE_VERTICAL,
   MOVE_TYPE_HORIZONTAL
} SpaceObjectMovement;

typedef struct {
   double center_x;
   double center_y;
   ALLEGRO_BITMAP* resource;
   SpaceObjectMovement move_type;
   float scale_factor;
   int move_span;
   float initial_angle;
   int is_rotating;
} SpaceObject;

static SpaceObject space_objects[2];

void draw_space_object(Context* context, SpaceObject* space_object, double time)
{
   int object_width = al_get_bitmap_width(space_object->resource);
   int object_height = al_get_bitmap_height(space_object->resource);

   if (is_in_the_box(
      space_object->center_x,
      space_object->center_y,
      context->current_x - (WIDTH / 2) - (object_width / 2) - (space_object->move_span / 2), 
      context->current_y - (HEIGHT / 2) - (object_height / 2) - (space_object->move_span / 2),
      WIDTH  + object_width + space_object->move_span,
      HEIGHT + object_height + space_object->move_span))
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
            space_object->center_x - context->current_x + (WIDTH / 2) + (int)x_skew, 
            space_object->center_y - context->current_y + (HEIGHT / 2) + (int)y_skew, 
            space_object->scale_factor, 
            space_object->scale_factor,
            space_object->initial_angle + (space_object->is_rotating ? time : 0), 
            0);
   }
}

void draw_world(Context* context)
{

   double time = al_get_time();


   draw_space_object(context, &space_objects[0], time);
   draw_space_object(context, &space_objects[1], time);
}

void load_world()
{
   SpaceObject boring_planet;
   boring_planet.center_x = 178223;
   boring_planet.center_y = 101241;
   boring_planet.resource = al_load_bitmap("res/planet3.png");
   boring_planet.move_type = MOVE_TYPE_STATIC;
   boring_planet.scale_factor = 0.3;
   boring_planet.move_span = 0;
   boring_planet.initial_angle = -M_PI_4;
   boring_planet.is_rotating = 0;
   space_objects[0] = boring_planet;



   SpaceObject spoutnik;
   spoutnik.center_x = 177223;
   spoutnik.center_y = 101541;
   spoutnik.resource = al_load_bitmap("res/spoutnik.png");
   spoutnik.move_type = MOVE_TYPE_CIRCLE;
   spoutnik.scale_factor = 0.4;
   spoutnik.move_span = 200;
   spoutnik.initial_angle = M_PI_2 + M_PI_4 + M_PI_2;
   spoutnik.is_rotating = 1;
   space_objects[1] = spoutnik;
}

