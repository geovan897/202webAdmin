<?php
session_start();
require_once("AdminDB.php.inc");
$selected = $_POST['client'];
$request = $_POST['request'];
//var_dump($_POST);
switch($request)
{
    case "login":
	$username = $_POST['username'];
	$password = $_POST['password'];
	$login = new AdminDB("connect.ini");
	$response = $login->validateAdmin($username,$password);
	if ($response['success']===true)
	{
		 header('Location:AdminWelcome.php');
		 session_start();
		 $_SESSION['username'] = $username;
	}
	else
	{
		$response = "Login Failed:".$response['message']."<p>";
	}
	break;
    case "register":
	$username = $_POST['username'];
	$password = $_POST['password'];
	$secret = $_POST['recovery'];
	$login = new AdminDB("connect.ini");
	$response = $login->addNewAdmin($username,$password);
	
	if ($response['success']===true)
	{
		$response = "Congrats You're Registered!<p>";
		?> <p align="center"><a href ="index.html" target ="_blank"/><b> Admin Login Here</b></a> </p>
		<?php
	
	}
	else
	{
		$response = "Sorry there was a problem: ".$response['message']."<p>";
	}
	break;
	
	// user permissions
    	
    case "deny":
	
	$login = new AdminDB("connect.ini");
	$response = $login->PermissionDeny($selected);
	//var_dump($response);
	//return $response;
	if ($response)
	{
	    
	    //echo $username;
	    $meg = "Successfully denied the specified user access! <p>";
	    echo $meg;
	}
	else 
	{
	    $meg = "Sorry there was a problem trying to deny the specified user access <p>";
	    echo $meg;
	}
	break;
	
    case "allow":
	$login = new AdminDB("connect.ini");
	$response = $login->PermissionAllow($selected);
	//var_dump($response);
	//return $response;
	if ($response)
	{
	    //echo $username;
	    $meg = "Successfully allowed the specified user access! <p>";
	    echo $meg;
	}
	else 
	{
	    $meg = "Sorry there was a problem trying to allow the specified user access <p>";
	   echo $meg;
	}
	break;
	

}
//echo $response;
?>
