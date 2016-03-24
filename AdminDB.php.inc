<?php

require_once("AdminError.php.inc");
class AdminDB
{
    private $db;
    private $salt;	
    private $logger;
    public function __construct($iniFile)
    {
	$ini = parse_ini_file($iniFile,true);
        $this->logger = new errorLogger("/var/log/it202.log");
	$this->db = new mysqli(
		$ini['loginDB']['host'],
		$ini['loginDB']["user"],
		$ini['loginDB']["password"],
		$ini['loginDB']["db"]);
	$this->salt = $ini['loginDB']['salt'];
	if ($this->db->connect_errno > 0 )
	{
		$this->logger->log(__FILE__.__LINE__."failed to connect to database re: ".$this->db->connect_error);
		exit(0);
	}
	$this->logger->log("testing");
    }
    public function __destruct()
    {
	$this->db->close();
    }

    public function getAdminId($name)
    {
	$query = "select AdminId from admins where AdminName = '$name';";
	$results = $this->db->query($query);
	if (!$results)
	{
	    $this->logger->log("error with results: ".$this->db->error);
	    return 0;
	}
        $admin = $results->fetch_assoc();
	if (isset($admin['AdminId']))
	{
	    return $admin['AdminId'];
	}
	return 0;
    }

    private function saltPassword($password)
    {
	return $this->db->real_escape_string(sha1($password.$this->salt));
    }

    public function validateAdmin($name,$password)
    {
	if ($this->getAdminId($name) == 0)
        {
	    return array("success"=>false,
		"message"=>"admin does not exist");
	}
	$query = "select * from admins where AdminName='$name';";
	$results = $this->db->query($query);
	if (!$results)
	{
	    return array("success"=>false,
		"message"=>"db failure");
	}
        $admin = $results->fetch_assoc();
        {
	    if ($admin['AdminPW'] == $this->saltPassword($password))
	    {
		return array("success"=>true);
	    }
        }
        return array("success"=>false,"message"=>"failed to match password");
    }

    public function addNewAdmin($name,$password)
    {
	if ($this->getAdminId($name) != 0)
        {
	    $this->logger->log("user $name already exists!!!!!");
	    $response = array(
		"message"=>"user $name already exists!",
		"success"=>false
		);
	    return $response;
	}
        $now = date("Y-m-d h:i:s",time());
        $name = $this->db->real_escape_string($name);
	$password = $this->saltPassword($password);
        $addQuery = "insert into admins (AdminName,AdminPW, firstLogin, lastLogin) values ('$name','$password','$now','$now');";
        $results = $this->db->query($addQuery);
	if (!$results)
	{
	    $this->logger->log("error: ".$this->db->error);
	}
	return array("success"=>true);
    }
    // Function to create dynamic list of users, added the form specifically for this portion might need to remove it
   
   public function ListUsers() {
    
      $query = "select * from clients order by clientName DESC";
      $results = $this->db->query($query);

      $header = "<select name = 'client'>";
  
      while ($row = mysqli_fetch_assoc($results)){
      
      $result.=  "<option value= '".$row['clientName']."'>".$row['clientName']."</option>";
      
      }
     
      
      $end = "</select>";
      return $header.$result.$end;
    
   }
 
    // function to deny user access
    public function PermissionDeny($username){
    
    //echo $username;
    
    $query = "update clients set permissions = 0 where clientName = '$username'";
    $result1 = $this->db->query($query);
    
    if (!$result1) {
	return false;
    }else {
	return true;
    }
    
    }
    // function to allow user access
    public function PermissionAllow($username){
    //echo $username;
    $query2 = "update clients set permissions = 1 where clientName = '$username'";
    $result2 = $this->db->query($query2);
    
    if (!$result2) {
	return false;
    }
    if ($result2) {
	return true;
    }
    
    }
    

}
// at this point db is connected
?>
