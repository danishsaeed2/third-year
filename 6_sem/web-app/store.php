<?php

	$conn = mysqli_connect("localhost", "root", "danish.saeed2", "music_theory");
	
	if ($conn->connect_error) {
		echo "<p>Connection Error</p>";
		die("Connection failed: " . $conn->connect_error);
	}

	$major = $_POST["major"];
	$minor = $_POST["minor"];
	
	$major = mysqli_real_escape_string($conn, $major);
	$minor = mysqli_real_escape_string($conn, $minor);
	
	$query = "INSERT INTO circle_fifth (major, minor) 
			VALUES ('".$major."','".$minor."')";

		$result = $conn->query($query);

		if ($result) {

		header('Location: circleoffifth.php');
		} else {
			die("Database query failed. " . mysqli_error($connection)); 
		}

	mysqli_close($conn);
?>