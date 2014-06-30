/****************************
 * lib.h
 * header document for the lib.c document
 *****************************/

//Defines and libs
#ifndef LIB_H
#define LIB_H

//Prototipes

void wirte_config_file( char * project_name );
void write_errors_file( char * project_name );

void make_directories( char * project_name );
void create_config_file( char * poject_name );
void create_errors_file( char * project_name );
void create_new_project( char * project_name );

#endif
