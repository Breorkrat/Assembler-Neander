# Assembler Neander

Um assembler para o computador [Neander](https://www.inf.ufrgs.br/arq/wiki/doku.php?id=neander).
Este repositório foi criado apenas como um exercício próprio.  
[Download](https://www.inf.ufrgs.br/arq/wiki/lib/exe/fetch.php?media=wneander.zip) (Windows)  
[Online](https://www.inf.ufrgs.br/~johann/neander2024/)

## Como usar?

* Clone o repositório e execute `make` para compilar o programa;    
* Escreva o pseudocódigo no arquivo `src.txt`, e então, execute o programa`main`, isso irá gerar o arquivo `out.mem` que contém as instruções para que o computador leia;
* Agora, basta importar o arquivo out.mem no simulador Neander 

## Conjunto de instruções
| Código | Instrução | Operação|
|--------|-----------|---------|
|  0000  |	  NOP	 |Nenhuma operação|
|  0001	 |  STA end	 |Armazena acumulador no endereço “end” da memória|
|  0010	 |  LDA end	 |Carrega o acumulador com o conteúdo do endereço “end” da memória|
|  0011	 |  ADD end	 |Soma o conteúdo do endereço “end” da memória ao acumulador|
|  0100	 |  OR end	 |Efetua operação lógica “OU” do conteúdo do endereço “end” da memória ao acumulador|
|  0101	 |  AND end	 |Efetua operação lógica “E” do conteúdo do endereço “end” da memória ao acumulador|
|  0110	 |    NOT    |Inverte todos os bits do acumulador|
|  1000	 |  JMP end	 |Desvio incondicional para o endereço “end” da memória|
|  1001	 |  JN end	 |Desvio condicional, se “N=1”, para o endereço “end” da memória|
|  1010	 |  JZ end	 |Desvio condicional, se “Z=1”, para o endereço “end” da memória|
|  1111	 |    HLT	 |Para o ciclo de busca-decodificação-execução|

* ### Pode se definir valores em endereços específicos de memória usando `*{end} {valor}`, como por exemplo, `*128 45` coloca o valor 45 no endereço 128 de memória
