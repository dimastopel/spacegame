#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <allegro5/allegro_memfile.h>

#include "ship.h"

// ld -r -b binary -o shipimage.o ship.png
extern unsigned char _binary_ship_png_start[];
extern unsigned char _binary_ship_png_end[];

void draw_ship(Context* context)
{
   static ALLEGRO_BITMAP* ship = NULL;

   static ALLEGRO_BITMAP* ship_fire = NULL;
   static ALLEGRO_BITMAP* ship_nofire = NULL;

   static int b_width = 0;
   static int b_height = 0;
   static float scale_factor = 0.6;

   if (!ship)
   {
         ship_fire = al_load_bitmap("res/ship_fire.png");
         ship_nofire = al_load_bitmap("res/ship_nofire.png");
         ship = ship_nofire;

         //size_t image_len = _binary_ship_png_end - _binary_ship_png_start;
         //ALLEGRO_FILE* ship_image_fp = al_open_memfile(_binary_ship_png_start, image_len, "r");
         //ship = al_load_bitmap_f(ship_image_fp, ".png");

		   b_width = al_get_bitmap_width(ship_fire);
   	   b_height = al_get_bitmap_height(ship_fire);
   }

   ship = context->is_moving ? ship_fire : ship_nofire;

   al_draw_scaled_rotated_bitmap(ship,
   		b_width / 2, b_height / 2, 
   		WIDTH / 2, HEIGHT / 2, 
   		scale_factor, scale_factor,
   		//context->angle * -1 + M_PI_2, 0);
         (context->angle * -1) - M_PI_4, 0);

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