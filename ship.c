#include <allegro5/allegro.h>
//#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>

#include "ship.h"
#include "allegro_utils.h"

// Example embedding resource within the executable and getting pointer to it.
// ld -r -b binary -o shipimage.o ship.png
//extern unsigned char _binary_ship_png_start[];
//extern unsigned char _binary_ship_png_end[];

#define MAX_FIRED_LASERS 200
#define FIRED_LASER_SPEED 3000//1300
#define FIRED_LASER_LIFE_TIME 5

#define SHIP_SCREEN_POSITION_HOR 0.5
#define SHIP_SCREEN_POSITION_VER 0.9

typedef struct {
   int alive;
   double fired_x;
   double fired_y;
   float fired_angle;
   double fired_time;
   double speed_x;
   double speed_y;
} FiredLaser;

static FiredLaser fired_lasers[MAX_FIRED_LASERS] = {0};
static int ship_length = 0;

void draw_fired_lasers(Context* context)
{
   double current_time = al_get_time();
   for (int i = 0; i < sizeof(fired_lasers)/sizeof(FiredLaser); i++)
   {
      if (fired_lasers[i].alive && ((current_time - fired_lasers[i].fired_time) <= FIRED_LASER_LIFE_TIME))
      {
         double time_delta = current_time - fired_lasers[i].fired_time;
         double laser_x = fired_lasers[i].fired_x + time_delta*fired_lasers[i].speed_x;
         double laser_y = fired_lasers[i].fired_y + time_delta*fired_lasers[i].speed_y;
         int sx = (screen_width * SHIP_SCREEN_POSITION_HOR) - (int)(context->current_x - laser_x);
         int sy = (screen_height * SHIP_SCREEN_POSITION_VER - (ship_length / 2)) - (int)(context->current_y - laser_y);


         if (sx > 0 && sx < screen_width && sy > 0 && sy < screen_height)
         {
            al_draw_rectangle(sx-5, sy-5, sx+5, sy+5, al_color_name("red"), 4);
         }
      }
      else
      {
         fired_lasers[i].alive = 0;
      }
   }
}

void draw_ship_vehicle(Context* context)
{
   static ALLEGRO_BITMAP* ship = NULL;

   static ALLEGRO_BITMAP* ship_fire = NULL;
   static ALLEGRO_BITMAP* ship_front_fire = NULL;
   static ALLEGRO_BITMAP* ship_nofire = NULL;

   static int b_width = 0;
   static int b_height = 0;
   static float scale_factor = 0.4;

   if (!ship)
   {
         ship_fire = al_load_bitmap("res/ship_fire.png");
         ship_front_fire = al_load_bitmap("res/ship_front_fire.png");
         ship_nofire = al_load_bitmap("res/ship_nofire.png");
         ship = ship_nofire;

         // Example of loading a resource embedded within the executable. Need mem_file include above. 
         //size_t image_len = _binary_ship_png_end - _binary_ship_png_start;
         //ALLEGRO_FILE* ship_image_fp = al_open_memfile(_binary_ship_png_start, image_len, "r");
         //ship = al_load_bitmap_f(ship_image_fp, ".png");

		   b_width = al_get_bitmap_width(ship_fire);
   	   b_height = al_get_bitmap_height(ship_fire);
         ship_length =b_height; 
   }

   
   if (is_engine_on(context, REAR_ENGINE))
   {
      ship = ship_fire;
   }
   else
   {
      ship = is_engine_on(context, FRONT_ENGINE) ? ship_front_fire : ship_nofire;
   }

   al_draw_scaled_rotated_bitmap(ship,
   		b_width / 2, b_height / 2, 
   		screen_width * SHIP_SCREEN_POSITION_HOR, 
         screen_height * SHIP_SCREEN_POSITION_VER, 
   		scale_factor, scale_factor,
         (context->angle * -1) - M_PI_4, 0);
}

void draw_ship(Context* context)
{
   draw_fired_lasers(context);
   draw_ship_vehicle(context);
}

void do_fire(Context* context, int key_up)
{
   static int fired = 0;

   if (key_up)
   {
      fired = 0; 
      return;
   }

   if (fired == 1)
   {
      return;
   }

   fired = 1;
   for (int i = 0; i < sizeof(fired_lasers)/sizeof(FiredLaser); i++)
   {
      double current_time = al_get_time();
      if (fired_lasers[i].alive && (current_time - fired_lasers[i].fired_time) > FIRED_LASER_LIFE_TIME)
      {
         fired_lasers[i].alive = 0;
      }

      if (!fired_lasers[i].alive)
      {
         fired_lasers[i].alive = 1;
         fired_lasers[i].fired_x = context->current_x;
         fired_lasers[i].fired_y = context->current_y;
         fired_lasers[i].fired_angle = context->angle;
         fired_lasers[i].fired_time = current_time;
         fired_lasers[i].speed_x = context->speed_x + FIRED_LASER_SPEED*cos(context->angle);
         fired_lasers[i].speed_y = context->speed_y - FIRED_LASER_SPEED*sin(context->angle);
         break;
      }
   }
}


void engine_on(Context* context, unsigned char engine, unsigned int on)
{
   if (on)
   {
      context->engine_on |= engine; 
   }
   else
   {
      context->engine_on &= ~engine; 
   }

}

unsigned int is_engine_on(Context* context, unsigned char engine)
{
   return context->engine_on & engine;
}

