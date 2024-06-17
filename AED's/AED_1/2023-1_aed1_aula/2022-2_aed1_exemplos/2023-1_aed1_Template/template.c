/**
  Program v0.0
  @author
  @version
  @date
*/

// lista de dependencias
#include <stdio.h>     // para entradas e saida
#include <stdlib.h>    // para a biblioteca padrao
#include <stdbool.h>   // para definicoes logicas
#include <string.h>    // para cadeias de caracteres
#include <math.h>      // para definicoes matematicas

#include <stdarg.h>    // para tratar argumentos
#include <stddef.h>    // para definicoes basicas
#include <ctype.h>     // para tipos padroes
#include <time.h>      // para medir tempo

/**
  Acao principal.
*/
int main ( )
{
 // definir dados/resultados

 // identificar
    printf ( "Programa - versao 0.0 - 20xx\n" );
    printf ( "999999 - XXX\n" );
    printf ( "\n" );

 // acoes

 // encerrar
    printf ( "\nApertar ENTER para terminar.\n" );
    getchar( );
    return ( 0 );
} // fim main ( )

/*

// Function: ...
int function (int parameter)
{
  int result = 0;
  //
  return ( result );
}

// Procedure: ...
void procedure ( )
{
  //
}

// Data: ...
char   c = '0'; //

double d = 0.0; //

float  f = 0.0; //

int    x =  0 ; //

char s[80];     //

struct st_data { int a, double b };

st_data   sd;
sd.a       = 0; sd.b       = 0.0;

st_data *psd = malloc ( 1*sizeof(st_data) );
(*psd).a = 0; (*psd).b = 0.0;

// Test: ...
if ( 1 )
{
  ; //
}

if ( 0 )
{
  ; //
}
else
{
  ; //
}

switch ( 0 )
{
  case 0:
    ; //
   break;
  default:
    ; //
}

// Loop: ...
while ( 1 )
{
  ; //
}

do
{
  ; //
}
while ( 1 );

for (x=0; x<1; x=x+1)
{
  ; //
}

// Input: ...
scanf ("%c" , &c);

scanf ("%lf", &d);

scanf ("%f" , &f);

scanf ("%d" , &x);

scanf ("%s" ,  s);

// Output: ...
printf ("\n");

printf ("c=%c \n", c);

printf ("d=%lf\n", d);

printf ("f=%f \n", f);

printf ("x=%d \n", x);

printf ("s=%s \n", s);

// Files: ...
FILE* afile ( "INPUT.TXT"  , "rt" );

FILE* afile ( "OUTPUT.TXT" , "wt" );

// File input:
fscanf ("%c" , &c);

fscanf ("%lf", &d);

fscanf ("%f" , &f);

fscanf ("%d" , &x);

fscanf ("%s" ,  s);

// File output: ...
fprintf (afile,"\n");

fprintf (afile,"c=%c \n", c);

fprintf (afile,"d=%lf\n", d);

fprintf (afile,"f=%f \n", f);

fprintf (afile,"x=%d \n", x);

fprintf (afile,"s=%s \n", s);

// Other
while (! feof (afile))
{ }

fclose (afile);

*/
