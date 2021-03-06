#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "allegro_utils.h"
#include "utils.h" 
#include "game.h"
#include "stars.h"

#include <math.h>

#define SCALE_FACTOR 0.5
#define TILE_SIZE 512

void draw_stars_tiles_with_scale(Context* context, int scale, int is_debug)
{
   static double center_x_1 = 157223;
   static double center_y_1 = 112241;

   static double center_x_2 = 100343;
   static double center_y_2 = 102311;

   static double center_x_3 = 107223;
   static double center_y_3 = 109833;

   ALLEGRO_COLOR star_color;

   int tile_size = TILE_SIZE;
   double real_x;
   double real_y;
   int center_x;
   int center_y;

   if (scale == 1) {
      real_x = center_x_1;
      real_y = center_y_1;
      star_color = al_map_rgb(255,255,255);
   } 
   else if (scale == 2)
   {
      real_x = center_x_2;
      real_y = center_y_2;
      star_color = al_map_rgb(190,190,190);
   }
   else
   {
      real_x = center_x_3;
      real_y = center_y_3;
      star_color = al_map_rgb(120,120,120);
   }

   center_x = to_int(real_x);
   center_y = to_int(real_y);

   int tile_x = ((center_x - screen_width / 2) / tile_size) * tile_size - tile_size;
   int tile_y = ((center_y - screen_height / 2) / tile_size) * tile_size - tile_size;

   for (int i = tile_x; i <= screen_width + tile_x + tile_size * 3; i += tile_size) {
       for (int j = tile_y; j <= screen_height + tile_y + tile_size * 3; j += tile_size) {

           int lx = 0, ly = 0;
           if (is_debug)
           {
              lx = i - (center_x - screen_width / 2);
              ly = j - (center_y - screen_height / 2);
              al_draw_line(0, ly, screen_width, ly, al_map_rgb(128,128,128), 1);
              al_draw_line(lx, 0, lx, screen_height, al_map_rgb(128,128,128), 1);
           }

           uint64_t hash = mix64(i, j);
           for (int n = 0; n < 4*scale; n++) {
               int hash_off_x = hash % tile_size;
               int px = screen_width / 2 + hash_off_x + (i - center_x);
               hash >>= 3;

               int hash_off_y = hash % tile_size;
               int py = screen_height / 2 + hash_off_y + (j - center_y);
               hash >>= 3;

               al_draw_rectangle(px, py, px+1, py+1, star_color, 1);

               if (is_debug)
               {
                  al_draw_textf(get_font(), al_color_name("white"), lx+2, ly+5+n*10, 0, "%d %d %lx %d %d", i, j, hash, hash_off_x, hash_off_y);
               }
           }
       }
   }

    real_x = context->current_x / (scale + SCALE_FACTOR);
    real_y = context->current_y / (scale + SCALE_FACTOR);

    if (scale == 1) {
       center_x_1 = real_x;
       center_y_1 = real_y;
    } 
    else if (scale == 2)
    {
       center_x_2 = real_x;
       center_y_2 = real_y;
    }
    else
    {
       center_x_3 = real_x;
       center_y_3 = real_y;
    }
}

void draw_stars_tiles(Context* context, int is_debug)
{
  draw_stars_tiles_with_scale(context, 3, is_debug);
  draw_stars_tiles_with_scale(context, 2, is_debug);
  draw_stars_tiles_with_scale(context, 1, is_debug);
}

