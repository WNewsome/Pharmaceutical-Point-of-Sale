<?php

$servername = "localhost";
$username = "wnewsome_compos";
$password = "LSSD2021";
$dbname = "wnewsome_compos";
$search = htmlspecialchars($_GET["name"]);

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// The SQL search query
$sql = "SELECT * FROM Patients_List WHERE FIRSTNAME LIKE '%".$search."%'";
$result = $conn->query($sql);

class Result {

}
$response = new Result();

$last = 0;
if ($result->num_rows > 0) {
    echo '{"results":[';
  while($row = $result->fetch_assoc()) {
    $response->first_name = $row["FIRSTNAME"];
    $response->middle_name = $row["MIDDLENAME"];
    $response->last_name = $row["LASTNAME"];
    $response->street = $row["STREET"];
    $response->city = $row["CITY"];
    $response->state = $row["STATE"];
    $response->zip_code = $row["ZIP"];
    $response->phone = $row["PHONE"];
    $response->ssn = $row["SSN"];
    $response->month = $row["MONTH"];
    $response->day = $row["DAY"];
    $response->year = $row["YEAR"];
    $response->prescription = $row["PRESCRIPTION"];
    $response->id = $row["id"];
    
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