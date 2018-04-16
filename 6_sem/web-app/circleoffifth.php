<!DOCTYPE html>

<html>
<title>Circle of Fifths</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link type="text/css" href="css/w3.css" rel="stylesheet"/>
<link type="text/css" href="css/font-awesome.min.css" rel="stylesheet"/>
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">

<style>
body {font-family: "Lato", sans-serif}
.mySlides {display: none}
</style>

<script type="text/javascript">
function myFunction() {
    var x = document.getElementById("navDemo");
    if (x.className.indexOf("w3-show") == -1) {
        x.className += " w3-show";
    } else { 
        x.className = x.className.replace(" w3-show", "");
    }
}
</script>

<body>

<!-- Navbar -->
<div class="w3-top">
  <div class="w3-bar w3-black w3-card">
  	<a class="w3-bar-item w3-button w3-padding-large w3-hide-medium w3-hide-large w3-right" href="javascript:void(0)" onclick="myFunction()" title="Toggle Navigation Menu"><i class="fa fa-bars"></i></a>
    <a href="/" class="w3-bar-item w3-button w3-padding-large">Home</a>
    <a href="circleoffifth.php" class="w3-bar-item w3-button w3-padding-large w3-hide-small">Circle of Fifths</a>
  </div>
</div>

<!-- Navbar on small screens -->
<div id="navDemo" class="w3-bar-block w3-black w3-hide w3-hide-large w3-hide-medium w3-top" style="margin-top:46px">
  <a href="circleoffifth.php" class="w3-bar-item w3-button w3-padding-large">Circle of Fifths</a>
</div>

<!-- Page content -->
<div class="w3-content" style="max-width:2000px;margin-top:46px">

  <!-- TAB1 Section -->
  <div class="w3-container w3-content w3-center w3-padding-64" style="max-width:800px" id="tab1">
    <h2 class="w3-wide">Circle of Fifths</h2>
    <p class="w3-opacity"><i>Find relative scales</i></p>
    <p class="w3-center"><center>
    	<?php

			$conn = mysqli_connect("localhost", "root", "danish.saeed2", "music_theory");
			if ($conn->connect_error) {
				echo "<p>Connection Error</p>";
				die("Connection failed: " . $conn->connect_error);			
			}
			$sql = "SELECT major,minor FROM circle_fifth";
			$result = $conn->query($sql);

				echo "<table class=\"w3-hoverable w3-tablemine\" style=\"text-align:center\"><tr class=\"w3-padding-large\"><th>Major Key</th><th>Minor Key</th></tr>";
				
				while($row = $result->fetch_assoc()) {
					echo "<tr class=\"w3-padding-64\"><td>".$row["major"]."</td><td>".$row["minor"]."</td></tr>";
				}
				echo "</table>";
			mysqli_close($conn);
		?>
		<br>
		<form action="store.php" method="POST">
			<fieldset>
				<legend><b>Enter data</b></legend>
				<br>
                Major Key: 
                <input type="text" name="major" id = "major"><br><br>
                Minor Key: 
                <input type="text" name="minor" id = "minor"><br>
                <br>
                <input type="submit" name = "submit" id="submit">
                <br>
			</fieldset>
		</form>
		</center>
	</p>

  </div>
  
<!-- End Page Content -->
</div>

<!-- Footer -->
<footer class="w3-container w3-padding-large w3-center w3-opacity w3-light-grey"><p><a href="info.php">Check PHP</a></p>
</footer>

</body>
</html>
	

