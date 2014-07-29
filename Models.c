
//Libararies
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "lib.h"
#include "SQL.h"
#include "Models.h"

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

  fprintf( newModel, "<?php\n\n " );
  fprintf( newModel, "\tinclude $_SERVER['DOCUMENT_ROOT'].'/Warrior/Model.php';\n\n" );
  fprintf( newModel, "\t//Class " );
  fprintf( newModel, "%s", model_name );
  fprintf( newModel, " Model\n" );
  fprintf( newModel, "\tclass " );
  fprintf( newModel, "%s ", model_name );
  fprintf( newModel, "extends Model {\n\n\t\t//Global Variables\n" );

  int i = 0;
  while( i < size_model_vars ){
    
    printf( "DataName:%s DataType:%s\n", vars_array[i], types_array[i] );
    fprintf( newModel, "\t\tprotected $" );
    fprintf( newModel, "%s", vars_array[i] );
    fprintf( newModel, ";\n" );

    i++;
  
  }
  fprintf( newModel, "\t}\n?>" );

  fclose( newModel );
  
  //Craate Model table on the database
  get_db_config();
  //SQL table creation
  create_table( url, username, password, db_name, model_name );

}//End of create_model Method
