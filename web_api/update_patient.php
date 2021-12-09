<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";
$id = htmlspecialchars($_GET["id"]);

// Get new drug values
$first_name = htmlspecialchars($_GET["first_name"]);
$middle_name = htmlspecialchars($_GET["middle_name"]);
$last_name = htmlspecialchars($_GET["last_name"]);
$street_number = htmlspecialchars($_GET["street_number"]);
$city = htmlspecialchars($_GET["city"]);
$state = htmlspecialchars($_GET["state"]);
$zip_code = htmlspecialchars($_GET["zip_code"]);
$phone = htmlspecialchars($_GET["phone"]);
$SSN = htmlspecialchars($_GET["SSN"]);
$month = htmlspecialchars($_GET["month"]);
$day = htmlspecialchars($_GET["day"]);
$year = htmlspecialchars($_GET["year"]);
$prescription = $_GET["prescription"];


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "UPDATE Patients_List SET FIRSTNAME='$first_name', MIDDLENAME='$middle_name', LASTNAME='$last_name', STREET='$street_number', CITY='$city', STATE='$state', PHONE='$phone', ZIP='$zip_code', SSN='$SSN', MONTH='$month', DAY='$day', YEAR='$year', PRESCRIPTION='$prescription'  WHERE id='$id'";

if ($conn->query($sql) === TRUE) {
  echo "200 Ok";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>