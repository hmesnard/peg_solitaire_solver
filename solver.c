#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct m
{
	char x;
	char y;
	char d;
}				move;

move	moves[32];

char game[7][7] = {
	{-1, -1, 1, 1, 1, -1, -1},
	{-1, -1, 1, 1, 1, -1, -1},
	{ 1,  1, 1, 1, 1,  1,  1},
	{ 1,  1, 1, 0, 1,  1,  1},
	{ 1,  1, 1, 1, 1,  1,  1},
	{-1, -1, 1, 1, 1, -1, -1},
	{-1, -1, 1, 1, 1, -1, -1},
};

void	print_game()
{
	/*printf("\n\n");
	usleep(10000);
	for (int y = 0; y < 7; y++)
	{
		for(int x = 0; x < 7; x++)
		{
			if (game[y][x] == -1)
				printf(" ");
			else if (game[y][x] == 0)
				printf("`");
			else if (game[y][x] == 1)
				printf("#");	
		}
		printf("\n");
	}*/
}

int	win()
{
	int count = 0;

	for (int y = 0; y < 7; y++)
		for (int x = 0; x < 7; x++)
		{
			if (game[y][x] == 1)
				count++;
			if (count > 1)
				return (0);
		}
	return (1);
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
	if (rm == 31)
	{
		print_moves();
		exit(0);
	}
	if (game[y][x] == 1)
	{
		if (0 < y && y < 6 && game[y - 1][x] == 1 && game[y + 1][x] == 0)
		{
			game[y - 1][x] = 0;
			game[y][x] = 0;
			game[y + 1][x] = 1;
			mk_move(x, y, 0, rm);
	print_game();
			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y - 1][x] = 1;
			game[y][x] = 1;
			game[y + 1][x] = 0;
	print_game();
		}
		if (0 < y && y < 6 && game[y - 1][x] == 0 && game[y + 1][x] == 1)
		{
			game[y - 1][x] = 1;
			game[y][x] = 0;
			game[y + 1][x] = 0;
			mk_move(x, y, 1, rm);
	print_game();
			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y - 1][x] = 0;
			game[y][x] = 1;
			game[y + 1][x] = 1;
	print_game();
		}
		if (0 < x && x < 6 && game[y][x - 1] == 1 && game[y][x + 1] == 0)
		{
			game[y][x - 1] = 0;
			game[y][x] = 0;
			game[y][x + 1] = 1;
			mk_move(x, y, 2, rm);
	print_game();
			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y][x - 1] = 1;
			game[y][x] = 1;
			game[y][x + 1] = 0;
	print_game();
		}
		if (0 < x && x < 6 && game[y][x - 1] == 0 && game[y][x + 1] == 1)
		{
			game[y][x - 1] = 1;
			game[y][x] = 0;
			game[y][x + 1] = 0;
			mk_move(x, y, 3, rm);
	print_game();
			solve(0, 0, rm + 1);
			rm_move(rm);
			game[y][x - 1] = 0;
			game[y][x] = 1;
			game[y][x + 1] = 1;
	print_game();
		}
	}
	if (x == 6 && y == 6)
		return ;
	else if (x == 6)
		solve(0, y + 1, rm);
	else
		solve(x + 1, y, rm);
}

int main()
{
	moves[0].x = -1;
	solve(0, 0, 0);
	printf("end\n");
	return (0);
}
