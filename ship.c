#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "ship.h"

void draw_ship(Context* context)
{
   static ALLEGRO_BITMAP* ship = NULL;
   static int b_width = 0;
   static int b_height = 0;
   static float scale_factor = 0.1;

   if (!ship)
   {
   		ship = al_load_bitmap("ship.png");
		b_width = al_get_bitmap_width(ship);
   	    b_height = al_get_bitmap_height(ship);
   }

   al_draw_scaled_rotated_bitmap(ship,
   		b_width / 2, b_height / 2, 
   		WIDTH / 2, HEIGHT / 2, 
   		scale_factor, scale_factor,
   		context->angle * -1 + M_PI_2, 0);

   /*
   */
   /*
   static int ship_lenght = 30;
   ALLEGRO_COLOR ship_color = al_color_name("lightcyan");
   al_draw_line(
      WIDTH / 2 + cos(angle)*ship_lenght/2, 
      HEIGHT / 2 - sin(angle)*ship_lenght/2, 
      WIDTH / 2 - cos(angle)*ship_lenght/2, 
      HEIGHT / 2 + sin(angle)*ship_lenght/2, 
      ship_color, 5);

   al_draw_filled_circle(
      WIDTH / 2 + cos(angle)*ship_lenght/2, 
      HEIGHT / 2 - sin(angle)*ship_lenght/2, 
      5, 
      ship_color);
	*/
      
}