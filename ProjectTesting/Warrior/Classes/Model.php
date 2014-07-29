<?php

	include $_SERVER['DOCUMENT_ROOT'].'/WarriorTesting/MySQL/connection.php';

	/***
	* Model class
	*******************/
	class Model{

	      public $attrs;

	      public function __construct(){
		     $attrs = get_object_vars( $this );
	      }//End of construct function

	      public function __get( $key ){
		     return $this->get( $key );
	      }//End of set function

	      public function __set( $key, $value ){
		     $this->set( $key, $value );
	      }//End of set function


	      protected function get( $key ){
	      	      return array_key_exists( $key, $this->attrs ) ? $this->attrs[$key] : null;
	      }//End of get function

	      protected function set( $key, $value ){
		     $this->attrs[$key] = $value;
	      }//End of set function

	      /***
	      * create
	      * Method that creates a none sense object
	      *	@params as - array that contents all the attrs of the new obj
	      *******************************/
	      public function create( $as ) {
  
		     foreach( (array) $as as $k => $v ){
		     	      $this->attrs[$k] = $v;
		     }		     

	      }//End of create function

	      /***
	      * save
	      *	method that creates on the database an object and if exists just update
	      * @params none
	      * @return none
	      **********************/
	      public function save(){

	      	     $conn = connection( );
		     $query = "CALL save_".get_class( $this )."(";
		     $i = 0;
	      	     foreach( (array)$this->attrs as $k => $v ){
		     	      if( $i > 0){
			      	  if( is_string( $v )){
					$query .= "'";
				  }
			      	  $query .= $v;
				  if( is_string( $v ) ){
				      $query .= "'";
				  }
				  if( $i < count( $this->attrs )-1 ){
				      $query .= ",";
				  }
			      } $i++;
		     }$query .= ")";

	      	     print( $query."\n" );

		     mysqli_query( $conn, $query );

	             close( $conn );

	      }//End of save function

	      /***
	      * getAll
	      * Method that returns an array of object of all the table
	      * @params none
	      * @return array
	      ************************/
	      public function getAll(){
	      
		$conn = connection();

		$all = mysqli_query( $conn, "CALL get_all_".get_class( $this ) );
		
		$newArray = array();

		while( $r = mysqli_fetch_array( $all ) ){
		       $obj = new $this;
		       foreach( (array)$this->attrs as $k => $v ){
		       		$obj->set($k, $r[$k]);
		       }
		       array_push( $newArray, $obj );
		}

		close( $conn );
		return $newArray;
		
	      }//End of getAll function

	      /***
	      * getByAttr
	      * Method that returns an array of all the method that have the same attr value in the table
	      * @param attr -  attribute
	      * @param value - value
	      * @returns array if multiple rows and an object if just one
	      *****************************************/
	      public function getByAttr( $attr, $value ){

		     $allObjs = $this->getAll();
		     $retObjs = array();

		     foreach( (array)$allObjs as $obj ){
			      if( $obj->attrs[$attr] == $value ){
			      	  array_push( $retObjs, $obj );
			      }	      
		     }

		     if( count( $retObjs ) == 0 ){
		     	 return null;
		     }else if( count( $retObjs ) == 1 ){
		     	 return $retObjs[0];
		     }else return $retObjs;

	      }//End of getByID function
	      
	}//End of Model Class

?>