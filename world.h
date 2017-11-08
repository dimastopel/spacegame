#include "game.h"

#ifndef _WORLD_
#define _WORLD_

typedef enum {
   MOVE_TYPE_STATIC,
   MOVE_TYPE_CIRCLE,
   MOVE_TYPE_VERTICAL,
   MOVE_TYPE_HORIZONTAL
} SpaceObjectMovement;

typedef struct {
   double center_x;
   double center_y;
   unsigned int mass;
   ALLEGRO_BITMAP* resource;
   SpaceObjectMovement move_type;
   float scale_factor;
   int move_span;
   float initial_angle;
   int is_rotating;
} SpaceObject;

extern SpaceObject space_objects[100];


void load_world();
void draw_world(Context* context);

#endif 
