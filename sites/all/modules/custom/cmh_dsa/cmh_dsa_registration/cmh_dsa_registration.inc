<?php
/**
 * @file         cmh_dsa_registration.inc
 * @version      1.0.0
 * @author       CTS
 * @desc         This is a inc file for Registration
 * @date         08/08/2013
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 * @modified by  
 * @modified on  
 * @desc  
 */

/**
 * @desc   - This is a form for Display DSA Registration Form
 * @access - public
 * @param  - $form:  The form being added or edited.
 * @param  - &$form_submit: The form state array.
 * @return - $form
 */
function cmh_dsa_register_form($form, &$form_submit) {
  
  if (isset($form_submit['input']['Email_ID']) && !empty($form_submit['input']['Email_ID'])) {
    cmh_dsa_register_submit($form, &$form_submit);
  }
  if (!empty($form_submit['input']['Country_ID'])) {
    $country_id_val = $form_submit['input']['Country_ID'];
  }
  if (!empty($form_submit['input']['State_ID'])) {
    $state_id_val = $form_submit['input']['State_ID'];
  }
  if (!empty($form_submit['input']['City_ID'])) {
    $city_id_val = $form_submit['input']['City_ID'];
  }
  $form = array(
    '#attributes' => array('name' => 'dsa_registration_form'),
  );
  $form['First_Name'] = array(
    '#type' => 'textfield',
    '#id' => 'txtFirstName',
    '#size' => '40',
		'#maxlength' => '50',
  );
  $form['Last_Name'] = array(
    '#type' => 'textfield',
    '#id' => 'txtLastName',
    '#size' => '40',
		'#maxlength' => '50',
  );
  $form['drpFamilyDetail1dd'] = array(
    '#type' => 'select',
    '#options' => array('0' => t('DD'), '1' => t('1'), '2' => t('2'), '3' => t('3'), '4' => t('4'), '5' => t('5'), '6' => t('6'), '7' => t('7'), '8' => t('8'), '9' => t('9'), '10' => t('10'), '11' => t('11'), '12' => t('12'), '13' => t('13'), '14' => t('14'), '15' => t('15'), '16' => t('16'), '17' => t('17'), '18' => t('18'), '19' => t('19'), '20' => t('20'), '21' => t('21'), '22' => t('22'), '23' => t('23'), '24' => t('24'), '25' => t('25'), '26' => t('26'), '27' => t('27'), '28' => t('28'), '29' => t('29'), '30' => t('30'), '31' => t('31')),
    '#attributes' => array('class' => array('select_width')),
    '#id' => 'drpFamilyDetail1dd',
    
  );
  $form['drpFamilyDetail1mm'] = array(
    '#type' => 'select',
    '#options' =>  array('0' => t('MM'), '1' => t('1'), '2' => t('2'), '3' => t('3'), '4' => t('4'), '5' => t('5'), '6' => t('6'), '7' => t('7'), '8' => t('8'), '9' => t('9'), '10' => t('10'), '11' => t('11'), '12' => t('12')),
    '#attributes' => array('class' => array('select_width')),
    '#id' => 'drpFamilyDetail1mm',
  );
  $options = array('0' => t('YYYY'));
  $starting_year  = date('Y', strtotime('-50 year'));
  //$ending_year = date('Y', strtotime('+15 year'));
	$ending_year = date('Y');
  for ($starting_year; $starting_year <= $ending_year; $starting_year++) {
    $options[$starting_year] =  $starting_year;
  }        
  $form['drpFamilyDetail1yy'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#attributes' => array('class' => array('select_width')),
    '#id' => 'drpFamilyDetail1yy',
  );
  $form['Business_Type'] = array(
    '#type' => 'select',
    '#options' =>  array('0' => t('-Please Select-'), 'Proprietor' => t('Proprietor'), 'Partner' => t('Partner'), 
             'Pvt. Ltd. Dealer' => t('Pvt. Ltd. Dealer'), 'Public Ltd. Dealer' => t('Public Ltd. Dealer'),
             'Self-employed' => t('Self-employed'), 'Professional' => t('Professional')),
    '#id' => 'busType',
  );
  $form['Industry'] = array(
    '#type' => 'textfield',
    '#id' => 'Industry',
    '#size' => '40',
  );
  $form['Current_Turnover'] = array(
    '#type' => 'select',
    '#options' =>  array('0' => t('-Please Select-'), 'Less than 2 lakhs' => t('Less than 2 lakhs'), '2-5 lakhs' => t('2-5 lakhs'), 
             '5-10 lakhs' => t('5-10 lakhs'), '10-20 lakhs' => t('10-20 lakhs'),
             '20-30 lakhs' => t('20-30 lakhs'), '30 lakhs and above' => t('30 lakhs and above')),
  );
  $form['Office_Space'] = array(
    '#type' => 'textfield',
    '#id' => 'txtOffSpace',
    '#size' => '40',
  );
  $form['priorExperience'] = array(
    '#type' => 'radios',
    '#options' => array('Yes' => t('Yes'), 'No' => t('No')),
    '#default_value' => t('No'), 
    '#attributes' => array('class' => array('expradio'), 'prepopulate' => array('yes')),
  );
  $form['priorExperience_otherField'] = array(
    '#type' => 'textfield',
    '#id' => 'textErrExp',
    '#size' => '40',
  );
  $form['knowledgeRating'] = array(
    '#type' => 'radios',
    '#options' => array('Expert' => t('Expert'), 'Good' => t('Good'), 'Novice' => t('Novice'), 'None' => t('None')),
    '#default_value' => t('None'),
		'#attributes' => array('prepopulate' => array('yes')),		
  );
  $form['rdModeOfenquiries'] = array(
    '#type' => 'radios',
    '#id' => 'rdModeOfenquiries',
    '#options' => array('domestic' => t('For Domestic enquiries'), 'international' => t('For International enquiries')),
    '#default_value' => t('domestic'),
    '#attributes' => array('class' => array('domesticIntrRadioBtn'), 'prepopulate' => array('yes')),
  );
  /* call select_country() function to populate the Country Dropdown */
  $result_country = select_country();
  $form['Country_ID'] = array(
    '#type' => 'select',
    '#options' => $result_country,
    '#id' => 'drpResAddrCountry',
   
  );
  $other_country = isset($form_submit['input']['country_otherField']) ? $form_submit['input']['country_otherField'] : '';
  $form['country_otherField'] = array(
    '#type' => 'textfield',
    '#default_value' => $other_country,
    '#id' => 'txtOtherCountry',
    '#attributes' => array('class' => array('inputOtherCountry')),
    '#size' => '40',
  );
  /* call select_state() function to populate the state Dropdown */
  $country_id_val = isset($country_id_val) ? $country_id_val : '1';
  $result_state = select_state($country_id_val);
  $selected_state = isset($state_id_val) ? $state_id_val : '';
  $form['State_ID'] = array(
    '#type' => 'select',
    '#id' => 'drpResAddrState',
    '#options' => $result_state,
    '#default_value' => $selected_state,
    
  );
  $other_state = isset($form_submit['input']['state_otherField']) ? $form_submit['input']['state_otherField'] : '';
  $form['state_otherField'] = array(
    '#type' => 'textfield',
    '#default_value' => $other_state,
    '#id' => 'txtOtherState',
    '#attributes' => array('class' => array('inputOtherState')),
    '#size' => '40',
		'#maxlength' => '50',
  );
  $result_city = select_city($selected_state);
  $selected_city = isset($city_id_val) ? $city_id_val : '';
  $form['City_ID'] = array(
    '#type' => 'select',
    '#id' => 'drpResAddrCity',
    '#options' =>  $result_city,
    '#default_value' => $selected_city,
    
  );
  $other_city = isset($form_submit['input']['city_otherField']) ? $form_submit['input']['city_otherField'] : '';
  $form['city_otherField'] = array(
    '#type' => 'textfield',
    '#default_value' => $other_city,
    '#id' => 'txtOtherCity',
    '#attributes' => array('class' => array('inputOtherCity')),
    '#size' => '40',
		'#maxlength' => '50',
  );
  $form['Mailing_Address'] = array(
    '#type' => 'textarea',
    '#id' => 'txtMailAddress',
    '#cols' => 15,
    '#rows' => 3,
    '#resizable' => FALSE,
    '#required' => TRUE,
  );
  $form['Email_ID'] = array(
    '#type' => 'textfield',
    '#id' => 'txtEmailId',
    '#size' => '40',
  );
  $form['Landline_No_CountryC'] = array(
    '#type' => 'textfield',
    '#id' => 'txtCountryCodeRes',
    '#attributes' => array('class' => array('inputCountryCodeRes'), 'prepopulate' => array('yes')),
    '#default_value' => 'Country Code',
    '#size' => '35',
    '#maxlength' => '4',
  );
  $form['Landline_No_StateC'] = array(
    '#type' => 'textfield',
    '#id' => 'txtAreaCodeRes',
    '#attributes' => array('class' => array('inputAreaCodeRes'), 'prepopulate' => array('yes')),
    '#default_value' => 'State Code',
    '#size' => '35',
    '#maxlength' => '5',
  );
  $form['Landline_No_TelephoneC'] = array(
    '#type' => 'textfield',
    '#id' => 'txtTelephoneRes',
    '#attributes' => array('class' => array('inputTelephoneRes'), 'prepopulate' => array('yes')),
    '#default_value' => 'Telephone',
    '#size' => '35',
    '#maxlength' => '10',
  );
  $form['MobileNumber'] = array(
    '#type' => 'textfield',
    '#id' => 'txtMobile',
    '#size' => '40',
  );
  /* Submit Button */   
  $form['submit'] = array(
    '#value' => 'Submit',
    '#type' => 'submit',
  );
  $form['#submit'][] = 'cmh_dsa_register_submit';
  $form['#theme'] = 'dsa_registration';
  return $form;
}

/**
 * @desc   - This is submit functionfor DSA Registration Form
 * @access - public
 * @param  - $form: The form being added or edited.
 * @param  - &$form_submit: The form state array.
 * @return - NULL
 */
function cmh_dsa_register_submit($form, &$form_state) { 
 
  $prior_experience_val = $form_state['input']['priorExperience'];
  if ($prior_experience_val == 'Yes') {
    $prior_experience_data = $form_state['input']['priorExperience_otherField'];
  }
  else{ 
    $prior_experience_data = $prior_experience_val; 
  }
  $country_id_val = $form_state['input']['Country_ID'];
  if ($country_id_val == 'Other') {
    $country_id_data = $form_state['input']['country_otherField'];
  }else if($country_id_val == '0') {
		$country_id_val = '1';
		$country_id_data = '';
	}else{
    $country_id_data = '';
  }
  $state_id_value = $form_state['input']['State_ID'];
  if ($state_id_value == 'Other') {
    $state_id_data = $form_state['input']['state_otherField'];
  }
  else{
    $state_id_data = '';
  }
  $city_id_value = $form_state['input']['City_ID'];
  if ($city_id_value == 'Other') {
    $city_id_data = $form_state['input']['city_otherField'];
  }
  else{
    $city_id_data = '';
  }

  $enquiry_mode = $form_state['input']['rdModeOfenquiries'];
  $dob_val = $form_state['input']['drpFamilyDetail1yy'] . '-' . $form_state['input']['drpFamilyDetail1mm'] . '-' . $form_state['input']['drpFamilyDetail1dd'];
  if ($dob_val != '0-0-0') {
    $mail_dob_val = $form_state['input']['drpFamilyDetail1dd'] . '-' . $form_state['input']['drpFamilyDetail1mm'] . '-' . $form_state['input']['drpFamilyDetail1yy'];
  }
  else {
    $mail_dob_val = '';
  }
	$country_code=(strtolower($form_state['input']['Landline_No_CountryC'])=="country code")?"":$form_state['input']['Landline_No_CountryC'];
  $area_code=(strtolower($form_state['input']['Landline_No_StateC'])=="state code")?"":$form_state['input']['Landline_No_StateC'];
  $telephone=(strtolower($form_state['input']['Landline_No_TelephoneC'])=="telephone")?"":$form_state['input']['Landline_No_TelephoneC'];
  $mailing_address = trim(strip_tags($form_state['input']['Mailing_Address']));
  //$mail_state=($state_id_value == "Other")?$state_id_data:select_statecity_name($state_id_value);
	if ($state_id_value == "Other") {
		$mail_state = trim($state_id_data);
	} else {
		$mail_state = select_state_name($state_id_value);
	}
  $mail_city=($city_id_value == "Other")?$city_id_data:select_city_name($city_id_value);
	
	if ($country_id_val == 'Other') {
    $mail_country = $form_state['input']['country_otherField'];
  }
  else{
    $mail_country = select_country_name($country_id_val);
  }
	$mobile_number = trim(strip_tags($form_state['input']['MobileNumber']));
	$industry_val = trim(strip_tags($form_state['input']['Industry']));
	$monthly_turnover = $form_state['input']['Current_Turnover'];
	$office_space = trim(strip_tags($form_state['input']['Office_Space']));
	$know_rating = $form_state['input']['knowledgeRating'];		
			  
  if ($dob_val == '0-0-0') {
    $data = array(
      'First_Name' => trim(strip_tags($form_state['input']['First_Name'])),
      'Last_Name' => trim(strip_tags($form_state['input']['Last_Name'])),
      'Business_Type' => $form_state['input']['Business_Type'],
      'Industry' => trim(strip_tags($form_state['input']['Industry'])),
      'Current_Turnover' => $form_state['input']['Current_Turnover'],
      'Office_Space' => trim(strip_tags($form_state['input']['Office_Space'])),
      'Experience' => $prior_experience_data,
      'Rating' => $form_state['input']['knowledgeRating'],
      'Country_ID' => $country_id_val,
      'State_ID' => $state_id_value,
      'City_ID' => $city_id_value,
      'Other_Country' => (!empty($country_id_data)) ? $country_id_data : '',
      'Other_State' => (!empty($state_id_data)) ? $state_id_data : '',
      'Other_City' => (!empty($city_id_data)) ? $city_id_data : '',
      'Mailing_Address' => trim(strip_tags($form_state['input']['Mailing_Address'])),
      'Email_ID' => trim(strip_tags($form_state['input']['Email_ID'])),
      'Country_Code' => trim(strip_tags($country_code)),
      'Area_Code' => trim(strip_tags($area_code)),
      'Telephone' => trim(strip_tags($telephone)),
      'MobileNumber' => trim(strip_tags($form_state['input']['MobileNumber'])),
      'Enquiry' => $enquiry_mode,
    ); 
  }
  else{
    $data = array(
      'First_Name' => trim(strip_tags($form_state['input']['First_Name'])),
      'Last_Name' => trim(strip_tags($form_state['input']['Last_Name'])),
      'DOB' => $dob_val,
      'Business_Type' => $form_state['input']['Business_Type'],
      'Industry' => trim(strip_tags($form_state['input']['Industry'])),
      'Current_Turnover' => $form_state['input']['Current_Turnover'],
      'Office_Space' => trim(strip_tags($form_state['input']['Office_Space'])),
      'Experience' => $prior_experience_data,
      'Rating' => $form_state['input']['knowledgeRating'],
      'Country_ID' => $country_id_val,
      'State_ID' => $state_id_value,
      'City_ID' => $city_id_value,
      'Other_Country' => (!empty($country_id_data)) ? $country_id_data : '',
      'Other_State' => (!empty($state_id_data)) ? $state_id_data : '',
      'Other_City' => (!empty($city_id_data)) ? $city_id_data : '',
      'Mailing_Address' => trim(strip_tags($form_state['input']['Mailing_Address'])),
      'Email_ID' => trim(strip_tags($form_state['input']['Email_ID'])),
      'Country_Code' => trim(strip_tags($country_code)),
      'Area_Code' => trim(strip_tags($area_code)),
      'Telephone' => trim(strip_tags($telephone)),
      'MobileNumber' => trim(strip_tags($form_state['input']['MobileNumber'])),
      'Enquiry' => $enquiry_mode,
    ); 
  }
  try {
		db_set_active('default');	
    /* Insert record in database */
    $is_success = db_insert('cmh_dsa_user')
    ->fields($data)
    ->execute();
  }catch (Exception $e) {
    $logger = log4php_details();
    $logger->error($e->getMessage());
  }
  /* If record has been sent successfully then send the mail to respective zone id and registered person*/
  $arr_data = array();
	if (!empty($is_success)) {
  
    $firstname = trim(strip_tags($form_state['input']['First_Name']));
    $lastname = trim(strip_tags($form_state['input']['Last_Name']));
    $emailid = trim(strip_tags($form_state['input']['Email_ID']));
    $current_business = trim($form_state['input']['Business_Type']);
				
    $arr_data = array("dsafirstname" => $firstname, "dsalastame" => $lastname, "dsadateofbirth" => $mail_dob_val, "dsacurrent_business" => $current_business, "dsaindustry" => $industry_val, "dsamonthlyturnover" => $monthly_turnover, "dsaofficespace" => $office_space, "dsapriorexpr" => $prior_experience_data, "dsaknowledgerate" => $know_rating, "dsacountrycode" => $country_code, "dsacountry" => $mail_country, "dsastate" => $mail_state, "dsacity" => $mail_city, "dsamailing_address" => $mailing_address, "dsaemailid" => $emailid,  "dsaareacode" => $area_code, "dsatelephone" => $telephone, "dsamobilenumber" => $mobile_number);
    
    /* Fetch zone email id for admin email process */
    $zone_email_detail = get_zone_mail_detail($state_id_value);
    
    /* Fetching template format from database */
    $template_data = get_mail_config('dsa_register');
    mail_dsa_user_registration($template_data, $firstname, $lastname, $emailid);
    
    $template_admin_data = get_mail_config('dsa_register_admin');
    mail_dsa_admin_registration($template_admin_data, $arr_data, $zone_email_detail);
    drupal_goto('DsaThankyou');
   
  }
}

/**
 * @desc   - Function to populate country list on page load
 * @access - public
 * @param  - $machine_name: machine name for the country taxonomy.
 * @return - $country_data
 */
function select_country() {
  db_set_active('clubmahindra_db');
	$result = db_query('select Country_ID, Country_Name from cmh_country as cc ORDER BY cc.Country_Name');
  $country_data = array('0' => '-Please Select-', 'Other' => 'Other');
  while ($record = $result->fetchAssoc()) {
    $country_data[$record['Country_ID']] = t($record['Country_Name']);
  }
	db_set_active('default');
	return $country_data;
}

/**
 * @desc   - Function to populate state list on country select
 * @access - public
 * @param  - $machine_name: machine name for the state taxonomy.
 * @return - $state_arr: state array
 */
function select_state($country_id_val) {
  
  if (isset($_POST) && $_POST != '' && !empty($_POST['countryID'])) {
    $country_id = $_POST['countryID'];
  }
  elseif (!empty($country_id_val)) {
    $country_id = $country_id_val;
  }
  else{
    $country_id = '1';
  }
	
	if (!empty($country_id)) {
    
    db_set_active('clubmahindra_db');	
	  $result = db_query('select StateID, StateName from cmh_states as cs where cs.CountryID = ' . "'$country_id'" . ' and cs.CountryID != 0 ORDER BY cs.StateName');
						
    $c_arr = array();
    $c_arr['0'] = '--Please Select--';
    while ($record = $result->fetchAssoc()) {
      $c_arr[$record['StateID']] = ucwords($record['StateName']);
    }		
    $c_arr['Other'] = 'Other';
		$state_array = array('drplist' => $c_arr);
    $state_arr = json_encode($state_array);
		db_set_active('default');
    return $state_arr;
  }
}

/**
 * @desc   - Function to populate city list on state select
 * @access - public
 * @param  - $machine_name: machine name for the city taxonomy.
 * @return - $city_arr: city array
 */
function select_city($state_id_val) {
  
  if (isset($_POST) && $_POST != '' && !empty($_POST['stateID'])) {
    $state_id = $_POST['stateID'];
  }
  elseif (!empty($state_id_val)) {
    $state_id = $state_id_val;
  }
  else{
    $state_id = 47;
  }
  if (!empty($state_id)) {
    db_set_active('clubmahindra_db');	
	  $result = db_query('select city_id, city_name from cmh_city as cct where cct.StateID = ' . "'$state_id'" . ' ORDER BY cct.city_name');
								
    $c_arr = array();
    $c_arr['0'] = '--Please Select--';
    while ($record = $result->fetchAssoc()) {
      $c_arr[$record['city_id']] = ucwords($record['city_name']);
    }
    $c_arr['Other'] = 'Other';
    $cityarray = array('drplist' => $c_arr);
    $city_arr = json_encode($cityarray);
		db_set_active('default');
    return $city_arr;
  }
}
/**
 * @desc   - Common Function for ajax call according to selected dropdown of country and state
 * @access - public
 * @param  - NULL
 * @return - Null
 */
function fill_drop_down() {
  if (isset($_GET['status']) && $_GET['status'] == 'city') {
    if (isset($_GET['state']) && $_GET['state'] != '') {
      $state = $_GET['state']; 
    }
    echo select_city($state);
    exit;
  } 
  elseif (isset($_GET['status']) && $_GET['status'] == 'state') {
    if (isset($_GET['country']) && $_GET['country'] != '') { 
      $country = $_GET['country']; 
    }
    echo select_state($country);
    exit;
  }
}
/**
 * @desc   - Function for checking entered Email ID present in DB or not
 * @access - public
 * @param  - NULL
 * @return - Null
 */
function check_emailid() {
  if (isset($_GET['status']) && $_GET['status'] == 'checkEmail') {
    $email = $_GET['email'];
    echo is_email_exists($email); 
    exit;
  }
}
/**
 * @desc   - Function for checking entered Email ID present in DB or not
 * @access - public
 * @param  - NULL
 * @return - $email_count
 */
function is_email_exists($email) {
  $email_count = 0;
  $result = db_query('select count(Email_ID) as cnt from {cmh_dsa_user} WHERE Email_ID = ' . "'$email'");
  foreach ($result as $email_cnt) {
    $email_count = $email_cnt->cnt;
  }
  return $email_count;
}
/**
 * @desc   - Function to return state name as per selected value
 * @access - public
 * @param  - $id_val: stateid.
 * @return - name of state
 */
function select_state_name($id_val) {
  if (!empty($id_val)) {
    db_set_active('clubmahindra_db');	
    $result = db_query('select cst.StateName as name from {cmh_states} as cst where cst.StateID = ' . "'$id_val'" . '')->fetchObject();
		db_set_active('default');	
    return trim($result->name);
		
  }	
}
/**
 * @desc   - Function to return city name as per selected value
 * @access - public
 * @param  - $id_val: cityid .
 * @return - name of city
 */
function select_city_name($id_val) {
  if (!empty($id_val)) {
    db_set_active('clubmahindra_db');	
    $result = db_query('select cct.city_name as name from {cmh_city} as cct where cct.city_id = ' . "'$id_val'" . '')->fetchObject();
    db_set_active('default');
		return trim($result->name);
			
  }	
}
/**
 * @desc   - Function to return country name as per selected value of country
 * @access - public
 * @param  - $id_val: countryid
 * @return - name of country
 */
function select_country_name($id_val) {
  if (!empty($id_val)) {
		db_set_active('clubmahindra_db');	
    $result = db_query('select ccn.Country_Name as name from {cmh_country} as ccn where ccn.Country_ID = ' . "'$id_val'" . '')->fetchObject();
		db_set_active('default');	
    return trim($result->name);
		
  }	
}