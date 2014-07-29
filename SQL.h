

#ifndef SQL_H
#define SQL_H
#include <my_global.h>
#include <mysql.h>

int create_db( char * u, char * un, char * p, char *db );
int starts_with( const char * a, const char * b );
int ends_with( const char * a, const char * b );
int create_table( char * u, char * un, char * p, char * db, char * tbname );
void create_procedures( char * model_name, MYSQL * conn );
void save_procedure( char * model_name, MYSQL * conn);
void getPK_procedure( MYSQL * conn );
void get_all_procedure( char * model_name, MYSQL * conn );

#endif

