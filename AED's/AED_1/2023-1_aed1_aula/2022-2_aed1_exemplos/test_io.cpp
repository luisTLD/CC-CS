#include "io.hpp"

int main ( void )
{
    bool   b   = false;
    char   c   = '$'  ;
    double d   = 1.23 ;
    float  f   = 1.23f;
    int    k   = 123  ;
    char   v [80];
    char  *s   = addr(v[0]);
    std::string r = "";

    strcpy ( v, "abc" );
    r = "def";

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
    IO_printf  ( "\nr = %s"     , r.c_str( ) );

    IO_pause   ( "\nApertar ENTER para continuar." );

    IO_print   ( "\nInputs\n" );

    b = IO_readbool   ( "b = " );
    c = IO_readchar   ( "c = " );
    d = IO_readdouble ( "d = " );
    f = IO_readfloat  ( "f = " );
    k = IO_readint    ( "k = " );

    strcpy ( v, IO_readstring ( "v = " ) );
    s = IO_readstring ( "s = " );
    r = IO_readstring ( "r = " );

    IO_println ( "\nOutputs" );
    IO_printf  ( "\nb = %d = %s", b, IO_boolalpha( b ) );
    IO_printf  ( "\nc = %c"     , c );
    IO_printf  ( "\nd = %lf"    , d );
    IO_printf  ( "\nf = %f "    , f );
    IO_printf  ( "\nk = %i"     , k );
    IO_printf  ( "\nv = %s"     , v );
    IO_printf  ( "\ns = %s"     , s );
    IO_printf  ( "\nr = %s"     , r.c_str( ) );
    IO_println ( "" );

    IO_println ( "\nString handlings\n" );
    IO_println ( IO_concat ("b = " , IO_toString ( b ) ) );
    IO_println ( IO_concat ("c = " , IO_toString ( c ) ) );
    IO_println ( IO_concat ("d = " , IO_toString ( d ) ) );
    IO_println ( IO_concat ("f = " , IO_toString ( f ) ) );
    IO_println ( IO_concat ("k = " , IO_toString ( k ) ) );
    IO_println ( IO_concat ("v = " ,               v   ) );
    IO_println ( IO_concat ("s = " ,               s   ) );
    IO_println ( IO_concat ("r = " ,               r   ) );

    IO_println ( "\nString inputs\n" );
    strcpy ( v, IO_readln ( "v = " ) );
    s = IO_readln ( "s = " );
    r = IO_readln ( "r = " );
    IO_printf  ( "\nv = [%s]" , v );
    IO_printf  ( "\ns = [%s]" , s );
    IO_printf  ( "\nr = [%s]" , r.c_str( ) );

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
    IO_printf ( "\n" );

    strcpy ( v, "abcdefghijk" );
    s = IO_substring ( v, 2, 5 );
    IO_printf ( "\n(%s)\n", s );

    r = "abcdefghijk";
    s =  IO_substring ( (char*) r.c_str( ), 2, 5 );
    IO_printf ( "\n(%s)\n", s );

    r = "abcdefghijk";
    s = (char*) (r.substr( 2, 5 )).c_str( );
    IO_printf ( "\n(%s)\n", s );
    IO_printf ( "\n" );

    for ( k=0; k<IO_length(s); k=k+1 )
        IO_printf ( "%c ", IO_charAt (s, k) );
    IO_printf ( "\n" );
    IO_debugOFF ( );

    IO_pause   ( "\nApertar ENTER para terminar.\n" );

    return ( 0 );
}
