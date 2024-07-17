PUC-Minas
Instituto de Ci�ncias Exatas e Informatica
Curso de Ci�ncia da Computa��o
Algoritmos e estrutura de dados

Pacote de arquivos para uso e descri��o da biblioteca
acess�ria para entradas e sa�das (io) para C/C++.

Itens

- io.h    - para linguagem C
- io.hpp  - para linguagem C++
- io_docs

Instala��o para linguagem C

O arquivo io.h poder� ser copiado e usado na
mesma pasta do programa a ser desenvolvido.

Nesse caso, dever� ser inclu�do no programa
mediante o uso do comando

#include "io.h"

O arquivo tamb�m poder� ser copiado para a 
pasta .../include do compilador.

Nesse caso, dever� ser inclu�do no programa
mediante o uso do comando

#include <io.h>

Essa �ltima forma poder� evitar a exist�ncia
de c�pia adicional em cada nova pasta de programa
a ser criada. � recomendada principalmente para
vers�es est�veis, sem expectativa de mudan�as.


Instala��o para linguagem C++

O arquivo io.hpp poder� ser copiado e usado na
mesma pasta do programa a ser desenvolvido.

Nesse caso, dever� ser inclu�do no programa
mediante o uso do comando

#include "io.hpp"

O arquivo tamb�m poder� ser copiado para a 
pasta .../include do compilador.

Nesse caso, dever� ser inclu�do no programa
mediante o uso do comando

#include <io>

Essa �ltima forma poder� evitar a exist�ncia
de c�pia adicional em cada nova pasta de programa
a ser criada. � recomendada principalmente para
vers�es est�veis, sem expectativa de mudan�as.


Observa��es

Os arquivos com a documenta��o poder�o ser
colocados em qualquer outra pasta de f�cil acesso 
para consulta. Sugere-se a sua leitura pr�via.

A biblioteca ser� recompilada toda a vez
que o programa tamb�m o for.

Favor informar sobre eventuais problemas,
a fim de depurar o recurso em suas vers�es futuras.
