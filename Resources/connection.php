<?php
	
        /***
        * connection
        * Method that connects to mysql database
        * params none
        * return connection
        *********************/
        function connection( ){
                $xml = simplexml_load_file( $_SERVER['DOCUMENT_ROOT']."/Warrior/MySQL/config.xml" );

                $url = $xml->connection->url;
                $user = $xml->connection->user_name;
                $password = $xml->connection->password;
                $db = $xml->connection->db_name;

                $conn = mysqli_connect( $url, $user, $password, $db );

                if( $conn ){
                        return $conn;
                }else {
                        die( "Could not connect: " . mysql_error() );
                        return $conn;
                }

        }//End of connection function

        /***
        * close
        * Method that closes connection
        * params none
        * return none
        *****************/
        function close( $c ){
                mysqli_close( $c );
        }//End of close  function

        /***
        * get_db_name
        * get the database name of the configuration file
        * @params none
        * @return string with db_name
        ************************************/
        function get_db_name(){
               $xml = simplexml_load_file( $_SERVER['DOCUMENT_ROOT']."/Warrior/MySQL/config.xml" );
               return $xml->connection->db_name;
        }//End of get_db_name function


?>