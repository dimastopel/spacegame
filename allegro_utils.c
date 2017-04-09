#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_utils.h"

void init_allegro()
{
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      exit(1);
   }

   al_init_primitives_addon();
   al_install_keyboard();
   al_init_image_addon();
   al_install_audio();
   al_init_acodec_addon();
   al_init_font_addon();
   al_init_ttf_addon();
}

ALLEGRO_DISPLAY* create_display(int width, int height)
{
   ALLEGRO_DISPLAY *display = NULL;
   display = al_create_display(width, height);

   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      exit(1);
   }

   return display;
}

ALLEGRO_EVENT_QUEUE* create_event_queue()
{
   ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   return event_queue;
}

ALLEGRO_FONT* get_font()
{
   static  ALLEGRO_FONT *font = NULL;

   if (!font)
   {
      font = al_load_ttf_font("neuropol_font.ttf", 10, 0);
   }
   return font;
}

void shut_down_allegro(ALLEGRO_DISPLAY* display) 
{
   al_destroy_display(display);
   al_shutdown_primitives_addon();
}


void process_key_events(ALLEGRO_EVENT_QUEUE* event_queue, Context* context)
{
   static ALLEGRO_EVENT ev;
   static ALLEGRO_TIMEOUT timeout;

   static int current_left = 0;
   static int current_right = 0;
   static int current_up = 0;
   static int current_down = 0;

   al_init_timeout(&timeout, 0.001);
   al_wait_for_event_until(event_queue, &ev, &timeout);

   if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
   {  
      exit(0);
   }

   if (current_left)
   {
      do_left(context, 0);
   }

   if (current_right)
   {         
      do_right(context, 0);
   }

   if (current_up)
   {
      do_up(context, 0);
   }

   if (current_down)
   {
      do_down(context, 0);
   }

   if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch(ev.keyboard.keycode) {
         case ALLEGRO_KEY_LEFT: 
            current_left = 1;
            break;
         case ALLEGRO_KEY_RIGHT:
            current_right = 1;
            break;
         case ALLEGRO_KEY_UP:
            current_up = 1;
            break;
         case ALLEGRO_KEY_DOWN:
            current_down = 1;
            break;
      }
   }

   if(ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch(ev.keyboard.keycode) {
         case ALLEGRO_KEY_LEFT: 
            if (current_left)
            {
               do_left(context, 1);
            }
            current_left = 0;
            break;
         case ALLEGRO_KEY_RIGHT:
            if (current_right)
            {
               do_right(context, 1);
            }
            current_right = 0;
            break;
         case ALLEGRO_KEY_UP:
            if (current_up)
            {
               do_up(context, 1);
            }
            current_up = 0;
            break;
         case ALLEGRO_KEY_DOWN:
            if (current_down)
            {
               do_down(context, 1);
            }
            current_down = 0;
            break;
      }
   }
}



