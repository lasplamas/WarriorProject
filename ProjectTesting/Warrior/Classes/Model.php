<?php
	require_once $_SERVER['DOCUMENT_ROOT'].'/MySQL/connection.php';

	class Model{

	      //Global Variables
	      protected $attrs;
	      protected $keys;

	      /***
	      * __construct
	      * Method constructor for initialize vars
	      * @params none
	      * @return none
	      *****************************/
	      public function __construct(){
		     //Init the attrs var
		     $this->attrs = array();
		     $this->attrs = get_object_vars( $this );
		     //Init the keys var
		     $this->keys = array();
		     $this->keys = $this->get_keys( );
	      }//End of __construct function

	      /***
	      * getByAttr
	      * get Element by attribute
	      * @param attr - attribute name
	      *	@param value - value of the attribute
	      * @return varios objects or object or null
	      ******************************************/
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
		     } else if( count( $retObjs ) == 1 ){
		       	 return $retObjs[0];
		     } else {
		         return $retObjs;
		     }
	      }//End of getByAttr function

	      /***
	      * update
	      * Method that updates an ojbect on the db
	      * @params none
	      * @return none
	      *****************************/
	      public function update(){
	      	    $conn = connection();
		    $primarykey = $this->keys[0][0];
		    $query = "UPDATE ".get_class( $this )." SET ";
		    $query2 = "";
		    $i = 0;
		    foreach( (array)$this->attrs as $k => $v ){
		    	     if( strpos( $primarykey, $k ) === false ){
			     	 if( $k != 'attrs' && $k != 'keys' ){
				     $query .= $k."=";
				     if( is_numeric( $v ) ){
				     	 $query .= $v;
			             }else if( is_string( $v ) ){
				    	  $query .= "'".$v."'";
				     } else if( is_bool( $v ) ){
				          if( $v ){
				     	      $query .= "1";
				     	  } else {
				       	      $query .= "0";
				          }
				     }
				     if( $i < $this->get_not_primary_size()-3 ){
				          $query .= ",";
				     }
				     $i++;
				 }
			     } else {
			       $query2 .= ($k."=");
			       if( is_numeric( $v ) ){
			       	 $query2 .= $v;
			       }else if( is_string( $v ) ){
			       	 $query2 .= "'".$v."'";
			       } else if( is_bool( $v ) ){
			       	 $v == TRUE ? $query2.="1" : $query2.="0";
			       }
			     }
		    }
		    $query .= ( " WHERE ". $query2 );
		    mysqli_query( $conn, $query );
		    close( $conn );
	      }//End of update method

	      /***
	      * save
	      * Method that saves an object on the database
	      * @params none
	      * @return none
	      **********************/
	      public function save(){
	      	     $conn = connection( );
		     $query = "CALL save_".get_class( $this )."(";

		     $i = 0;

	      	     foreach( (array)$this->attrs as $k => $v ){
		     	   if( $k != 'attrs' && $k != 'keys' ){
			      if( is_numeric( $v ) ){
			      	$query .= $v;
			      } else if( is_string( $v ) ){
			      	$query .= ("'".$v."'" );
			      } else if( is_bool( $v ) ){
			      	if( $v ){
				    $query .= 1;
				} else {
				    $query .= 0;
				}
			      }

			      if( $i < count( $this->attrs )-3 ){
				$query .= ",";
			      }

			      $i++;
			   }

		     }$query .= ")";
		     mysqli_query( $conn, $query );

	             close( $conn );

	      }//End of save function

	      /***
	      * getAll
	      * Method that gets all the objects of the db table
	      * @params none
	      * @return an array of objects
	      ************************/
	      public function getAll(){
	      	     $conn = connection();

		     $query = "CALL get_all_".get_class( $this );
		     $allObj = mysqli_query( $conn, $query );
		     $retArray = array();
		     while( $r = mysqli_fetch_array( $allObj ) ){
		     	    $tempObj = new $this;
			    $temp = array();
			    foreach( (array)$this->attrs as $k => $v ){
			    	    if( $k != 'attrs' && $k!='keys' ){
					$temp[$k] = $r[$k];
			    	    }
			    }
			    $tempObj->create( $temp );
			    array_push( $retArray, $tempObj );
		     }

		     close( $conn );
		     return $retArray;
	      }//End of getAll function

	      /***
	      * create
	      * Method that initialize an object with an array
	      * @param as - array of attributes
	      * @return none
	      *****************************/
	      public function create( $as ){
	      	     foreach( (array)$as as $k => $v ){
		     	      $this->attrs[$k] = $v;
		     }
	      }//End of create function

	      /***
	      * __get
	      * Magic getter method
	      * @params key - name of the attribute
	      * @return attrubute value
	      *****************************/
	      public function __get( $key ){
	      	     return array_key_exists( $key, $this->attrs ) ? $this->attrs[$key] : null;
	      }//End of __get function

	      /***
	      * __set
	      * Magic settter method
	      * @param key - the name of the attribute
	      * @param value - the value of the attrubute
	      * @return none
	      *************************************/
	      public function __set( $key, $value ){
	      	     $this->attrs[$key] = $value;
	      }//End of __set function

	      /***
	      * get_keys
	      * Method that gets the primary keys of the object
	      * @params none
	      * @return an array of primary keys of the object
	      **************************/
	      public function get_keys(){
	      	     $conn = connection();
		     $query = "SELECT getPKColumns('".get_db_name()."','".get_class( $this )."')";
		     $k = mysqli_query( $conn, $query );
		     $retArray = array();
		     while( $r = mysqli_fetch_array( $k ) ){
		     	    array_push( $retArray, $r );
		     }
		     close( $conn );
		     return $retArray;
	      }//End of get_keys function

	      /***
	      * get_not_primary_size
	      * Method that gets the size of the not primary variables
	      * @params none
	      * @return int size
	      **************************************/
	      public function get_not_primary_size(){
	      	     $i = 0;
		     $primarykey = $this->keys[0][0];
		     foreach( (array)$this->attrs as $k => $v ){
		     	      if( strpos( $primarykey, $k ) === false ){
			      	  $i++;
			      }
		     }return $i;
	      }//End of get_not_primary_size function

	      /***
              * delete
              * Method that deletes a register of the database
              * @params none
              * @rerurn none
              **********************************/
              public function delete( $attr, $value ){

                     $conn = connection();
                     $query = "DELETE FROM ".get_class( $this )." WHERE ".$attr."=".$value;
                     mysqli_query( $conn, $query );
                     close( $conn );

              }//End of delete function

	}//End of Model Class
?>
