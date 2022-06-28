/*******************************************************************************/
/*                                                                             */
/*              :::::::                                                        */
/*            :+:    :+:                                                       */
/*           +:+                                                               */
/*          +#+                                                                */
/*         +#+                                                                 */
/*        #+#     #+#                                                          */
/*   snake.########                                                            */
/*                                                                             */
/*                                                                             */
/*   By: fatpound                                                              */
/*                                                                             */
/*   Created: 19/02/2022 00:17:19 by fatpound                                  */
/*   Updated: 07/06/2022 06:04:09 by fatpound                                  */
/*                                                                             */
/*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SWAP(x, y) (x == y ? 0 : (x ^= y ^= x ^= y))

#define UP    'w'
#define DOWN  's'
#define RIGHT 'd'
#define LEFT  'a'

#define END    27 // ESC (Terminate)
#define WIN   'n'

#define MAX_SIZE 15

#define C(x) (SetConsoleTextAttribute(h, x))

int i, j, snake[MAX_SIZE][MAX_SIZE], temp[2], tail[2], head[2], table[2], score = 0, hitapple = 0, gameover = 0;
char k = LEFT, lastmove = LEFT;

int IncreaseNumbers()
{
	for (i = 0; i < table[0]; i++)
	{
		for (j = 0; j < table[1]; j++)
		{
			if (snake[i][j] > 1)
			{
				snake[i][j]++;
			}
		}
	}
}

void LowerTheCase()
{
	if (k == UP - 32 || k == DOWN - 32 || k == LEFT - 32 || k == RIGHT - 32)
	{
		k += 32;
	}
}

void HeadLocation()
{
	for (i = 0; i < table[0]; i++)
	{
		for (j = 0; j < table[1]; j++)
		{
			if (snake[i][j] == 1)
			{
				head[0] = i;
				head[1] = j;
			}
		}
	}
}

void TailLocation()
{
	int greatest = 0;
	
	for (i = 0; i < table[0]; i++)
	{
		for (j = 0; j < table[1]; j++)
		{
			if (snake[i][j] > greatest)
			{
				greatest = snake[i][j];
				
				tail[0] = i;
				tail[1] = j;
			}
		}
	}
}

void PlaceApple()
{
	while (snake[temp[0]][temp[1]] > 0)
	{
		temp[0] = rand() % table[0];
		temp[1] = rand() % table[1];
	}
	
	snake[temp[0]][temp[1]] = -1;
}

void SwapHead()
{
	if (k == UP)    SWAP(snake[head[0]][head[1]], snake[head[0] - 1][head[1]]);
	if (k == DOWN)  SWAP(snake[head[0]][head[1]], snake[head[0] + 1][head[1]]);
	if (k == LEFT)  SWAP(snake[head[0]][head[1]], snake[head[0]][head[1] - 1]);
	if (k == RIGHT) SWAP(snake[head[0]][head[1]], snake[head[0]][head[1] + 1]);
}

void MoveBoard()
{
	if ((k == UP && snake[head[0] - 1][head[1]] == -1) || (k == DOWN && snake[head[0] + 1][head[1]] == -1) || (k == LEFT && snake[head[0]][head[1] - 1] == -1) || (k == RIGHT && snake[head[0]][head[1] + 1] == -1))
	{
		hitapple = 1;
	}
	
	if (hitapple)
	{
		score++;
		
		snake[temp[0]][temp[1]] = 1;
		snake[head[0]][head[1]] = 0;
		
		IncreaseNumbers();
		
		snake[head[0]][head[1]] = 2;
		
		if (score != (table[0] * table[1] - 2))
		{
			PlaceApple();
		}
		else
		{
			k = WIN;
		}
		
		hitapple = !hitapple;
	}
	else
	{
		SwapHead();
		TailLocation();
		IncreaseNumbers();
		
		SWAP(snake[head[0]][head[1]], snake[tail[0]][tail[1]]);
		
		snake[head[0]][head[1]] = 2;
	}
}

void BoardLogic()
{
	HeadLocation();
	
	if ((k == UP && (head[0] == 0 || snake[head[0] - 1][head[1]] > 0)) || (k == DOWN && (head[0] == table[0] - 1 || snake[head[0] + 1][head[1]] > 1)) || (k == LEFT && (head[1] == 0 || snake[head[0]][head[1] - 1] > 1)) || (k == RIGHT && (head[1] == table[1] - 1 || snake[head[0]][head[1] + 1] > 1)))
	{
		gameover = 1;
	}
	
	if (!gameover)
	{
		MoveBoard();
	}
}

void DrawBoard(HANDLE h, WORD wOldColorAttrs)
{
	if (!gameover && k != END)
	{
		for (system("CLS"), i = 0; i < table[0] + 2; i++)
		{
			for (j = 0; j < table[1] + 2; j++)
			{
				SetConsoleTextAttribute(h, (snake[i - 1][j - 1] == 1) ? 1 : ((snake[i - 1][j - 1]) ? (((snake[i - 1][j - 1]) == -1) ? 11 : wOldColorAttrs) : 1));
				
				printf("%c%s", (i == 0 || j == 0 || i == table[0] + 1 || j == table[1] + 1) ? (C(3), '#') : (snake[i - 1][j - 1] == 1 ? 'X' : (snake[i - 1][j - 1] ? (snake[i - 1][j - 1] == -1 ? 42 : 'O') : 32)), j == table[1] + 1 ? "\n" : "");
			}
		}
		
		SetConsoleTextAttribute(h, 14);
		printf("\nSCORE : %d", score);
	}
	
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

int main(int argc, char *argv[])
{
	if (argc != 3 || ((atoi(argv[1]) * atoi(argv[2])) < 3)) // If there's no cmdline parameters, then exit the game with an error code
	{
		printf("Too %s%s!\nUsage: snake <Rows> <Columns>\n\nCopright %c fatpound (2022)", argc == 3 ? "small board" : (argc < 3 ? "few" : "many"), argc != 3 ? " parameters" : "", 184);
		
		getch();
		exit(1);
	}
	
	if (atoi(argv[1]) > MAX_SIZE || atoi(argv[2]) > MAX_SIZE)
	{
		printf("Rows or Columns can not be more than %d because of Windows Terminal's slowness.\nEvery size that is more than %d will be set to the limit", MAX_SIZE, MAX_SIZE);
		
		getch();
	}
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	WORD wOldColorAttrs = csbiInfo.wAttributes;
	
	// Setting board limits
	for (i = 0; i < 2; i++)
	{
		table[i] = atoi(argv[i + 1]) > MAX_SIZE ? MAX_SIZE : atoi(argv[i + 1]);
	}
	
	// Board preparation
	for (i = 0; i < table[0]; i++)
	{
		for (j = 0; j < table[1]; j++)
		{
			snake[i][j] = 0;
		}
	}
	
	// Placing snake's head
	if (table[1] == 1)
	{
		snake[1][table[1] - 1] = 1;
	}
	else
	{
		snake[0][table[1] - 2] = 1;
	}
	
	// Placing snake's first 'O'
	snake[0][table[1] - 1] = 2;
	
	unsigned int tim = time(0);
	
	srand(tim);
	temp[0] = rand() % table[0];
	temp[1] = rand() % table[1];
	
	PlaceApple();
	DrawBoard(h, wOldColorAttrs);
	
	// Game Loop
	while (!gameover && k != WIN)
	{
		k = getch();
		LowerTheCase();
		
		while ((k == LEFT && lastmove == RIGHT) || (k == RIGHT && lastmove == LEFT) || (k == UP && lastmove == DOWN) || (k == DOWN && lastmove == UP))
		{
			k = getch();
			LowerTheCase();
		}
		
		if (k == END)
		{
			DrawBoard(h, wOldColorAttrs);
			break;
		}
		
		lastmove = k;
		
		if (k == UP || k == DOWN || k == LEFT || k == RIGHT)
		{
			BoardLogic();
			DrawBoard(h, wOldColorAttrs);
		}
	}
	
	printf("\n\nGame %s!\n\nCopyright %c fatpound (2022)", k == END ? "Terminated" : (k == WIN ? "Ended" : "Over"), 184);
	
	getch();
	return 0;
}