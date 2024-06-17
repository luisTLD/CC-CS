/**
  * ----------------------------------- Documentacao preliminar
  * Pontificia Universidade Catolica de Minas Gerais
  * Curso de Ciencia da Computacao
  * Algoritmos e Estruturas de Dados I
  *
  * Trabalho pratico: lista 00
  *
  * Objetivo:
  * Modelo de programa para a disciplina AED I
  * Sugestao para montar um trabalho pratico
  *
  * Autor:   Matricula: 999999  Nome: xxx yyy zzz
  * Versao:  1.0                Data: 01/mm/20aa
  *
  * Dados:
  * - opcao de execucao escolhida pelo usuario
  *
  * Resultados:
  * - execucao de um teste de cada vez a escolha do usuario
  *
  * Condicoes:
  * - so' aceitara' as opcoes oferecidas.
  *
  * Arquivos:
  *
  * - lista_00.c
  * - lista_00     ( no Linux   )
  * - lista_00.exe ( no Windows )
  *
  * Forma de compilacao:
  * - acionar o compilador no modo console 
  *   (terminal/janela de comandos):
  *
  *   Linux  : gcc -o ./lista_00     ./lista_00.c
  *   Windows: gcc -o   lista_00.exe   lista_00.c
  *
  * Forma de uso:
  * - acionar o programa   no modo console 
  *   (terminal/janela de comandos):
  *
  *   Linux  :  ./lista_00
  *   Windows:    lista_00
  *
  * Referencias:
  * - Exemplos mostrados em sala de aula
  * - Apostila: Fundamentos de Programacao - Notas de aulas
  *
  */

// ------------------------------------- classes nativas
//                                       ou auxiliares

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// ------------------------------------- definicao de classe

/**
  * Modelo para definir exemplo de um programa.
  * Obs.: E' recomendado ter o nome do programa
  *       sem espacos em branco, acentos ou cedilha.
  */

// ------------------------------------- tratamento de erro


// ------------------------------------- definicao de constantes


// ------------------------------------- definicao de armazenadores globais


// ------------------------------------- definicao de prototipos


// ------------------------------------- definicao de metodos

/**
  * Metodo01.
  */
void metodo01 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo01" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo01 ( )

/**
  * Metodo02.
  */
void metodo02 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo02" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo02 ( )

/**
  * Metodo03.
  */
void metodo03 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo03" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo03 ( )

/**
  * Metodo04.
  */
void metodo04 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo04" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo04 ( )

/**
  * Metodo05.
  */
void metodo05 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo05" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo05 ( )

/**
  * Metodo06.
  */
void metodo06 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo06" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo06 ( )

/**
  * Metodo07.
  */
void metodo07 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo07" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo07 ( )

/**
  * Metodo08.
  */
void metodo08 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo08" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo08 ( )

/**
  * Metodo09.
  */
void metodo09 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo09" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );
} // fim metodo09 ( )

/**
  * Metodo10.
  */
void metodo10 ( void )
{
 // identificar
    printf ( "%s", "\nMetodo10" );
 // encerrar
    printf ( "%s", "\nApertar ENTER para continuar.\n" );
    getchar( );

} // fim metodo10 ( )


// ------------------------------------- definicao do metodo principal

int main ( void )
{
 // definir dados/resultados
    int opcao = 0;

 // repetir ate' desejar parar
    do
    {
     // identificar
        printf ( "\n" );             // para saltar linha
        printf ( "%s\n", "Lista_00 - v.0.0 - 01/mm/20aa"       );
        printf ( "%s\n", "Matricula: 999999 Nome: xxx yyy zzz" );

     // mostrar opcoes
        printf ( "%s\n", "Opcoes:"         );
        printf ( "%s\n", " 0 - parar"      );
        printf ( "%s\n", " 1 - metodo 01   2 - metodo 02" );
        printf ( "%s\n", " 3 - metodo 03   4 - metodo 04" );
        printf ( "%s\n", " 5 - metodo 05   6 - metodo 06" );
        printf ( "%s\n", " 7 - metodo 07   8 - metodo 08" );
        printf ( "%s\n", " 9 - metodo 09  10 - metodo 10" );
        printf ( "%s\n", "" );        // para saltar linha

     // ler opcao
        printf ( "%s", "Qual a sua opcao? " );
        scanf  ( "%d", &opcao ); getchar ( );
        printf ( "%d",  opcao );
        
     // escolher acao
        switch ( opcao )
        {
           case  0:               break;
           case  1: metodo01 ( ); break;
           case  2: metodo02 ( ); break;
           case  3: metodo03 ( ); break;
           case  4: metodo04 ( ); break;
           case  5: metodo05 ( ); break;
           case  6: metodo06 ( ); break;
           case  7: metodo07 ( ); break;
           case  8: metodo08 ( ); break;
           case  9: metodo09 ( ); break;
           case 10: metodo10 ( ); break;
           default:
                printf ( "%s\n", "\nERRO: Opcao invalida.\n" );
              break;
        } // fim escolher
    }
    while ( opcao != 0 );

 // encerrar execucao
    printf ( "%s\n", "\nApertar ENTER para terminar.\n" );
    getchar( );

} // end main ( )


/*
---------------------------------------- documentacao complementar


---------------------------------------- notas / observacoes / comentarios


---------------------------------------- previsao de testes


---------------------------------------- historico

Versao	Data		    Modificacao
  0.1	__/__		    esboco

 --------------------------------------- testes

Versao	Teste
  0.1	01. ( OK )		identificacao de programa

*/
