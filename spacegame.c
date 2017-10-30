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
   static const int planet_x = 178223;
   static const int planet_y = 101241;
   static const int planet_mass = 100000000;

   static const int ship_mass = 10;
   static const int ship_rear_engine = 1000;
   static const int ship_front_engine = 50;

   // gravity force vector
   double distance_to_planet_squared =
      fabs(context->current_x - planet_x)*fabs(context->current_x - planet_x) + 
      fabs(context->current_y - planet_y)*fabs(context->current_y - planet_y);

   double vec_grav_mag = planet_mass * ship_mass / distance_to_planet_squared;
   double vec_grav_angle = -1 * atan2(planet_y - context->current_y, planet_x - context->current_x);
   
   // engine force vector
   double vec_engine_mag = context->rear_engine_on ? ship_rear_engine : 0;  
   double vec_engine_angle = context->front_engine_on ? (context->angle + M_PI) : context->angle;  
   if (vec_engine_angle > 2*M_PI)
   {
      vec_engine_angle -= 2*M_PI;
   }

   if (context->front_engine_on) 
   {
      vec_engine_mag -= ship_front_engine;
      vec_engine_mag = fabs(vec_engine_mag);
   }

   // combine all forces
   double temp_alpha = vec_grav_angle-vec_engine_angle; 
   while (temp_alpha > M_PI)
   {
      temp_alpha -= 2*M_PI;
   }

   while (temp_alpha < (-1*M_PI))
   {
      temp_alpha += 2*M_PI;
   }

   double final_vec_mag = sqrt(vec_grav_mag*vec_grav_mag + vec_engine_mag*vec_engine_mag + 2*vec_grav_mag*vec_engine_mag*cos(temp_alpha)); 
   double final_vec_ang = vec_engine_angle + atan2(vec_grav_mag*sin(temp_alpha), vec_engine_mag + vec_grav_mag*cos(temp_alpha));

   /*
   double final_vec_mag = vec_engine_mag;
   double final_vec_ang = vec_engine_angle;
   */

   //calculate acceleration and velocity
   double acceleration = final_vec_mag / ship_mass;
   double acceleration_x = acceleration*cos(final_vec_ang);
   double acceleration_y = -1*acceleration*sin(final_vec_ang);

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