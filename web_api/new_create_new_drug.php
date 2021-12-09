<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";

// Get new drug values
$name = htmlspecialchars($_GET["name"]);
$brand = htmlspecialchars($_GET["brand"]);
$cost = htmlspecialchars($_GET["cost"]);
$price = htmlspecialchars($_GET["price"]);
$control_status = htmlspecialchars($_GET["control_status"]);
$picture_url = htmlspecialchars($_GET["picture_url"]);
$quantity = htmlspecialchars($_GET["quantity"]);
$UPC = htmlspecialchars($_GET["UPC"]);
$DEA = htmlspecialchars($_GET["DEA"]);
$GPI = htmlspecialchars($_GET["GPI"]);
$NDC = htmlspecialchars($_GET["NDC"]);
$storeid = htmlspecialchars($_GET["storeid"]);
$storetable="Store_Inventory_{$storeid}";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$sql = "SELECT * FROM New_Drug_List WHERE NAME='$name'";
$res=$conn->query($sql);
if($res->num_rows <= 0){
    $sql = "INSERT INTO New_Drug_List (NAME, BRAND, COST, PRICE, CONTROLSTATUS, PICTUREURL, UPC, DEA, GPI, NDC)
VALUES ('$name', '$brand', '$cost', '$price', '$control_status', '$picture_url', '$UPC', '$DEA', '$GPI', '$NDC')";

if ($conn->query($sql) === TRUE) {
    $sql = "SELECT ID FROM New_Drug_List WHERE NAME='$name'";
    $result=$conn->query($sql);
    $id=$result->fetch_assoc()["ID"];
    $storesql="INSERT INTO $storetable (id,AMOUNT)
VALUES ('$id', '$quantity')";
if ($conn->query($storesql) === TRUE) {
    echo "200 Ok";
}else {
  echo "Error: " . $storesql . "<br>" . $conn->error;
}
  
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}
}
else {
    $sql = "SELECT ID FROM New_Drug_List WHERE UPC='$UPC'";
    $result=$conn->query($sql);
    $id=$result->fetch_assoc()["ID"];
    $storesql="INSERT INTO $storetable (id,AMOUNT)
VALUES ('$id', '$quantity')";
if ($conn->query($storesql) === TRUE) {
    echo "200 Ok";
}else {
  echo "Error: " . $storesql . "<br>" . $conn->error;
}
  
} 

$conn->close();

?>