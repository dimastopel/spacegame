#include "game.h"
#include <allegro5/allegro_font.h>

#ifndef _ALLEGRO_HELPERS_
#define _ALLEGRO_HELPERS_

void init_allegro();
ALLEGRO_DISPLAY* create_display();
ALLEGRO_FONT* get_font();
void shut_down_allegro(ALLEGRO_DISPLAY* display);
void process_events(ALLEGRO_EVENT_QUEUE* event_queue, Context* context);

// movement callbacks
void do_left(Context* context, int key_up);
void do_right(Context* context, int key_up);
void do_up(Context* context, int key_up);
void do_down(Context* context, int key_up);

// ship fire callback
void do_fire(Context* context, int key_up);

// process movement
void do_move(Context* context);

#endif
