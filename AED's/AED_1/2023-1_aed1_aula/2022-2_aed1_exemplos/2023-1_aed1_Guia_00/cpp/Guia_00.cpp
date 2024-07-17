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
// dependencies
#include "karel.hpp"

// --------------------------- methods section

/**
   Put objects in the world.
 */
void decorateWorld ( const char* fileName )
{
 // create wall
    world->set (  5,  1, VWALL  );
    world->set (  5,  2, VWALL  );
    world->set (  5,  3, VWALL  );

 // create stair
    world->set (  2,  1, VWALL  );
    world->set (  3,  1, HWALL  );
    world->set (  3,  2, VWALL  );
    world->set (  4,  2, HWALL  );
    world->set (  4,  3, VWALL  );
    world->set (  5,  3, HWALL  );

 // put beepers
    world->set (  3,  2, BEEPER );
    world->set (  4,  3, BEEPER );
    world->set (  5,  4, BEEPER );

 // save world
    world->save( fileName );

} // decorateWorld ( )

class MyRobot : public Robot
{
  public:

  /**
     Turn robot direction to right.
   */
     void turnRight ( )
     {
      // test if robot is active
         if ( checkStatus ( ) )
         {
            turnLeft ( );
            turnLeft ( );
            turnLeft ( );
         } // end if
     } // end turnRight ( )

  /**
     stepUp - Climb one step at a time (sub-action).
   */
     void stepUp ( )
     {
        turnLeft ( );
        move ( );
        turnRight ( );
        move ( );
     } // end stepUp ( )

  /**
     doTask - Script robot actions to be executed.
   */
     void doTask ( )
     {
      // prepare
         move ( );

      // execute
         stepUp ( );
         pickBeeper ( );
         stepUp ( );
         pickBeeper ( );
         stepUp ( );
         pickBeeper ( );

      // stop
         turnOff ( );
     } // end doTask ( )

}; // end class MyRobot

// --------------------------- main action

int main ( )
{
 // define context
    MyRobot *robot = new MyRobot( );

 // set the stage and decorate with objects

    world->create ( "" );
    decorateWorld ( "Guia_00.txt" );
    world->show   ( );

    world->reset  ( );
    world->read   ( "Guia_00.txt" );
    world->show   ( );

    set_Speed  ( 3 );

 // put robot on the stage
    robot->create  ( 1, 1, EAST, 0, "Karel" );

 // execute action
    robot->doTask ( );

 // world shutdown
    world->close ( );

//  program shutdown
    getchar ( );
    return ( 0 );
} // end main ( )