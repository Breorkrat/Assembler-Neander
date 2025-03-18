#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mem 512

int hash(unsigned char *str)
{
  int hash = (str[0] * 3 + str[1] + str[2]) % 100;
  return hash;
}

// Skip indica onde o endereço começa, 3 para funções como JZ e 4 para STA...
unsigned char address(char *str, char skip)
{
  unsigned char valor;

  sscanf(str + skip, "%hhx", &valor);
  return valor;
}

int main()
{
  // https://www.inf.ufrgs.br/~johann/neander2024/

  FILE *fptr, *saida;
  fptr = fopen("src.txt", "r");
  saida = fopen("out.mem", "w");

  char raw[256] = {};

  // Primeiros bytes de um arquivo de memória criado pelo próprio neander, acredito que sejam
  // Headers com informações sobre como mostrar as informações.
  unsigned char final[mem] = {0x03, 0x4E, 0x44, 0x52};
  int bytes = 4;
  while (fgets(raw, mem, fptr))
  {
    if (raw[0] > 'A' && raw[0] < 'Z')
    {
      char key[] = {raw[0], raw[1], raw[2]};

      switch (hash(key))
      {
      case 93: // NOP
        final[bytes] = 0x00;
        bytes+=2;
        break;

      case 98: // STA
        final[bytes] = 0x10;
        final[bytes + 2] = address(raw, 4);
        bytes += 4;
        break;

      case 61: // LDA
        final[bytes] = 0x20;
        final[bytes + 2] = address(raw, 4);
        bytes += 4;
        break;

      case 31: // ADD
        final[bytes] = 0x30;
        final[bytes + 2] = address(raw, 4);
        bytes += 4;
        break;

      case 51: // OR
        final[bytes] = 0x40;
        final[bytes + 2] = address(raw, 3);
        bytes += 4;
        break;

      case 41: // AND
        final[bytes] = 0x50;
        final[bytes + 2] = address(raw, 4);
        bytes += 4;
        break;

      case 97: // NOT
        final[bytes] = 0x60;
        bytes+=2;
        break;

      case 79: // JMP
        final[bytes] = 0x80;
        final[bytes + 2] = address(raw, 4);
        bytes += 4;
        break;

      case 32: // JN
        final[bytes] = 0x90;
        final[bytes + 2] = address(raw, 3);
        bytes += 4;
        break;

      case 44: // JZ
        final[bytes] = 0xA0;
        final[bytes + 2] = address(raw, 3);
        bytes += 4;
        break;

      case 76: // HLT
        final[bytes] = 0xF0;
        bytes+=2;
        break;
      }
    }

    if (raw[0] == '*') {
      final[address(raw, 1)*2+4] = address(raw, 3);
    }
  }

  for (int i = 0; i < mem; i++)
  {
    printf("%#04X  ", final[i]);
  }
  printf("\n");

  fwrite(final, 1, mem, saida);


  fclose(fptr);
  fclose(saida);

  return 0;
}

