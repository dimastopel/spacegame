# BUILD RESOURCES:
# 	ld -r -b binary -o shipimage.o ship.png
# extern unsigned char _binary_ship_png_start[];
# extern unsigned char _binary_ship_png_end[];


#walk : walk_game.c 
#	   @gcc -O -s -Wall \
#	   -o walk \
#	   walk_game.c \
#	   allegro_utils.c \
#	   utils.c \
#	   stars.c \
#	   hud.c \
#	   ship.c \
#	   -lm \
#	   `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
CC     =gcc
CFLAGS =-s -O -Wall -I.

ODIR   =obj
LDIR   =.

LIBS   =-lm `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
DEPS   =allegro_utils.h  game.h  hud.h  ship.h  stars.h  utils.h  world.h
#OBJ    =walk_game.o allegro_utils.o utils.o stars.o hud.o ship.o world.o shipimage.o
OBJ    =*.o


%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

walk: $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	@rm -f *.o walk

