#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct	o
{
	char	visual;
	int		time;

	char	endPosition;
	char	x;
	char	y;
}				options;

options	opt;

typedef struct	m
{
	char x;			//removed ball position
	char y;

	char d;			//UP, DOWN, RIGHT or LEFT move
}				move;

move	moves[31];		//array to store all done moves

char game[7][7] = {
	{-1, -1,  1,  1,  1, -1, -1},

	{-1, -1,  1,  1,  1, -1, -1},

	{ 1,  1,  1,  1,  1,  1,  1},

	{ 1,  1,  1,  0,  1,  1,  1},

	{ 1,  1,  1,  1,  1,  1,  1},

	{-1, -1,  1,  1,  1, -1, -1},

	{-1, -1,  1,  1,  1, -1, -1},
};										//original peg solitaire board

void	print_game()
{
	char buf[56];

	for (int y = 0; y < 7; y++)
	{
		for(int x = 0; x < 7; x++)
		{
			if (game[y][x] == -1)
				buf[y * 8 + x] = ' ';
			else if (game[y][x] == 0)
				buf[y * 8 + x] = '`';
			else if (game[y][x] == 1)
				buf[y * 8 + x] = '#';
		}
		buf[y * 8 + 7] = '\n';
	}

	usleep(opt.time);
	system("clear");
	write(1, buf, 56);
}

void	mk_move(char x, char y, char d, char rm)
{
	moves[rm].x = x;
	moves[rm].y = y;
	moves[rm].d = d;
	moves[rm + 1].x = -1;
	return ;
}

void	rm_move(char rm)
{
	moves[rm].x = -1;
	return ;
}

void	print_moves()
{
	int i = 0;
	while (i < 31)
	{
		switch (moves[i].d)
		{
			case (0):
				printf("move (x %d y %d) to (x %d y %d) --- DOWN\n", moves[i].x, moves[i].y - 1, moves[i].x, moves[i].y + 1);
				break;
			case(1):
				printf("move (x %d y %d) to (x %d y %d) --- UP\n", moves[i].x, moves[i].y + 1, moves[i].x, moves[i].y - 1);
				break;
			case(2):
				printf("move (x %d y %d) to (x %d y %d) --- RIGHT\n", moves[i].x - 1, moves[i].y, moves[i].x + 1, moves[i].y);
				break;
			case(3):
				printf("move (x %d y %d) to (x %d y %d) --- LEFT\n", moves[i].x + 1, moves[i].y, moves[i].x - 1, moves[i].y);
				break;
			default:
				printf("wtf");
				break;
		}
		i++;
	}
}

void	solve(char x, char y, char rm)
{
	if (rm == 31 && (opt.endPosition == 0 || game[opt.y][opt.x] == 1))	//game is solved as 31 balls were removed
	{
		print_moves();
		exit(0);
	}
	if (game[y][x] == 1)												//there is a ball on this place
	{
		if (0 < y && y < 6 && game[y - 1][x] == 1 && game[y + 1][x] == 0)	//trying to remove ball by a DOWN move
		{
			game[y - 1][x] = 0;			//doing move
			game[y][x] = 0;
			game[y + 1][x] = 1;
			mk_move(x, y, 0, rm);		//storing move in our array

if (opt.visual)
	print_game();

			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y - 1][x] = 1;
			game[y][x] = 1;
			game[y + 1][x] = 0;

if (opt.visual)
	print_game();

		}
		if (0 < y && y < 6 && game[y - 1][x] == 0 && game[y + 1][x] == 1)	//trying to remove ball by a UP move
		{
			game[y - 1][x] = 1;
			game[y][x] = 0;
			game[y + 1][x] = 0;
			mk_move(x, y, 1, rm);

if (opt.visual)
	print_game();

			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y - 1][x] = 0;
			game[y][x] = 1;
			game[y + 1][x] = 1;

if (opt.visual)
	print_game();

		}
		if (0 < x && x < 6 && game[y][x - 1] == 1 && game[y][x + 1] == 0)	//trying to remove ball by a RIGHT move
		{
			game[y][x - 1] = 0;
			game[y][x] = 0;
			game[y][x + 1] = 1;
			mk_move(x, y, 2, rm);

if (opt.visual)
	print_game();

			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y][x - 1] = 1;
			game[y][x] = 1;
			game[y][x + 1] = 0;

if (opt.visual)
	print_game();

		}
		if (0 < x && x < 6 && game[y][x - 1] == 0 && game[y][x + 1] == 1)	//trying to remove ball by a LEFT move
		{
			game[y][x - 1] = 1;
			game[y][x] = 0;
			game[y][x + 1] = 0;
			mk_move(x, y, 3, rm);
if (opt.visual)
	print_game();
			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y][x - 1] = 0;
			game[y][x] = 1;
			game[y][x + 1] = 1;
if (opt.visual)
	print_game();
		}
	}
	if (x == 6 && y == 6)		//there are no more possible moves -> going back
		return ;
	else if (x == 6)			//going to next line
		solve(0, y + 1, rm);
	else						//going to next space
		solve(x + 1, y, rm);
}

int	getOption(int argc, char **argv, int *i)
{
	if (!strcmp(argv[*i], "-v"))
	{
		if (argc <= *i + 1)
			return (1);
		opt.visual = 1;
		opt.time = atoi(argv[*i + 1]);
		*i += 2;
		return (0);
	}
	else if (!strcmp(argv[*i], "-s"))
	{
		if (argc <= *i + 2)
			return (1);
		int x = atoi(argv[*i + 1]);
		int y = atoi(argv[*i + 2]);
		if (!(0 <= x && x <= 6) || !(0 <= y && y <= 6) || game[y][x] == -1)
			return (1);
		game[3][3] = 1;
		game[y][x] = 0;
		*i += 3;
		return (0);
	}
	else if (!strcmp(argv[*i], "-e"))
	{
		if (argc <= *i + 2)
			return (1);
		opt.endPosition = 1;
		opt.x = atoi(argv[*i + 1]);
		opt.y = atoi(argv[*i + 2]);
		if (!(0 <= opt.x && opt.x <= 6) || !(0 <= opt.y && opt.y <= 6) || game[opt.y][opt.x] == -1)
			return (1);
		*i += 3;
		return (0);
	}
	return (1);
}

int	init(int argc, char **argv)
{
	int i = 1;

	if (argc <= i)
	{
		opt.visual = 0;
		opt.endPosition = 0;
		return (0);
	}
	while (argc > i)
		if (getOption(argc, argv, &i))
			return (1);
	moves[0].x = -1;
	return (0);
}

int main(int argc, char **argv)
{
	if (init(argc, argv))
	{
		write(2, "Error | usage : $>./a.out [-v time] [-s x y] [-e x y]\n", 54);
		return (1);
	}

	solve(0, 0, 0);

	write(2, "Could not find a solution\n", 26);
	return (2);
}
