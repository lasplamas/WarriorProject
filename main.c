/*******************************
 * Warrior Machinne!
 * Sistem that generates a php work framework
 * @author Ramiro Guterrez Alaniz
 * @date 25/06/2014
 * @version v1.0
 *******************************
 ********************************/

//Libreries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"
#include "Models.h" 


/***
 * main()
 * method that performs the nucle of the sistem
 ***********************************************/
int main( int argc[], char * argv[] ){

  if( argv[1] != NULL ){
        
    if( !strcmp( argv[1], "new") ){
      if( argv[2] != NULL ){
	create_new_project( argv[2] );
      } else {
	printf("Especify the name of the new project.\n");
      }
    } else if( !strcmp( argv[1], "model" ) ){
      if( argv[2] != NULL ){
	printf( "Creating new model...\n" );
	create_model( argv[2] );
      } else {
	printf( "Especify model name.\n" );
      }
    } else if( !strcmp( argv[1], "controller" ) ){  
      printf("Creating new controller...\n");
    } else if( !strcmp( argv[1], "-h" ) || !strcmp( argv[1], "--help" ) ){
      printf("Help panel.\n");
    } else if( !strcmp( argv[1], "push" ) ){
      //The push command is for the pushing and realizing all de database data to de real db lmL
      printf( "Pushing to db...\n" );
    } else if( !strcmp( argv[1], "module" ) ){
      //If there is an existing module of the framework it downloads it and install it in the framework
      printf( "Downloading new  module...\n" );
    } else if( !strcmp( argv[1], "view" ) ){
      printf( "Creating new view...\n" );
    }

  }else{
    
    printf("Error:  you must enter parametters, see --help or -h for help.\n");
  
  }
  return 0;
}//End of main method
