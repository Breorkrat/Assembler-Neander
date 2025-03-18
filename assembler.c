#include <stdio.h>
#include <stdlib.h>

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

unsigned char temDesvio(unsigned char desvio[mem], char linha){
  for (int i = 0; i < mem; i++) {
    if (desvio[i] == linha) {
      printf("Desvio para linha %d encontrado na linha %d, endereço %X\n", desvio[i], linha, i);
      return i;
    }
  }
  return 0;
}

int main()
{
  // https://www.inf.ufrgs.br/~johann/neander2024/

  FILE *entrada, *saida;
  entrada = fopen("src.txt", "r");
  saida = fopen("out.mem", "w");

  char raw[mem] = {};
  unsigned char final[mem] = {0x03, 0x4E, 0x44, 0x52};
  unsigned char desvio[mem] = {0};


  int bytes = 4;
  for (char linha = 1; fgets(raw, mem, entrada); linha ++)
  {
    //printf("Escrevendo no byte %X\n", bytes);
    unsigned char posDesvio = temDesvio(desvio, linha);
    if(posDesvio != 0) {
      final[posDesvio] = bytes;
      //printf("Final[%X] vai para %X\n", posDesvio, bytes);
      //printf("Desvio: %X, Destino: %X", posDesvio, posDesvio-bytes);

    }
    // Intervalo para letras maiúsculas em ASCII
    if (raw[0] >= 'A' && raw[0] <= 'Z')
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

        desvio[bytes] = 0x80;
        desvio[bytes+2] = address(raw, 4);
        //printf("JMP para %X\n", desvio[bytes+3]);

        bytes += 4;
        break;

      case 32: // JN
        final[bytes] = 0x90;
        final[bytes + 2] = address(raw, 3);

        //desvio[bytes+2][0] = bytes+2;
        //desvio[bytes + 2][1] = address(raw, 4);
        //printf("PosDesvio: %X, para %X\n", bytes+2, desvio[bytes+2][1]);

        bytes += 4;
        break;

      case 44: // JZ
        final[bytes] = 0xA0;
        final[bytes + 2] = address(raw, 3);

        //desvio[bytes+2][0] = bytes+2;
        //desvio[bytes + 2][1] = address(raw, 4);
        //printf("PosDesvio: %X, para %X\n", bytes+2, desvio[bytes+2][1]);

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


  fwrite(final, 1, mem, saida);


  fclose(entrada);
  fclose(saida);

  return 0;
}

