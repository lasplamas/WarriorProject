/**************************
 * lib.c
 * docuemnt for that works as a librarie for our system
 ****************************************/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "lib.h"
#include "SQL.h"

/***
 * append
 * Method that concatenates a char to a string(char array)
 * @param char * s -string 
 * @param char c - character
 * @return none
 ***********************************/
void append( char * s, char c ){

  int len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';

}//End of append Method

/***                                                                                     
 * get_db_config                 
 * Method that gets the database information of the config_file and asings the info on global variabes                                                                                                  
 * @params - none
 * @return - int, -1 if error && 0 if success
 ***********************************************************/
int get_db_config( ){

  //Local variables
  FILE * config_file = fopen( ".config_file", "r+" );
  char line[100];
  int ban = -1;

  //Validation fot the existence of the file               
  if( config_file == NULL){
    printf( "Error opening .config_file file.\n" );
    return( -1 );
  }//End of the error validation                                                                                                                                                                      
  //loop for reading line by line       
  while( fgets( line, 100, config_file ) != NULL ){

    //Validation of the cometarized lines
    if( line[0] != ';' ){

      //The database line part toggle validation
      if( strstr( line, "database" ) != NULL ){
        ban *= -1;
        fgets( line, 100, config_file );
      }//End of the line on the database part toggle

      //Validation fot the toggle of the correct line that is in the database part  
      if( ban == 1 ){

        //Other local variables  
        int i = 0;
        int ban2 = -1;

        //Loop for reading char by char the line
        for( i = 0; i < strlen( line ); i++ ){
          //Validation for the right word and changin the toggle
          if( line[i] == '\'' ){
            ban2 *= -1;
            i++;
          }//Enf of validation of right word 

          //Validation of the toggle 
          if( ban2 == 1 ){

            if( strstr( line, "url" ) != NULL ){
              append( url, line[i] );
            } else if( strstr( line, "user_name" ) != NULL ){
              append( username, line[i] );
            } else if( strstr( line, "password" ) != NULL ){
              append( password, line[i] );
            } else if( strstr( line, "db_name" )  != NULL ){
              append( db_name, line[i] );
            }

          }//End of toggle validation

        }//End of the loop for the char by char                                                      

      }//End of validation of the toggle of the line                                                 

    }//End of validation of the not comentarized line

  }//End of the line by line loop                                                                    

  fclose( config_file );

  return( 0 );

}//End of reading_file_line_by_line Method

/***
 * read_errors_file
 * method that reads the errors file
 * @params none
 * @return none
 ***********************************/
void read_errors_file( ){

  //Declaration of variables
  //validation of file
  //loop for reading file
  //Printing of file for testing

}//End of read_errors_file Method

/***
 * push_to_db
 * Method that pushes all to the database
 * @params none
 * @return none
 **************************************/
void push_to_db( ){

  get_db_config();//Reading of config_file
  create_db( url, username, password, db_name );//Create database
  write_xml_config_file();

}//End of push_to_db Method

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
  printf( "\t\t|-->%s/\n", project_name );
  printf( "\t\t|------------>Services/\n" );

  ///Controllers folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Controllers" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>Controllers/\n" );

  //Models folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Models" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>Models/\n" );

  //Helpers folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Helpers" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>Helpers/\n" );
  
  ///Warrior folder
  strcpy( temp, project_name );
  strcat( temp, "/" );
  strcat( temp, "Warrior" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>Warrior/\n" );
  //Mysql Folder
  strcat( temp, "/MySQL" );
  mkdir( temp, 0777 );
  printf( "\t\t|---------------->MySQL/\n" );
  copy_file( "Resources/connection.php", temp );
  printf( "\t\t|---------------------->connection.php\n" );
  
  //Clases Folder
  strcpy( temp, project_name );
  strcat( temp, "/Warrior/Classes" );
  mkdir( temp, 0777 );
  //Copy model file to warrior folder
  copy_file( "Resources/Model.php", temp );
  printf( "\t\t|---------------------->Model.php\n" );
  copy_file( "Resources/Controller.php", temp );
  printf( "\t\t|---------------------->Controller.php\n" );

  //css folder
  strcpy( temp, project_name );
  strcat( temp, "/css" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>css/\n" );
  
  //Images folder
  strcat( temp, "/images" );
  mkdir( temp, 0777 );
  printf( "\t\t|----------------->/images\n" );

  //js folder
  strcpy( temp, project_name );
  strcat( temp, "/js" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>js/\n" );

  //fonts folder
  strcpy( temp, project_name );
  strcat( temp, "/fonts" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>fonts/\n" );
  
  //Views folder
  strcpy( temp, project_name );
  strcat( temp, "/Views" );
  mkdir( temp, 0777 );
  printf( "\t\t|------------>Views/\n" );
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
 * write_xml_config_file
 * Method that writes the xml config file
 * @params none
 * @returns none
 ************************************************/
void write_xml_config_file( ){

  char temp_route[50];

  strcpy( temp_route, "Warrior/MySQL/config.xml" );

  FILE * xml_file = fopen( temp_route, "w" );

  fprintf( xml_file, "<?xml version='1.0' encoding='UTF-8'?>\n" );
  fprintf( xml_file, "<configuration>\n\t<connection>\n\t\t<url>" );
  fprintf( xml_file, "%s", url );
  fprintf( xml_file, "</url>\n\t\t<user_name>" );
  fprintf( xml_file, "%s", username );
  fprintf( xml_file, "</user_name>\n\t\t<password>" );
  fprintf( xml_file, "%s", password );
  fprintf( xml_file, "</password>\n\t\t<db_name>" );
  fprintf( xml_file, "%s", db_name );
  fprintf( xml_file, "</db_name>\n\t</connection>\n</configuration>" );

  fclose( xml_file );

}//End of write_xml_config_file Method

/***
 * create_xml_config_file
 * Create the xml configuration file
 * @param char * project_name
 * @returns none
 ****************************/
void create_xml_config_file( char * project_name ){

  char temp[80];

  strcpy( temp, project_name );
  strcat( temp, "/Warrior/MySQL/config.xml" );

  FILE * xml_file = fopen( temp, "ab+" );

  fclose( xml_file );

}//create_xml_config_file Method

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
  create_xml_config_file( project_name );
  copy_file( "./warrior", project_name );
}//End of create_new_project Method

/***
 * copy_file
 * Method that copies a file to another location
 * @param char * source -  the source file to copy
 * @param char * dest - the destination file of the copied file
 * @return none
 ***************************************/
void copy_file( char * source, char * dest ) {

  //Local variables
  int childExitStatus;
  pid_t pid;
  int status;

  if (!source || !dest) {

    printf( "Parameters are incorrect...\n" );

  }//Validate Parameters

  pid = fork();//Process

  if (pid == 0) { /* child */
  
    execl("/bin/cp", "/bin/cp", source, dest, (char *)0);
  
  } else if (pid < 0) {

    printf( "Coudn't start process...\n" );

  }//End of condition for error couldn't start process

  else {
    //parent - wait for child - this has all error handling, you
    //could just call wait() as long as you are only expecting to
    //have one child process at a time
    pid_t ws = waitpid( pid, &childExitStatus, WNOHANG);
    
    if (ws == -1) {

      printf( "There was an error copping the ./warrior file...\n" );

    }//Error handler if

    if( WIFEXITED(childExitStatus)) {

      status = WEXITSTATUS(childExitStatus); //zero is normal exit
	
    }//End of exit code in childExitStatus if
    else if (WIFSIGNALED(childExitStatus)) {
      
    }//End of killed if
    else if (WIFSTOPPED(childExitStatus)) {
    
    }//End of stopped if
  
  }//End of else for error handler

}//End of copy_file Method
