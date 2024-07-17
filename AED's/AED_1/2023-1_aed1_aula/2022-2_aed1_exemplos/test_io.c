#include "io.h"

int main ( void )
{
    bool   b   = false;
    char   c   = '$'  ;
    double d   = 1.23 ;
    float  f   = 1.23f;
    int    k   = 123  ;
    char   v [80];
    char  *s   = addr(v[0]);

    strcpy ( v, "abc" );

    IO_debugON  ( );
//  IO_debugOFF ( );

    IO_clrscr  ( );

    IO_println ( IO_concat ("Test_IO - ", IO_version( )) );

    IO_println ( "\nOutputs" );
    IO_printf  ( "\nb = %d = %s", b, IO_boolalpha( b ) );
    IO_printf  ( "\nc = %c"     , c );
    IO_printf  ( "\nd = %lf"    , d );
    IO_printf  ( "\nf = %f "    , f );
    IO_printf  ( "\nk = %i"     , k );
    IO_printf  ( "\nv = %s"     , v );
    IO_printf  ( "\ns = %s"     , s );

    IO_pause   ( "\nApertar ENTER para continuar." );

    IO_print   ( "\nInputs\n" );

    b = IO_readbool   ( "b = " );
    c = IO_readchar   ( "c = " );
    d = IO_readdouble ( "d = " );
    f = IO_readfloat  ( "f = " );
    k = IO_readint    ( "k = " );

    strcpy ( v, IO_readstring ( "v = " ) );
    s = IO_readln ( "s = " );

    IO_println ( "\nOutputs" );
    IO_printf  ( "\nb = %d = %s", b, IO_boolalpha( b ) );
    IO_printf  ( "\nc = %c"     , c );
    IO_printf  ( "\nd = %lf"    , d );
    IO_printf  ( "\nf = %f "    , f );
    IO_printf  ( "\nk = %i"     , k );
    IO_printf  ( "\nv = %s"     , v );
    IO_printf  ( "\ns = %s"     , s );
    IO_println ( "" );

    IO_println ( "\nString handlings\n" );
    IO_println ( IO_concat ("b = " , IO_toString_b ( b ) ) );
    IO_println ( IO_concat ("c = " , IO_toString_c ( c ) ) );
    IO_println ( IO_concat ("d = " , IO_toString_f ( d ) ) );
    IO_println ( IO_concat ("f = " , IO_toString_f ( f ) ) );
    IO_println ( IO_concat ("k = " , IO_toString_d ( k ) ) );
    IO_println ( IO_concat ("v = " ,                 v   ) );
    IO_println ( IO_concat ("s = " ,                 s   ) );

    IO_println ( "\nString inputs\n" );
    strcpy ( v, IO_readstring ( "v = " ) );
    s = IO_readln ( "s = " );
    IO_printf  ( "\nv = [%s]" , v );
    IO_printf  ( "\ns = [%s]" , s );

    IO_pause   ( "\nApertar ENTER para continuar." );

    IO_print   ( "\nDebugging\n" );

    IO_debugON ( );

    b = true;
    IO_debug   ( b, "verdadeiro" );

    k = 2;
    if ( ! IO_check ( &b, &k, sizeof(k) ) )
       IO_printf ( "\n(%d) diferente de (%i)", b, k );

    if ( ! IO_check (  v,  s, strlen(s) ) )
       IO_printf ( "\n\"%s\" diferente de \"%s\"", v, s );

    s = IO_substring ( v, 2, 5 );
    
    IO_printf ( "\n(%s)\n", s );
    
    s = IO_strapp ( v, '!' );

    IO_printf ( "\n(%s)\n", s );

    for ( k=0; k<IO_length(s); k=k+1 )
        IO_printf ( "%c ", IO_charAt (s, k) );
    IO_printf ( "\n" );
    IO_debugOFF ( );

    IO_pause   ( "\nApertar ENTER para terminar.\n" );

    return ( 0 );
}
