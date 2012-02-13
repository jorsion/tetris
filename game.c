#include "game.h"
#include <cairo.h>

Game *game_new()
{
	Game *game;
	game = (Game*)malloc(sizeof(Game));
	game->window = NULL;
	game->curX = 0;
	game->curY = 0;
	game->scores = 0;
	game->isStarted = false;
	game->isPaused = false;
	game->curPiece = NULL;
	game_clear(game);

	return game;
}

void game_start(Game *game)
{
}

void game_pause(Game *game)
{
}

void game_clear(Game *game)
{
	for(int i = 0; i< WIDTH * HEIGHT; i++)
	{
		game->board[i] = NoShape;
	}
}

ShapeType game_shape_at(int x, int y)
{
	return boards[y * width + x];
}

void game_set_current_position(Game *game, int x, int y)
{
	game->curX = x;
	game->curY = y;
}

bool game_move_current_shape(Game *game, int x, int y)
{
	for(int i = 0; i < 4; i++)
	{
		int newX = x + shape_get_x_coordinate(game->curPiece, i);
		int newY = y - shape_get_y_coordinate(game->curPiece,i);
		if(newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) 
			return false;

		if(game_shape_at(newX, newY) != NO_SHAPE)
			return false;
	}

	game_set_current_position(game, newX, newY);	
}

void game_draw_square(GtkWidget *widget, int x, int y, ShapeType type)
{
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgb(cr, 255, 0, 0);
	cairo_set_line_width(cr,1);
	

}
