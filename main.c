#include <stdio.h>
#include <signal.h>

#ifdef _WIN32
#include "filesWin/ansi_escapes.c"
#include "filesWin/winkeypress.c"
#else
#include "filesUNIX/kbhit.c"
#endif

#include "maps/main.c"

int draw();
int updatemap();
int mappos();
int gameOver();
int gameCompleted();
int stopGame();
void INThandler();

#ifdef _WIN32
const int waitMS = 40;
#else
const int waitMS = 40;
#endif

const int defpos[2] = { 1,1 };
const int bonuslines = 2;
const int levelmax = 5;
const int LWIDTH = 8;
const int LHEIGHT = 8;

char currentTile;
char currentColour;

unsigned int pos[2] = {1,1};
unsigned int level = 0;
unsigned int STOP = 0;
unsigned int STOPCODE = 128;
unsigned int coins = 0;
unsigned int SEECRET = 0;

char map2[72]; // LHEIGHT*(LWIDTH+1) (+1 for \n)
char colmap2[72];
char map[500]; // Size needed unknown.

int main ()
{
#ifdef _WIN32
	setupConsole();
#endif
	printf("\033[?25l");
	signal(SIGINT, INThandler);
	for (int i=0;i<=LHEIGHT+bonuslines;i++)
	{
		printf("\n");
	}
	char x;
	
	while (1)
	{
		if (STOP)
		{
			return STOPCODE;
		}

		updatemap();
		draw();

		if (kbhit())
		{
#ifdef _WIN32
			x = getKeyPress();
#else
			x = getchar();
#endif

			switch (x)
			{
			case 'w':
				pos[1]--;
				if (colmap(level, mappos(0)) == 'r')
				{
					pos[1]++;
				}
				break;

			case 'a':
				pos[0]--;
				if (colmap(level, mappos(0)) == 'r')
				{
					pos[0]++;
				}
				break;

			case 's':
				pos[1]++;
				if (colmap(level, mappos(0)) == 'r')
				{
					pos[1]--;
				}
				break;

			case 'd':
				pos[0]++;
				if (colmap(level, mappos(0)) == 'r')
				{
					pos[0]--;
				}
				break;
				
			case 'r': // SEECRET
				SEECRET = 1;
				break;

			default:
				break;
			}
			
			if (x == 0x1b | x == 0x03)
			{
				INThandler();
			}
#ifdef _WIN32
			Sleep(waitMS);
#else
			usleep(waitMS*1000);
#endif
		}

		currentColour = colmap(level, mappos(0));
		currentTile = basemap(level, mappos(0));

		if (currentColour == 'g' && currentTile == '&')
		{
			level++;
			coins = 0;
			pos[0] = defpos[0];
			pos[1] = defpos[1];
			if (level>=levelmax)
			{
				gameCompleted();
			}
		}
		if (currentColour == 'R' && currentTile == '%')
		{
			coins--;
			if (coins <= 0)
			{
				coins = 0;
				gameOver();
			}
		}
		if (currentColour == 'g' && currentTile == '0')
		{
			coins++;
		}
		
		fflush(stdout);
#ifdef _WIN32
		Sleep(20);
#else
		usleep(20 * 1000);
#endif
	}
	
	return 0;
}

int draw ()
{
	printf("\r");
	for (int i=0;i<LHEIGHT+bonuslines;i++)
	{
		printf("\033[A");
	}
	printf("%s\033[0m\n",map);
	if (SEECRET)
	{
		printf("Riley is the best! %d  \n\033[0;30m", coins);
		SEECRET = 0;
	}
	else
	{
		printf("Coins: %d                           \n\033[0;30m", coins);
	}

	return 0;
}

int updatemap ()
{
	int j = 0;
	for (int i = 0;i <= LHEIGHT*LWIDTH;i++)
	{
		map2[i+j] = basemap(level, i);
		colmap2[i+j] = colmap(level, i);
		if (i % 8 == 7)
		{
			j++;
			map2[i+j] = '\n';
			colmap2[i+j] = '\n';
		}
	}
	map2[mappos(1)] = '@';
	colmap2[mappos(1)] = ' ';
	
	j = 0;
	for (int i=0;i<=LHEIGHT*(LWIDTH+1);i++)
	{
		switch (colmap2[i])
		{
		case 'r':
			map[j] = '\033';j++;
			map[j] = '[';j++;
			map[j] = '0';j++;
			map[j] = ';';j++;
			map[j] = '3';j++;
			map[j] = '1';j++;
			map[j] = 'm';j++;
			break;

		case 'g':
			map[j] = '\033';j++;
			map[j] = '[';j++;
			map[j] = '0';j++;
			map[j] = ';';j++;
			map[j] = '3';j++;
			map[j] = '2';j++;
			map[j] = 'm';j++;
			break;

		case 'R':
			map[j] = '\033';j++;
			map[j] = '[';j++;
			map[j] = '1';j++;
			map[j] = ';';j++;
			map[j] = '3';j++;
			map[j] = '1';j++;
			map[j] = 'm';j++;
			break;

		default:
			map[j] = '\033';j++;
			map[j] = '[';j++;
			map[j] = '0';j++;
			map[j] = 'm';j++;
			break;
		}
		map[j] = map2[i];j++;
	}
	
	return 0;
}

void INThandler (int sig)
{
	signal(sig, SIG_IGN);

	STOPCODE = 1;
	stopGame();
}

int mappos(int x)
{
	return pos[0] + pos[1] * (LWIDTH+x);
}

int gameCompleted()
{
	printf("\n\033[0mGame completed!!!\n");
#ifdef _WIN32
	Sleep(3000);
#else
	usleep(3000*1000);
#endif
	STOPCODE = 0;
	stopGame();
	return 0;
}

int gameOver()
{
	printf("\n\033[0mGame Over!!!\n");
#ifdef _WIN32
	Sleep(3000);
#else
	usleep(3000*1000);
#endif
	STOPCODE = 0;
	stopGame();
	return 0;
}


int stopGame()
{
	printf("\033[0m\033[?25h\n");
#ifdef _WIN32
	restoreConsole();
#endif
	STOP = 1;
	return 0;
}