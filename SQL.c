


#include <string.h>
#include "lib.h"
#include "SQL.h"

/***
 * create_db
 * Method that initializes the project db
 * @param char *u - url
 * @param char * un - username
 * @param char * p - password
 * @param char * db - database
 * @return int
 ***********************************************/
int create_db( char * u, char * un, char * p, char * db ){

  MYSQL * conn = mysql_init( NULL );
  char query[80];

  strcpy( query, "CREATE DATABASE " );
  strcat( query, db );
  
  if( mysql_real_connect( conn, u, un, p, NULL, 0, NULL, 0 )  == NULL ){
    printf( "Was an sql error bitch! %s\n", mysql_error( conn ) );
    mysql_close( conn );
  } else {
    mysql_query( conn, query );
    printf( "Database Creation successful :)\n" );
    mysql_close( conn );
  }

  return 0;

}//End of create_db Method

/***
 * create_table
 * Method that creates table on the project db
 * @param char * u - url
 * @param char * un -  username
 * @param char * p - password
 * @param char * db - database
 * @param char * tbname - table name
 * @returns int
 ***********************************************/
int create_table( char * u, char * un, char * p, char * db, char * tbname ){
  
  printf( "%s\n", u );
  printf( "%s\n", un );
  printf( "%s\n", p );
  printf( "%s\n", db );
  printf( "%s\n", tbname );
  printf( "%d\n", size_model_vars );

  char query[150];
  
  int i = 0;
  strcpy( query, "CREATE TABLE " );
  strcat( query, tbname );
  strcat( query, " (" );

  while( i < size_model_vars ){
    
    strcat( query, vars_array[i] );
    strcat( query, " " );

    if( starts_with( types_array[i], "int" ) ){
      strcat( query, "INT(10)" );
      if( ends_with( types_array[i], "key" ) ){
	strcat( query, " NOT NULL AUTO_INCREMENT PRIMARY KEY" );
      }
    }else if( !strcmp( types_array[i], "string" ) ){
      strcat( query, "VARCHAR(100)" );
    }else if( !strcmp( types_array[i], "text" ) ){
      strcat( query, "VARCHAR(500)" );
    }else if( !strcmp( types_array[i], "bool" ) ){
      strcat( query, "BIT" );
    }

    if( i < size_model_vars-1 ){
      strcat( query, "," );
    }

    printf( "\tName: %s\n", vars_array[i] );
    printf( "\tType: %s\n", types_array[i] );

    i++;
  
  }
  strcat( query, " )" );
  printf( "query: %s\n", query );

  //Create connection
  MYSQL * conn = mysql_init( NULL );
   
  if( mysql_real_connect( conn, u, un, p, db, 0, NULL, 0 ) == NULL ){

    printf( "There was an error creating table: %s\n", mysql_error( conn ) );
    mysql_close( conn );

  } else {
    
    //Creates model table
    mysql_query( conn, query );
    printf( "Table Created on the database :D\n" );
    
    //Creates the stored procedures on the database
    create_procedures( tbname, conn );
    printf( "StoredProcedures Created On DB :D\n" );
    mysql_close( conn );

  }

}//create_table_test

int starts_with( const char * a, const char * b ){
  if( strncmp( a, b, strlen( b ) ) == 0 ) return 1;
  return 0;
}//End of starts_with method


int ends_with( const char * a, const char * b ){

  if (!a || !b)
    return 0;
  size_t lenstr = strlen(a);
  size_t lensuffix = strlen(b);
  if (lensuffix >  lenstr)
    return 0;
  return strncmp(a + lenstr - lensuffix, b, lensuffix) == 0;

}//End of ends_with Method

void create_procedures( char * model_name, MYSQL * conn ){
  save_procedure( model_name, conn );
  getPK_procedure( conn );
  get_all_procedure( model_name, conn );
  
}

/***
 * save_procedure
 * Method that creates the insert procedure on the db
 * @params model_name 
 * @return none
 ****************************************/
void save_procedure( char * model_name, MYSQL * conn ){

  char query[1000];

  strcpy( query, "DROP PROCEDURE IF EXISTS save_" );
  strcat( query, model_name );
  mysql_query( conn, query );
  printf( "%s\n", query );

  strcpy( query, "CREATE PROCEDURE `save_" );
  strcat( query, model_name );
  strcat( query, "` ( " );
  
  int i = 0;

  while( i < size_model_vars ){
    
      
      strcat( query, " IN p_" );
      strcat( query, vars_array[i] );

      if( starts_with( types_array[i], "int" ) ){
	strcat( query, " INT(10)" );
      }else if( !strcmp( types_array[i], "string" ) ){
	strcat( query, " VARCHAR(100)" );
      }else if( !strcmp( types_array[i], "text" ) ){
	strcat( query, " VARCHAR(500)" );
      }else if( !strcmp( types_array[i], "bool" ) ){
	strcat( query, " BIT" );
      }

      if( i < size_model_vars-1 ){
	
	strcat( query, "," );
    
      }

      i++;
  
  }
  strcat( query, " )" );

  strcat( query, " BEGIN " );
  strcat( query, "INSERT INTO " );
  strcat( query, model_name );
  strcat( query, "(" );
  
  int j = 0;
  
  while( j < size_model_vars ){

      strcat( query, vars_array[j] );

      if( j < size_model_vars-1 ){
	strcat( query, ", " );
      }

      j++;
  
  }

  strcat( query, " )" );
  strcat( query, " VALUES ( " );
  int k = 0;
  
  while( k < size_model_vars ){

    
      strcat( query, "p_" );
      strcat( query, vars_array[k] );

      if( k < size_model_vars-1 ){
	strcat( query, ", " );
      }
    
      k++;
  
  }

  strcat( query, " ); END" );
  printf( "%s\n", query );
  mysql_query( conn, query );

}//End of insert_procedure Method

/***
 * get_all_procedure
 * Method that creates the get all procedure on the db
 * @params model_name 
 * @return none
 ****************************************/
void get_all_procedure( char * model_name, MYSQL * conn ){

  char query[500];

  strcpy( query, "DROP PROCEDURE IF EXISTS get_all_" );
  strcat( query, model_name );
  mysql_query( conn, query );
  printf( "%s\n", query );

  strcpy( query, "CREATE PROCEDURE `get_all_" );
  strcat( query, model_name );
  strcat( query, "`() BEGIN SELECT * FROM " );
  strcat( query, model_name );
  strcat( query, "; END" );
  
  printf( "%s\n", query );

  mysql_query( conn, query );

}//End of get_all_procedure Method

/***
 * update_procedure
 * Method that creates the update stored procedure in the db
 * @params model_name 
 * @return none
 *********************************/
void getPK_procedure( MYSQL * conn ){

  char query[550];

  //Drop query
  strcpy( query, "DROP FUNCTION IF EXISTS `getPKColumns`" );
  printf( "%s\n", query );
  mysql_query( conn, query );
  
  //Create procedure
  strcpy( query, "CREATE DEFINER=`" );
  strcat( query, username );
  strcat( query, "`@`" );
  strcat( query, url );
  strcat( query, "` FUNCTION `getPKColumns`(" );
  strcat( query, " dbName VARCHAR(64),tableName VARCHAR(64)) RETURNS text CHARSET utf8 " );
  strcat( query, "BEGIN " );
  strcat( query, "DECLARE PKColumns TEXT; " );
  strcat( query, " SELECT GROUP_CONCAT(`COLUMN_NAME` SEPARATOR '`, `') " );
  strcat( query, " FROM `information_schema`.`COLUMNS` " );
  strcat( query, " WHERE (`TABLE_SCHEMA` = dbName)" );
  strcat( query, " AND (`TABLE_NAME` = tableName)" );
  strcat( query, " AND (`COLUMN_KEY` = 'PRI')" );
  strcat( query, " INTO PKColumns;" );
  strcat( query, " SET PKColumns = CONCAT('`', PKColumns, '`');" );
  strcat( query, " RETURN PKColumns;" );
  strcat( query, " END" );

  mysql_query( conn, query );

}//End of update_procedure Method


