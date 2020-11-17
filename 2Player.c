#include <stdio.h>
#include <stdlib.h>

char *get2pPos()
{
  FILE *f = fopen("2p.io", "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

  char *x = malloc(fsize + 1);
  fread(x, 1, fsize, f);
  fclose(f);

  x[fsize] = 0;

  return x;
}
int send1pPos(int x, int y)
{
  FILE *f = fopen("1p.io", "wb");
  fwrite(&x, 1, 1, f);
  fwrite(&y, 2, 2, f);
  fclose(f);
  
  return 0;
}