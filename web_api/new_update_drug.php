<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";
$id = htmlspecialchars($_GET["id"]);

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
$id = htmlspecialchars($_GET["id"]);
$storeid = htmlspecialchars($_GET["storeid"]);
$storetable= "Store_Inventory_{$storeid}";


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "UPDATE New_Drug_List SET NAME='$name', BRAND='$brand', COST='$cost', PRICE='$price', CONTROLSTATUS='$control_status', PICTUREURL='$picture_url', UPC='$UPC', DEA='$DEA', GPI='$GPI', NDC='$NDC' WHERE ID='$id'";

if ($conn->query($sql) === TRUE) {
    $storesql = "SELECT * FROM $storetable WHERE id='$id'";
    $res = $conn->query($storesql);
    if($res->row_count>0)
    $storesql = "UPDATE $storetable SET AMOUNT='$quantity' WHERE id='$id'";
    else
    $storesql = "INSERT INTO $storetable (id,AMOUNT)
VALUES ('$id', '$quantity')";
    if($conn->query($storesql) === TRUE)
    echo "200 Ok";
    else{
        echo "Error: " . $storesql . "<br>" . $conn->error;
    }
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>