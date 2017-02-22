#include "mechanics.h"
#include <stdio.h>

ACTIONS get_action()
{
	unsigned int action = 0;
	scanf("%u", &action);

	return (action <= 4) ? action : -1;
}

#define _STATE(dx,dy) (maze->maze[maze->player_x + (dx)][maze->player_y + (dy)] & ST_MASK)
#define _STATE_NUM(dx,dy) (maze->maze[maze->player_x + (dx)][maze->player_y + (dy)] & ST_NUM_MASK)

void _go_down_the_river(Maze* maze)
{
}

void _go_down_the_hole (Maze* maze)
{
}

unsigned int do_action(ACTIONS action, Maze* maze)
{
	if(maze == NULL) return RS_ERROR;

#define _ACTION_CHK(ac,dx,dy)                                           \
	if(action == ac)                                                \
	{                                                               \
		if((0 > (maze->player_x + dx)) ||                       \
			((maze->player_x + dx) >= MAZE_SIZE))           \
			{puts("escape"); return RS_ESCAPE;}             \
		if((0 > (maze->player_y + dy)) ||                       \
			((maze->player_y + dy) >= MAZE_SIZE))           \
			{puts("escape"); return RS_ESCAPE;}             \
		if(_STATE(dx,dy) == ST_WALL)                            \
			{puts("wall"); return RS_WALL;}                 \
		maze->player_x += dx;                                   \
		maze->player_y += dy;                                   \
                                                                        \
		if(_STATE(0,0) == ST_RIVER) _go_down_the_river( maze);  \
		if(_STATE(0,0) == ST_HOLE)  _go_down_the_hole(  maze);  \
		return _STATE(0,0);                                     \
	}

	_ACTION_CHK(AC_LEFT, -1,  0)
	_ACTION_CHK(AC_RIGHT, 1,  0)
	_ACTION_CHK(AC_UP,    0, -1)
	_ACTION_CHK(AC_DOWN,  0,  1)
	_ACTION_CHK(AC_HALT,  0,  0)

	return RS_ERROR;
}

int print_result(unsigned int result)
{
	printf("%u\n", result);

	return 0;
}

void _print_cell(unsigned int state)
{
	switch(state&ST_MASK)
	{
		case ST_FREE:
		printf("F");
		break;

		case ST_RIVER:
		printf("R");
		break;

		case ST_WALL:
		printf("W");
		break;

		case ST_HOLE:
		printf("H");
		break;

		default:
		printf("?");
		break;
	}
}

int print_maze(Maze* maze)
{
	int x = 0, y = 0;
	
	for(y = 0; y < 10; y++)
	{
		for(x = 0; x < 10; x++)
		{
			if(maze->player_x == x && maze->player_y == y) printf("P");
			else _print_cell( maze->maze[x][y] );
		}
		printf("\n");
	}

	printf("player position (%u, %u)\n\n\n", maze->player_x, maze->player_y);

	return 0;
}

int create_maze(Maze* maze)
{
	char chr_tr[5] = "FRWH";
	int  int_tr[5] = { ST_FREE, ST_RIVER, ST_WALL, ST_HOLE, -1};

	FILE* input = NULL;
	input = fopen("test.maze", "r");

	fscanf(input, "%d %d ", &maze->player_x, &maze->player_y);
	
	int x = 0;
	int y = 0;
	for( y = 0; y < MAZE_SIZE; y++)
	{
		for( x = 0; x < MAZE_SIZE; x++)
		{
			char c;
			fscanf(input, "%c", &c);
			int i = 0;
			for( ; i < 5; i++)
				if(c == chr_tr[i]) break;

			maze->maze[x][y] = int_tr[i];
		}
		fscanf(input, "%*c");
	}
}
