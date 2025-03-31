#define MAX_MEM 512

enum {
    NOP = 93,
    STA = 98,
    LDA = 61,
    ADD = 31,
    OR = 51,
    AND = 41,
    NOT = 97,
    JMP = 79,
    JN = 32,
    JZ = 44,
    HLT = 76,
};

// Faz um hashing de uma string de três letras
int hash(char*);

// Recebe uma instrução e devolve o endereço no qual a instrução procura
unsigned char address(char *str, int start);

// Recebe um array de números de linhas que tenham desvios, a linha atual da procura e a quantidade de desvios no array de linhas, e retorna o índice no qual esse array possui um desvio que aponta para a linha atual;
// Caso não seja encontrado um desvio para a linha atual, retorna -1
int checarDesvio(char*, char, int);
