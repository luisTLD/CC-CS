// Autor: 999999 - Xxx Yyy Zzz     Versao: 0.1     Data: __ / __ / _____

// Comentario em uma unica linha serve para incluir informacoes

// lista de dependencias externas (nas pastas padroes do compilaador)

#include <stdio.h>     // para entradas e saida
#include <stddef.h>    // para definicoes basicas
#include <stdlib.h>    // para a biblioteca padrao
#include <string.h>    // para cadeias de caracteres
#include <stdarg.h>    // para tratar argumentos
#include <stdbool.h>   // para definicoes logicas
#include <ctype.h>     // para tipos padroes
#include <math.h>      // para definicoes matematicas
#include <time.h>      // para medir tempo

#include "my_lib.h"    // definicoes particulares (se na mesma pasta)

/*
   Comentarios em varias linhas servem para dar maiores detalhes.
   Se os arquivos estiverem na mesma pasta, usar
   no Windows (execucao em terminal (cmd)):
   para compilar: gcc -o 2019-1_aed1_Exemplo_00.exe 2019-1_aed1_Exemplo_00.c
   para executar: 20xx-1_aed1_Exemplo_00.
   no Linux (execucao em terminal (shell)):
   para compilar: gcc -o 2019-1_aed1_Exemplo_00     2019-1_aed1_Exemplo_00.c
   para executar: ./20xx-1_aed1_Exemplo_00.
*/

/**
   Comentarios para documentacao automatica (Dox_) precedem
   as descricoes dados e acoes.
*/

/** uma funcao e' um metodo para se obter valor de certo tipo (String) */
    char* mudarLinha ( )                          // <- parenteses servem para indicar acoes
    {                                             //    que podem conter parametros, ou nao
     // obter o codigo dependente do sistema operacional
        return ( "\n" );                          // <- o retorno e' obrigatorio em funcoes
    } // fim da funcao ( )

/** um procedimento (void) e' um metodo para definir outros dados e/ou acoes particulares
   (incluindo usos de outros metodos), para usos futuros. */
    void identificar ( )
    {                                             // <- bloco { } serve para agrupar definicoes
     // exibir mensagem na saida padrao(console)
        printf ( "AED1 v0.1 - " );                // saida nao formatada
     // exibir mensagens sem mudar de linha
        printf ( "%s", "PUC-Minas" );             // saida formatada (%s = formato para caracteres)
        printf ( "%s", " - " );
        printf ( "%s", "ICEI" );
     // mudar de linha
        printf   ( mudarLinha( ) );               // <- uso do retorno da funcao
    } // fim do metodo ( )

/** prototipo de metodo (antecipar definicao para uso (assinatura))  */
     void pause ( );

/** para ser executavel devera' haver uma acao principal (main) como ponto de partida. */
    int main ( int argc, char* argv [ ] )         // <- parametros opcionais, neste caso
    {
     // usar metodo estatico definido acima neste arquivo
        identificar ( );                          // <- chamada (uso) de procedimento
     // saltar linha (forma alternativa)
        printf ( "\n" );

     // ----------------------------------------- //    acoes
     // exibir mensagens e constantes
        printf ( "%s", "-> Valores imutaveis (constantes)\n" );
        printf
        (
          "%s %d %c %s %c %c%s %lf %s %s %i %s",
          "boolean: ", true , '\t' ,   /* caractere para tabulacao  (TAB) */
          "char   : ", 'a'  , '\n' ,   /* caractere para mudanca de linha */
          "double : ", 3.14 , "\t" ,   /* string    para tabulacao        */
          "integer: ", 10   , "\n"     /* string    para mudanca de linha */
        );

     // tipos primitivos e armazenadores de dados (variaveis)
	 // OBS.; Os nomes devem comecar por letras (sem acentos, cedilha ou caracteres especiais)

     // short   - inteiro de 16 bits com sinal em complemento de dois
     // (-32,768 <= short <= 32767)
        short aShort = 10000;

     // int     - inteiro de 32 bits com sinal em complemento de dois
     // (-2147483648 <= int <= 2147483647)
        int    aInt = 1;

     // long    - inteiro de 64 bits com sinal em complemento de dois
     // (-9223372036854775808 <= long <= 9223372036854775807)
        long   aLong = 100000L;           // usar a letra 'L' e' obrigadorio

     // float   - real de precisao simples,
     //           em ponto flutuante 32-bits no padrão IEEE 754
        float  aFloat = 234.5f;           // usar a letra 'f' e' obrigatorio

     // double  - real de precisao dupla,
     //           em ponto flutuante 64-bits no padrão IEEE 754
        double aDouble       =  123.4,    //                      -2
               anotherDouble = -1.234e-2; // o mesmo que -1.234x10

     // boolean - valores logicos (false, true)
        bool   aBoolean       = false;
        bool   anotherBoolean = true;

     // char    - caractere Unicode (simbolo) de 16 bits
        char   aChar = 'A';               // usar apostrofos e' obrigatorio

     // usar final para tornar uma definicao imutavel.
        const  double pi = 3.141592;      //  menos preciso que em <math.h>

        printf ( "\n" );
        printf ( "%s\n", "-> Valores mutaveis (variaveis)"
                         " (tipo, tamanho em bytes, endereco, valor)" );
        printf ( "%s (%d) [%p]: %d  \n" , "short  ", sizeof(short) , &aShort  , aShort   );
        printf ( "%s (%d) [%p]: %i  \n" , "int    ", sizeof(int)   , &aInt    , aInt     );
        printf ( "%s (%d) [%p]: %f  \n" , "float  ", sizeof(float) , &aFloat  , aFloat   );
        printf ( "%s (%d) [%p]: %lf \n" , "double ", sizeof(double), &aDouble , aDouble  );
        printf ( "%s (%d) [%p]: %d  \n" , "bool   ", sizeof(bool)  , &aBoolean, aBoolean );

     // String  - armazenador para grupos de simbolos (cadeias de caracteres)
        char* aNullString   = NULL; // dado inexistente, nao tem tamanho
        char* anEmptyString = "";   // dado vazio      , tamanho = 0
        char* aString       = "Exemplo de cadeia de caracteres";

        char* twoLineString = "Exemplo \n com mudanca de linha\n"; // '\n' = mudar de linha
        char* tabbedString  = "Exemplo \t com tabulacao\n";        // '\t' = tabular

        printf ( "\n" );
        printf ( "%s\n", "-> Cadeias de caracteres" );
        printf ( "%s\n", aNullString   );
        printf ( "%s%s%s%s%d\n",
		         "\"", anEmptyString, "\"",
		         "\n tem tamanho = ", strlen ( anEmptyString ) );
        printf ( "%s%s%d%s%c%s%d\n",
		         aString,
                 "\n tem tamanho = ", strlen ( aString ),
                 "\n o primeiro caractere e' ", aString[0],
                 "\n o ultimo   caractere e' ", aString[strlen(aString)-1]
               );
        printf ( twoLineString );
        printf ( tabbedString  );

     // Arranjos = grupos de dados homogeneos
     //            cujo tamanho precisara' ser determinado
        bool    booleanArray [  ] = { };            // grupo ainda inexistente
        char    charArray    [ 1] = { '0' };        // grupo para  1 item
        double  doubleArray  [ 1];                  // grupo para  1 item, sem valor
        int     intArray     [10];                  // grupo para 10 itens
        char*   stringArray  [ 2];                  // grupo para  2 itens

     // forma alternativa para definir e dar valores ao arranjo
        bool    boolArray    [ ]  = { false, true };

        printf ( "%s", "\n-> Arranjos\n" );

     // acesso ao primeiro elemento em arranjo
        printf ( "boolArray na posicao [0]: %d\n", boolArray[0] );

     // acesso ao primeiro elemento em arranjo
        intArray [0] = 1;
        printf ( "intArray na posicao  [0]: %d\n", intArray [0] ); // => 1
     // acesso ao ultimo   elemento em arranjo
        printf ( "intArray na posicao  [9]: %d\n", intArray [9] ); // => 0

    	pause ( );

     // Operadores
        printf ( "\n-> Operadores\n" );

        int x1 = 1, x2 = 2; // definir dados com valores iniciais

     // expressoes aritmeticas basicas (e saida formatada)
        printf ( "1+2  = %d\n"   , (x1 + x2) ); // => 3
        printf ( "2-1  = %d\n"   , (x2 - x1) ); // => 1
        printf ( "2*1  = %d\n"   , (x2 * x1) ); // => 2
        printf ( "1/2  = %d\n"   , (x1 / x2) ); // => 0 (truncado para baixo)
        printf ( "1/2  = %5.2f\n", ((double) x1 / x2) ); // => 0.50
        printf ( "1/2  = %5.2f\n", (  1.0 * x1  / x2) ); // => 0.50 (alternativo)

     // resto inteiro da divisao (modulo)
        printf ( "10%%2 = %d\n" , (10 % 2) );   // => 0 (  par)
        printf ( "11%%2 = %d\n" , (11 % 2) );   // => 1 (impar)

     // comparacoes (expressoes relacionais)
        printf ( "3 == 2 ? %d\n", (3 == 2) );   // => false
        printf ( "3 != 2 ? %d\n", (3 != 2) );   // => true
        printf ( "3 >  2 ? %d\n", (3 >  2) );   // => true
        printf ( "3 <  2 ? %d\n", (3 <  2) );   // => false
        printf ( "2 <= 2 ? %d\n", (2 <= 2) );   // => true
        printf ( "2 >= 2 ? %d\n", (2 >= 2) );   // => true

     // Estruturas de Controle
        printf ( "\n-> Estruturas de Controle\n" );

     // alternativas (testes)
        int y = 10;
        printf   ( "\n->Teste\n" );
        if ( y == 10 )
        {
            printf ( "se verdadeiro, sera' exibido\n" );
        }
        else if ( y > 10 )
        {
            printf ( "maior, nao sera' exibido\n" );
        }
        else
        {
            printf ( "menor, tambem nao sera' exibido\n" );
        } // fim do bloco da alternativa

     // alternativa multipla
     //    com tipos de dados primitivos: bool, short, char e int
     // ou com tipos enumerados (Enum)
        int month = 2;
        char* monthString;
        switch ( month )
        {
            case 1:
                    monthString = "Janeiro";
                    break; // indispensavel
            case 2:
                    monthString = "Fevereiro";
                    break; // indispensavel
            case 3:
                    monthString = "Marco";
                    break; // indispensavel
            default:       // nenhuma das opcoes anteriores (opcional)
                    monthString = "Algum outro mes";
                    break; //   dispensavel
        } // fim do bloco da alternativa multipla
        printf ( "apos a alternativa multipla  : %s\n", monthString);

     // atribuicao condicional (alternativa em forma abreviada)
        int    aValue = 9;
        char   aStringValue [2];
	       aStringValue [0] = (aValue >= 10) ? 'X' : ((char)(aValue+48));
        aStringValue [1] = '\0';                   // INDISPENSAVEL terminar a sequencia
        printf ( "apos a atribuicao condicional: %d%s%s\n", aValue," = ", aStringValue );

        printf ( "\n->Repeticao\n" );

     // repeticao (loop) com teste no fim
        int controlDoWhile = 0;                    // iniciar
        do
        {
           printf ( "%s%d", " ",controlDoWhile );  // mostrar
           controlDoWhile = controlDoWhile+1;      // passar ao proximo
        }
        while ( controlDoWhile < 5 );              // testar
        printf ( " e apos a repeticao: %d\n", controlDoWhile);

     // repeticao (loop) com teste no inicio
        int controlWhile = 0;                      // iniciar
        while ( controlWhile < 5 )                 // testar
        {
           printf ( "%s%d", " ", controlWhile );   // mostrar
           controlWhile = controlWhile+1;          // passar ao proximo
        } // fim do bloco da repeticao
        printf ( " e apos a repeticao: %d\n", controlWhile );

     // repeticao (loop) com teste no inicio e variacao
        int controlFor;  // iniciar, testar e passar ao proximo (juntos)
        for ( controlFor=0; controlFor<5; controlFor=controlFor+1 )
        { //  iniciar       testar        passar ao proximo
          printf ( "%s%d", " ", controlFor );
        } // fim do bloco da repeticao
        printf ( " e apos a repeticao: %d\n\n", controlFor );

        pause ();

     // repeticao (loop) para todos os valores em grupos homogeneos ou arranjos
        printf ( "\n->Grupos de dados homogeneos\n" );

        int index;

        typedef char* String;        // definir tipo equivalente
        String  s = "palavra";
        printf ( "\n->String = cadeia de caracteres\n\n" );
        printf ( "%s\n", s );
        char*   base_Char = &(s[0]); // definir o endereco no primeiro elemento
        char*   p_Char = base_Char;  // apontar para o primeiro elemento
        for( index = 0; index<strlen( s ); index=index+1 )
        {
         // acessar posicao indexada ou dereferenciar o apontamento (achar o valor)
            printf ( "%c\'%c\' = \'%c' = \'%c'", '\n',
                      s [ index ], *(base_Char+index), *p_Char );
            p_Char = p_Char+1; // avancar apontador para o proximo
        } // fim do bloco da repeticao
        printf ( "\n" );

        int intList [ ] = { 1,2,3,4,5 };
        printf ( "\n->Arranjo unidimensional\n" );
        for( index = 0; index<5; index=index+1 )
        {
           printf ( "%c\t%d", '\n', intList [ index ] );
        } // fim do bloco da repeticao
        printf ( "\n" );

        int intMatrix [ ][3] = { {1,2,3},
                                 {4,5,6},
                                 {7,8,9} };
        int line, column;
        printf ( "\n->Arranjo bidimensional\n\n" );
        for ( line = 0; line<3; line=line+1 )
        {
           for ( column = 0; column<3; column=column+1 )
           {
               printf ( "%s%d", "\t", intMatrix [ line ][ column ] );
           }
           printf ( "\n" );
        } // fim do bloco da repeticao
        printf ( "\n" );

        pause ();

     // repeticao (loop) para dados em arquivos
        printf ( "\n->Arquivos\n" );

     // definir variavel para manipular arquivo
        FILE* arquivo;

     // abrir arquivo para leitura de texto
        arquivo = fopen ( "my_lib.h", "rt" );

     // ler arquivo
        const int LINE_LENGTH = 80;
        char linha [LINE_LENGTH+1];
        int  contador = 0;
        fgets ( linha, LINE_LENGTH, arquivo );
        while ( ! feof ( arquivo ) )
        {
	       puts ( linha );
           contador = contador + 1;
           fgets( linha, LINE_LENGTH, arquivo );
        }
	    fclose ( arquivo );  // RECOMENDAVEL fechar arquivo na leitura

        pause ( );

     // repeticao (loop) para dados em grupos heterogeneos
        printf ( "\n->Grupos heterogeneos\n\n" );

        struct s_reader                     // definir estrutura de dados
        {
           int   length;
           char* lines [20];
        };

        typedef struct s_reader ReaderType; // definir tipo equivalente

        ReaderType reader;                  // definir dado do tipo estrutural

        reader.length = 20;
     // reabrir abrir arquivo para leitura de texto
        arquivo = fopen ( "my_lib.h", "rt" );
        for ( index = 0; index < reader.length; index=index+1 )
        {                                   // ler uma linha de cada vez
            fgets ( linha, LINE_LENGTH, arquivo );
                                            // reservar espaco para guardar dados
            reader.lines [ index ] = (char*) malloc ( LINE_LENGTH * sizeof(char) );
                                            // copiar da linha para a estrutura
		    strcpy ( reader.lines [ index ], linha );
        }
        fclose ( arquivo );

        typedef ReaderType* ref_ReaderType; // definir tipo apontador para estrutura
        ref_ReaderType p_Reader = &reader;  // apontar para estrutura ja' existente

     // abrir arquivo para gravacao de texto
        arquivo = fopen ( "reverse.txt", "wt" );
        for ( index = p_Reader->length-1; index>=0; index=index-1 )
        {                                   // gravar uma linha de cada vez
            fputs ( p_Reader->lines [ index ], arquivo );
        }
        fclose ( arquivo ); // INDISPENSAVEL fechar na gravacao

     // reabrir abrir arquivo para leitura de texto
        arquivo = fopen ( "reverse.txt", "rt" );
        fgets ( linha, LINE_LENGTH, arquivo );
        contador = 0;
        while ( ! feof ( arquivo ) )       // repetir enquanto nao for o fim do arquivo
        {
           contador = contador + 1;
           printf ( "%d%s", contador, linha );
           fgets( linha, LINE_LENGTH, arquivo );
         }
         fclose ( arquivo );

     // pausa para terminar
        getchar( );
        return ( 0 ); // saida sem erros (retorno ao sistema operacional)
    } // fim do metodo main ( )

/** implementacao tardia do prototipo */
    void pause ( )
    {
	printf ( "Apertar ENTER para continuar" );
	getchar( );
    } // fim pause ( );

// fim do exemplo AED1
