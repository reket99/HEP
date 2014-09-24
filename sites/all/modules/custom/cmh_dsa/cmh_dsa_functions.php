<?php
/**
 * @file         dsa_common_function file
 * @version      1.0.0
 * @author       CTS
 * @desc         This is a DAS Common Function file
 * @date         26/07/2013
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 */
 
 /**
 * @desc   - Session Logout after in activity .
 * @access - public
 * @return - NULL
 */
function session_timeout(){ 
	$logLength = SESSION_TIMEOUT; // time in seconds :: 1800 = 30 minutes 
	$ctime = strtotime("now"); // Create a time from a string 
	// If no session time is created, create one 
	$session_val = get_session('dsa_user_data', 'session_timeout');
	if (!isset($session_val) || $session_val == '') {  
			// create session time 
	set_session('dsa_user_data', array('session_timeout' => $ctime));
	}
	else {             
		// Check if they have exceded the time limit of inactivity 
		if (((strtotime("now") - get_session('dsa_user_data', 'session_timeout')) > $logLength) && is_user_session_active()) { 
			//If exceded the time, log the user out 
			global $user;
			if ($user->uid != 1 ) {
				unset_session();
			}
		}
		else{ 
			// If they have not exceded the time limit of inactivity, keep them logged in 
			set_session('dsa_user_data', array('session_timeout' => $ctime));
		} 
	} 
}  
 
/**
 * @desc   - log4php Function for centralising error logs in one file.
 * @access - public
 * @return - logger
 */
function log4php_details() {

  feeds_include_library('Logger.php', 'log4php');
  Logger::configure('sites/all/libraries/log4php/Log4php.properties');
  $logger = Logger::getRootLogger();
  return $logger;
}
/**
 * @desc   - Function for including libraries file.
 * @access - public
 * @return - true/false
 */
function feeds_include_library($file, $library) {
  static $included = array();
  static $ignore_deprecated = array('simplepie');

  if (!isset($included[$file])) {
    // Disable deprecated warning for libraries known for throwing them
    if (in_array($library, $ignore_deprecated)) {
      $level = error_reporting();
      // We can safely use E_DEPRECATED since Drupal 7 requires PHP 5.3+
      error_reporting($level ^ E_DEPRECATED ^ E_STRICT);
    }

    $library_dir = variable_get('feeds_library_dir', FALSE);
    $feeds_library_path = DRUPAL_ROOT . '/' . drupal_get_path('module', 'feeds') . "/libraries/$file";

    // Try first whether libraries module is present and load the file from
    // there. If this fails, require the library from the local path.
    if (module_exists('libraries') && file_exists(libraries_get_path($library) . "/$file")) {
      require libraries_get_path($library) . "/$file";
      $included[$file] = TRUE;
    }
    elseif ($library_dir && file_exists("$library_dir/$library/$file")) {
      require "$library_dir/$library/$file";
      $included[$file] = TRUE;
    }
    elseif (file_exists($feeds_library_path)) {
      // @todo: Throws "Deprecated function: Assigning the return value of new
      // by reference is deprecated."
      require $feeds_library_path;
      $included[$file] = TRUE;
    }
    // Restore error reporting level
    if (isset($level)) {
      error_reporting($level);
    }
  }
  if (isset($included[$file])) {
    return TRUE;
  }
  return FALSE;
}
/**
 * @desc   - Function for getting template from DB according to template type.
 * @access - public
 * @return - array of template data
 */
function get_mail_config($template) {

  $sql = db_select('node', 'n');
  $sql->join('field_data_body ', 'fdb', 'n.nid = fdb.entity_id');
  $sql->join('field_data_field_mail_subject', 'fdfms', 'n.nid = fdfms.entity_id');
  $sql->join('field_data_field_from_id', 'fdffid', 'n.nid = fdffid.entity_id');
  $sql->join('field_data_field_to_id ', 'fdftid', 'n.nid = fdftid.entity_id');
  $sql->fields('n', array('title')) 
      ->fields('fdb', array('body_value')) 
      ->fields('fdfms', array('field_mail_subject_value')) 
      ->fields('fdffid', array('field_from_id_value')) 
      ->fields('fdftid', array('field_to_id_value')); 
  $sql->condition('n.title', $template, '=');
  $result = $sql->execute();
      
  $template_data = array();
  while ($record = $result->fetchAssoc()) {
    $template_data['title'] = t($record['title']);
    $template_data['mail_content'] = t($record['body_value']);
    $template_data['mail_subject'] = t($record['field_mail_subject_value']);
    $template_data['mail_from_id'] = t($record['field_from_id_value']);
    $template_data['mail_to_id'] = t($record['field_to_id_value']);
  }
  return $template_data;
}

/**
 * @desc - Common function for setting session
 * @param - $sess_name : name of a session 
 * @param - $sess_value : value to set into a session this should be array 
 * @return - NULL
 * @author - 362137
 */
function set_session($sess_name, $sess_value) {
  if (!isset($_SESSION[SITE_SESSION][$sess_name])) {
    $_SESSION[SITE_SESSION][$sess_name] = array();
  }
  foreach ($sess_value as $key => $val) {
    $_SESSION[SITE_SESSION][$sess_name][$key] = $val;   
  }
}

/**
 * @desc - Common function for getting session
 * @param - $sess_name : name of a session
 * @param - $sess_property : whose value we want to get from session 
 * @return - value of particular property from session
 * @author - 362137
 */
function get_session($sess_name, $sess_property = '') {
  if (isset($_SESSION[SITE_SESSION][$sess_name])) {
    if ($sess_property != '') {
      return isset($_SESSION[SITE_SESSION][$sess_name][$sess_property]) ? $_SESSION[SITE_SESSION][$sess_name][$sess_property] : '';
    }
    else{
      return isset($_SESSION[SITE_SESSION][$sess_name]) ? $_SESSION[SITE_SESSION][$sess_name] : '' ;
    }
  } 
}

/**
 * @desc   - Common function for unset session
 * @param  - $sess_name : name of a session
 * @param  - $sess_property : whose value we want to unset from session 
 * @return - NULL
 */
function unset_session($sess_name = '', $sess_property = '') {
  if (isset($_SESSION[SITE_SESSION][$sess_name])) {
    if ($sess_property != '') {
      unset($_SESSION[SITE_SESSION][$sess_name][$sess_property]);
    }
    else{
      unset($_SESSION[SITE_SESSION][$sess_name]);
    }
  }
  else {
    unset($_SESSION[SITE_SESSION]);
  }  
}

/**
 * @desc   - Common function for system configuration
 * @access - public
 * @param  - $property_name : whose system configuration want to get 
 * @return - returns a string containing configuration property value
 * @author - 362137
 */
function get_system_config($property_name) {
  if (isset($property_name) && $property_name != '') {
    try{
      $result = db_query("select b.body_value as value from {node} n left join {field_data_body} b on b.entity_id = n.nid where n.title = :title", array(":title" => $property_name))->fetchObject();
      return trim($result->value);
    }
    catch (Exception $e) {
      $logger = log4php_details();
      $logger->error($e->getMessage());
    }
  }
  else{
    return FALSE;
  }
}

/**
 * @desc   - This is to get the dsa member details from web service.
 * @access - public
 * @param  - $ws_name : name of webservice
 * @param  - $ws_response : response name
 * @param  - $details : details to be passed to a webservice to fetch data in array format
 * @param  - $sort(optional) : if want webservice result in sorted order then pass 'SORT' as param
 * @param  - $sort_by(optional) : to sort result by which object like sort by memberID or memberName etc
 * @return - Returns an array of data comes from webservice response(optional sorted order)
 */
function get_data_ws($ws_name, $ws_response, $details, $sort = '', $sort_by = '') {
  $logger = log4php_details();
  //create object of soap client with service url
  $ws_url = get_system_config('webserviceurl');
  try{
    $service_start = microtime(true);
    $logger->debug('Service call starts');
    $client = new SoapClient($ws_url);
    $obj_details = (object) $details;
    //function call for webservice to get the details
    $response = $client->$ws_name($obj_details);
    $microtime_end = microtime(true);
    $logger->debug($response);
    $logger->debug('Service call End');
    $timetaken = round($microtime_end - $service_start, 5);
    $logger->debug('Time taken to fetch webservice -->' . $ws_name . ' details is:' . $timetaken);
    //parsing of response to xml 
    $xml = simplexml_load_string($response->$ws_response);    
    //parsing of xml to json
    $microtime_start = microtime(true);
    $json = drupal_json_encode($xml);
    //decode of json to array 
    $detail_array = drupal_json_decode($json);
    $microtime_end = microtime(true);
    $timetaken = round($microtime_end - $microtime_start, 5);
    $logger->debug('Time taken to fetch webservice response-->' . $ws_response . ' is:' . $timetaken);
    //for sorting the result
    if ($sort == 'SORT' || $sort !='') {
      foreach ($detail_array[$ws_name] as $array2) {
        foreach ($array2['@attributes'] as $key => $val) {
          $array3[$key][]  = $val;
        }
      }
      array_multisort($array3[$sort_by], SORT_STRING, $detail_array[$ws_name]);
      foreach ($detail_array[$ws_name] as $arr) {
        $arr_members[$arr['@attributes']['MemberId']][$arr['@attributes']['MembershipId']] = $arr['@attributes'];
      }
      $detail_array = $arr_members;
    } 
    return $detail_array;
  }
  catch (Exception $e) {
    $elapsed = elapsedtime($service_start, microtime(true));
    $controller = 'get_data_ws-' . $ws_name;
    logcontext("", "", $controller, "failiure", $elapsed);
    $logger->error($e->getMessage());
  }
}

/**
 * @desc   - Function for getting Registration page header and left panel from content type.
 * @access - public
 * @return - array()
 * @param  - Category ID and image 
 */
 function get_registration_page_content($category_name, $image='') {
  
  if (!empty($image)) {  
    $sql = db_select('node', 'n');
    $sql->join('field_data_body', 'fdb', 'n.nid = fdb.entity_id');
    $sql->join('field_data_field_registration_image', 'fdfri', 'n.nid = fdfri.entity_id');
    $sql->join('field_data_field_page_category', 'fdfpc', 'n.nid = fdfpc.entity_id');
    $sql->join('taxonomy_term_data', 'ttd', 'ttd.tid = fdfpc.field_page_category_tid');
    $sql->fields('n', array('title')) 
        ->fields('fdb', array('body_value'))
        ->fields('fdfri', array('field_registration_image_fid '));
    $sql->condition('ttd.name', $category_name, '=');
    
    $result = $sql->execute();
    $registration_content = array();
    while ($record = $result->fetchAssoc()) {
      $registration_content['title'] = t($record['title']);
      $registration_content['header_body'] = t($record['body_value']);
      $registration_content['image_val'] = t($record['field_registration_image_fid']);
    }
  }
  else{    
    $sql = db_select('node', 'n');
    $sql->join('field_data_body', 'fdb', 'n.nid = fdb.entity_id');
    $sql->join('field_data_field_page_category', 'fdfpc', 'n.nid = fdfpc.entity_id');
    $sql->join('taxonomy_term_data', 'ttd', 'ttd.tid = fdfpc.field_page_category_tid');
    $sql->fields('n', array('title')) 
        ->fields('fdb', array('body_value'));
    $sql->condition('ttd.name', $category_name, '=');
    
    $result = $sql->execute();
    $registration_content = array();
    while ($record = $result->fetchAssoc()) {
      $registration_content['title'] = t($record['title']);
      $registration_content['header_body'] = t($record['body_value']);
    }
  }
  return $registration_content;
}
/**
 * @desc   - Function for getting email details as per state zone name.
 * @access - public
 * @return - email string
 * @param  - State ID
 */
function get_zone_mail_detail($stateid) {
  $zone="";
  if (strtolower($stateid)!='other') {          
    $sql = db_select('taxonomy_term_data', 'ttd');
    $sql->join('field_data_field_zone', 'fdfz', 'ttd.tid = fdfz.field_zone_tid');
    $sql->fields('ttd', array('name')) ;
    $sql->condition('fdfz.entity_id', $stateid, '=');
    $result = $sql->execute();
    
    while ($record = $result->fetchAssoc()) {
      $zone_name = $record['name'];
    }
    $zone=strtoupper($zone_name) . "_ZONE";
  }
  $arr_zone_mail = get_zone_mail($zone);
  
  $arrmail_data=array();
  foreach ($arr_zone_mail as $arr_zone) { 
    $arrmail_data[] = $arr_zone;
  }
  $arrmail_data = array_unique($arrmail_data);
  $mailto = implode(",", $arrmail_data);
  return $mailto;
}
/**
 * @desc   - Function for getting email details as per state zone name.
 * @access - public
 * @return - email array()
 * @param  - Zone Name
 */
function get_zone_mail($zone) {  
  $arrzone=(!empty($zone) && $zone!='_ZONE') ? array($zone) : array("EAST_ZONE", "WEST_ZONE", "SOUTH_ZONE", "NORTH_ZONE", "CENTRAL_ZONE");
  try{
    $all_zone_email = array();
    if (count($arrzone) > 1) { 
      $result = db_query("select n.nid, b.body_value as value from {node} n left join {field_data_body} b on b.entity_id = n.nid where n.title in ('EAST_ZONE','WEST_ZONE','SOUTH_ZONE','NORTH_ZONE','CENTRAL_ZONE')");
      while ($record = $result->fetchAssoc()) {
        $all_zone_email[] = $record['value'];
      }
    }
    else{ 
      $all_zone_email[] = get_system_config($arrzone);
    }
  }
  catch (Exception $e) {
    $logger = log4php_details();
    $logger->error($e->getMessage());     
  }
  return $all_zone_email;
}
/**
 * @desc   - Function for Mail sent to user after DSA registration
 * @access - public
 * @return - value
 * @param  - parameter,firstname,lastname,emailid
 */
function mail_dsa_user_registration($parameter, $firstname, $lastname, $emailid) {
  $logger = log4php_details();
  
  $subject = $parameter['mail_subject'];
  $body = $parameter['mail_content'];

  $logger->debug("---> for registration");
  $logger->debug($parameter);

  $name = ucfirst(stripcslashes($firstname));
  $lname = ucfirst(stripcslashes($lastname));
  $to = $emailid;
  $from = $parameter['mail_from_id'];

  //Replace placeholders with actual values.
  $logo_image = get_system_config('MAIL_TEMPLATE_LOGO');
  $security_url = get_system_config('SITE_EMAIL_SECURITY_URL');
  $body = str_replace("MAIL_TEMPLATE_LOGO", $logo_image, $body);
  $body = str_replace("SITE_EMAIL_SECURITY_URL", $security_url, $body);

  $body = str_replace("FIRSTNAME", $name, $body);
  $body = str_replace("LASTNAME", $lname, $body);
  $logger->debug($body);
  $parameter = array('Subject' => $subject, 'to' => $to, 'from' => $from, 'body' => $body, 'key' => 'Registration');
  return send_email($parameter);
}
/**
 * @desc   - Function for Mail sent to admin after DSA registration
 * @access - public
 * @return - value
 * @param  - parameter,arrdata,emailId
 */
function mail_dsa_admin_registration($parameter, $arrdata, $to) {
  $logger = log4php_details();
  $subject = $parameter['mail_subject'];
  $body = $parameter['mail_content'];
  
  $logger->debug("---> for registration");
  $logger->debug($parameter);
  
  $from = $arrdata['dsaemailid'];
  //Replace placeholders with actual values.
  $logo_image = get_system_config('MAIL_TEMPLATE_LOGO');
  $security_url = get_system_config('SITE_EMAIL_SECURITY_URL');
  $body = str_replace("MAIL_TEMPLATE_LOGO", $logo_image, $body);
  $body = str_replace("SITE_EMAIL_SECURITY_URL", $security_url, $body);

  foreach ($arrdata as $key => $value)
    $body = str_replace($key, $value, $body);
  $logger->debug($body);

  $parameter = array('Subject' => $subject, 'to' => $to, 'from' => $from, 'body' => $body, 'key' => 'Registration');
  return send_email($parameter);
}

/**
 * @desc   - Function for Mail sent to admin for Feedback
 * @access - public
 * @return - value
 * @param  - parameter,arrdata
 */
function mail_feedback($parameter, $arrdata) {
  $logger = log4php_details();
  $subject = $parameter['mail_subject'];
  $body = $parameter['mail_content'];
  $to = $parameter['to'];
  $from = $parameter['from'];
  $key = $parameter['key'];
  
  $logger->debug("---> for feedback");
  $logger->debug($parameter);
  
  //Replace placeholders with actual values.
  $logo_image = get_system_config('MAIL_TEMPLATE_LOGO');
  $security_url = get_system_config('SITE_EMAIL_SECURITY_URL');
  $body = str_replace("MAIL_TEMPLATE_LOGO", $logo_image, $body);
  $body = str_replace("SITE_EMAIL_SECURITY_URL", $security_url, $body);
  
  foreach ($arrdata as $key => $value)
    $body = str_replace($key, $value, $body);
  $logger->debug($body);

  $parameter = array('Subject' => $subject, 'to' => $to, 'from' => $from, 'body' => $body, 'key' => $key);
  return send_email($parameter);
}

/**
 * @desc   - Function for Mail sent to DSA for Forgot Password
 * @access - public
 * @return - value
 * @param  - parameter,arrdata
 */
function mail_forgot_pwd($parameter, $arrdata) {
  $logger = log4php_details();
  $subject = $parameter['mail_subject'];
  $body = $parameter['mail_content'];
  $to = $parameter['to'];
  $from = $parameter['from'];
  $key = $parameter['key'];
  
  $logger->debug("---> for Forgot Password");
  $logger->debug($parameter);
  
  //Replace placeholders with actual values.
  $logo_image = get_system_config('MAIL_TEMPLATE_LOGO');
  $security_url = get_system_config('SITE_EMAIL_SECURITY_URL');
  $body = str_replace("MAIL_TEMPLATE_LOGO", $logo_image, $body);
  $body = str_replace("SITE_EMAIL_SECURITY_URL", $security_url, $body);
  
  foreach ($arrdata as $key => $value)
    $body = str_replace($key, $value, $body);
  $logger->debug($body);

  $parameter = array('Subject' => $subject, 'to' => $to, 'from' => $from, 'body' => $body, 'key' => $key);
  return send_email($parameter);
}

/**
 * @desc   - Function for Mail sent to DSA for Availability
 * @access - public
 * @return - value
 * @param  - parameter,arrdata
 */
function mail_availability($parameter, $arrdata) {
  $logger = log4php_details();
  $subject = $parameter['mail_subject'];
  $body = $parameter['mail_content'];
  $to = $parameter['to'];
  $from = $parameter['from'];
  $key = $parameter['key'];
  
  $logger->debug("---> for Availability Details");
  $logger->debug($parameter);
  
  //Replace placeholders with actual values.
  $logo_image = get_system_config('MAIL_TEMPLATE_LOGO');
  $security_url = get_system_config('SITE_EMAIL_SECURITY_URL');
  $body = str_replace("MAIL_TEMPLATE_LOGO", $logo_image, $body);
  $body = str_replace("SITE_EMAIL_SECURITY_URL", $security_url, $body);
  
  foreach ($arrdata as $key => $value)
    $body = str_replace($key, $value, $body);
  $logger->debug($body);

  $parameter = array('Subject' => $subject, 'to' => $to, 'from' => $from, 'body' => $body, 'key' => $key);
  return send_email($parameter);
}


/**
 * @desc   - Function to check if user session is active
 * @access - public
 * @param  - NULL
 * @return - NULL
 */

function is_user_session_active($js_call = '') {
  global $user;
  if ($user->uid ==1 ) {
    if ($js_call != '' && $js_call == 'ajax') {
      echo 'TRUE';exit;
    }
    else {
      return TRUE;
    }
  }
  else {
    $dsa_member_id = get_session('dsa_user_data', 'dsa_member_id');
    
    if ($dsa_member_id == '') {
      if ($js_call != '' && $js_call == 'ajax') {
        echo 'FALSE'; exit;
      }
      else { 
        return FALSE;
      }
    } 
    else {
      if ($js_call != '' && $js_call == 'ajax') {
        echo 'TRUE';exit;
      }
      else { 
        return TRUE;
      }
    }
  }
}
/**
 * @desc   - Function for sending an email in Drupal
 * @access - public
 * @return - value
 * @param  - parameter
 */
function send_email($parameter) {
  require_once "mail.php"; // PEAR Mail package
  require_once('Mail/mime.php'); // PEAR Mail_Mime packge
  
  $logger = Logger::getRootLogger();
  $host = get_system_config('smtp_host');
  $port = get_system_config('smtp_port');
  $username = get_system_config('smtp_username');
  $password = get_system_config('smtp_password');
   
  $headers = array('From' => $parameter['from'], 'To' => $parameter['to'], 'Subject' => $parameter['Subject']);
  $crlf = "\n";
   
  $mime = new Mail_mime($crlf);
  $mime->setHTMLBody($parameter['body']);
  //$test=$mime->addAttachment($file, 'image/jpeg');
   
  //do not ever try to call these lines in reverse order
  $body = $mime->get();
  $headers = $mime->headers($headers);
   
  $smtp = Mail::factory('smtp', array('host' => $host, 'port' => $port, 'auth' => FALSE, 'username' => $username, 'password' => $password));
  $mail = $smtp->send($parameter['to'], $headers, $body);
  
  if (PEAR::isError($mail)) {
    $logger->debug("<p>" . $mail->getMessage() . "</p>");
  return FALSE;
  }
  else {
    return TRUE;
  }  
}
/**
 * @desc   - Function to generate token value
 * @access - public
 * @param  - $memberid : The user Id
 * @return - A string of token value
 */ 
function generate_token($memberid) {
  $chars = "abcdefghij012345" . $memberid;
  srand((double)microtime()*1000000);
  $i = 0;
  $token = '' ;

  while ($i <= 7) {
    $num = rand() % 33;
    $tmp = substr($chars, $num, 1);
    $token = $token . $tmp;
    $i++;
  }
  return substr(hash("sha256", $token), 0, 20);
}

/**
 * function to log the context
 * @access - public
 * @param  $loginid : (member/demo member userID) can be send in case of member login and demo login else blank
 * @param  $message : can be blank
 * @param  $controller : function name in which logcontext is called.
 * @param  $response : success or failure
 * @param  $responsetime : elapsed time
 * @return 
 */
function logcontext($loginid, $message, $controller, $response, $responsetime) {
  //to get url
  $url = 'http';
  if ($_SERVER["HTTPS"] == "on")
    $url .= "s";
  $url .= "://";
  if ($_SERVER["SERVER_PORT"] != "80") {
    $url .= $_SERVER["SERVER_NAME"] . ":" . $_SERVER["SERVER_PORT"] . request_uri();
  } 
  else {
    $url .= $_SERVER["SERVER_NAME"] . request_uri();
  }
  //to get screenname
  $args = arg();
  $screenname = $args[0];
  
  if (!stristr(strtolower($controller), 'booking')) {
    $log_context_var = LOG_CONTEXT_VAR;
    if ($log_context_var == "yes") {
      try{
      //to get loginid
        if ($loginid == '')
          $loginid = 0;
      //data to insert
        $data = array(
          'Ip' => IP, 
          'Login_Id' => $loginid, 
          'Message' => $message, 
          'Url' => $url, 
          'Session_Id' => SESSID,
          'Screen_Name' => $screenname,
          'Controller' => $controller,
          'Response' => $response,
          'Response_Time' => $responsetime,
          'UserAgent' => USER_AGENT,
          );
        /* Insert record in database */
        $is_success = db_insert('cmh_audit_log')
        ->fields($data)
        ->execute();
      }
      catch (Exception $e) {
        $logger = log4php_details();
        $logger->error($e->getMessage());
      }
    }
  }
}

/**
 * function to get the elapsed time
 * @param $starttime
 * @param $enddtime
 * @return $elapsed : elapsed time
 */
function elapsedtime($starttime, $enddtime) {
  $elapsed = $enddtime-$starttime;
  return $elapsed;
}

/**
 * @desc   - Function for Mail sent to Channel manager after updating account details
 * @access - public
 * @return - value
 * @param  - parameter,firstname,lastname,emailid
 */
function mail_dsa_myaccount($parameter, $acc_details) {

  $logger = log4php_details();
  
  $subject = $parameter['mail_subject'];
  $body = $parameter['mail_content'];

  $logger->debug("query post");
  $logger->debug($parameter);

  $to = $parameter['mail_to_id'];
  $from = $acc_details['EMAILID'];
    
  //Replace placeholders with actual values.
  $logo_image = get_system_config('MAIL_TEMPLATE_LOGO');
  $security_url = get_system_config('SITE_EMAIL_SECURITY_URL');
  $body = str_replace("MAIL_TEMPLATE_LOGO", $logo_image, $body);
  $body = str_replace("SITE_EMAIL_SECURITY_URL", $security_url, $body);
  
	foreach ($acc_details as $key => $value)
    $body = str_replace($key, $value, $body);
  $logger->debug($body);
		
  $parameter = array('Subject' => $subject, 'to' => $to, 'from' => $from, 'body' => $body, 'key' => 'dsa_myaccount');
  return send_email($parameter);
}

/**
 * @desc   - function to auto complete, rechech & onchange ajax for member ID
 * @access - public
 * @param  - $_POST : variables from the $_POST
 * @return - NULL
 */
function member_autocomplete_callback($string = "") {
  $dsa_members = array();
  $searchby_memberid = array();
  $dsa_members_memberid = array();
  // $dsa_members = get_session('search_member_ws_data');
 
  $dsa_id = get_session('dsa_user_data', 'dsa_member_id');
	$details = array('DsaID' => $dsa_id);
  //$dsa_members = get_data_ws('SearchMemberbyDSAID', 'SearchMemberbyDSAIDResult', $details, 'SORT', 'MemberName');

	$dsa_members = get_session('search_member_ws_data');
	if (empty($arr_dsa_members)) {
		$dsa_members = get_data_ws('SearchMemberbyDSAID', 'SearchMemberbyDSAIDResult', $details, 'SORT', 'MemberName');
		set_session('search_member_ws_data', $dsa_members);
	}  
	
  foreach ($dsa_members as $arr_members) {
		foreach ($arr_members as $members);
    $searchby_memberid[] = $members['MemberId'];
    $dsa_members_memberid[$members['MemberId']] = $members['MembershipId'];
  }
  
  //Code for the ajax to get the contract Id
  if ( $_POST['member_str_contract'] ) {
    drupal_json_output($dsa_members_memberid[$_POST['member_str_contract']]);
  } 
  elseif ( $_POST['member_str'] ) {
    //Code for the ajax check on change if selected val is correct
    $flag = 'invalid';
    $fl_array = preg_grep('/^' . $_POST['member_str'] . '.*/', $searchby_memberid);
    
      if ( in_array($_POST['member_str'], $fl_array) ) {
        $flag = 'valid';
      }
      else {
        $flag = 'invalid';
      }
    echo  $flag;
  }
  else {
    //Code for the auto complete ajax
    $matches = array();
    if ( $string ) {
      $fl_array = preg_grep('/^' . $string . '.*/', $searchby_memberid);
      foreach ( $fl_array as $index => $key ) {
        $matches[$key] = $key;
      }
      drupal_json_output($matches);
    };
  }
}