<?php
     $host="localhost";
     $dbname="id20514385_compdatabase";
     $username="id20514385_component";
     $password="Uoktester@1100";

   $conn = new mysqli($host, $username, $password, $dbname);

if ($conn->connect_error) {
   die("Connection failed: " . $conn->connect_error);
} 

// Clear the database table
$sql = "DELETE FROM component"; // Replace with your actual table name
if ($conn->query($sql) === TRUE) {
  echo "Database cleared successfully";
} else {
  echo "Error clearing database: " . $conn->error;
}

$conn->close();
?>