#include <math.h>

#ifndef _GAME_
#define _GAME_


#define SCROLL_VELOCITY 5
#define ANGULAR_VELOCITY (M_PI / 100)
#define HORIZONTAL_VELOCITY 5
#define MAX_SHIP_SPEED 10
#define FPS 50

//#define WIDTH  1000
//#define HEIGHT 1000
extern int screen_width;
extern int screen_height;


#define FONT_SIZE 10

/*

Notes:

int, float: 32 bit
long, double: 64 bit

compile within container: sudo docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp dimastopel/allegro5 make


*/


typedef struct {
	double x;
	double y;
} Vector;


//Player context
typedef struct {
	double current_x;
	double current_y;
	unsigned int engine_on;
	float angle;
	//float speed;
	float speed_x;
	float speed_y;
} Context;

// Engine
#define FRONT_ENGINE 1
#define REAR_ENGINE 2
#define RIGHT_ENGINE 4
#define LEFT_ENGINE 8

void engine_on(Context* context, unsigned char engine, unsigned int on);
unsigned int is_engine_on(Context* context, unsigned char engine);

#endif

