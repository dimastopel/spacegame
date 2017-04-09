#include "game.h"

#ifndef _ALLEGRO_HELPERS_
#define _ALLEGRO_HELPERS_

void init_allegro();
ALLEGRO_DISPLAY* create_display();
ALLEGRO_EVENT_QUEUE* create_event_queue();
ALLEGRO_FONT* get_font();
void shut_down_allegro(ALLEGRO_DISPLAY* display);
void process_key_events(ALLEGRO_EVENT_QUEUE* event_queue, Context* context);


// keys callbacks
void do_left(Context* context, int key_up);
void do_right(Context* context, int key_up);
void do_up(Context* context, int key_up);
void do_down(Context* context, int key_up);

#endif
