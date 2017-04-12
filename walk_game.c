#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_utils.h"
#include "utils.h"
#include "stars.h"
#include "hud.h"
#include "ship.h"
#include "game.h"

#define M_PI_DOUBLE 6.283185307

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

   ALLEGRO_DISPLAY *display = create_display(WIDTH, HEIGHT);
   ALLEGRO_EVENT_QUEUE* event_queue = create_event_queue();

   al_reserve_samples(1);
   ALLEGRO_SAMPLE* sample = al_load_sample("TheForestAwakes.ogg");
   //al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   Context context = {40,40,0,0};

   while (true)
   {

      process_key_events(event_queue, &context);

      al_clear_to_color(al_color_name("black"));

      draw_stars_tiles(&context, 3, 0);
      draw_stars_tiles(&context, 2, 0);
      draw_stars_tiles(&context, 1, 0);

      draw_ship(&context);
      draw_hud(&context);

      al_flip_display();
   }

   al_destroy_sample(sample);

   shut_down(display);

   return 0;
}

void do_left(Context* context, int key_up)
{
   context->angle += ANGULAR_VELOCITY;
}

void do_right(Context* context, int key_up)
{
   context->angle -= ANGULAR_VELOCITY;
}

void do_up(Context* context, int key_up)
{
   context->is_moving = !key_up;
}

void do_down(Context* context, int key_up)
{
}