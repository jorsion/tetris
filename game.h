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
	ShapeType board[WIDTH * HEIGHT];
};

Game* game_new();

void game_start(Game *game);

void game_pause(Game *game);

void game_new_piece(Game *game);

void game_clear(Game *game);

void game_move_shape(Game *game, const Shape &shp, int newX, int newY);

void game_draw_square(Game *game, int x, int y, ShapeType type);

void game_remove_lines(Game *game);

#endif
