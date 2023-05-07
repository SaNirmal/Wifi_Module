<?php
     $host="localhost";
     $dbname="id20514385_compdatabase";
     $username="id20514385_component";
     $password="Uoktester@1100";

    $conn = new mysqli($host, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
else {
    // echo "Connected My SQL.";
}

$sql = "SELECT 	voltage,current FROM component";
$readData = $conn->query($sql);
if ($readData->num_rows > 0) {
    echo "
                            <table border='1'>
                            <thead class='thead-light'>
                            <tr>
                                <th scope='col'>#</th>
                                <th scope='col'>Last Month</th>
                            </tr>
                        </thead>
                        <tbody>
                            ";
    while ($row = $readData->fetch_assoc()) {
        echo "
                                <tr>
                                <th scope='row'>{$row['voltage']}</th>
                                <td>{$row['current']}</td>
                                
                            </tr>

                                ";
    }
} else {
    echo "0 result";
}
echo "</center>";
$conn->close();
?>