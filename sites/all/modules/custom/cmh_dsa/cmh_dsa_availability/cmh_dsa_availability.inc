<?php
/**
 * @file         cmh_dsa_availability.inc
 * @version      1.0.0
 * @author       CTS
 * @desc         This is a DAS Availability file
 * @date         16/08/2013
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 * @modified by  
 * @modified on  
 * @desc  
 */

 
 /*Code for DSA Availabilit Start*/

/**
 * @desc   - Implementation of hook_form().Display a resort availability editing form.
 * @access - public
 * @param  - $form : The form being added or edited.
 * @param  - $form_submit  : The form state array.
 * @return - An array containing the title and any custom form elements to be displayed in the resort availability editing form. 
 */
 function cmh_dsa_resort_availability_form($form, &$form_submit) {
 
  $location_arrval = array('0' => '-Please Select-', 'all' => 'All');
  $location_det = availability_location('Location');
  
	$location_array = ($location_arrval + $location_det);
 
  $form['drpWLPlanLocation'] = array(
    '#type' => 'select',
    '#id' => 'drpWLPlanLocation',
    '#options' => $location_array,
    '#default_value' => 0,
  );
  $form['drpWLPlanResort'] = array(
    '#type' => 'select',
    '#id' => 'drpWLPlanResort',
    '#options' => array('0' => '-Please Select-'),
    '#default_value' => '0',
  );  
  $form['member_list'] = array(
    '#type' => 'textfield',
    '#id' => 'member_list_id',
    '#size' => 25,
    '#autocomplete_path' => 'member_autocomplete_callback',
  );
  $form['drpContract'] = array(
    '#type' => 'select',
    '#id' => 'drpContract',
    '#options' => array('0' => '-Please Select-'),
  );
  $form['submit'] = array(
    '#value' => 'Check Availability',
		'#type' => 'submit',
    '#prefix' => '<div class="action-button-border float-left">
											<span class="left"></span>
											<span class="mid">',
		'#suffix' => '</span><span class="right"></span></div>',
    '#attributes' => array('class' => array('submitbtn'), 'id' => array('checkAvailabilityBtn'), 'title' => array('Check Availability')),
  );
  $form['#theme'] = 'cmh_dsa_resort_availability';
  return $form;
}

/**
 * @desc   - Function to populate availability locations list on page load
 * @access - public
 * @param  - NULL
 * @return - Array of availability locations list
 */
function availability_location() {
  try{
    $result = db_query("SELECT Sub_Cat_Name,Sub_Cat_Id FROM {cmh_sub_category} WHERE Cat_Id = :Cat_Id ORDER BY Sub_Cat_Name", array(":Cat_Id" => '3'));
    $location_arr = array();  
		//$location_arr['0'] = '-Please Select-';
    while ( $record = $result->fetchAssoc() ) {
      $location_arr[$record['Sub_Cat_Id']] = ucwords($record['Sub_Cat_Name']);
    }
		//print_r($location_arr);
    return $location_arr;
  }
  catch (Exception $e) {
    $logger = log4php_details();
    $logger->error($e->getMessage());
  }
}


/**
 * @desc   - function to get the resorts options according to sub-category
 * @access - public
 * @param  - $_POST : variables from the $_POST(catId)
 * @return - NULL
 */
function get_resorts_list() {
	if ( $_POST['catId'] == '0' ) {
	  $req_resorts['0'] = '-Please Select-';
    drupal_json_output($req_resorts);
  
  }
  else{
		try{
			if ( $_POST['catId'] == 'all' ) {
			  $location_array = availability_location('Location');
				$all_category_id = implode(',', array_keys($location_array));
				$result = db_query("SELECT Resort_ID FROM {cmh_resort_category}  WHERE Sub_Cat_Id IN (" . $all_category_id . ")");
					
			} else {
				 $result = db_query("SELECT Resort_ID FROM {cmh_resort_category}  WHERE Sub_Cat_Id = :Sub_Cat_Id", array(":Sub_Cat_Id" => $_POST['catId']));
			}	
			while ( $resort_list = $result->fetchAssoc() ) {
				$resort_ids[] = "'" . $resort_list['Resort_ID'] . "'";
			}
			$resort_str = '';
			$resort_str = implode(',', $resort_ids);
			
    }
    catch (Exception $e) {
      $logger = log4php_details();
      $logger->error($e->getMessage());
    }
    
    try{
      $result = db_query("SELECT Resort_Title,Resort_ID,Crest_Resort_Id FROM  cmh_resort_info where Resort_ID IN (" . $resort_str . ") AND Status = '1' ORDER BY Resort_Title");
      $req_resorts = array();
      $req_resorts['0'] = '-Please Select-';
      while ($resorts = $result->fetchAssoc()) {
        $req_resorts[$resorts['Crest_Resort_Id']] = $resorts['Resort_Title'];
      }
      drupal_json_output($req_resorts);
    }
    catch (Exception $e) {
      $logger = log4php_details();
      $logger->error($e->getMessage());
    }
  }
}

/**
 * @desc   - Ajax function to get the resorts availability grid onClick of 'Check Availability'
 * @access - public
 * @param  - $_POST : variables from the $_POST
 * @return - displays the resorts availability grid
 */
function get_resorts_availability() {
  $crest_id = $_REQUEST['crest_id'];
  $from_date = $_REQUEST['checkindate'];
  $todate = date("Y-m-d", strtotime("+1 days", strtotime($_REQUEST['checkoutdate'])));
	$contract_id = $_REQUEST['contract_id'];
  $login_id = $_REQUEST['member_id'];
    
  $resort_id = array('ResortId' => $crest_id);
  $room_type = get_data_ws('getResortRoomType', 'getResortRoomTypeResult', $resort_id);
  $room_type = format_records_from_webservice($room_type['ResortRoomType']);
  
  $details = array('MemberID' => $login_id, 'MemberShipId' => $contract_id);

  $product_details = get_data_ws('GetMemberProfileProductDetails', 'GetMemberProfileProductDetailsResult', $details);
  $product_info = $product_details['tblGetMemberProfileProductDetails'];
  $profile_array = get_product_details($product_info, 'Normal');
  if ( !empty($profile_array) ) {
    $profile_id = $profile_array['0']['Member_x0020_Profile_x0020_ID'];
  }
  else {
    $profile_id = '1';
  }
  
	$todate_range = date("Y-m-d", strtotime("-1 days", strtotime($todate)));
  $date_array = create_date_range_array($from_date, $todate_range);
  
  $webservice_request = '|';
  if ( !empty($webservice_request) ) {
    foreach ( $room_type as $key => $value ) {
      $webservice_request .= $value['ResortRoomType'] . ',' . $from_date . ',' . $todate . ',1|';
    }
  }
  
  $resort_details = array('CreProfileMasterID' => $profile_id, 'MemberShipId' => $contract_id, 'ResortId' => $crest_id, 'tRoomGrid' => $webservice_request, 'NoRecRoomType' => count($room_type));

  $availability_array = get_data_ws('GetAvailabilityMultipleRoomType', 'GetAvailabilityMultipleRoomTypeResult', $resort_details);
  $availability_array = format_records_from_webservice($availability_array['tblGetAvailabilityMultipleRoomType']);
    
  $new_availability_array = array();
  foreach ($availability_array as $key => $value) {
    if ( $value['Date'] >= $from_date )
      $new_availability_array[] = $value;
  }
  $availability_array = $new_availability_array;
  
  $room_types = array_unique(array_map(function ($i) {
    return $i['RoomType'];
  }, $availability_array));
  $room_types = array_values($room_types);
  
  $req_availability_array = array();
  foreach ( $room_types as $key => $value ) {
    $i = 0;
    foreach ( $new_availability_array as $key1 => $value1 ) {
      if ( $value == $value1['RoomType'] ) {
        $req_availability_array[$value][$i]['ResortID'] = $value1['ResortID'];
        $req_availability_array[$value][$i]['RmtypeID'] = $value1['RmtypeID'];
        $req_availability_array[$value][$i]['RoomType'] = $value1['RoomType'];
        $req_availability_array[$value][$i]['Date'] = $value1['Date'];
        $req_availability_array[$value][$i]['NoofRooms'] = $value1['NoofRooms'];
        $req_availability_array[$value][$i]['Status'] = $value1['Status'];
        $req_availability_array[$value][$i]['Season'] = $value1['Season'];
        $i++;
      }
    }
  }
  
  $new_date_array = array();
  foreach ( $date_array as $key => $value ) {
    if ( $value >= $from_date )
      $new_date_array[] = $value;
  }
  $date_array = $new_date_array;
  
  $rtdarray = array();
  foreach ( $room_types as $key => $value ) {
    foreach ( $req_availability_array as $key1 => $value1 ) {
      foreach ( $value1 as $key2 => $value2 ) {
        if ( $value2['RoomType'] == $value ) {
          $rtdarray[$value][] = $value2['Date'];
        }
      }
    }
  }  
  
  $r = 0;
  foreach ( $rtdarray as $key2 => $value2 ) {
    $diff_date_array[$r][] = array_diff($date_array, $value2);
    $r++;
  }
  
  $t = count($availability_array) + 1;
  if ( !empty($diff_date_array) ) {
    foreach ( $diff_date_array as $key => $value ) {
      foreach ( $value as $key1 => $value1 ) {
        foreach ( $value1 as  $key2 => $value2 )  {
          $availability_array[$t]['ResortID'] = $crest_id;
          $availability_array[$t]['RmtypeID'] = '';
          $availability_array[$t]['RoomType'] = $room_types[$key];
          $availability_array[$t]['Date'] = $value2;
          $availability_array[$t]['NoofRooms'] = '0';
          $availability_array[$t]['Status'] = 'NA';
          $availability_array[$t]['Season'] = 'noDataClass';
          $availability_array[$t]['TotalDaysRequired'] = '0';
          $t++;
        }
      }
    }
  }
  
  $availability_array = reverse_sort($availability_array, 'RoomType');
  
  $final_array = array();
  foreach ( $room_types as $key => $value ) {
    $i = 0;
    foreach ( $availability_array as $key1 => $value1 ) {
      if ( $value == $value1['RoomType'] ) {
        $final_array[$value][$i]['ResortID'] = $value1['ResortID'];
        $final_array[$value][$i]['RmtypeID'] = $value1['RmtypeID'];
        $final_array[$value][$i]['RoomType'] = $value1['RoomType'];
        $final_array[$value][$i]['Date'] = $value1['Date'];
        $final_array[$value][$i]['NoofRooms'] = $value1['NoofRooms'];
        $final_array[$value][$i]['Status'] = $value1['Status'];
        $final_array[$value][$i]['Season'] = $value1['Season'];
        $i++;
      }
    }
  }
  
  $filtered_array = array();
  foreach ( $final_array  as $key => $value ) {
    $filtered_array[] = reverse_sort($value, 'Date');
  }
  
  $availability_string  = '';
  $availability_string .= '<input type="hidden" id="room_type_count" value="' . count($room_types) . '">';
  $availability_string .= '<input type="hidden" id="crest_id" value="' . $crest_id . '">';
  
  if ( count($room_types) > 0 ) {
    $availability_string .= '<div id="availabilityLive">';
    $availability_string .= '<div id="availability_' . $crest_id . '">';
    $availability_string .= '<div class="clearfix" style="width:660px;">';
    $availability_string .= '<fieldset class="gridFieldSetNoBorder">';
    
    
    $availability_string .= '
    <table border="1" cellpadding="0" cellspacing="0" class="availabilityTable floatLeft roomTypeTable noMargin" style="margin-left:5px;">
      <tr>
        <td class="firstAvailTD" style="font-size: 11px;height: 37px;vertical-align: middle;">Room Type</td>
      </tr>';
    $i = 0;
    foreach ( $final_array as $rooms => $roomtype ) {
      $availability_string .= ' <tr>';
      if ( $i == 0 ) {
        $availability_string .= '<td class="firstAvailTD" style="font-size: 11px;height: 18px;text-align: center;vertical-align: middle;">' . $rooms . '</td>';
      }
      $availability_string .= ' </tr>';
    }
    $availability_string .= '</table>';
        
    $availability_string .= '
    <div  class="scroll-pane-os horizontal-only floatLeft roomTypeDateTable" id="dates_' . $crest_id . '">
      <table border="1" cellpadding="0" cellspacing="0" class="availabilityTable noMargin" >
        <tr>';
    foreach ( $date_array as $dates ) {
      $availability_string .= '<th><div class="availabilityTableDiv">' . date("d-m D", strtotime($dates)) . '</div></th>';
    }
    $availability_string .= '</tr>';
    
    $i = 0;
    foreach ( $filtered_array as $avail ) {
      $availability_string .= '<tr>';
      foreach ( $avail as $rooms ) {
        $season = strtolower($rooms['Season']);
        $availability_string .= '<td class="' . $season . '"';
        if ( $rooms['Status'] == 'NA' ) {
            $availability_string .= 'title="Not Available" ';
        }
        else {
            $availability_string .= 'title="Available" '; 
        }
        $availability_string .= 'style="width:43px;font-size: 11px;height: 18px;vertical-align: middle;">';
        
        if ( $rooms['Status'] == 'NA' ) {
            $availability_string .= '<span style="font-style: italic;">X</span>';
        }
        else {
          // $availability_string .= '<a id="' . $rooms['RoomType'] . $rooms['Date'] . '" class="spotlight" href="javascript:triggerQuickBook(\'' . $rooms['ResortID'] . '\',\'' . $rooms['RoomType'] . '\',\'' . $rooms['Date'] . '\',\'' . strtolower($rooms['Season']) . '\',\'' . $contract_room_type . '\')">';
          $availability_string .= '<span style="font-weight: normal;font-family: Arial Unicode MS, Lucida Grande">&#10003;</span>';
        }
        $availability_string .= ' </td>';
        $availability_string .= ' <span ' . $i++ . ' style="display:none;"></span>';
      }      
      $availability_string .= '</tr>';
    }
    $availability_string .= '</table>';
    $availability_string .= '</div>';
    
    $availability_string .= '<div class="availabilityLegend clearfix">';
      $availability_string .= '<div class="seasonContainer" style="margin: 0; width: auto;">';
        $availability_string .= '<span>Season</span>';
        $availability_string .= '<div class="purple">&nbsp;</div>';
        $availability_string .= '<span>Purple</span>';
        $availability_string .= '<div class="red"></div>';
        $availability_string .= '<span>Red</span>';
        $availability_string .= '<div class="white whiteBox"></div>';
        $availability_string .= '<span>White</span>';
        $availability_string .= '<div class="blue"></div>';
        $availability_string .= '<span>Blue</span>';
      $availability_string .= '</div>';
      $availability_string .= '<div class="seasonContainer" style="margin: 0pt; width: auto; float: right;">';
        $availability_string .= '<span class="floatLeft" style="padding-right: 1px;font-family: Arial Unicode MS, Lucida Grande">&#10003; -</span>';    
        $availability_string .= '<span>Available</span>';
        $availability_string .= '<span class="floatLeft" style="padding-right: 4px;font-family: Arial Unicode MS, Lucida Grande font-style: italic;">X -</span>';
        $availability_string .= '<span>Not Available</span>';
      $availability_string .= '</div>';
    $availability_string .= '</div>';
    
    $availability_string .= '</fieldset>';
    $availability_string .= '</div>';
	
	//To show, hide booking request div
	$booking_req_display_flag = '1';
  } 
  else {
    $availability_string .=  '<div class="noBookHoliday" style="padding: 20px 0 20px 20px;">We are temporarily unable to retrieve availability data for your current selection </div>';
	//To show, hide booking request div
	$booking_req_display_flag = '0';	
  }
  
  $availability_string .= '</div>';
  $availability_string .= '</div>';
  
  
  //Textbox for mail
	
	$availability_string .='<div class="margintop30"><img width="662" height="18" src="sites/all/themes/cmh_orange_theme/images/bm_form_top_img.jpg"></div>';
	$availability_string .= '<input type="hidden" id="booking_req_display_flag" value="' . $booking_req_display_flag . '"/>';
  $availability_string .= '<div id="booking_req" class="bookReg">';
  $availability_string .= '<div class="accountSettingDetails clearfix fullWidth">';
  $availability_string .= '<div class="formfield">';
		$availability_string .= '<div class="formfield-label">';
      $availability_string .= '<label class="font13bold">Share Details With MRC<span class="asterik">* </span></label>';
    $availability_string .= '</div>';
    $availability_string .= '<div class="clearfix">';
			
      $availability_string .= '<div id="formSendMail" class="txtAreaMask clearfix largetxtArea">';
         $availability_string .= '<div class="">
                                    <textarea class="form-textarea hasMaxLength" rows="6" cols="50" name="txtSendMail" id="txtSendMail">
                                    </textarea>
                                  </div>';
      $availability_string .= '</div>';
    $availability_string .= '</div>';
  $availability_string .= '</div>';
  $availability_string .= '</div>  ';
  $availability_string .= '<div style="" id="actionBtns" class="float-right">';
    $availability_string .= '<div id="btnAgree" class="action-button-border floatLeft">';
      $availability_string .= '<a href="javascript:void(0)" id="sendMailAvailabilityBtn" title="Booking Request" class=""> ';
        $availability_string .= '<span title="Booking Request" class="left">&nbsp;</span><span title="Booking Request" class="mid">Booking Request</span> <span title="Booking Request" class="right">&nbsp;</span>';
      $availability_string .= '</a>';
    $availability_string .= '</div>';
  $availability_string .= '</div>';
  $availability_string .= '</div>';
  
  echo $availability_string;
}

/**
 * @desc   - This method returns a sorted array of elements in reverse order based on given key value
 * @access - public
 * @param  - $sub_key : the key on which we have to sort the array
 * @param  - $unique_resort_details : Array which we have to sort
 * @return - sorted array
 */
function reverse_sort($unique_resort_details, $sub_key) {
  $required_result = array();
  if ( !empty($unique_resort_details) ) {
    foreach ( $unique_resort_details as $key => $value ) {
      $temp[$key] = strtolower($value[$sub_key]);
    }
    if ( !empty($temp) ) {  
      asort($temp);
      foreach ($temp as $key => $val ) {
        $required_result[] = $unique_resort_details[$key];
      }
    }
  }
  return $required_result;
}



 /**
 * @desc   - This method returns a formatted array from the webservies
 * @access - public
 * @param  - $actual_array: array from the webservice 
 * @return - formatted array
 */
function format_records_from_webservice($actual_array) {
  if ( count($actual_array) == 1 ) {
    return array('0' => $actual_array['@attributes']);
  }
  else{
    for ($i = 0, $count = count($actual_array); $i < $count; $i++) {
      $myobj = $actual_array[$i];
      $required_array[$i] = $myobj['@attributes'];
    }
  }
  return $required_array;
}



 /**
 * @desc   - To get the array of date range
 * @access - public
 * @param  - $str_date_from: from date
 * @param  - $str_date_to: to date
 * @return - date range array
 */
function create_date_range_array($str_date_from, $str_date_to) {
  // takes two dates formatted as YYYY-MM-DD and creates an
  // inclusive array of the dates between the from and to dates.
  // could test validity of dates here but I'm already doing
  // that in the main script

  $ary_range = array();

  $date_from = mktime(1, 0, 0, substr($str_date_from, 5, 2), substr($str_date_from, 8, 2), (int) substr($str_date_from, 0, 4));
  $date_to = mktime(1, 0, 0, substr($str_date_to, 5, 2), substr($str_date_to, 8, 2), (int) substr($str_date_to, 0, 4));

  if ( $date_to >= $date_from ) {
    array_push($ary_range, date('Y-m-d', $date_from)); // first entry
    while ( $date_from < $date_to ) {
      $date_from += 86400; // add 24 hours
			date('Y-m-d', $date_from);
      array_push($ary_range, date('Y-m-d', $date_from));
    }
  }
  return $ary_range;
}


 /**
 * @desc   - To get the formatted array from the webservice
 * @access - public
 * @param  - $product_info: webservice array
 * @param  - $type: type
 * @return - formatted product array
 */
function get_product_details($product_info, $type) {
  if ( !empty($product_info) ) {
    if ( count($product_info) == 1 ) {
      $product_array['0']['Member_x0020_Profile_x0020_ID'] = $product_info['@attributes']['Member_x0020_Profile_x0020_ID'];
      $product_array['0']['Product_x0020_ID'] = $product_info['@attributes']['Product_x0020_ID'];
      $product_array['0']['Days'] = $product_info['@attributes']['Days'];
      $product_array['0']['PaidInventory'] = $product_info['@attributes']['Paid_x0020_Inventory'];
      if ( $type == 'Normal' )
        return $product_array;
      else {
        $product_array = array();
        return $product_array;
      }
    } 
    else {
      for ( $i = 0, $count = count($product_info); $i < $count; $i++) {
        $myobj = $product_info[$i];
        $product_array[$i] = $myobj['@attributes'];
      }
      if ( $type == '') {
        return $product_array;
      }
      elseif ( $type == 'Normal' ) {
        foreach ( $product_array as $key => $value ) {
          if ( trim( $value['Profile_x0020_ShortName'] ) != 'CMH SPL OFFER' ) {
            $product_details_array['0']['Member_x0020_Profile_x0020_ID'] = $value['Member_x0020_Profile_x0020_ID'];
            $product_details_array['0']['Product_x0020_ID'] = $value['Product_x0020_ID'];
            $product_details_array['0']['Days'] = $value['Days'];
            $product_array['0']['PaidInventory'] = $value['Paid_x0020_Inventory'];
            return $product_details_array;
          }  
        }  
      } 
      elseif ( $type == 'Specialoffer' ) {
        $product_details_array = array();
        $i = 0;
        foreach ( $product_array as $key => $value ) {
          if ( trim( $value['Profile_x0020_ShortName'] ) == 'CMH SPL OFFER' ) {
            $product_details_array[$i]['Product_x0020_Name'] = $value['Product_x0020_Name'];
            $product_details_array[$i]['Days'] = $value['Days'];
            $product_details_array[$i]['Product_x0020_ID'] = $value['Product_x0020_ID'];
            $product_details_array[$i]['Points'] = $value['Points'];
            $product_details_array[$i]['PaidInventory'] = $value['Paid_x0020_Inventory'];
            $product_details_array[$i]['Member_x0020_Profile_x0020_ID'] = $value['Member_x0020_Profile_x0020_ID'];
            $i++;
          }
        }
        return $product_details_array;
      }
    }  
  } 
  else {
    $product_array = array();
    return $product_array;
  }
}

 /**
 * @desc   - Ajax function to send the mail of availability
 * @access - public
 * @param  - $_POST 
 * @return - NULL
 */
function send_availability_mail() {
  
  if ( $_POST['member_id'] != '') {
    $template_data = get_mail_config('dsa_availability');  
      
    $arrdata = array();
    $arrdata['DSA_ID'] = $_POST['member_id'];
    $arrdata['CONTRACT'] = $_POST['contract_id'];
    $lines = preg_split('/\n|\r\n?/', $_POST['txtAreaSendMail']);
    $arrdata['BOOKING_REQ_DETAILS'] = implode ( '<br />' ,  $lines);
   
  	$parameter = array();
    $parameter['mail_subject'] = $template_data['mail_subject'];        
    $parameter['mail_content'] = $template_data['mail_content'];
    $parameter['to'] = $template_data['mail_to_id'];
    $parameter['from'] = $template_data['mail_from_id'];
    $parameter['key'] = 'availability_mail';
    
    $sent = mail_availability($parameter, $arrdata);    
    if ($sent) {
      set_session('dsa_user_data', array('booking_req_sent' => $sent));			
      echo "valid";
    }
    else {
      echo "invalid";
    }
  }
  

}
/////////////////////////////////////////////////////////////////
/*Code for DSA Availabilit End*/