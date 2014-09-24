<?php
/**
 * @file         cmh_dsa_account.inc
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
 * @desc   - Implementation of hook_form().Display a node editing form.
 * @access - public
 * @param  - $form : The form being added or edited.
 * @param  - $form_submit  : The form state array.
 * @return - An array containing the title and any custom form elements to be displayed in the node editing form. 
 */
function cmh_dsa_myaccount_form($form, &$form_submit) {
  
  $user_id = get_session('dsa_user_data', 'dsa_member_id');
  $details = array('DsaID' => $user_id);
  //$arr_dsa_ws = get_data_ws('getDSADetails', 'GetDSADetailsResult', $details);
  
  $form['dsa_id'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'dsaid',
    //'#disabled' => TRUE,
    '#default_value' => $user_id,
    '#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
  $form['dsa_name'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'dsaname',
    //'#disabled' => TRUE,
    '#default_value' => get_session('dsa_user_data', 'dsa_name'),
    '#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
  $form['owner1'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'owner1',
    //'#disabled' => TRUE,
    //'#default_value' => 'owner1',
   // '#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
  $form['owner2'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'owner2',
    //'#disabled' => TRUE,
    //'#default_value' => 'owner2',
    //'#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
  $form['phone1'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'phone1',
    //'#default_value' => 'phone1',
  );
  $form['phone2'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'phone2',
    //'#default_value' => 'phone2',
  );
  $form['email_address'] = array(
    '#type' => 'textfield',
    '#size' => '30',
    '#id' => 'emailaddress',
    //'#default_value' => 'email id',
  );
  $form['office_address'] = array(
    '#type' => 'textarea',
    '#id' => 'off_address',
    '#cols' => 40,
    '#rows' => 5,
    '#resizable' => FALSE,
    //'#disabled' => TRUE,
    //'#default_value' => 'Hingewadi Pune',
    //'#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
	$form['submit'] = array(
		'#id' => 'save-changepass',
		'#prefix' => '<div class="action-button-border float-left">
										<a title="Submit" onclick="" class="clearfix" id="save-myaccount" href="javascript:void(0)">
											<span class="left"></span>
											<span class="mid">Submit',
		'#suffix' => '</span>
									<span class="right"></span>
									</a></div>',
	);
  
  $form['#theme'] = 'cmh_dsa_myaccount';
  return $form;  
}

/**
 * @desc   - This function is ajax call after submitting the my account form and do the business logic.
 * @access - public
 * @param  - NULL
 * @return - Success message after successfuldata submission
 */
function myaccount_submit_fun() {
  $user_id = get_session('dsa_user_data', 'dsa_member_id');
  if ($user_id == '' && !isset($user_id)) {
    //redirect to login page
    echo "redirect_login";
    exit();
  }
  else {
    $acc_details = array();
    if (isset($_POST) && !empty($_POST)) {
    
      $dsa_id = $_POST['dsa_id'];
      $dsa_name = $_POST['dsa_name'];
      $dsa_owner1 = $_POST['owner1'];
      $dsa_owner2 = $_POST['owner2'];
      $dsa_offaddress = $_POST['office_address'];
      $email_id = $_POST['email_address'];
      $phone1 = $_POST['phone1'];
      $phone2 = $_POST['phone2'];
      
      $acc_details = array("DSA_ID" => $dsa_id, 
                            "DSA_NAME" => $dsa_name, 
                            "OWNER1" => $dsa_owner1, 
                            "OWNER2" => $dsa_owner2, 
                            "PHONE1" => $phone1, 
                            "PHONE2" => $phone2, 
                            "EMAILID" => $email_id, 
                            "OFFADDRESS" => $dsa_offaddress);
                            
      // Update the Account details with webservice
          
      //Mail to Channel manager for personal details updates
      $template_myaccount = get_mail_config('dsa_myaccount');
      //mail_dsa_myaccount($template_myaccount, $phone1, $phone2, $email_id);
      mail_dsa_myaccount($template_myaccount, $acc_details);
      echo "success";  
      exit();
    } 
  }    
}
/**
 * @desc   - Implementation of hook_form(). Display a form for change of password
 * @access - public
 * @param  - $form : The form being added or edited.
 * @param  - $form_submit  : The form state array.
 * @return - An array containing the title and any custom form elements to be displayed in the Change Password form. 
 */	
function cmh_dsa_change_pwd_form($form, &$form_submit) {

	$form['current_password'] = array(
		'#type' => 'password',
		'#size' => '30',
	);
	$form['new_password'] = array(
		'#type' => 'password',
		'#size' => '30',
	);
	$form['confirm_new_password'] = array(
		'#type' => 'password',
		'#size' => '30',
	);
	$form['submit'] = array(
		'#id' => 'save-changepass',
		'#prefix' => '<div class="action-button-border float-left">
										<a title="Submit" onclick="" class="clearfix" id="save-changepass" href="javascript:void(0)">
											<span class="left"></span>
											<span class="mid">Submit',
		'#suffix' => '</span>
									<span class="right"></span>
									</a></div>',
	);
	//$form['#submit'][] = 'validate_current_password';
	$form['#theme'] = 'cmh_dsa_change_pwd';
	return $form;
}
/**
 * @desc   - Ajax function to validate the current password and update database.
 * @access - public
 * @param  - NULL
 * @return - success message
 */  
function validate_current_password() {

  $user_id = get_session('dsa_user_data', 'dsa_member_id');
  if ($user_id == '' && !isset($user_id)) {
    //redirect to login page
    echo "redirect_login";
    exit();
  }
  else {
  
    if (isset($_POST['status']) && $_POST['status']=='checkPwd') {
    
      $hash_current_pass = hash("sha256", $_POST['current_pwd']);
      $result = db_query("select count(Email_ID) as count  from `cmh_dsa_user` where Dsa_ID='" . $user_id . "' and Password='" . $hash_current_pass . "'");
      while ($record = $result->fetchAssoc()) {
        $count = t($record['count']);
      }
      if ( $count > 0 ) {
        if ( $_POST['new_pass'] && isset($_POST['new_pass'] ) ) {
          //encrypting the password
          $hash_new_password = hash("sha256", $_POST['new_pass']);
          //update password in the database.
          db_query("update  `cmh_dsa_user` set Password='" . $hash_new_password . "'  where Dsa_ID='" . $user_id . "'");
          echo "Success";
          exit();
        }
      }
    }
  }
}

