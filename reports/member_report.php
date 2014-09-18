<?php
require_once "Mail.php"; // PEAR Mail package
require_once "Mail/mime.php"; // PEAR Mail_Mime packge

$host="172.16.10.31";
$uname="root";
$pass="mhril";
$database = "cmh_drupal"; 

$connection=mysql_connect($host,$uname,$pass); 

echo mysql_error();

//or die("Database Connection Failed");
$selectdb=mysql_select_db($database) or 
die("Database could not be selected"); 
$result=mysql_select_db($database)
or die("database cannot be selected <br>");

// Fetch Record from Database
$output = "";
$table = "cmh_dsa_user"; // Enter Your Table Name 
$date = date('Y-m-d', strtotime( '-1 days' ));
//$sql = mysql_query("select * from $table where created_date between('$date 00:00') and ('$date 23:59')");
$sql = mysql_query("select * from $table limit 100");
$columns_total = mysql_num_fields($sql);

// Get The Field Name
for ($i = 0; $i < $columns_total; $i++) {
$heading = mysql_field_name($sql, $i);
$output .= '"'.$heading.'",';
}
$output .="\n";

// Get Records from the table
$filename = "file.csv";
$fp = fopen($filename, 'w');
$i = 0;
while($row = mysql_fetch_assoc($sql)) {
	if($i == 0 && $row) {
		fputcsv($fp, array_keys($row));
		// reset pointer back to beginning
		mysql_data_seek($result, 0);
	}
	fputcsv($fp, $row);
	$i++;
}

// Download the file
$headers = array('From' => 'karnavanaja@gmail.com', 'To' => 'karnavanaja@gmail.com', 'Subject' => 'LTR - Become a Member Leads');
$crlf = "\n";

$smtp_host = '172.16.16.21';
$smtp_port = '25';
$smtp_username = 'CMWEBAUTH';
$smtp_password = 'Web_srv@2012';

$mime = new Mail_mime($crlf);
$mime->setHTMLBody('<html><body>Test email</body></html>');
$test=$mime->addAttachment($filename, 'text/csv');
 
//do not ever try to call these lines in reverse order
$body = $mime->get();
$headers = $mime->headers($headers);
 
$smtp = Mail::factory('smtp', array('host' => $smtp_host, 'port' => $smtp_port, 'auth' => FALSE, 'username' => $smtp_username, 'password' => $smtp_password));
print_r($smtp);
$mail = $smtp->send('karnavanaja@gmail.com', $headers, $body);
echo $mail->getMessage().'---'; exit;

?>