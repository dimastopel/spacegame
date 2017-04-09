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

void draw_stars_tiles(float angle, int scale, int is_moving, int width, int height, int is_debug)
{
   static int star_seed = 0x9d2c5680;
   static float star_step = 5;
   static int center_x_1 = 100000;
   static int center_y_1 = 100000;
   static int center_x_2 = 100343;
   static int center_y_2 = 100000;
   static int center_x_3 = 100000;
   static int center_y_3 = 100000;

   ALLEGRO_COLOR star_color;

   int tile_size = 512;
   int center_x;
   int center_y;

   if (scale == 1) {
      center_x = center_x_1;
      center_y = center_y_1;
      star_color = al_map_rgb(255,255,255);
   } 
   else if (scale == 2)
   {
      center_x = center_x_2;
      center_y = center_y_2;
      star_color = al_map_rgb(190,190,190);
   }
   else
   {
      center_x = center_x_3;
      center_y = center_y_3;
      star_color = al_map_rgb(120,120,120);
   }

   int tile_x = ((center_x - width / 2) / tile_size) * tile_size - tile_size;
   int tile_y = ((center_y - height / 2) / tile_size) * tile_size - tile_size;

   for (int i = tile_x; i <= width + tile_x + tile_size * 3; i += tile_size) {
       for (int j = tile_y; j <= height + tile_y + tile_size * 3; j += tile_size) {

           int lx = 0, ly = 0;
           if (is_debug)
           {
              lx = i - (center_x - width / 2);
              ly = j - (center_y - height / 2);
              al_draw_line(0, ly, width, ly, al_map_rgb(128,128,128), 1);
              al_draw_line(lx, 0, lx, height, al_map_rgb(128,128,128), 1);
           }

           uint32_t hash = mix(star_seed, i, j);

           for (int n = 0; n < 3*scale; n++) {
               //int px = (hash % tile_size) + (i - center_x);
               int hash_off_x = hash % tile_size;
               int px = width / 2 + hash_off_x + (i - center_x);
               hash >>= 2;
               //int py = (hash % tile_size) + (j - center_y);
               int hash_off_y = hash % tile_size;
               int py = height / 2 + hash_off_y + (j - center_y);
               hash >>= 2;

               if (scale == 1 && rand() % 5 == 0)
               {
                  al_draw_rectangle(px, py, px+1, py+1, star_color, 1);
               }
               else
               {
                  al_draw_rectangle(px, py, px+1, py+1, star_color, 1);
                  //al_put_pixel(px, py, star_color);
               }

               if (is_debug)
               {
                  al_draw_textf(get_font(), al_color_name("white"), lx+2, ly+5+n*10, 0, "%d %d %x %d %d", i, j, hash, hash_off_x, hash_off_y);
               }
           }
       }
   }

   if (is_moving)
   {
      center_x += star_step / (scale) * cos(angle);
      center_y -= star_step / (scale) * sin(angle);

      if (scale == 1) {
         center_x_1 = center_x;
         center_y_1 = center_y;
      } 
      else if (scale == 2)
      {
         center_x_2 = center_x;
         center_y_2 = center_y;
      }
      else
      {
         center_x_3 = center_x;
         center_y_3 = center_y;
      }
   }

}
