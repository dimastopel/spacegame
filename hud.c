#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_utils.h"
#include "hud.h"

#define LOC_HUD_WIDTH (WIDTH / 100 * 20)
#define LOC_HUD_HEIGHT (HEIGHT / 100 * 6)
#define LOC_HUD_MARGIN_WIDTH 20
#define LOC_HUD_MARGIN_HEIGHT 20
#define LOC_HUD_MARGIN_TEXT_WIDTH 2
#define LOC_HUD_MARGIN_TEXT_HEIGHT 5

void draw_hud(Context* context)
{
	int location_hud_x = WIDTH - LOC_HUD_WIDTH - LOC_HUD_MARGIN_WIDTH;
	int location_hud_y = HEIGHT - LOC_HUD_HEIGHT - LOC_HUD_MARGIN_HEIGHT;
    al_draw_filled_rectangle(location_hud_x, location_hud_y, 
    	location_hud_x + LOC_HUD_WIDTH, 
    	location_hud_y + LOC_HUD_HEIGHT, 
    	al_color_name("black"));

    al_draw_rounded_rectangle(location_hud_x, location_hud_y, 
        location_hud_x + LOC_HUD_WIDTH, 
        location_hud_y + LOC_HUD_HEIGHT, 
        10,10,
        al_color_name("white")
        , 1);

    al_draw_textf(get_font(), al_color_name("white"), 
    	location_hud_x + LOC_HUD_MARGIN_TEXT_WIDTH, 
    	location_hud_y + LOC_HUD_MARGIN_TEXT_HEIGHT, 
    	0, 
    	"Ship position:");
    al_draw_textf(get_font(), al_color_name("white"), 
    	location_hud_x + LOC_HUD_MARGIN_TEXT_WIDTH, 
    	location_hud_y + 2*LOC_HUD_MARGIN_TEXT_HEIGHT + FONT_SIZE, 
    	0, 
    	"X: %d", context->current_x);
    al_draw_textf(get_font(), al_color_name("white"), 
    	location_hud_x + LOC_HUD_MARGIN_TEXT_WIDTH, 
    	location_hud_y + 3*LOC_HUD_MARGIN_TEXT_HEIGHT + 2*FONT_SIZE, 
    	0, 
    	"Y: %d", context->current_y);
}
