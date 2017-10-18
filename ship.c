#include <allegro5/allegro.h>
//#include <allegro5/allegro_memfile.h>

#include "ship.h"

// Example embedding resource within the executable and getting pointer to it.
// ld -r -b binary -o shipimage.o ship.png
//extern unsigned char _binary_ship_png_start[];
//extern unsigned char _binary_ship_png_end[];

void draw_ship(Context* context)
{
   static ALLEGRO_BITMAP* ship = NULL;

   static ALLEGRO_BITMAP* ship_fire = NULL;
   static ALLEGRO_BITMAP* ship_nofire = NULL;

   static int b_width = 0;
   static int b_height = 0;
   static float scale_factor = 0.4;

   if (!ship)
   {
         ship_fire = al_load_bitmap("res/ship_fire.png");
         ship_nofire = al_load_bitmap("res/ship_nofire.png");
         ship = ship_nofire;

         // Example of loading a resource embedded within the executable. Need mem_file include above. 
         //size_t image_len = _binary_ship_png_end - _binary_ship_png_start;
         //ALLEGRO_FILE* ship_image_fp = al_open_memfile(_binary_ship_png_start, image_len, "r");
         //ship = al_load_bitmap_f(ship_image_fp, ".png");

		   b_width = al_get_bitmap_width(ship_fire);
   	   b_height = al_get_bitmap_height(ship_fire);
   }

   ship = context->is_accelerating ? ship_fire : ship_nofire;

   al_draw_scaled_rotated_bitmap(ship,
   		b_width / 2, b_height / 2, 
   		WIDTH / 2, HEIGHT / 2, 
   		scale_factor, scale_factor,
         (context->angle * -1) - M_PI_4, 0);
}