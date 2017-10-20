#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_utils.h"
#include "utils.h"
#include "hud.h"

#define LOC_HUD_MARGIN_WIDTH 20
#define LOC_HUD_MARGIN_HEIGHT 20
#define LOC_HUD_MARGIN_TEXT_WIDTH 2
#define LOC_HUD_MARGIN_TEXT_HEIGHT 5

void draw_hud(Context* context)
{
    int loc_hud_width = screen_width / 100 * 20;
    int loc_hud_height = screen_height / 100 * 8;
	
    int location_hud_x = screen_width - loc_hud_width - LOC_HUD_MARGIN_WIDTH;
	int location_hud_y = screen_height - loc_hud_height - LOC_HUD_MARGIN_HEIGHT;
    al_draw_filled_rectangle(location_hud_x, location_hud_y, 
    	location_hud_x + loc_hud_width, 
    	location_hud_y + loc_hud_height, 
    	al_color_name("black"));

    al_draw_rounded_rectangle(location_hud_x, location_hud_y, 
        location_hud_x + loc_hud_width, 
        location_hud_y + loc_hud_height, 
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
    	"X: %10.1f", context->current_x);
    al_draw_textf(get_font(), al_color_name("white"), 
    	location_hud_x + LOC_HUD_MARGIN_TEXT_WIDTH, 
    	location_hud_y + 3*LOC_HUD_MARGIN_TEXT_HEIGHT + 2*FONT_SIZE, 
    	0, 
    	"Y: %10.1f", context->current_y);
    al_draw_textf(get_font(), al_color_name("white"), 
        location_hud_x + LOC_HUD_MARGIN_TEXT_WIDTH, 
        location_hud_y + 4*LOC_HUD_MARGIN_TEXT_HEIGHT + 3*FONT_SIZE, 
        0, 
        "Alpha: %3.2f", radians_to_degrees(context->angle));
}
