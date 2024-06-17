// Autor: 999999 - Xxx Yyy Zzz   Versao: 0.1   Data: __ / __ / _____

// Comentario em uma unica linha serve para incluir informacoes

/* 
   Comentario em mais de uma linha
   lista de dependencias externas 
   (nas pastas padroes do compilador)
*/
#include <cstdio>       // c-stdio  compativel
#include <cstdlib>      // c-stdlib compativel

#include <iostream>     // para entrada-e-saida padrao
#include <iomanip>      // para formatos
#include <istream>      // para entrada         em arquivo
#include <ostream>      // para saida           em arquivo
#include <fstream>      // para entrada-e-saida em arquivo
#include <string>       // para tratar cadeias de caracteres

#include "my_lib.hpp"   // definicoes particulares (se na mesma pasta)

// classes

class Pet               // classe primitiva (super-classe)
{
  protected:            // dados compartilhados
  // dados e funcoes membros da classe sao normalmente privados (default).
     std::string name;

  public:
  // definicoes nessa secao serao acessiveis, sem restricoes

  // constructor padrao
     Pet ( );

  // destructor padrao
     virtual ~Pet ( ); // virtual obriga a existencia na classe derivada

  // metodo para dar nome
  // OBS: Obrigatorio o uso do contexto padrao em cabecalho.
     void setName ( const std::string petName );

  // funcao para obter nome
     virtual std::string getName ( ) const;

}; // OBS.: Obrigatorio o uso de ';' na definicao da classe.

// Definicao dos metodos membros da classe em separado
Pet::Pet ( )
{
    std::cout << "Um item individual (Pet) construido.\n";
} // end Pet::constructor ( )

Pet::~Pet ( )
{
    std::cout << "Um item individual (Pet) dispensado.\n";
} // end Pet::destructor ( )

void Pet::setName ( const std::string petName )
{
    name = petName;
} // end Pet::setName ( )

std::string Pet::getName ( ) const
{
    return ( name );
} // end Pet::getName ( )

typedef
 struct s_Filiacao
 {
    std::string pai;
    std::string mae;
 }
Filiacao;

class Dog : Pet          // classe derivada (sub-classe)
{
  public:
  // definicoes nessa secao serao acessiveis, sem restricoes

     Filiacao pais;

  // constructor padrao
     Dog ( );

  // destructor padrao
    ~Dog ( );

  // metodo para dar nome
  // OBS: Obrigatorio o uso do contexto padrao em cabecalho.
     void setName ( const std::string petName );

  // funcao para obter nome
     virtual std::string getName ( ) const;

}; // OBS.: Obrigatorio o uso de ';' na definicao da classe.

// Definicao dos metodos membros da classe em separado
Dog::Dog ( )
{
    std::cout << "Um item individual (Dog) construido.\n";
} // end Dog::constructor ( )

Dog::~Dog ( )
{
//    std::cout << "Um item individual (Dog) dispensado.\n";
} // end Dog::destructor ( )

void Dog::setName ( const std::string petName )
{
    name = petName;
} // end Dog::setName ( )

std::string Dog::getName ( ) const
{
    return ( name );
} // end Dog::getName ( )


using namespace std;    // contexto padrao (NAO E' RECOMENDADO)


// sobrecarga de metodos (overloading)

/*
   Metodo para trocar valores entre dados inteiros.
   @param a - primeiro valor
   @param b - segundo  valor
 */
void swap ( int& a, int& b )
{
 // definir dado local
    int c = a;

    a = b;
    b = c;
} // end swap ( )

/*
   Metodo para trocar valores entre dados reais.
   @param a - primeiro valor
   @param b - segundo  valor
 */
void swap ( double& a, double& b )
{
 // definir dado local
    int c = a;

    a = b;
    b = c;
} // end swap ( )

namespace mylib
{
  template <class T>
  void swap ( T& a, T& b )
  {
    T c = a;

    a   = b;
    b   = c;
  } // end swap ( )

  template <class T>
  T add ( const T a, const T b )
  {
    T c = a+b;

    return ( c );
  } // end adder ( )

  template <class T, int N>
  T scale ( T val )
  {
    return ( val * N );
  } // end scale ( )

  template <class T, class U>
  bool equals ( T a, U b )
  {
    return ( a==b );
  } // end equals ( )
} // end mylib

/*
  Acao principal.
 */
int main ( int argc, char** argv )
{
 // definir dados locais
    bool   b = false;
    char   c = '0';
    char   d = 'A';
    int    x =  0 ;
    int    y = 10 ;
    float  f = 1.2;
    double a = 3.4;
    double g = 5.6;
    string s = "0";
    string z = "X";

 // saida padrao
    cout << "Teste C++\n";
    cout << "XXX YYY ZZZ - 00/00/0000\n";
    cout << endl; // saltar linha

    cout << "Saidas: \n" << endl
         << "b = " << b  << endl
         << "c = " << c  << endl
         << "x = " << x  << endl
         << "a = " << a  << endl
         << "s = " << s  << endl;

 // entrada padrao
    cout << endl << "Entrada de dados: \n\n";
    cout << "logico     : ";
    cin  >> b;
    cout << "caractere  : ";
    cin  >> c;
    cout << "inteiro    : ";
    cin  >> x;
    cout << "real       : ";
    cin  >> a;
    cout << "caracteres : ";
    cin  >> s;

 // saida padrao
    cout << endl << "Saidas: \n"  << endl
         << "b = " << b           << endl
         << "c = " << c           << endl
         << "x = " << x           << endl
         << "f = " << f           << endl
         << "a = " << a           << endl
         << "s = " << s
         << "  ( " << s.length( ) << " )" << endl;

 // saida padrao com formatos
    cout << endl << "Saidas: \n"  << endl
         << "b = " << b << " " << std::boolalpha  << b << endl
         << "c = " << std::setfill ('_') << std::setw (10)    << c << endl
         << "x = " << x << " " << std::oct        << x << " " << std::hex   << x << endl
         << "f = " << f << " " << std::scientific << f << " " << std::fixed << f << endl
         << "a = " << std::setw(10) << std::setprecision(2)   << a << endl
         << "s = " << std::setfill (' ')  <<  std::setw(10)   << std::right << s
         << "  ( " << s.length( ) << " )" << endl;

    for  ( auto c : s )
         cout << endl << "[" << c << "]";
    cout << endl;


    cerr << endl << "ERRO: Para mensagens de erro." << endl;

    cout << endl << "Apertar ENTER para continuar.";
    cin.get ( );
    cin.get ( );

 // trocar valores por meio de procedimento
 // com passagem de parametros de referencia
    cout << "antes : x = " << x  << "\ty = " << y << endl;
    swap ( x, y );
    cout << "depois: x = " << x  << "\ty = " << y << endl;
    cout << endl;
    cout << "antes : a = " << a  << "\tg = " << g << endl;
    swap ( a, g );
    cout << "depois: a = " << a  << "\tg = " << g << endl;
    cout << endl;

 // sobrecargas, generalizacoes, gabaritos e contextos
    cout << endl << "Overloading - templates - namespaces" << endl;
    cout << endl;

 // trocar valores por meio de procedimento
 // com generalizacao (template) e indicacao de contexto
    cout << "antes : c = " << c  << "\td = " << d << endl;
    mylib::swap ( c, d );
    cout << "depois: c = " << c  << "\td = " << d << endl;
    cout << endl;
    cout << "antes : s = " << s  << "\tz = " << z << endl;
    mylib::swap ( c, d );
    cout << "depois: s = " << s  << "\tz = " << z << endl;
    cout << endl;

 // somar valores por meio de funcao
 // com generalizacao (template) e insercao de contexto

    using namespace mylib;   // a partir desse ponto

    cout << x << "+" << y << " = " << add ( x, y ) << endl;
    cout << a << "+" << g << " = " << add ( a, g ) << endl;

    cout << endl;

    cout << x << " * 2 = " << scale<int   ,2> ( x ) << endl;
    cout << a << " * 2 = " << scale<double,2> ( a ) << endl;

    cout << endl;

    cout << " 1 == 1.0 == '1' = "
         << ( equals ( 1, (int) 1.0 ) && equals ( 1.0, (double) ('1')    ) )
         << endl;
    cout << " 1 == 1.0 == '1' = "
         << ( equals ( 1, (int) 1.0 ) && equals ( 1.0, (double) ('1'-48) ) )
         << endl;

    cout << endl;

    cout << endl << "Apertar ENTER para continuar.";
    cin.get ( );
    cin.get ( );

 // arquivos
    cout << endl;
    cout << "Arquivos" << endl;
    cout << endl;

    ofstream afile;      // arquivo para gravar
    afile.open   ( "example_00.txt" );

    afile << "Gravacao em arquivo.\n";
    afile.close  ( );

    fstream bfile;       // arquivo para ler e gravar
    bfile.open   ( "example_00.txt", ios::app );

    bfile << "Outra gravacao em arquivo.\n";
    bfile.close ( );

    ifstream  cfile;     // arquivo para ler
    cfile.open   ( "example_00.txt" );

    do
    {
      cfile >> s;
      cout << "Lido: " << s << endl;
    }
    while ( ! cfile.eof( ) );

    cfile.open  ( "example_00.txt" );
               
    cfile.close ( );

    cout << endl;

    cout << "Tratamento de excecoes" << endl;
    cout << endl;

    bfile.exceptions ( ifstream::badbit ); // nao precisa testar failbit

    try        // regiao critica
    {
//      bfile.open  ( "example_01.txt", ios::in );
      bfile.open  ( "example_00.txt", ios::in );

      while ( getline ( bfile, s ) )
      {
        cout << "Lido: " << s << endl;
      } // end
    }          // captura da excecao
    catch ( const ifstream::failure& e )
    {
      cerr << "ERRO: Excecao ao abrir/ler arquivo.";
    } // end


 // enumeracao
    cout << endl;
    cout << "Enumeracao" << endl;
    cout << endl;
    enum Moeda { um, dois, cinco=5, dez=10 };

    Moeda nota = dez;

    switch ( nota )
    {
      case um   : cout << "nota ( 1) = um   " << endl; break;
      case dois : cout << "nota ( 2) = dois " << endl; break;
      case cinco: cout << "nota ( 5) = cinco" << endl; break;
      case dez  : cout << "nota (10) = dez  " << endl; break;
    }

 // grupos de dados homogeneos
    cout << endl;
    cout << "Grupos de dados homogeneos" << endl;
    cout << endl;

    cout << "String" << endl;

    char carray [ ] = "aeiou";
    s = carray;                                  // converter c-string para string
    cout << "string = " << s           << endl;  // mostrar como string
    cout << "carray = " << s.c_str ( ) << endl;  // mostrar como c-string

    cout << endl;

    int    iarray [ ] = { 1, 2, 3, 4, 5 };
    double darray [ ]   { 0.1, 0.2, 0.3, 0.4, 0.5 };

    cout << "Arranjo" << endl;

    for  ( int x : iarray )
         cout << x << " : " << darray [ x-1 ] << endl;
    cout << endl;

    cout << "Matriz" << endl;

    int    imatrix [ ][2] { {1, 2}, {3, 4} };

    for ( int x = 0; x < 2; x++ )
    {
      for ( int y = 0; y < 2; y++ )
      {
          cout << imatrix [ x ][ y ] << "\t";
      } // end
      cout << endl;
    } // end

    cout << endl;
    cout << "Classe" << endl;
    cout << endl;

 // grupos de dados heterogeneos
    Dog aDog;

 // aDog.name     = "Mat"  ; // nao acessivel por ser protegido
    aDog.setName  ( "Mat" ); //     acessivel via metodo

    aDog.pais.pai = "Rex"  ; // acessivel por ser publico
    aDog.pais.mae = "Lud"  ; // acessivel por ser publico

    cout << endl;
    cout << "Um cao com nome de " << aDog.getName ( ) 
         << " filho de (" << aDog.pais.pai << "," << aDog.pais.mae << ")" << endl;

    cout << endl;

 // encerrar
    cout << endl << "Apertar ENTER para terminar.";
    cin.get ( );
    cin.get ( );
    return ( 0 );
}