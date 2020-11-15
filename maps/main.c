#include <stdio.h>
#include <stdlib.h>

char basemap(int x,int y)
{
  FILE *f = fopen("basemap.dat", "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

  char *basemapString = malloc(fsize + 1);
  fread(basemapString, 1, fsize, f);
  fclose(f);

  basemapString[fsize] = 0;

  return basemapString[x*64+y];
}

char colmap(int x,int y)
{
  FILE *f = fopen("colmap.dat", "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

  char *colmapString = malloc(fsize + 1);
  fread(colmapString, 1, fsize, f);
  fclose(f);

  colmapString[fsize] = 0;

  return colmapString[x*64+y];
}
/* for testing
int main()
{
  int x = basemap(0, 3);
  printf("%c", x);

  return 0;
}
*/