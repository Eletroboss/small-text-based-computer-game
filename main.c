#include <stdio.h>
#include <signal.h>

#ifdef _WIN32
#include "filesWin/ansi_escapes.c"
#include "filesWin/winkeypress.c"
#else
#include "filesUNIX/kbhit.c"
#endif

#include "maps/main.c"
#include "2Player.c"
#include "save.c"

unsigned char draw(void);
unsigned char updatemap(void);
unsigned char mappos(unsigned char x);
unsigned char gameOver(void);
unsigned char gameCompleted(void);
unsigned char stopGame(void);

void INThandler(int sig);

const unsigned char waitMS = 40;
const unsigned char defpos[2] = { 1,1 };
const unsigned char bonuslines = 2;
const unsigned char levelmax = 5;

unsigned char currentTile;
unsigned char currentColour;

unsigned char pos[2] = { 1,1 };
unsigned char level = 0;
unsigned char STOP = 0;
unsigned char STOPCODE = 128;
unsigned char SEECRET = 0;
unsigned char p2 = 0;

signed long coins = 0;

unsigned char map2[72]; // LHEIGHT*(LWIDTH+1) (+1 for \n)
unsigned char colmap2[72];
unsigned char map[500]; // Size needed unknown.

unsigned char main(int argc, char* argv[])
{
  p2 = argc;
#ifdef _WIN32
  setupConsole();
#endif
  printf("\033[?25l");
  signal(SIGINT, INThandler);
  for (unsigned char i = 0;i <= LHEIGHT + bonuslines;i++)
  {
    printf("\n");
  }
  unsigned char x;

  while (1)
  {
    if (p2 >= 2)
    {
      send1pPos(mappos(1), level);
      if (get2pPos()[1] > level & get2pPos()[1] < levelmax) {
        level = get2pPos()[1];
      }
    }
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

      case 'q':
        save(pos[0], pos[1], level);
        break;

      case 'e':
        pos[0] = load(0);
        pos[1] = load(1);
        level = load(2);
        break;

      default:
        break;
      }

#ifdef _WIN32
      Sleep(waitMS);
#else
      usleep(waitMS * 1000);
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
      if (level >= levelmax)
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

unsigned char draw(void)
{
  printf("\r");
  for (unsigned char i = 0;i < LHEIGHT + bonuslines;i++)
  {
    printf("\033[A");
  }
  printf("%s\033[0m           \n", map);
  if (SEECRET)
  {
    printf("Riley is the best! %ld  \n\033[0;30m", coins);
    SEECRET = 0;
  }
  else
  {
    printf("Coins: %ld                           \n\033[0;30m", coins);
  }

  return 0;
}

unsigned char updatemap(void)
{
  unsigned short j = 0;
  for (unsigned char i = 0;i <= LHEIGHT * LWIDTH;i++)
  {
    map2[i + j] = basemap(level, i);
    colmap2[i + j] = colmap(level, i);
    if (i % 8 == 7)
    {
      j++;
      map2[i + j] = '\n';
      colmap2[i + j] = '\n';
    }
  }

  map2[mappos(1)] = '@';
  colmap2[mappos(1)] = ' ';
  if (p2 >= 2)
  {
    map2[get2pPos()[0]] = '@';
    colmap2[get2pPos()[0]] = 'g';
  }

  j = 0;
  for (unsigned char i = 0;i <= LHEIGHT * (LWIDTH + 1);i++)
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

void INThandler(int sig)
{
  signal(sig, SIG_IGN);

  STOPCODE = 1;
  stopGame();
}

unsigned char mappos(unsigned char x)
{
  return pos[0] + pos[1] * (LWIDTH + x);
}

unsigned char gameCompleted(void)
{
  printf("\n\033[0mGame completed!!!\n");
#ifdef _WIN32
  Sleep(3000);
#else
  usleep(3000 * 1000);
#endif
  STOPCODE = 0;
  stopGame();
  return 0;
}

unsigned char gameOver(void)
{
  printf("\n\033[0mGame Over!!!\n");
#ifdef _WIN32
  Sleep(3000);
#else
  usleep(3000 * 1000);
#endif
  STOPCODE = 0;
  stopGame();
  return 0;
}


unsigned char stopGame(void)
{
  printf("\033[0m\033[?25h\n");
#ifdef _WIN32
  restoreConsole();
#endif
  STOP = 1;
  return 0;
}