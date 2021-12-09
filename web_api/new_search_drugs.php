<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";
$search = htmlspecialchars($_GET["name"]);
$withstore=false;
$storeid;
$sotrTable;
if(isset($_GET['storeid']))
{
    $storeid = htmlspecialchars($_GET["storeid"]);
    $sotrTable = "Store_Inventory_{$storeid}";
    $withstore=true;
}

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// The SQL search query
$sql = "SELECT * FROM New_Drug_List WHERE (NAME LIKE '%".$search."%' OR BRAND LIKE '%".$search."%')";
$result = $conn->query($sql);

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
    $response->UPC = $row["UPC"];
    $response->DEA = $row["DEA"];
    $response->GPI = $row["GPI"];
    $response->NDC = $row["NDC"];
    $response->id = $row["ID"];
    if($withstore){
        $drugid=strval($response->id);
        $storesql = "SELECT * FROM $sotrTable WHERE id = $drugid";
        $storeresult = $conn->query($storesql);
        if($storeresult>0){
            $storerow=$storeresult->fetch_assoc();
        $response->quantity = $storerow["AMOUNT"];
        }
        else{
           $response->quantity=0; 
        }
    }
    else{
        $response->quantity=0;
    }
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