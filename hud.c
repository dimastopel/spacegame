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
#define LOC_HUD_TEXT_HEIGHT 25

void draw_hud(Context* context)
{
    int loc_hud_width = screen_width / 100 * 20;
    int loc_hud_height = screen_height / 100 * 13;
    char ver[50];
	
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

    char* hud_msg = "Ship position: \n"
        "X: %10.1f\n"
        "Y: %10.1f\n"
        "Alpha: %3.2f\n"
        "Speed: %3.2f\n"
        "Alg ver: %s\n"
        "Fuel: %3.2f\n";

    get_allegro_version(ver);
    al_draw_multiline_textf(get_font(), al_color_name("white"), 
        location_hud_x + LOC_HUD_MARGIN_TEXT_WIDTH, 
        location_hud_y + LOC_HUD_MARGIN_TEXT_HEIGHT, 
        loc_hud_width - LOC_HUD_MARGIN_WIDTH, //max_width
        //LOC_HUD_TEXT_HEIGHT, //line height
        al_get_font_line_height(get_font()) + LOC_HUD_MARGIN_TEXT_WIDTH,
        0, // flags
        hud_msg,
    	context->current_x, 
        context->current_y, 
        radians_to_degrees(context->angle), 
        sqrt(pow(context->speed_x,2) + pow(context->speed_y,2)), 
        ver, 
        context->fuel);
}
