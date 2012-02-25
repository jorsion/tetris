#include "game.h"
#include "graph.h"
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
	game->isStarted = true;
	game->isPaused = false;
}

void game_pause(Game *game)
{
	game->isStarted = false;
	game->isPaused = true;
}

void game_new_piece(Game *game)
{
	shape_set_random_type(game->curPiece);
	game->curX = WIDTH / 2 + 1;
	game->curY = HEIGHT - 1 + shape_min_x(game->curPiece);

	if(!game_try_move(game,game->curX,game->curY))
	{
		//TODO game over
	}
}

void game_clear(Game *game)
{
	int i;
	for(i = 0; i< WIDTH * HEIGHT; i++)
	{
		game->board[i] = NoShape;
	}
}

ShapeType game_get_shape_at(Game *game, int x, int y)
{
	int xIndex = x / 10;
	int yIndex = y / 10;
	return game->boards[yIndex * WIDTH + xIndex];
}

void game_set_shape_at(Game *game, int x, int y, ShapeType type)
{
	int xIndex = x / 10;
	int yIndex = y / 10;
	game->boards[yIndex * WIDTH + xIndex] = type;
}

void game_set_current_position(Game *game, int x, int y)
{
	game->curX = x;
	game->curY = y;
}

bool game_has_space_at(Game *game, int x ,int y)
{
	if(game_shape_at(game, x, y) != NO_SHAPE)
		return false;
	
	return true;
}

bool game_try_move(Game *game, int x, int y)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		int newX = x + shape_get_x_coordinate(game->curPiece, i);
		int newY = y - shape_get_y_coordinate(game->curPiece,i);
		if(newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) 
			return false;

		if(!game_has_space_at(game, newX, newY) 
			return false;
	}

	game_set_current_position(game, newX, newY);	

	return true;
}

bool game_move_left(Game *game)
{
	int x = game->curX - SHAPE_WIDTH;
	int y = game->curY;
	return game_try_move(game, x, y);	
}

bool game_move_right(Game *game)
{
	int x = game->curX + SHAPE_WIDTH;
	int y = game->curY;
	return game_try_move(game, x, y);
}

bool game_rotate_left(Game *game)
{
	shape_rotate_left(game->curPiece);
	int x = game->curX;
	int y = game->curY;
	return game_try_move(game, x, y);
}

bool game_rotate_right(Game *game)
{
	shape_rotate_right(game->curPiect);
	int x = game->curX;
	int y = game->curY;
	return game_try_move(game, x, y);
}

void game_remove_lines(Game *game)
{
	int numFullLines = 0;
	int i;
	for(i = HEIGHT - 1; i >= 0; i--)
	{
		bool isFull = true;
		int j;
		for(j = 0; j < WIDTH; j++)
		{
			if(game_has_space_at(i, j))
				isFull = false;
			break;
		}

		if(isFull)
		{
			numFullLines++;
			int k;
			for(k = i; k < HEIGHT - 1; k++)
			{
				int m
				for(m =0; m < WIDTH; m++)
					game_shape_at(game, m, k) = game_shape_at(game, j, m + 1);
			}
		}
	}

	if(numFullLines > 0)
	{
		game->scores+=numFullLines;
		
		game->isFallingFinished = true;
		shape_set_type(game->curPiece,NO_SHAPE);
	}
	
}

void game_draw_square(GtkWidget *widget, int x, int y, ShapeType type)
{
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgb(cr, 255, 0, 0);
	cairo_set_line_width(cr,1);
	
	static Color colors[] =
	{
		Color(0,0,0), Color(204,102,102),
		Color(102,204,102), Color(102,102,204),
		Color(204,204,102), Color(204,102,204),
		Color(102,204,2.4), Color(218,170,0)	
	};

	static Color light[] =
	{
		Color(0,0,0), Color(248,159,171),
		Color(121,252,121), Color(121,121,252),
		Color(252,252,121), Color(252,121,252),
		Color(121,252,252), Color(252,198,0)
	};

	static Color dark[] =
	{
		Color(0,0,0), Color(128,59,59),
		Color(59,128,59), Color(59,59,128),
		Color(128,128,59), Color(128,59,128),
		Color(59,128,128), Color(128,98,0)
	};

	graph_set_color(cr, light[int(type)]);
	graph_draw_line(cr, x, y + SHAPE_WIDTH - 1, x, y);
	graph_draw_line(cr, x, y, x + SHAPE_WIDTH - 1, y);

	graph_set_color(cr, dark[int(type)]);
	graph_draw_line(cr, x + 1, y + SHAPE_WIDTH - 1, x + SHAPE_WIDTH - 1, y+ SHAPE_WIDTH -1);
	graph_draw_line(cr, x + SHAPE_WIDTH - 1, y + SHAPE_WIDTH - 1, X + SHAPE_WIDTH - 1, y + 1);

	graph_draw_rectangle(cr, x + 1, y + 1, SHAPE_WIDTH - 2, SHAPE_WIDTH - 2, colors[int(type)], colors[int(type)]);

	cairo_destroy(cr);
}

void game_increment_score(Game *game)
{
	game->score++;
}

void game_drop_piece(Game *game)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		int x = game->curPiece.coords[i].x + game->curX;
		int y = game->curpiece.coords[i].y + game->curY;
		game_set_shape_at(game, x, y, game->curPiece->type);

	}
	
	game_remove_lines(game);
	
	if(game->isFallingFinished)
		game_new_piece();
	
}

void game_drop_to_bottom(Game *game)
{
	int newY = game->curY;
	while(newY > 0)
	{
		if(!game_try_move(game, game->curX, newY )
			break;
		newY -= SHAPE_WIDTH;
	}
		
	game_drop_piece(game);
}

void game_one_line_down(Game *game)
{
	if(game_try_move(game, game->curX, newY)
		game_drop_piece(game);
}

void game_refresh(Game *game)
{
	gtk_widget_queue_draw(game->window);
}
