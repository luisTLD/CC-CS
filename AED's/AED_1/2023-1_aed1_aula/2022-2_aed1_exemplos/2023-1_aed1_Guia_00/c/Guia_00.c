/*
   Guia_00 - v0.0. - __ / __ / _____
   Author: _________________________

   Para compilar em uma janela de comandos (terminal):

   No Linux  :   gcc -o Guia_00   ./Guia_00.c
   No Windows:   gcc -o Guia_00.exe Guia_00.c
   
   OBS.: O arquivo de definiçoes karel.h devera' estar disponivel
         na pasta include do compilador/usuario.
         A biblioteca libkarel devera' estar disponivel
         na pasta lib do compilador/usuario.

   Para executar em uma janela de comandos (terminal):

   No Linux  :   ./Guia_00.c
   No Windows:     Guia_00

 */
// lista de dependencias
#include "karel.h"

// --------------------------- definicoes de metodos

/**
   decorateWorld - Metodo para preparar o cenario.
   @param fileName - nome do arquivo para guardar a descricao.
 */
void decorateWorld ( char* fileName )
{
 // colocar obstaculos verticais no mundo
    set_World ( 2, 1, VWALL );
    set_World ( 3, 2, VWALL );
    set_World ( 4, 3, VWALL );
    set_World ( 5, 1, VWALL );
    set_World ( 5, 2, VWALL );
    set_World ( 5, 3, VWALL );

 // colocar obstaculos horizontais no mundo
    set_World ( 3, 1, HWALL );
    set_World ( 4, 2, HWALL );
    set_World ( 5, 3, HWALL );

 // colocar marcadores no mundo
    set_World ( 3, 2, BEEPER );
    set_World ( 4, 3, BEEPER );
    set_World ( 5, 4, BEEPER );

 // salvar a configuracao atual do mundo
    save_World( fileName );

} // decorateWorld ( )

/**
  * turnRight - Metodo para virar 'a direita.
  */
  void turnRight( )
  {
   // o executor deste metodo
   // deve virar tres vezes 'a esquerda
      turnLeft( );
      turnLeft( );
      turnLeft( );
  } // end turnRight( )

/**
  * metodo para subir escada.
  */
  void stepUp ( )
  {
   // se estiver voltado para cima,
   // mover-se uma posicao nesse sentido
      move ( );
   // virar 'a direita
      turnRight( );
   // mover-se uma posicao para a direita
      move ( );
   // voltar-se para cima
      turnLeft ( );
   // OBS.: O agente esta' implicito (nao precisa do this),
   //       porque o metodo pode ser executado
   //       por qualquer agente definido por essa classe.
  } // end stepUp ( )

/**
  * tarefa: subir uma escada,
  *         recolher tres marcadores,
  *         desligar-se.
  */
  void doTask ( )
  {
   // avancar uma posicao
      move ( );
   // voltar-se para norte
      turnLeft ( );
   // subir um degrau, segundo o novo metodo definido
      stepUp ( );
   // recolher o primeiro marcador
      pickBeeper ( );
   // subir mais um degrau
      stepUp ( );
   // recolher o segundo marcador
      pickBeeper ( );
   // subir mais um degrau
      stepUp ( );
   // recolher o terceiro marcador
      pickBeeper ( );
  } // end task ( )

// --------------------------- acao principal

/**
  *  Acao principal: executar a tarefa descrita acima.
  */

int main ( )
{
 // definir o contexto atual ( mundo + robo + caixa (opcional) )
    world v_world;  ref_world ref_v_world = ref v_world;  world_now = ref_v_world;
    robot v_robot;  ref_robot ref_v_robot = ref v_robot;  robot_now = ref_v_robot;
    box   v_box  ;  ref_box   ref_v_box   = ref v_box  ;  box_now   = ref_v_box  ;

 // criar o mundo
    create_World ( "Guia_00_v01" );

 // criar o ambiente com um marcador
 // OBS.: executar pelo menos uma vez,
 //       antes de qualquer outra coisa
 //       (depois de criado, podera' ser comentado)
    decorateWorld( "Guia_00.txt" );

 // comandos para tornar o mundo visivel
    reset_World( );		           // limpar configuracoes
    set_Speed  ( 1 );              // escolher velocidade
    read_World ( "Guia_00.txt" );  // ler configuracao do ambiente

 // colocar o robo no necessario
    create_Robot ( 1, 1, EAST, 0, "Karel" );

 // executar acoes
    doTask ( );

 // preparar o encerramento
    close_World ( );

//  encerrar o programa
    getchar ( );
    return ( 0 );
} // end main ( )

// ---------------------------------------------- testes

/*
---------------------------------------------- documentacao complementar

---------------------------------------------- notas / observacoes / comentarios



---------------------------------------------- previsao de testes



---------------------------------------------- historico

Versao	Data		    Modificacao
  0.1	__/__		    esboco

 ---------------------------------------------- testes

Versao	Teste
  0.1	01. ( OK )		identificacao de programa

*/
