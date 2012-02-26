#include "game.h"
#include "graph.h"
#include <cairo.h>
#include <stdio.h>

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
	game->curPiece = shape_new();
	game_clear(game);

	return game;
}

void game_start(Game *game)
{
	game->isStarted = true;
	game->isPaused = false;
	printf("started:%d,paused:%d\n",game->isStarted, game->isPaused);
	game_new_piece(game);
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
	game->curY = shape_min_y(game->curPiece);

	if(!game_try_move(game,game->curX,game->curY))
	{
		printf("false false false\n");
		game->isStarted = false;
	}
}

void game_clear(Game *game)
{
	int i;
	for(i = 0; i< WIDTH * HEIGHT; i++)
	{
		game->boards[i] =  NO_SHAPE;
	}
}

ShapeType game_get_shape_at(Game *game, int x, int y)
{
	int xIndex = x / 10;
	int yIndex = y / 10;
	printf("xIndex:%d,yIndex:%d\n",xIndex, yIndex);
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
	if(game_get_shape_at(game, x, y) != NO_SHAPE)
		return false;
	
	return true;
}

bool game_try_move(Game *game, int x, int y)
{
	int i;
	int newX, newY;
	for(i = 0; i < 4; i++)
	{
		newX = x + shape_get_x_coordinate(game->curPiece, i);
		newY = y - shape_get_y_coordinate(game->curPiece,i);
		if(newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) 
			return false;

		if(!game_has_space_at(game, newX, newY)) 
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
	shape_rotate_right(game->curPiece);
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
			if(game_has_space_at(game, i, j))
				isFull = false;
			break;
		}

		if(isFull)
		{
			numFullLines++;
			int k;
			for(k = i; k < HEIGHT - 1; k++)
			{
				int m;
				for(m =0; m < WIDTH;m++)
					;
//TODO					game_shape_at(game, m, k) = game_shape_at(game, j, m + 1);
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
	
	Color colors[] =
	{
		{0,0,0}, {204,102,102},
		{102,204,102}, {102,102,204},
		{204,204,102}, {204,102,204},
		{102,204,2.4}, {218,170,0}	
	};

	Color light[] =
	{
		{0,0,0}, {248,159,171},
		{121,252,121}, {121,121,252},
		{252,252,121}, {252,121,252},
		{121,252,252}, {252,198,0}
	};

	Color dark[] =
	{
		{0,0,0}, {128,59,59},
		{59,128,59}, {59,59,128},
		{128,128,59}, {128,59,128},
		{59,128,128}, {128,98,0}
	};

	graph_set_color(cr, light[type]);
	graph_draw_line(cr, x, y + SHAPE_WIDTH - 1, x, y);
	graph_draw_line(cr, x, y, x + SHAPE_WIDTH - 1, y);

	printf("SHAPE_WIDTH:%d\n",SHAPE_WIDTH);
	graph_set_color(cr, dark[type]);
	graph_draw_line(cr, x + 1, y + SHAPE_WIDTH - 1, x + SHAPE_WIDTH - 1, y+ SHAPE_WIDTH -1);
	graph_draw_line(cr, x + SHAPE_WIDTH - 1, y + SHAPE_WIDTH - 1, x + SHAPE_WIDTH - 1, y + 1);

//	graph_draw_rectangle(cr, x + 1, y + 1, SHAPE_WIDTH - 2, SHAPE_WIDTH - 2, colors[type], colors[type]);

	cairo_destroy(cr);
}

void game_draw(Game *game)
{
	printf("draw draw \n");
	int i,j;
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			ShapeType type = game_get_shape_at(game, j * SHAPE_WIDTH, i * SHAPE_WIDTH);
			if(type != NO_SHAPE)
			{
				game_draw_square(game->window, j * SHAPE_WIDTH, i * SHAPE_WIDTH, type);
			}
		}
	}

	if(game->curPiece->type != NO_SHAPE)
	{
		printf("Draw current piece\n");
		for(i = 0; i < 4; i++)
		{
			int x = game->curX + game->curPiece->coords[i].x;
			printf("x = %d,",x);
			int y =  game->curY + game->curPiece->coords[i].y;
			printf("y = %d\n",y);
			game_draw_square(game->window, x * SHAPE_WIDTH, y * SHAPE_WIDTH, game->curPiece->type);
		}
	}
}

void game_increment_score(Game *game)
{
	game->scores++;
}

void game_drop_piece(Game *game)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		int x = game->curPiece->coords[i].x + game->curX;
		int y = game->curPiece->coords[i].y + game->curY;
		game_set_shape_at(game, x, y, game->curPiece->type);
	}
	
	game_remove_lines(game);
	
	if(game->isFallingFinished)
		game_new_piece(game);
	
}

void game_drop_to_bottom(Game *game)
{
	int newY = game->curY;
	while(newY > 0)
	{
		if(!game_try_move(game, game->curX, newY ))
			break;
		newY -= SHAPE_WIDTH;
	}
		
	game_drop_piece(game);
}

void game_one_line_down(Game *game)
{
	int newY = game->curY - SHAPE_WIDTH;
	if(game_try_move(game, game->curX, newY))
		game_drop_piece(game);
}

void game_refresh(Game *game)
{
	gtk_widget_queue_draw(game->window);
}
