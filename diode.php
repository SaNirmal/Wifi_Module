<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="./style.css">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

    <title>Hello, world!</title>
  </head>
  <body>
  <nav class="navbar navbar-expand-lg navbar-dark bg-primary">
  <a class="navbar-brand" href="#">UOK</a>
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavDropdown" aria-controls="navbarNavDropdown" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>
  <div class="collapse navbar-collapse" id="navbarNavDropdown">
    <ul class="navbar-nav">
      <li class="nav-item active">
        <a class="nav-link" href="/index.php">Home <span class="sr-only">(current)</span></a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="#">Features</a>
      </li>
    </ul>
  </div>
</nav>
    <div class="container-fluid">
      <div class="row my-4">
        <div class="col-md-4 col-sm-12">
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

$sql = "SELECT voltage,current FROM component";
$readData = $conn->query($sql);
echo '<table cellspacing="3" cellpadding="2" width="200" height="200">
      <tr> 
        <th>voltage</th> 
        <th>current</th>        
      </tr>';
 
if ($result = $conn->query($sql)) {
   $i = 0;
   $graph= array(array());
    while ($row = $result->fetch_assoc()) {
        
        $row_value1 = $row["voltage"];
        $row_value2 = $row["current"]; 
        $graph[$i][0] = $row_value1;
        $graph[$i][1] = $row_value2;
        $i++;
        
    }
    for($i=0;$i<20;$i++){
        echo '<tr> 
                
                <td>' . $graph[$i][0] . '</td> 
                <td>' . $graph[$i][1] . '</td>
               
                
              </tr>';
    }
    $result->free();
}

$conn->close();

?> 
</table>

        </div>
        <div class="col-md-8 col-sm-12">
          <canvas id="myChart"></canvas>
        </div>
      </div>
    </div>

    <script>
// Get the graph data from PHP using AJAX
var graphData = <?php echo json_encode($graph); ?>;
// Extract the y-values from graphData
var yValues = graphData.map(function(data) {
    return data[1];
});
// Get the canvas element
var ctx = document.getElementById('myChart').getContext('2d');
// Create a new Chart object
var myChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: graphData.map(function(voltage) { return voltage[0]; }),
        datasets: [{
            label: 'voltage vs current',
            data: graphData.map(function(voltage) { return voltage[1]; }),
            fill: false,
            borderColor: 'rgb(75, 192, 192)',
            tension: 0.1
        }]
    },
    options: {
        scales: {
            xAxes: [{
                display: true,
                scaleLabel: {
                    display: true,
                    labelString: 'Data Points'
                }
            }],
            yAxes: [{
                display: true,
                scaleLabel: {
                    display: true,
                    labelString: 'Values'
                }
            }]
        }
    }
});
</script>



    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.12.9/dist/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
  </body>
</html>