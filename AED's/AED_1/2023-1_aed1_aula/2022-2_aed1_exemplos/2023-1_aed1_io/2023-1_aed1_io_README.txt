PUC-Minas
Instituto de Ciências Exatas e Informatica
Curso de Ciência da Computação
Algoritmos e estrutura de dados

Pacote de arquivos para uso e descrição da biblioteca
acessória para entradas e saídas (io) para C/C++.

Itens

- io.h    - para linguagem C
- io.hpp  - para linguagem C++
- io_docs

Instalação para linguagem C

O arquivo io.h poderá ser copiado e usado na
mesma pasta do programa a ser desenvolvido.

Nesse caso, deverá ser incluído no programa
mediante o uso do comando

#include "io.h"

O arquivo também poderá ser copiado para a 
pasta .../include do compilador.

Nesse caso, deverá ser incluído no programa
mediante o uso do comando

#include <io.h>

Essa última forma poderá evitar a existência
de cópia adicional em cada nova pasta de programa
a ser criada. É recomendada principalmente para
versões estáveis, sem expectativa de mudanças.


Instalação para linguagem C++

O arquivo io.hpp poderá ser copiado e usado na
mesma pasta do programa a ser desenvolvido.

Nesse caso, deverá ser incluído no programa
mediante o uso do comando

#include "io.hpp"

O arquivo também poderá ser copiado para a 
pasta .../include do compilador.

Nesse caso, deverá ser incluído no programa
mediante o uso do comando

#include <io>

Essa última forma poderá evitar a existência
de cópia adicional em cada nova pasta de programa
a ser criada. É recomendada principalmente para
versões estáveis, sem expectativa de mudanças.


Observações

Os arquivos com a documentação poderão ser
colocados em qualquer outra pasta de fácil acesso 
para consulta. Sugere-se a sua leitura prévia.

A biblioteca será recompilada toda a vez
que o programa também o for.

Favor informar sobre eventuais problemas,
a fim de depurar o recurso em suas versões futuras.
