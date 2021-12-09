<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";

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

$sql = "INSERT INTO Patients_List (FIRSTNAME, MIDDLENAME, LASTNAME, STREET, CITY, STATE, ZIP, PHONE, SSN, MONTH, DAY, YEAR, PRESCRIPTION)
VALUES ('$first_name', '$middle_name', '$last_name', '$street_number', '$city', '$state', '$zip_code', '$phone', '$SSN', '$month', '$day', '$year', '$prescription')";

if ($conn->query($sql) === TRUE) {
  echo "200 Ok";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

?>