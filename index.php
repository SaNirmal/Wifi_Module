<!doctype html>
<html lang="en">
<?php
$host = "localhost";
$dbname = "id20514385_compdatabase";
$username = "id20514385_component";
$password = "Uoktester@1100";

$conn = new mysqli($host, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if (isset($_GET['type'])) {
    $type = $_GET['type'];
    $query = mysqli_query($conn, "INSERT INTO deviceType(type) VALUES($type)");
}
?>

<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <link rel="stylesheet" href="./style.css">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

    <title>Hello, world!</title>
    <style>
        #progress {
            width: 0%;
        }
    </style>
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
                    <a class="nav-link" href="#">Home <span class="sr-only">(current)</span></a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="#">Features</a>
                </li>
            </ul>
        </div>
    </nav>
    <div class="container-fluid">
        <div class="row my-4">
            <div class="col-md-12 col-sm-12">
                <div class="my-5 mx-5">
                    <center>
                        <h1>Component Tester</h1>
                    </center>
                </div>
            </div>
        </div>
        <div class="row my-4">
            <div class="col-md-12 col-sm-12">
                <div class="my-5 mx-5">
                    <center>
                        <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#exampleModal">
                            Launch Demo Modle
                        </button>
                        <!-- Modal -->
                        <div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
                            <div class="modal-dialog" role="document">
                                <div class="modal-content">
                                    <div class="modal-header">
                                        <h5 class="modal-title" id="exampleModalLabel">Device Type</h5>
                                        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                            <span aria-hidden="true">&times;</span>
                                        </button>
                                    </div>
                                    <div class="modal-body">
                                        <center>
                                            <h2>
                                                Looking For Data
                                            </h2>
                                        </center>
                                        <?php
                                        $select = mysqli_query($conn, "SELECT * FROM deviceType ORDER BY id DESC LIMIT 5;");
                                        $row = mysqli_fetch_assoc($select);
                                        $x = $row['type'];
                                        ?>
                                        <div class="text-center">
                                            <a href="<?php if($x == 1){echo './diode.php';}elseif($x == 2){echo './ic.php';} ?>"class="btn btn-primary <?php if(!($x == 1 || $x == 2)){echo 'd-none'; } ?>"><?php if($x == 1){echo 'View Diode Details';}elseif($x == 2){echo 'View IC Details';} ?></a>
                                            
                                        </div>
                                        <div class="card-body">
                                            <h3 class="<?php if(($x == 1 || $x == 2)){echo 'd-none'; } ?>"><strong>Device Type : </strong> <?php if($x == 3){echo 'Transister';}elseif($x == 4){echo 'Operation Amplifier';} ?></h3>
                                        </div>
                                        <!-- <div class="progress">
                                            <div class="progress-bar" role="progressbar" style="width: 0%;" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100"></div>
                                        </div> -->



                                        <!-- <div class="card my-3 bg-light">
                                            <div class="card-body">
                                                <h1><strong>Device Type : </strong> Diode</h1>
                                            </div>
                                            <div class="text-center">
                                                <button type="button" class="btn btn-primary my-3">View Details</button>
                                            </div>
                                        </div> -->

                                    </div>
                                </div>
                            </div>
                        </div>
                    </center>
                </div>
            </div>
        </div>
    </div>

    <script>
        $(document).ready(function() {
            var progress = 0;
            var interval = setInterval(function() {
                progress += 10;
                $(".progress-bar").css("width", progress + "%").attr("aria-valuenow", progress);
                if (progress >= 100)
                    clearInterval(interval);
            }, 2000);
        });
    </script>



    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.12.9/dist/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
</body>

</html>