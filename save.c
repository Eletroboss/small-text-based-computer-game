unsigned char save(unsigned char x, unsigned char y, unsigned char z);
unsigned char load(unsigned char i);

unsigned char save(unsigned char x, unsigned char y, unsigned char z)
{
  FILE *f = fopen("save.dat", "wb");
  fwrite(&x, 1, 1, f);
  fwrite(&y, 2, 2, f);
  fwrite(&z, 3, 3, f);
  fclose(f);

  printf("\033[0m%d%d%d", x, y, z);

  return 0;
}

unsigned char load(unsigned char i)
{
  unsigned char x;

  FILE *f = fopen("save.dat", "rb");

  fread(&x, i+1, i+1, f);

  fclose(f);

  return x;
}