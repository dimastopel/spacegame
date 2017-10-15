#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <math.h>

#include "world.h"
#include "utils.h"


void draw_static_planet(Context* context)
{
   static ALLEGRO_BITMAP* planet1 = NULL;
   static int b_width = 0;
   static int b_height = 0;
   static float scale_factor = 0.3;

   static double planet1_x = 178223;
   static double planet1_y = 101241;


   if (!planet1)
   {
      planet1 = al_load_bitmap("res/planet3.png");
      b_width = al_get_bitmap_width(planet1);
      b_height = al_get_bitmap_height(planet1);
   }

   if (is_in_the_box(
      planet1_x,
      planet1_y,
      context->current_x - (WIDTH / 2) - (b_width / 2), 
      context->current_y - (HEIGHT / 2) - (b_height / 2),
      WIDTH + b_width,
      HEIGHT  + b_height))
   {
      al_draw_scaled_rotated_bitmap(planet1,
            b_width / 2, 
            b_height / 2, 
            planet1_x - context->current_x + (WIDTH / 2), 
            planet1_y - context->current_y + (HEIGHT / 2), 
            scale_factor, 
            scale_factor,
            0, 
            0);
   }

}

void draw_moving_planet(Context* context)
{
   static ALLEGRO_BITMAP* planet1 = NULL;
   static int b_width = 0;
   static int b_height = 0;
   static float scale_factor = 0.4;

   static double planet1_x = 175223;
   static double planet1_y = 101241;

   static int movement_span = 200;

   if (!planet1)
   {
      //planet1 = al_load_bitmap("res/spoutnik.png");
      planet1 = al_load_bitmap("res/spoutnik.png");
      b_width = al_get_bitmap_width(planet1);
      b_height = al_get_bitmap_height(planet1);
   }

   if (is_in_the_box(
      planet1_x,
      planet1_y,
      context->current_x - (WIDTH / 2) - (b_width / 2) - (movement_span / 2), 
      context->current_y - (HEIGHT / 2) - (b_height / 2) - (movement_span / 2),
      WIDTH + b_width + movement_span,
      HEIGHT  + b_height + movement_span))
   {
      double time = al_get_time();

      double x_skew = sin(time) * movement_span;
      double y_skew = cos(time) * movement_span;

      al_draw_scaled_rotated_bitmap(planet1,
            b_width / 2, 
            b_height / 2, 
            planet1_x - context->current_x + (WIDTH / 2) + (int)x_skew, 
            planet1_y - context->current_y + (HEIGHT / 2) + (int)y_skew, 
            scale_factor, 
            scale_factor,
            M_PI_2 + M_PI_4, 
            0);
   }
}

void draw_world(Context* context)
{
   draw_static_planet(context);
   draw_moving_planet(context);

}