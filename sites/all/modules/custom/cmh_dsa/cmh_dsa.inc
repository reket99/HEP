<?php
/**
 * @file         cmh_dsa.inc
 * @version      1.0.0
 * @author       CTS
 * @desc         This is a DAS functionality file
 * @date         16/08/2013
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 * @modified by  
 * @modified on  
 * @desc  
 */

/////////////////////////Login Functionality Start///////////////////////////// 
 /**
 * @desc   - Implementation of hook_form().Display a node editing form.
 * @access - public
 * @param  - $form : The form being added or edited.
 * @param  - $form_submit  : The form state array.
 * @return - An array containing the title and any custom form elements to be displayed in the node editing form. 
 */ 
function cmh_dsa_login_form($form, &$form_submit) { 
  //To check if user session is active
  if (!is_user_session_active()) {
    $form['user_id'] = array(
      '#type' => 'textfield',
    );
    $form['password'] = array(
      '#type' => 'password',
    );
    $form['submit'] = array(
      '#value' => '',
      '#type' => 'submit',
    );    
    $form['#submit'][] = 'cmh_dsa_login_submit';
    $form['#theme'] = 'cmh_dsa_login';
    return $form;
  } 
  else {
    drupal_goto('Dashboard');
  }
}


/**
 * @desc   - This is to submit the form and do the business logic.
 * @access - public
 * @param  - $form : The form being used 
 * @param  - $form_state  :  The form state array.
 * @return - NULL
 */
function cmh_dsa_login_submit($form, &$form_state) { 
  //Removing the tags,spaces from the post variables 
  $user_id  = trim(strip_tags($_REQUEST['user_id']));
  $password = trim(strip_tags($_REQUEST['password']));
  //Validating the Post variables 
  if ( isset($user_id) && isset($password) &&  $user_id != '' &&  $password != '' ) {
    //encrypting the password
    $hash_password=hash("sha256", $password);
//    $hash_password=hash("sha256", 'dsa123');
//print_r($hash_password);    
//db query to fetch the records for the given details
    try{
      $result = db_query("select Dsa_ID,First_Name,Last_Name from {cmh_dsa_user} where Dsa_ID='" . $user_id . "' and Status='ACTIVE' and Password='" . $hash_password . "'");
      while ($record = $result->fetchAssoc()) {
        $dsa_user_data[] = t($record);
      }
    } catch (Exception $e) {
      $logger = log4php_details();
      $logger->error($e->getMessage());
    }
    //Set the flag for for redirect
    $is_valid = FALSE;
    //If user is validated from DB then check for the Web Service
    if (!empty($dsa_user_data)) {
      //call WS here
      $details = array('DsaID' => $user_id);
      $arr_dsa_ws = get_data_ws('getDSADetails', 'GetDSADetailsResult', $details);
      
      //if WS retirns data then set properties in the session
      if (is_array($arr_dsa_ws) && isset($arr_dsa_ws['GetDSADetails']) && count($arr_dsa_ws['GetDSADetails']) > 0) {
        $is_valid = TRUE;
        $dsa_agnet_name = (isset($arr_dsa_ws['GetDSADetails']['0']['@attributes']['DSASalesAgentName']))?$arr_dsa_ws['GetDSADetails']['0']['@attributes']['DSASalesAgentName']:$arr_dsa_ws['GetDSADetails']['@attributes']['DSASalesAgentName'];
        //set the id in the session
        //set the agent name in the session
        set_session('dsa_user_data', array('dsa_member_id' => $user_id));
        set_session('dsa_user_data', array('dsa_name' => $dsa_agnet_name));
        //update datatime in the database.
        try {
      db_query("update {cmh_dsa_user} set Last_login_time=now(), Successful_logins=Successful_logins+1 where DSA_ID='" . $user_id . "'");
        } catch (Exception $e) {
          $logger = log4php_details();
          $logger->error($e->getMessage());
        }
        if ($is_valid) {
          //redirect to the Sales Tools page
          $form_state['redirect'] = 'Dashboard';
        }
      }
    }
    else {
      set_session('dsa_user_data', array('dsa_login_err' => 'invalid'));
      return FALSE;
    }
  }
  else {
    set_session('dsa_user_data', array('dsa_login_err' => 'invalid'));
    return FALSE;
  }
}
/////////////////////////Login Functionality End/////////////////////////////

/////////////////////////forgot Password Functionality Start/////////////////////////////
/**
 * @desc   - Ajax function to validate the current password.
 * @access - public
 * @param  - $user_id
 * @param  - $email_id
 * @param  - $tojenval
 * @param  - $update_tokenval
 * @param  - $pwd
 * @param  - $conpwd
 * @param  - $vercode
 * @param  - $sign_flag
 * @return - NULL
 */ 
function forgot_password($user_id = '', $email_id = '',  $tokenval = '',  $update_tokenval = '', $pwd = '', $conpwd = '', $vercode = '', $sign_flag = '') {
  if ($sign_flag == 'invalid') {
    $sign_flag = '';
  }
  //For the forgot password ajax
  if ($email_id != '') {
    //to get first name from database for validate user
     // $result_data = db_query("select First_Name,Email_ID from {cmh_dsa_user} where Email_ID = '" . $email_id . "' and Dsa_ID = '" . $user_id . "'");
     $result_data = db_query("select First_Name,Email_ID from {cmh_dsa_user} where Email_ID = :email_id and Dsa_ID = :user_id", array(':email_id' => $email_id, ':user_id' => $user_id));
    
    while ($record = $result_data->fetchAssoc()) {
      $user_details['First_Name'] = $record['First_Name'];
      $user_details['Email_ID'] = $record['Email_ID'];
    }
    if ($user_details['First_Name'] != '') {
      $token = generate_token($user_id);
      //$timestamp = date('Y-m-d G:i:s');
    //$timestamp = strtotime(date('Y-m-d G:i:s'))+6000;
      //Update the moviedb table
      // $is_update = db_update('cmh_dsa_user')->fields(array(
            // 'Token_Val' => $token,
            //'Token_Expiry' => $timestamp,
            //'Token_Expiry' => " DATE_ADD(now(),  INTERVAL '1:1' MINUTE_SECOND) ",
          // ))->condition('DSA_ID', $user_id)
            // ->execute();
    
    $is_update = db_query("update {cmh_dsa_user} set Token_Val = :token ,Token_Expiry = DATE_ADD(now(),  INTERVAL '10:0' MINUTE_SECOND) where DSA_ID = :user_id", array(':token' => $token, ':user_id' => $user_id));      
      // If record has been sent successfully then send the mail to respective zone id 
      if ($is_update) {
        $template_data = get_mail_config('dsa_forgot_pwd');
          
        $arrdata = array();
        $arrdata['FIRSTNAME'] = $user_details['First_Name'];
        $arrdata['LASTNAME'] =   $user_details['Last_Name'];
        $arrdata['DSA_ID'] = $user_id;
       // $arrdata['FORGOT_PASS_URL'] = SITE_URL . '/forgot_password/' . $user_id . '//' . $token . '/////DSAForgotPassword.php?show=ok&token=' . $token . '&userid=' . $user_id;
        $arrdata['FORGOT_PASS_URL'] = SITE_URL . '?q=forgot_password/' . $user_id . '//' . $token . '/////valid';

        $parameter = array();
        $parameter['mail_subject'] = $template_data['mail_subject'];        
        $parameter['mail_content'] = $template_data['mail_content'];;
        $parameter['to'] = $user_details['Email_ID'];
        $parameter['from'] = $template_data['mail_from_id'];
        $parameter['key'] = 'forgot_pwd';
        
        $sent = mail_forgot_pwd($parameter, $arrdata);
        if ($sent) {
          echo "valid";
        }
    else {
      echo "invalid_mail";
    }
      }
    } 
    else {
      echo "invalid";
    }
  }
  
  //if hit on URL from mail then if token is there
  if ($tokenval != '') {
    //$userid=$_REQUEST{'userid'};
    $current_time = date("d-m-Y H:i:s");
    
    $result_data = db_query("select Token_Val,DATE_FORMAT(Token_Expiry,'%d-%m-%Y %H:%i:%s') as Token_Expiry,DSA_ID from {cmh_dsa_user} where Token_Val = :tokenval and DSA_ID = :user_id", array(':tokenval' => $tokenval, ':user_id' => $user_id));
  
    while ($record = $result_data->fetchAssoc()) {
      $response_time['Token_Val'] = $record['Token_Val'];
      $response_time['Token_Expiry'] = $record['Token_Expiry'];
      $response_time['DSA_ID'] = $record['DSA_ID'];
    } 

    //$day_difference = (round((strtotime($current_time) - strtotime($response_time['Token_Expiry']))) / 86400) ;
    $day_difference = (round((strtotime($current_time) - strtotime($response_time['Token_Expiry']))) / 600) ;
    
    $expiry_limit = 1;
    
    if ($day_difference > $expiry_limit) {
      set_session('dsa_user_data', array('dsa_user_id_reset_errormsg' => 'Sorry ! The change password link has expired.'));
    } 
    else {
      unset_session('dsa_user_data', 'dsa_user_id_reset_errormsg');
    }
    // Call the Dsa Reset Form here
    set_session('dsa_user_data', array('dsa_user_id_reset' => $user_id));
    set_session('dsa_user_data', array('dsa_token_reset' => $tokenval));
    return drupal_render(drupal_get_form('cmh_dsa_reset_password_form'));
  } 
  
  if ($update_tokenval != '') {
  
  $current_time = date("d-m-Y H:i:s");
    
    $result_data = db_query("select Token_Val,DATE_FORMAT(Token_Expiry,'%d-%m-%Y %H:%i:%s') as Token_Expiry,DSA_ID from {cmh_dsa_user} where Token_Val = :tokenval and DSA_ID = :user_id", array(':tokenval' => $update_tokenval, ':user_id' => $user_id));
  
    while ($record = $result_data->fetchAssoc()) {
      $response_time['Token_Val'] = $record['Token_Val'];
      $response_time['Token_Expiry'] = $record['Token_Expiry'];
      $response_time['DSA_ID'] = $record['DSA_ID'];
    } 

    //$day_difference = (round((strtotime($current_time) - strtotime($response_time['Token_Expiry']))) / 86400) ;
    $day_difference = (round((strtotime($current_time) - strtotime($response_time['Token_Expiry']))) / 600) ;
    
    $expiry_limit = 1;
    
    if ($day_difference > $expiry_limit) {
      echo 'link_expired';
    } 
    else {
      $sesvercode = get_session('dsa_user_data', 'vercode');
      if (($vercode != $sesvercode) || $sesvercode=='') {
        // This code is for new das users. We are not doing this part now.
        // if ($sign_flag != '')
        // {
        // //$objSmarty->assign("validationStatus",'createErrCode');
        // echo 'createErrCode';
        // }
        if ($sign_flag == '') {
          echo 'errorcode';
        }
      } 
      else {
        //if everything is correct then update in the database with new password
        $pwd = hash("sha256", $pwd);
        db_query("update {cmh_dsa_user} set Password = :pwd ,Token_Val = :update_tokenv ,Status = 'active', Token_Expiry = now() where DSA_ID = :user_id", array(':pwd' => $pwd, ':update_tokenv' => $update_tokenv, ':user_id' => $user_id));

        $token = generate_token($user_id);
        db_query("update {cmh_dsa_user} set Token_Val = :token ,Token_Expiry=now() where DSA_ID = :user_id", array(':token' => $token, ':user_id' => $user_id));
        echo "success";
      }
    }
  }
}

/**
 * @desc   - Ajax call for the captcha image
 * @access - public
 * @param  - NULL
 * @return - An image of captcha code 
 */ 
function captcha_image() {
  $vercode_text = rand(10000, 99999);  
  set_session('dsa_user_data', array('vercode' => $vercode_text));
  $height = 30;
  $width = 55;

  $image_p = imagecreate($width, $height);
  $black = imagecolorallocate($image_p, 102, 255, 153);
  $white = imagecolorallocate($image_p, 0, 0, 0);
  $font_size = 14;

  imagestring($image_p, $font_size, 5, 5, $vercode_text, $white);
  imagejpeg($image_p, NULL, 80);
}

/**
 * @desc   - Implementation of hook_form().Display a DSA reset new password form.
 * @access - public
 * @param  - $form : The form being added or edited.
 * @param  - $form_submit  : The form state array.
 * @return - An array containing the title and any custom form elements to be displayed in the DSA reset new        
       password form. 
 */
function cmh_dsa_reset_password_form($form, &$form_submit) {  
  $form['user_id'] = array(
    '#type' => 'textfield',
    '#default_value' => get_session('dsa_user_data', 'dsa_user_id_reset'),
    '#attributes' => array('prepopulate' => array('yes'))
  );
  $form['new_password'] = array(
    '#type' => 'password',
    '#id' => 'password',
    '#name' => 'password',
  );
  $form['confirm_new_password'] = array(
    '#type' => 'password',
    '#id' => 'confirmpassword',
    '#name' => 'confirmpassword',
  );  
  $form['varification_code'] = array(
    '#type' => 'textfield',
    '#id' => 'vercode',
    '#name' => 'vercode',
  '#attributes' => array('style' => array('width:115px'))
  );  
  $form['submit'] = array(
    '#value' => 'Save',
    '#type' => 'submit',
  ); 
  $form['submit'] = array(
    '#value' => 'Submit',
		'#type' => 'submit',
    '#prefix' => '<div class="action-button-border float-right">
											<span class="left"></span>
											<span class="mid">',
		'#suffix' => '</span><span class="right"></span></div>',
    '#attributes' => array('class' => array('submitbtn'), 'id' => array('reset-pass-btn'), 'title' => array('Submit')),
  );  
  $form['#theme'] = 'cmh_dsa_reset_pass';
  unset_session('dsa_user_data', 'dsa_user_reset_id');
  
  return $form;
}
/////////////////////////forgot Password Functionality End/////////////////////////////

/**
 * @desc   - Display output of block content.
 * @access - public
 * @param  - $form: The form being added or edited.
 * @param  - &$form_submit: The form state array.
 * @return - $form
 */
 function feedback_form($form, &$form_submit) {
 
  $user_id = get_session('dsa_user_data', 'dsa_member_id');
  $form['dsa_id'] = array(
    '#type' => 'textfield',
    '#size' => '23',
    '#id' => 'dsaid',
   // '#disabled' => TRUE,
    '#default_value' => $user_id,
    '#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
  $form['dsa_contact'] = array(
    '#type' => 'textfield',
    '#size' => '23',
    '#id' => 'dsaname',
   // '#disabled' => TRUE,
    '#default_value' => '8798766897',
    '#attributes' => array('prepopulate' => array('yes'), 'readonly' => array('readonly')),
  );
  $form['drpsubject'] = array(
    '#type' => 'select',
    '#id' => 'drpsubject',
    '#options' => feedback_subject('feedback_subject'),
  );
  $form['sub_text'] = array(
    '#type' => 'textfield',
		'#size' => '23',
    '#id' => 'subjectId',
    '#name' => 'subjectName',
    '#attributes' => array('class' => array('feedback_sub')),
  );
  $form['txtfeedback'] = array(
    '#type' => 'textarea',
    '#id' => 'txtfeedback',
    '#cols' => 55,
    '#rows' => 5,
    '#resizable' => FALSE,
  );
  $form['submit'] = array(
    '#value' => 'Submit',
    '#type' => 'submit',		
  );
  $form['#submit'][] = 'cmh_dsa_feedback_subject_submit';
  $form['#theme'] = 'cmh_dsa_feedback';
  
  return $form;
}

/**
 * @desc   - Function to populate feedback subject list on page load
 * @access - public
 * @param  - $machine_name: subject's machine name
 * @return - Array of feedback subject list
 */
function feedback_subject($machine_name) {
  
  $sql = db_select('taxonomy_vocabulary', 'tv');
  $sql->join('taxonomy_term_data', 'ttd', 'tv.vid = ttd.vid');
  $sql->join('field_data_field_send_email', 'fdfse', 'ttd.tid = fdfse.entity_id');
  $sql->fields('ttd', array('tid')) 
      ->fields('ttd', array('name'))
      ->fields('fdfse', array('field_send_email_value'));
  $sql->condition('tv.machine_name', $machine_name, '=');
  $result = $sql->execute();

  $feedback_sub_Data = array('0' => '-Please Select-');
  while ($record = $result->fetchAssoc()) {
    $feedback_sub_Data[$record['tid'] . '-' . $record['field_send_email_value']] = t($record['name']);
  }
  return $feedback_sub_Data;
}


/**
 * @desc   - This is to submit the Feedback form and do the business logic.
 * @access - public
 * @param  - $form : The form being used 
 * @param  - $form_state  :  The form state array.
 * @return - NULL
 */
function cmh_dsa_feedback_subject_submit($form, &$form_state) { 
  //Check if user is logged in 
  $user_id = get_session('dsa_user_data', 'dsa_member_id');
  $user_id = '2950';
  /* Fetching template format from database */
  $template_data = get_mail_config('dsa_feedback');
  $result_data = db_query("select Email_ID from {cmh_dsa_user} where DSA_ID='" . $user_id . "'");
  while ($record = $result_data->fetchAssoc()) {    
    $user_details['Email_ID'] = $record['Email_ID'];
  }
  
  if (isset($_POST['subjectName']) && $_POST['subjectName'] != '') {
    $subject = $_POST['subjectName'];
  }
  else{
    $subject = $template_data['mail_subject'];
  }
  
  if ($user_details['Email_ID'] != '') {
  $from = $user_details['Email_ID'];
  }
  else {
  $from = $template_data['mail_from_id'];
  }
  
  
  $body = $template_data['mail_content'];
  
  $sub_category = explode("-", $_POST['drpsubject']);
  
  //Code to get the category.
  $sql = db_select('taxonomy_term_data', 'ttd');
  $sql->fields('ttd', array('tid')) 
      ->fields('ttd', array('name'));
  $sql->condition('ttd.tid', $sub_category[0], '=');
  $result = $sql->execute();
  
  $record = $result->fetchAssoc();
  
  $arrdata = array();
  $arrdata['DSA_ID'] = $user_id;
  $arrdata['SUBJECT'] = $subject;
  $arrdata['FEEDBACK'] = $_POST['txtfeedback'];
  $arrdata['CATEGORY'] = $record['name'];  
  $arrdata['CONTACT'] = $_POST['dsa_contact'];  
  
  if ($sub_category[1] == '1') {
    //$to = 'Anand.Vignesh@mahindraholidays.com, Mayuri.V@mahindraholidays.com';
    $to = $template_data['mail_to_id'];
    $parameter = array('mail_subject' => $subject, 'to' => $to, 'from' => $from, 'mail_content' => $body, 'key' => 'dsafeedback');
  }
  else {
    $to = $template_data['mail_to_id'];
    $parameter = array('mail_subject' => $subject, 'to' => $to, 'from' => $from, 'mail_content' => $body, 'key' => 'dsafeedback');
  }
	mail_feedback($parameter, $arrdata);
  //set success message on successful submission
  set_session('dsa_user_data', array('feedback_success_msg' => 'Feedback has been sent Sucessfully'));
}
/////////////////////////Feedback Functionality End/////////////////////////////