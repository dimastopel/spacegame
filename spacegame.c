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

void do_up(Context* context, int key_up)
{
   static SpeedState speed_state = SPEED_STATIC;
   static SpeedState current_speed_state = SPEED_STATIC;
   static double speed_v0 = 0;
   static double start_time = 0;
   static const double acceleration = 3.5;
   
   if (context->speed == 0 && key_up)
   {
      return;
   }

   if (key_up && context->speed < 0.001)
   {
      context->speed = 0;
      speed_state = SPEED_STATIC; 
      return;
   }


   if (key_up) 
   {
      speed_state = SPEED_DECREASING;
      context->is_accelerating = 0;
   }
   else
   {
      speed_state = SPEED_INCREASING;
      context->is_accelerating = 1;
   }

   if (current_speed_state != speed_state)
   {
      start_time = al_get_time();
      current_speed_state = speed_state;
      speed_v0 = context->speed;
   }

   double time_delta = al_get_time() - start_time;
   double actual_acceleration = speed_state == SPEED_INCREASING ? acceleration : (-1 * acceleration);
   
   context->speed = speed_v0 + actual_acceleration*time_delta;


   if (context->speed > MAX_SHIP_SPEED)
   {
      context->speed = MAX_SHIP_SPEED;
   }

   //DEBUG
   //printf("%f %d %d %f %f\n", context->speed, speed_state, current_speed_state, actual_acceleration, speed_v0);

   context->current_x += context->speed * cos(context->angle);
   context->current_y -= context->speed * sin(context->angle);
}

void do_down(Context* context, int key_up)
{
}