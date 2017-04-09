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

#define WIDTH  1000
#define HEIGHT 1000
#define M_PI_DOUBLE 6.283185307

void init() 
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


   srand(time(NULL));

}

ALLEGRO_DISPLAY* createDisplay()
{
   ALLEGRO_DISPLAY *display = NULL;
   display = al_create_display(WIDTH, HEIGHT);

   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      exit(1);
   }

   return display;
}

ALLEGRO_EVENT_QUEUE* createEventQueue()
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

void shutDown(ALLEGRO_DISPLAY* display) 
{
   al_destroy_display(display);
   al_shutdown_primitives_addon();
}


struct star
{
   int pos_x;
   int pos_y;
   int shown;
};



int is_in_the_box(int x, int y, int bx, int by, int bw, int bh)
{
   return 
      x >= bx && x < bx + bw && y >= by && y < by + bh;  
}

void draw_stars(float angle, int move)
{
   static int init_state = 1;
   static float star_step = 5;
   static int margin_size = 200;
   static struct star stars_layer_1[512] = {0};
   //static struct star stars_layer2[256];
   //static struct star stars_layer3[256];

   angle = angle + M_PI;
   if (angle > M_PI_DOUBLE)
   {
      angle -= M_PI_DOUBLE;
   }

   int num_of_stars = sizeof(stars_layer_1)/sizeof(stars_layer_1[0]);
   for (int i = 0; i < num_of_stars; i++)
   {
      int in_bounding_box = is_in_the_box(
            stars_layer_1[i].pos_x,
            stars_layer_1[i].pos_y,
            -margin_size, -margin_size, WIDTH + margin_size, HEIGHT + margin_size);

      if (stars_layer_1[i].shown && !in_bounding_box)
      {
         stars_layer_1[i].shown = 0;
      }

      if (!stars_layer_1[i].shown && init_state)
      {
         stars_layer_1[i].shown = rand() % 2 == 0 ? 1 : 0;
         stars_layer_1[i].pos_x = rand() % WIDTH;
         stars_layer_1[i].pos_y = rand() % HEIGHT;
      }

      if (!stars_layer_1[i].shown && !in_bounding_box)
      {
         while (!stars_layer_1[i].shown)
         {
            stars_layer_1[i].shown = 1;//rand() % 2 == 0 ? 1 : 0;
            stars_layer_1[i].pos_x = (rand() % (WIDTH  + 2 * margin_size)) - margin_size;
            stars_layer_1[i].pos_y = (rand() % (HEIGHT + 2 * margin_size)) - margin_size;
            if (is_in_the_box(
               stars_layer_1[i].pos_x,
               stars_layer_1[i].pos_y,
               0, 0, WIDTH, HEIGHT))
            {
               stars_layer_1[i].shown = 0;//rand() % 2 == 0 ? 1 : 0;
            }
         }
      }

      if (stars_layer_1[i].shown)
      {
         if (move)
         {
            stars_layer_1[i].pos_x += star_step*cos(angle);
            stars_layer_1[i].pos_y -= star_step*sin(angle);
         }
         al_put_pixel(stars_layer_1[i].pos_x, stars_layer_1[i].pos_y, al_map_rgb(255,255,255));
      }
   }
   
   init_state = 0;
}


/** Robert Jenkins' 96 bit Mix Function. */
uint32_t mix(uint32_t a, uint32_t b, uint32_t c) {
    a -= b; a -= c; a ^= (c>>13);
    b -= c; b -= a; b ^= (a<<8);
    c -= a; c -= b; c ^= (b>>13);
    a -= b; a -= c; a ^= (c>>12);
    b -= c; b -= a; b ^= (a<<16);
    c -= a; c -= b; c ^= (b>>5);
    a -= b; a -= c; a ^= (c>>3);
    b -= c; b -= a; b ^= (a<<10);
    c -= a; c -= b; c ^= (b>>15);
    return c;
}

/*


public void drawStars(Graphics2D g, int xoff, int yoff, int starscale) {
    int size = STAR_TILE_SIZE / starscale;
    int w = getWidth();
    int h = getHeight();

    int sx = ((xoff - w/2) / size) * size - size;
    int sy = ((yoff - h/2) / size) * size - size;

    for (int i = sx; i <= w + sx + size * 3; i += size) {
        for (int j = sy; j <= h + sy + size * 3; j += size) {
            int hash = mix(STAR_SEED, i, j);
            for (int n = 0; n < 3; n++) {
                int px = (hash % size) + (i - xoff);
                hash >>= 3;
                int py = (hash % size) + (j - yoff);
                hash >>= 3;
                g.drawLine(px, py, px, py);
            }
        }
    }
}
*/

void draw_stars_tiles(float angle, int scale, int is_moving, int is_debug)
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

   int tile_x = ((center_x - WIDTH / 2) / tile_size) * tile_size - tile_size;
   int tile_y = ((center_y - HEIGHT / 2) / tile_size) * tile_size - tile_size;

   for (int i = tile_x; i <= WIDTH + tile_x + tile_size * 3; i += tile_size) {
       for (int j = tile_y; j <= HEIGHT + tile_y + tile_size * 3; j += tile_size) {

           int lx = 0, ly = 0;
           if (is_debug)
           {
              lx = i - (center_x - WIDTH / 2);
              ly = j - (center_y - HEIGHT / 2);
              al_draw_line(lx, 0, lx, HEIGHT, al_map_rgb(128,128,128), 1);
              al_draw_line(0, ly, WIDTH, ly, al_map_rgb(128,128,128), 1);
           }

           uint32_t hash = mix(star_seed, i, j);

           for (int n = 0; n < 3*scale; n++) {
               //int px = (hash % tile_size) + (i - center_x);
               int hash_off_x = hash % tile_size;
               int px = WIDTH / 2 + hash_off_x + (i - center_x);
               hash >>= 2;
               //int py = (hash % tile_size) + (j - center_y);
               int hash_off_y = hash % tile_size;
               int py = HEIGHT / 2 + hash_off_y + (j - center_y);
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

void draw_ship(float angle)
{
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
}


int main(int argc, char **argv){

   init();   

   ALLEGRO_DISPLAY *display = createDisplay();
   ALLEGRO_EVENT_QUEUE* event_queue = createEventQueue();

   ALLEGRO_EVENT ev;
   ALLEGRO_TIMEOUT timeout;


   al_reserve_samples(1);
   ALLEGRO_SAMPLE* sample = al_load_sample("TheForestAwakes.ogg");
   //al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);




   ALLEGRO_BITMAP *map = al_load_bitmap("map.png");
   if (map == NULL)
   {
      fprintf(stderr, "failed to load map!\n");
      exit(1);
   }

   int current_x = 40;
   int current_y = 40;

   int current_left = 0;
   int current_right = 0;
   int current_up = 0;
   int current_down = 0;

   int scroll_speed = 5;
   float angle = 0;
   float angle_speed = M_PI / 100;

   int in_move = 0;

   int shouldExit = 0;
   while (!shouldExit)
   {
      al_init_timeout(&timeout, 0.001);
      al_wait_for_event_until(event_queue, &ev, &timeout);

      if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
      {  
            exit(0);
      }


      if (current_left)
      {
         current_x -= scroll_speed;
         angle += angle_speed;
      }

      if (current_right)
      {         
         current_x += scroll_speed;
         angle -= angle_speed;
      }

      if (current_up)
      {
         current_y -= scroll_speed;
      }

      if (current_down)
      {
         current_y += scroll_speed;
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
               in_move = 1;
               break;
            case ALLEGRO_KEY_DOWN:
               current_down = 1;
               break;
         }
      }

      if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT: 
               current_left = 0;
               break;
            case ALLEGRO_KEY_RIGHT:
               current_right = 0;
               break;
            case ALLEGRO_KEY_UP:
               current_up = 0;
               in_move = 0;
               break;
            case ALLEGRO_KEY_DOWN:
               current_down = 0;
               break;
         }
      }


      //al_draw_scaled_bitmap(map, current_x, current_y, 200, 200, 0, 0, WIDTH, HEIGHT, 0);
      al_clear_to_color(al_color_name("black"));

      //draw_stars(angle, in_move);
      //draw_stars_tiles(angle, 5, 0);
      //draw_stars_tiles(angle, 3, 0);
      draw_stars_tiles(angle, 3, in_move, 0);
      draw_stars_tiles(angle, 2, in_move, 0);
      draw_stars_tiles(angle, 1, in_move, 0);

      draw_ship(angle);

      al_flip_display();
   }

   al_destroy_sample(sample);

   shutDown(display);

   return 0;
}
