#include <math.h>

#ifndef _GAME_
#define _GAME_


#define SCROLL_VELOCITY 5
#define ANGULAR_VELOCITY (M_PI / 100)

#define WIDTH  1000
#define HEIGHT 1000

#define FONT_SIZE 10

/*

Notes:

int, float: 32 bit
long, double: 64 bit

 */

typedef struct {
	int current_x;
	int current_y;
	int is_moving;
	float angle;
} Context;


#endif

