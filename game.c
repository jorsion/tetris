#include "game.h"

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

