#include <math.h>

#ifndef _GAME_
#define _GAME_


#define SCROLL_VELOCITY 5
#define ANGULAR_VELOCITY (M_PI / 100)

typedef struct {
	int current_x;
	int current_y;
	int is_moving;
	float angle;
} Context;


#endif

