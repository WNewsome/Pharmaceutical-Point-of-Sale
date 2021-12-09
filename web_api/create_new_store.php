<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";
$storeid = htmlspecialchars($_GET["storeid"]);

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// The SQL search query
$sql = "SELECT * FROM information_schema.tables WHERE (table_schema = '$dbname' AND table_name = Store_Inventory_{$storeid})";
$result = $conn->query($sql);
echo $result->num_rows;

if ($result->num_rows > 0) {
  echo "exist";
} else {
  $sql="CREATE TABLE IF NOT EXISTS Store_Inventory_{$storeid}(id INT(11),AMOUNT INT(11), PRIMARY KEY ( id ))ENGINE=InnoDB DEFAULT CHARSET=utf8";
    if($conn->query($sql)==true){
        echo "created";
    }
    else{
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}


$conn->close();

?>