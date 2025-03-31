#include "neander.h"
#include <stdlib.h>

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
