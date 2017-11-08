#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

#include "allegro_utils.h"
#include "utils.h"
#include "stars.h"
#include "hud.h"
#include "ship.h"
#include "world.h"
#include "game.h"

#define M_PI_DOUBLE 6.283185307 

typedef enum {
   SPEED_INCREASING,
   SPEED_DECREASING,
   SPEED_STATIC
} SpeedState;

void init() 
{
   init_allegro();
   srand(time(NULL));
}

void shut_down(ALLEGRO_DISPLAY* display) 
{
   shut_down_allegro(display);
}

int main(int argc, char **argv){

   init();   

   ALLEGRO_DISPLAY *display = create_display();

   ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   //Backgroud music example
   //al_reserve_samples(1);
   //ALLEGRO_SAMPLE* sample = al_load_sample("res/TheForestAwakes.ogg");
   //al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
   load_world();
   Context context = {177223,102241,0,0,0};

   while (true)
   {

      process_events(event_queue, &context);

      al_clear_to_color(al_color_name("black"));

      draw_stars_tiles(&context, 0);
      draw_ship(&context);
      draw_world(&context);
      draw_hud(&context);

      al_flip_display();
   }

   //al_destroy_sample(sample);

   shut_down(display);

   return 0;
}

void do_left(Context* context, int key_up)
{
   if (key_up)
   {
      return;
   }

   context->angle += ANGULAR_VELOCITY;
   if (context->angle > 2*M_PI)
   {
   		context->angle -= 2*M_PI;
   }
}

void do_right(Context* context, int key_up)
{
   if (key_up)
   {
      return;
   }

   context->angle -= ANGULAR_VELOCITY;
   if (context->angle < 0)
   {
   		context->angle += 2*M_PI;
   }
}

void do_move(Context* context)
{
   static const int ship_mass = 10;
   static const int ship_rear_engine = 3000;
   static const int ship_front_engine = 1000;

   // gravity force vector
   Vector force_gravity = {0};
   for (int i = 0; i < sizeof(space_objects)/sizeof(SpaceObject); i++)
   {
      double distance_to_planet_squared =
         pow(context->current_x - space_objects[i].center_x, 2) + 
         pow(context->current_y - space_objects[i].center_y, 2);

      double force_mag = space_objects[i].mass * ship_mass / distance_to_planet_squared;

      double distance_to_planet = sqrt(distance_to_planet_squared);
      force_gravity.x += force_mag*(space_objects[i].center_x - context->current_x)/distance_to_planet;
      force_gravity.y += force_mag*(space_objects[i].center_y - context->current_y)/distance_to_planet;
   }

   // engine force vector
   Vector force_engine = {0};
   if (context->rear_engine_on)
   {
      force_engine.x = ship_rear_engine * cos(context->angle);
      force_engine.y = -1 * ship_rear_engine * sin(context->angle);
   }
   if (context->front_engine_on)
   {
      force_engine.x -= ship_front_engine * cos(context->angle);
      force_engine.y -= -1 * ship_front_engine * sin(context->angle);
   }

   // final vector
   Vector force_combined;
   force_combined.x = force_gravity.x + force_engine.x;
   force_combined.y = force_gravity.y + force_engine.y;

   //calculate acceleration and velocity
   double acceleration_x = force_combined.x / ship_mass;
   double acceleration_y = force_combined.y / ship_mass;

   context->speed_x += acceleration_x * (1.0/FPS);
   context->speed_y += acceleration_y * (1.0/FPS);

   context->current_x += context->speed_x * (1.0/FPS); 
   context->current_y += context->speed_y * (1.0/FPS); 

   //DEBUG
   //printf("%f %d %d %f %f\n", context->speed, speed_state, current_speed_state, actual_acceleration, speed_v0);
   //printf("%.3f %.3f %.3f %.3f %.3f %.3f\n", final_vec_mag, final_vec_ang, vec_engine_mag, vec_engine_angle, vec_grav_mag, vec_grav_angle);
}

void do_up(Context* context, int key_up)
{
   context->rear_engine_on = !key_up;
}

void do_down(Context* context, int key_up)
{
   context->front_engine_on = !key_up;
}