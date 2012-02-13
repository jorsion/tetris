#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <gtk/gtk.h>
#include "shape.h"

enum
{
	WIDTH = 10,
	HEIGHT = 22
};

typedef struct _game Game;

struct _game
{
	GtkWidget *window;
	Shape *curPiece;
	int curX;
	int curY;
	int scores;
	bool isStarted;
	bool isPaused;
	bool isFallingFinished;
	ShapeType boards[WIDTH * HEIGHT];
};

Game* game_new();

void game_start(Game *game);

void game_pause(Game *game);

void game_new_piece(Game *game);

void game_clear(Game *game);

void game_move_shape(Game *game, const Shape &shp, int newX, int newY);

void game_draw_square(Game *game, int x, int y, ShapeType type);

void game_remove_lines(Game *game);

ShapeType game_shape_at(int x, int y);

void game_set_current_position(Game *game, int x, int y);

bool game_move_current_shape(Game *game, int x, int y);

void game_draw_square(int x, int y,ShapeType type);

#endif
