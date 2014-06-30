/**************************
 * lib.c
 * docuemnt for that works as a librarie for our system
 ****************************************/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

/***
 * make_directories
 * method that create all the directories of the project
 * @param project_name -  name of the project
 * @return none
 *************************/
void make_directories( char * project_name ){
  char temp[80];
  strcpy( temp, project_name );
  printf( "Creating new PHP WarriorMachinne Project...\n" );
  printf( "Generating folders...\n" );
  mkdir( temp, 0777 );
  
  ///Services folder
  strcat( temp, "/" );
  strcat( temp, "Services" );
  mkdir( temp, 0777 );
  printf( "\t-%s/\n", project_name );
  printf( "\t\t------Services/\n" );

  ///Controllers folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Controllers" );
  mkdir( temp, 0777 );
  printf( "\t\t------Controllers/\n" );

  //Models folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Models" );
  mkdir( temp, 0777 );
  printf( "\t\t------Models/\n" );

  //Helpers folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Helpers" );
  mkdir( temp, 0777 );
  printf( "\t\t------Helpers/\n" );
  
  //style folder
  strcpy( temp, project_name );
  strcat( temp, "/style" );
  mkdir( temp, 0777 );
  printf( "\t\t------style/\n" );

  //images folder
  strcat( temp, "/images" );
  mkdir( temp, 0777 );
  printf( "\t\t\t------------images/\n" );
  
  //css folder
  strcpy( temp, project_name );
  strcat( temp, "/style/css" );
  mkdir( temp, 0777 );
  printf( "\t\t\t------------css/\n" );

  //Views folder
  strcpy( temp, project_name );
  strcat( temp, "/Views" );
  mkdir( temp, 0777 );
  printf( "\t\t------Views/\n" );
  printf( "For creating database, edit the config file and type 'push' command.\n" );
}//End of make_directories Method

/***
 * wirite_config_file
 * Method that writes info on the config_file
 * char * project_name
 **********************************************/
void write_config_file( char * project_name ){
  
  char temp_route[80];
  
  strcpy( temp_route, project_name );
  strcat( temp_route, "/.config_file" );

  FILE * config_file = fopen( temp_route, "w" );

  fprintf( config_file, ";config_file\n;this file works as a configuration file for all the warrior project" );
  fprintf( config_file, ";write here the db information and shit\n;as well if you want to add new modulesto the porject and/or scripts" );
  fprintf( config_file, ";for comments jsut add the ';' character\n;for a new variable just put name variable between '[variable_name]' followed by ':'varuable_value';'" );
  fprintf( config_file, "\n\n" );

  //Generating the project info 
  strcpy( temp_route, "[project_name]:'" );
  strcat( temp_route, project_name );
  strcat( temp_route, "';\n" );

  fprintf( config_file, "%s", temp_route );
  fprintf( config_file, "\n\n" );
  
  //Generating the database information of the project, so it can be customizable
  fprintf( config_file, "[database]:\n" );
  fprintf( config_file, "\t[url]:'localhost';\n" );
  fprintf( config_file, "\t[user_name]:'username';\n" );
  fprintf( config_file, "\t[password]:'password';\n" );
  fprintf( config_file, "\t[db_name]:'db_name';\n" );
  fprintf( config_file, "[/database];\n" );
  fprintf( config_file, "\n\n" );

  //Generate the new module example
  fprintf( config_file, ";;;;for new modules\n" );
  fprintf( config_file, ";[module]:\n" );
  fprintf( config_file, ";\t[module_name]:'module_name';\n" );
  fprintf( config_file, ";\t[module_config]:\n" );
  fprintf( config_file, ";\t\t[x_config]:'x_config_variable';\n" );
  fprintf( config_file, ";\t[/module_config];\n" );
  fprintf( config_file, ";[/module];\n" );

  fclose( config_file );

}//End of write_config_file

/***
 * create_config_file
 * method that creates the config file in the project
 * char * project_name -  name of the project
 **********************************************/
void create_config_file( char * project_name ){ 

  char temp[80];
  
  strcpy( temp, project_name );
  strcat( temp, "/.config_file" );
  
  FILE * conf_file = fopen( temp, "ab+" );
  
  fclose( conf_file );

  write_config_file( project_name );

}//End of create_config_file Method

/***
 * create_errors_file
 * method that create the errors file
 * char * project_name
 *********************************************/
void create_errors_file( char * project_name ){

  char temp[80];

  strcpy( temp, project_name );
  strcat( temp, "/.errors" );

  FILE * error_file = fopen( temp, "ab+" );
  
  fclose( error_file );

}//End of create_errors_file Method

/***
 * create_new_project
 * Method that performs all the action of creating the new project
 * @return char * project_name
 ******************************************/
void create_new_project( char * project_name ){
  make_directories( project_name );
  create_config_file( project_name );
  create_errors_file( project_name );
}//End of create_new_project Method
