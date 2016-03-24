<?php
session_start(); 
$meg = "";
if ( isset( $_SESSION['username'] ) ){
  
  
  require_once('AdminDB.php.inc');
  $login = new AdminDB("connect.ini");
  $response = $login->ListUsers(); //this portion and the code below works fine but we need to make a nav bar for the list of teams in a league
 //$response2 = $login->leagues();
}

//echo $_POST['client'];
//include('rpc.php');
?>

<!DOCTYPE html>
<html>
<head>
<style>
ul {
    list-style-type: none;
    margin: 0;
    position:absolute; 
    right:0px;
  
    padding: 0;
    width: 200px;
    background-color: #f1f1f1;
}
li a {
    display: block;
    right:0px;
    top:200px;
    color: #000;
    padding: 8px 0 8px 16px;
    text-decoration: none;
}
/* Change the link color on hover */
li a:hover {
    background-color: #555;
    color: white;
}
.left {
    position: absolute;
    left: 0px;
    width: 300px;
    border: 3px solid #708090;
    padding:10px;
}

</style>
</head>
<body>

<h2></h2>
<form action="rpc.php" method="post" >

<?php
 echo $response;
?> 

<input type="submit" name="request" value="deny"/>
<input type="submit" name="request" value="allow"/>
<?php
 echo $meg;
?> 
</form>


<ul>
 
  <li><a href="AdminWelcome.php">My Profile</a></li>
  <li><a href="AdminLogout.php">Log Out</a></li>
</ul>

</body>
</html>