#include <stdio.h>
#include <stdlib.h>

typedef struct m
{
	char x;
	char y;
	char d;
}				move;

move	moves[500];

char game[7][7] = {
	{-1, -1, 1, 1, 1, -1, -1},
	{-1, -1, 1, 1, 1, -1, -1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 0, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{-1, -1, 1, 1, 1, -1, -1},
	{-1, -1, 1, 1, 1, -1, -1},
};

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

void	mk_move(char x, char y, char d)
{
	int i = 0;
	while(i < 500)
	{
		if (moves[i].x == -1)
		{
			moves[i].x = x;
			moves[i].y = y;
			moves[i].d = d;
			moves[i + 1].x = -1;
			return ;
		}
		i++;
	}
	printf("Error : not enough moves\n");
	exit(1);
}

void	rm_move()
{
	int i = 0;
	while (i < 500)
	{
		if (moves[i].x == -1 && i > 0)
		{
			moves[i - 1].x = -1;
			return ;
		}
		i++;
	}
	printf("Error : unknown\n");
	exit(1);
}

void	print_moves()
{
	int i = 0;
	while (i < 500 && moves[i].x != -1)
	{
		printf("y %d x %d ", moves[i].y, moves[i].x);
		switch (moves[i].d)
		{
			case (0):
				printf("bas");
				break;
			case(1):
				printf("haut");
				break;
			case(2):
				printf("droite");
				break;
			case(3):
				printf("gauche");
				break;
			default:
				printf("wtf");
				break;
		}
		printf("\n");
		i++;
	}
}

void	solve(char x, char y, char rm)
{
	//printf("y %d x %d\n", y, x);
	printf("%d\n", rm);
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
			mk_move(x, y, 0);
			solve(0, 0, rm + 1);
			rm_move();
			game[y - 1][x] = 1;
			game[y][x] = 1;
			game[y + 1][x] = 0;
		}
		if (0 < y && y < 6 && game[y - 1][x] == 0 && game[y + 1][x] == 1)
		{
			game[y - 1][x] = 1;
			game[y][x] = 0;
			game[y + 1][x] = 0;
			mk_move(x, y, 1);
			solve(0, 0, rm + 1);
			rm_move();
			game[y - 1][x] = 0;
			game[y][x] = 1;
			game[y + 1][x] = 1;
		}
		if (0 < x && x < 6 && game[y][x - 1] == 1 && game[y][x + 1] == 0)
		{
			game[y][x - 1] = 0;
			game[y][x] = 0;
			game[y][x + 1] = 1;
			mk_move(x, y, 2);
			solve(0, 0, rm + 1);
			rm_move();
			game[y][x - 1] = 1;
			game[y][x] = 1;
			game[y][x + 1] = 0;
		}
		if (0 < x && x < 6 && game[y][x - 1] == 0 && game[y][x + 1] == 1)
		{
			game[y][x + 1] = 1;
			game[y][x] = 0;
			game[y][x + 1] = 0;
			mk_move(x, y, 3);
			solve(0, 0, rm + 1);
			rm_move();
			game[y][x + 1] = 0;
			game[y][x] = 1;
			game[y][x + 1] = 1;
		}
	}
	/*if (win())
	{
		print_moves();
		exit(0);
	}*/
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
