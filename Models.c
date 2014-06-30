
//Libararies
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>


/***
 * create_model
 * Method that creates a model in the project
 * char *model_name - name of the new model
 ************************************/
void create_model( char * model_name ){
 
  char tmp[80];
  
  strcpy( tmp, "Models/" );
  strcat( tmp, model_name );
  strcat( tmp, ".php" );

  FILE * newModel = fopen( tmp, "ab+" );

}//End of create_model Method

void create_model_table( char * model_name ){

}//End of create_model_table Method

void create_model_procedures( char * model_name ){

}//End of create_model_procedures Method
