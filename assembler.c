#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mem 256

// djb2 hash
int hash(unsigned char *str)
{
  int hash = str[0] * 17 + str[1] * 4 + str[2] * 1849;
  return hash % 10000;
}

// Retorna o operando em binário
char* address(char* str){
  int start = 0;
  for (start = 0; str[start] != ' '; start++);
  start ++;
  str[start+3] = '\0';
  return (char *)(str + start);

}

int main()
{
  // https://www.inf.ufrgs.br/~johann/neander2024/

  FILE *fptr, *saida;
  fptr = fopen("src.txt", "r");
  saida = fopen("out.txt", "w");

  char raw[256] = {};
  char final[256] = {};
  int bytes = 0;
  while (fgets(raw, 256, fptr))
  {
    for (int i = 0; i < 7; i++)
    {
      // Intervalo para letras maiúsculas em ASCII
      if (raw[i] > 40 && raw[i] < 91)
      {
        char key[] = {raw[i], raw[i+1], raw[i+2]};
        bytes++;
        switch(hash(key))
        {
        case 9562: // NOP
          fprintf(saida, "0, ");
          break;

        case 1932: // STA
          fprintf(saida, "16, %s, ", address(raw));
          bytes++;
          break;

        case 1749: // LDA
          fprintf(saida, "32, %s, ", address(raw));
          bytes++;
          break;

        case 7109: // ADD
          fprintf(saida, "48, %s, ", address(raw));
          bytes++;         
          break;

        case 839: // OR
          fprintf(saida, "64, %s, ", address(raw));
          bytes++;
          break;

        case 7149: // AND
          fprintf(saida, "80, %s, ", address(raw));
          bytes++;
          break;

        case 6958: // NOT
          fprintf(saida, "96, ");
          break;

        case 9486: // JMP
          fprintf(saida, "128, %s, ", address(raw));
          bytes++;
          break;

        case 738: // JN
          fprintf(saida, "144, %s, ", address(raw));
          bytes++;
          break;

        case 786: // JZ
          fprintf(saida, "160, %s, ", address(raw));
          bytes++;
          break;

        case 6844: // HLT
          fprintf(saida, "240, ");
          break;
        }
      }
    }
  }

  do {
    fprintf(saida, "0, ");
    bytes++;
    printf("%d\n", bytes);
  } while (bytes < 256);


  printf("%s", final);
  fclose(fptr);
  fclose(saida);

  return 0;
}
