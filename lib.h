/****************************
 * lib.h
 * header document for the lib.c document
 *****************************/

//Defines and libs
#ifndef LIB_H
#define LIB_H

//Global variables for the config file
char url[50];
char username[50];
char password[50];
char db_name[50];

//Global variables for the model part
char vars_array[20][50];//The array of variables of the model
char types_array[20][50];//The array of types of the moel variables
int size_model_vars;//Cuantity of variables of the model

//Prototipes
void append( char* s, char c );//Method that concatenate a char to a string(char array)
void copy_file( char * source, char * dest );//Method that copies a source file to a destination file

int get_db_config( );//Method that reads config_file and gets all the db config
void read_errors_file( );//Method that reads errors_file
void push_to_db(  );//Method that pushes the db creation

void wirte_config_file( char * project_name );//Method that writes_config_file
void write_errors_file( char * project_name );//Mehtod that writes_errors file
void write_xml_config_file();//Method that writes the config xml file
void make_directories( char * project_name );//Method makes all the directories
void create_config_file( char * poject_name );//Method that creates the config_file
void create_errors_file( char * project_name );//Method that creates errors_file
void create_new_project( char * project_name );//Method that creates all the new project
void create_xml_config_file( char * project_name );//Method that creates the config xml file


#endif
