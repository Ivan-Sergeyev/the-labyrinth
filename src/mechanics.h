#ifndef __MECHANICS_H__
#define __MECHANICS_H__

#define MAZE_SIZE 10
#define HOLE_NUM  5

enum _ACTIONS
{
	AC_LEFT,
	AC_RIGHT,
	AC_UP,
	AC_DOWN,
	AC_HALT,
	AC_ERROR = -1
};
typedef enum _ACTIONS ACTIONS;

enum _RESULTS
{
	RS_WALL,
	RS_FREE,
	RS_RIVER,
	RS_HOLE,
	RS_ESCAPE,
	RS_ERROR = -1
};
typedef enum _RESULTS RESULTS;

enum _STATES
{
	ST_FREE   = 0b000000,
	ST_RIVER  = 0b010000,
	ST_WALL   = 0b100000,
	ST_HOLE   = 0b110000,
	ST_MASK   = 0b110000,

	ST_PLAYER   = 0b1000000,
	ST_TREASURE = 0b10000000,

	ST_NUM_MASK = 0b1111,
};

typedef enum _STATES STATES;

struct _Maze
{
	unsigned int maze[MAZE_SIZE][MAZE_SIZE];
	unsigned int player_x;
	unsigned int player_y;
};

typedef struct _Maze Maze;

ACTIONS get_action();

unsigned int do_action(ACTIONS action, Maze* maze);

int print_result(unsigned int result);

int print_maze(Maze* maze);

int create_maze(Maze* maze);

#endif
