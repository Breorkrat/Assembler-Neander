#include <stdio.h>
#include "libraries/neander.h"

int main()
{
  // https://www.inf.ufrgs.br/~johann/neander2024/

  FILE *entrada, *saida;
  entrada = fopen("src.txt", "r");
  saida = fopen("out.mem", "w");

  char headers[] = {0x03, 0x4E, 0x44, 0x52};
  char raw[MAX_MEM];
  unsigned char mem[MAX_MEM] = {0};
  unsigned char desvio[2][MAX_MEM] = {0};
  int quantDesvio = 0;
  int bytes = 0;

  for (char linha = 1; fgets(raw, MAX_MEM, entrada); linha ++)
  {
    int temDesvio = checarDesvio(desvio[0], linha, quantDesvio);
    if (temDesvio != -1){
	mem[desvio[1][temDesvio]] = (char) bytes/2; 
    }

    if (raw[0] >= 'A' && raw[0] <= 'Z')
    {
      char key[] = {raw[0], raw[1], raw[2]};
      switch (hash(key))
      {
      case NOP:
        mem[bytes] = 0x00;
        break;

      case STA: 
        mem[bytes] = 0x10;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case LDA: 
        mem[bytes] = 0x20;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case ADD: 
        mem[bytes] = 0x30;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case OR: 
        mem[bytes] = 0x40;
        bytes += 2;
        mem[bytes] = address(raw, 3);
        break;

      case AND: 
        mem[bytes] = 0x50;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case NOT: 
        mem[bytes] = 0x60;
        break;

      case JMP: 
        mem[bytes] = 0x80;
	desvio[0][quantDesvio] = address(raw, 4); // Linha que o desvio procura
	bytes += 2;
	desvio[1][quantDesvio] = bytes;		  // Endereço para voltar
	quantDesvio++;
        break;

      case JN: 
        mem[bytes] = 0x90;
        bytes += 2;
        mem[bytes] = address(raw, 3);
        break;

      case JZ: 
        mem[bytes] = 0xA0;
        bytes += 2;
        mem[bytes] = address(raw, 3);
        break;

      case HLT: 
        mem[bytes] = 0xF0;
        break;
      }
      bytes += 2;
    }

    if (raw[0] == '*') {
      mem[address(raw, 1)*2] = address(raw, 4);
    }
  }


  fwrite(headers, 1, sizeof(headers), saida);
  fwrite(mem, 1, MAX_MEM, saida);

  fclose(entrada);
  fclose(saida);

  return 0;
}

