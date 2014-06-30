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
	create_model( argv[2] );
      } else {
	printf( "Especify models name.\n" );
      }
    } else if( !strcmp( argv[1], "controller" ) ){  
      printf("Controller action.\n");
    } else if( !strcmp( argv[1], "-h" ) || !strcmp( argv[1], "--help" ) ){
      printf("Help panel.\n");
    } else if( !strcmp( argv[1], "push" ) ){
      printf( "Pushing to db..." );
    }

  }else{
    
    printf("Error:  you must enter parametters, see --help or -h for help.\n");
  
  }
  return 0;
}//End of main method
