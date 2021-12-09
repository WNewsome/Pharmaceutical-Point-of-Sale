<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";
$id = htmlspecialchars($_GET["id"]);
$storeid = htmlspecialchars($_GET["storeid"]);

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// The SQL search query
$sql = "SELECT * FROM New_Drug_List WHERE ID='$id'";
$storesql = "SELECT AMOUNT FROM Store_Inventory_{$storeid} WHERE id='$id'";
$result = $conn->query($sql);
$storeresult = $conn->query($storesql);

class Result {

}
$response = new Result();

$last = 0;
if ($result->num_rows > 0) {
    echo '{"results":[';
  while($row = $result->fetch_assoc()) {
    $response->name = $row["NAME"];
    $response->brand = $row["BRAND"];
    $response->cost = $row["COST"];
    $response->price = $row["PRICE"];
    $response->control_status = $row["CONTROLSTATUS"];
    $response->picture_url = $row["PICTUREURL"];
    $response->quantity = $storeresult->fetch_assoc()["AMOUNT"];
    $response->UPC = $row["UPC"];
    $response->DEA = $row["DEA"];
    $response->GPI = $row["GPI"];
    $response->NDC = $row["NDC"];
    $response->id = $row["ID"];
     
    echo json_encode($response);
    $last ++;
    if ($last < $result->num_rows){
        echo ",";
    }
    
  }
  echo "]}";
} else {
  echo '{"results":[]}';
}


$conn->close();

?>