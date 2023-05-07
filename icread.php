<?php

    $host="localhost";
    $dbname="id20514385_compdatabase";
    $username="id20514385_component";
    $password="Uoktester@1100";

    $conn = new mysqli($host, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
else { echo"Connected My SQL.";}

$va1=$_GET['v1'];
$va2=$_GET['v2'];
echo $va1;
echo $va2;
       
$sql ="INSERT INTO ic(name,valueSet) VALUES ('".$va1."','".$va2."')";
$result = mysqli_query($conn,$sql);
$conn->close();


?>