#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM 512

int hash(char *str)
{
  int hash = (str[0] * 3 + str[1] + str[2]) % 100;
  return hash;
}

unsigned char address(char *str, int start){
    int value = atoi(str+start);
    return (char)value;
}

int checarDesvio(char linhas[MAX_MEM], char linha, int max){
    for (int i = 0; i < max; i++){
	if (linhas[i] == linha){
	    return i;
	}
    }
    return -1;
}

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
      case 93: // NOP
        mem[bytes] = 0x00;
        break;

      case 98: // STA
        mem[bytes] = 0x10;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case 61: // LDA
        mem[bytes] = 0x20;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case 31: // ADD
        mem[bytes] = 0x30;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case 51: // OR
        mem[bytes] = 0x40;
        bytes += 2;
        mem[bytes] = address(raw, 3);
        break;

      case 41: // AND
        mem[bytes] = 0x50;
        bytes += 2;
        mem[bytes] = address(raw, 4);
        break;

      case 97: // NOT
        mem[bytes] = 0x60;
        break;

      case 79: // JMP
        mem[bytes] = 0x80;
	desvio[0][quantDesvio] = address(raw, 4); // Linha que o desvio procura
	bytes += 2;
	desvio[1][quantDesvio] = bytes;		  // Endereço para voltar
	quantDesvio++;
        break;

      case 32: // JN
        mem[bytes] = 0x90;
        bytes += 2;
        mem[bytes] = address(raw, 3);
        break;

      case 44: // JZ
        mem[bytes] = 0xA0;
        bytes += 2;
        mem[bytes] = address(raw, 3);
        break;

      case 76: // HLT
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

