<?php
/**
 * @file         cmh_dsa_member.inc
 * @version      1.0.0
 * @author       CTS
 * @desc         This is a DAS Member functionalities file
 * @date         10/16/2013
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 * @modified by  
 * @modified on  
 * @desc  
 */

 
 
/**
 * @desc   - To search dsa members (business logic included).
 * @access - public
 * @param  - null
 * @return - output string.
 * @author - 362137
 */
function cmh_dsa_search_member() {
  $args = arg();
  //code for sending page id to ajax
  drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');

	if(!isset($_POST['page']))
	  $pageid = 1;
	else
	  $pageid = $_POST['page'];
		
	if(!isset($_POST['type']))
		$post_type = 'searchmember';
	else
		$post_type = $_POST['type'];
	
	if (isset($pageid)) {
    $dsa_id = get_session('dsa_user_data', 'dsa_member_id');
    $name = get_session('dsa_user_data', 'dsa_name');
    $details = array('DsaID' => $dsa_id);
		if (module_exists('cmh_dsa') && function_exists('get_data_ws')) {
			$arr_dsa_members = get_session('search_member_ws_data');
			if (empty($arr_dsa_members)) {
				$arr_dsa_members = get_data_ws('SearchMemberbyDSAID', 'SearchMemberbyDSAIDResult', $details, 'SORT', 'MemberName');
				set_session('search_member_ws_data', $arr_dsa_members);
			}
    }
		// changing the contract information for a member
		if ( isset($post_type) && $post_type == 'contract' ) {
			$status = $arr_dsa_members[$_POST['member']][$_POST['contract']]['MemberContractstatus'];
			$contract_status = '';
			if ($status == "Active") {
				$contract_status = '<span class="active_image"></span>';
			} 
			else {
				$contract_status = '<span class="deactive_image"></span>';
			}
			drupal_json_output(array('data' => $contract_status));
			exit();
		}
    //code for searching member and to get default result 
    if (isset($post_type) && $post_type != 'searchmember' && $post_type != '0') {
      foreach ($arr_dsa_members as $dsamembers) {
				foreach ($dsamembers as $key => $members) {
					if(!in_array($members[$post_type], $dsa_members_searchby)){
					  $dsa_members_searchby[] = $members[$post_type];
					}
					$dsa_members_id[$members['MemberId']][$key] = $members;
					$dsa_members_name[$members['MemberName']][$key] = $members;
				}
      }
      $arr_dsa_members = array();
			
			if ($post_type == 'MemberId') {
				$fl_array = preg_grep('/^' . trim($_POST['search']) . '.*/', $dsa_members_searchby);
				foreach ( $fl_array as $index => $key ) {
					$arr_dsa_members[] = $dsa_members_id[$key];
				}
			}
			else if ($post_type == 'MemberName') {
				foreach ($dsa_members_searchby as $key => $search_result) {
					if (!stristr($search_result, trim($_POST['search'])) === FALSE) {
						$arr_dsa_members[] = $dsa_members_name[$search_result];
					}
				}
			}
    }
	}
	// reindexing the array with numerics
	$arr_dsa_members = array_values($arr_dsa_members);
	
	if(!isset($_POST['page'])) {
		$out = '<div class="content-header">
							<div class="content-header-text">Members List</div>
						</div>
						<div class="content-block paddingbottom20">';
		$out .='	<div class="member-drp bottom-border-dotted">	
								<div id="error-msg" class="validationErrMsg error-msg" style="display:none">
									<span class="error-img"></span>
									<span class="font13bold float-left margintop12">Please enter search text</span>
								</div>';
		$out .= drupal_render(drupal_get_form('cmh_dsa_member_form'));
		$out .='	</div>
							<div id="searchMemberContent">';
	}
						
	if (count($arr_dsa_members) > 0) {
		$total_pages = count($arr_dsa_members);
		$limit = 10;
		$stages = 3;
		if ($_POST['page'])
			$page = $_POST['page'];
		else
			$page = 0;                
		if ($page) {
			$start = ($page - 1) * $limit; 
		}
		else{
			$start = 0;            
		}
		$out .='<div class="member-active">
							<div class="status_active">
								<div class="active_image float-left margintop3 "></div>
								<div class="activelabel marginleft10 float-left">Active</div>
							</div>
							<div class="status_active">
								<span class="deactive_image float-left margintop3"></span>
								<span class="activelabel marginleft10 float-left">Inactive</span>
							</div>';
		$out .= '	<div class="pagination_div">';
		$out .= 		cmh_dsa_paging($post_type, $total_pages, $page, $start, $limit);
		$out .= '	</div>';
		$out .= '<div class="member-detail-table">						
							<table summary="Member Details" cellspacing="0" cellpadding="10px" border="0" width="100%" id="memberDetailTbl">';
		$out .= '		<tr class="trbackcolor">
									<td><label class="trlabel">Member ID</label></td>
									<td><label class="trlabel">Name</label></td>
									<td><label class="trlabel">Contract</label></td>
									<td><label class="trlabel">Status</label></td>
									<td><label class="trlabel">Phone No</label></td>
									<td><label class="trlabel">Email ID</label></td>
								</tr>';
		$count = ($total_pages - $start) < $limit ? $total_pages : $start + $limit;
		for ($i = $start; $i < $count; $i++) {
			$even = $i%2;
			$contract_options = '';
			$contract_status = '';
			foreach ($arr_dsa_members[$i] as $keys_arr_dsa_members);
		  $mem_status = '';
			if (count($arr_dsa_members[$i]) > 1) {
				$contracts = array_keys($arr_dsa_members[$i]);
				$contract_options = '<select name="contract" class="contract" id="' . $keys_arr_dsa_members['MemberId'] . '">';
				$c = 0;
				foreach ($arr_dsa_members[$i] as $members_contracts) {
					// $contracts_list = get_session('member_contracts');
					// if (empty($arr_dsa_member_profile)) {
						// $contracts_list = get_data_ws('getMemberContracts', 'getMemberContractsResult', $user_id);
						// set_session('member_contracts', $contracts_list);
					// }
					$contracts_list[$keys_arr_dsa_members['MemberId']][] = $members_contracts['MembershipId'];
					if($c == 0)
					  $mem_status = $members_contracts['MemberContractstatus'];
					$contract_options .= '<option value="' . $members_contracts['MembershipId'] . '">' . $members_contracts['MembershipId'] . '</option>';
					$c++;
				}
				$contract_options .= '</select>';
			}
			else {
				$contracts_list[$keys_arr_dsa_members['MemberId']] = $keys_arr_dsa_members['MembershipId'];
				$contract_options = $keys_arr_dsa_members['MembershipId'];
				$mem_status = $keys_arr_dsa_members['MemberContractstatus'];
			}
			// display active or inactive image for contratc status
			if (($mem_status) == "Active") {
				$contract_status = '<span class="active_image"></span>';
			} 
			else {
				$contract_status = '<span class="deactive_image"></span>';
			}
			if ($even == 0) {
				$out .= '	<tr class="even" style="display: table-row;">
										<td class="tdlabel"><a class="memberid-bluefont" href="DsaMember/MemberDetails/' . $keys_arr_dsa_members['MemberId'] . '" target="_blank">' . $keys_arr_dsa_members['MemberId'] . '</a></td>
										<td class="tdlabel">' . $keys_arr_dsa_members['MemberName'] . '</td><td class="tdlabel">' . $contract_options . '</td>
										<td class="tdlabel" align="center" id="status-' . $keys_arr_dsa_members['MemberId'] . '">' . $contract_status . '</td>';
				$out .= '		<td class="tdlabel">' . $keys_arr_dsa_members['MemberMobileNo'] . '</td>
										<td class="tdlabel">' . $keys_arr_dsa_members['MemberEmailID'] . '</td>
									</tr>';
			}
			else {
				 $out .= '<tr style="display: table-row;">
										<td class="tdlabel"><a class="memberid-bluefont" href="DsaMember/MemberDetails/' . $keys_arr_dsa_members['MemberId'] . '" target="_blank">' . $keys_arr_dsa_members['MemberId'] . '</a></td>
										<td class="tdlabel">' . $keys_arr_dsa_members['MemberName'] . '</td>
										<td class="tdlabel">' . $contract_options . '</td>
										<td class="tdlabel" align="center" id="status-' . $keys_arr_dsa_members['MemberId'] . '">' . $contract_status . '</td>';
				$out .= '		<td class="tdlabel">' . $keys_arr_dsa_members['MemberMobileNo'] . '</td>
										<td class="tdlabel">' . $keys_arr_dsa_members['MemberEmailID'] . '</td>
									</tr>';
			}
		}
		set_session('member_contracts', $contracts_list);
			
		$out .='		</table>
							</div>';
		$out .='<div class="pagination_div btm">';
		$out .= cmh_dsa_paging($post_type, $total_pages, $page, $start, $limit);
		$out .='</div>';
	}
	if(isset($_POST['page'])) {
		drupal_json_output(array('data' => $out));
		exit();
	}
	else {
		$out .= '	
					</div>
				</div>
			</div>';
		return $out;
	}
}

/**
* pagination
* @param $type string contains the category(latest, featured, explore etc...)
* @param $total_pages int contains the count of total number of records
* @param $page int contains the page number
* @param $start int
* @param $limit int
* @return string returns the list of number of pages
*/
function cmh_dsa_paging($type = NULL, $total_pages, $page = 0, $start = 0, $limit = 0) {
  // Initial page num setup
  if ($page == 0) {
    $page = 1;
  }
  $prev = $page - 1;          
  $next = $page + 1;                                                                                                         
  $last_page = ceil($total_pages/$limit);
  $last_pagem1 = $last_page - 1;                                                                    
  if ($last_page <= 5)
    $stages = $last_page;
  else 
    $stages = 5;
  $paginate = '';
  //$paginate = '<div class="pagination-div">';
  if ($last_page > 1) {            
    $paginate .= '<div class="float-right" id="pageNavPosition">';
    // Previous
    if ($page > 1) {
			$paginate .= "<a href='javascript:void(0)' title='First' class='pager pg-normal' id='" . $type . "-1'> &lt;&lt; </a>";
      $paginate .= "<a href='javascript:void(0)' class='pager pg-normal' id='" . $type . "-" . $prev . "' title='Previous'><span class='disabled'> < </span></a>";  
    }
    // Pages 
    //for showing last 5 pages
    if (($last_page - $page) < 4) {
      if (($last_page - 4) < 0) $pagecount = 1;
      else $pagecount = $last_page - 4;
      for ($counter = $pagecount; $counter <= $last_page; $counter++) {
        if ($counter == $page) {
          $paginate .= "<a href='javascript:void(0)' class='current pg-selected'>$counter</a>";
        }
        else{
        $paginate .= "<a href='javascript:void(0)' class='pager pg-normaltext' id='" . $type . "-" . $counter . "'>$counter</a>";
        }
      }
    }
    else{
      for ($counter = $page; $counter <= ($page + 4); $counter++) {
        if ($counter == $page) {
          $paginate .= "<a href='javascript:void(0)' class='current pg-selected'>$counter</a>";
        }
        else{
          $paginate .= "<a href='javascript:void(0)' class='pager pg-normaltext' id='" . $type . "-" . $counter . "'>$counter</a>";
        }
      }
    }
    //Next
    if ($page < $counter - 1 && $page != $last_page) { 
			$paginate .= "<a href='javascript:void(0)' title='Next' class='pager pg-normal' id='" . $type . "-" . $next . "'> > </span></a>";
      $paginate .= "<a href='javascript:void(0)' class='pager pg-normal' id='" . $type . "-" . $last_page . "' title='Last'> >> </a>";
    }
  }
	$paginate .= '</div>';
  return $paginate;
}

/**
 * @desc   - Implementation of hook_form().Display a resort availability editing form.
 * @access - public
 * @param  - $form : The form being added or edited.
 * @param  - $form_submit  : The form state array.
 * @return - An array containing the title and any custom form elements to be displayed in the resort availability editing form. 
 */
function cmh_dsa_member_form($form, &$form_submit) {
	$mem_arr = array('1' => 'Search Member', '0' => 'All', 'MemberId' => 'Member Id', 'MemberName' => 'Member Name');

  $form['drpSearchMember'] = array(
    '#type' => 'select',
    '#id' => 'drpSearchMember',
		'#attributes' => array('class' => array('drpdown')),
		'#options' => $mem_arr,
		'#prefix' => '<div class="normtxtbox float-left">',
		'#suffix' => '</div>'
  );
  $form['txtSearchKeyword'] = array(
    '#type' => 'textfield',
    '#id' => 'txtSearchKeyword',
		'#default_value' => 'Enter Member ID',
	  '#size' => 25,
    '#prefix' => '<div class="normtxtbox float-left" id="searchkeywordtxtbox" style="display: none;"><div class="txtField autoTxtFieldDiv">',
	  '#suffix' => '</div></div>',
	  '#autocomplete_path' => 'member_autocomplete_callback'
  );  
	$form['txtSearchKeywordName'] = array(
    '#type' => 'textfield',
    '#id' => 'txtSearchKeywordName',
	'#size' => 25,
    '#prefix' => '<div class="normtxtbox float-left" id="searchkeywordtxtboxname" style="display: none;"><div class="txtField">',
	'#suffix' => '</div></div>
							<div style="display: block;" class="action-button-border float-left" id="divFilter">
								 <a title="Filter" href="javascript:void(0)" id="filter" alt="Filter">
									 <span class="left">&nbsp;</span>
									 <span class="mid" title="Filter">Filter</span>
									 <span class="right">&nbsp;</span>
								 </a>
								 <div class="clear"></div>
							 </div>',
  );  
  return $form;
}

/**
 * @desc   - function to auto complete, rechech & onchange ajax for member ID
 * @access - public
 * @param  - $_POST : variables from the $_POST
 * @return - NULL
 */
function home_autocomplete_callback($string = "") {
  $dsa_members = array();
  $searchby_memberid = array();
  $dsa_members_memberid = array();
  $dsa_members = get_session('search_member_ws_data');
  
  
  foreach ($dsa_members as $members) {
    $searchby_memberid[] = $members['MemberId'];
  }
	//Code for the auto complete ajax
	$matches = array();
	if ( $string ) {
		$fl_array = preg_grep('/^' . $string . '.*/', $searchby_memberid);
		foreach ( $fl_array as $index => $key ) {
			$matches[$key] = $key;
		}
		drupal_json_output($matches);
	}  
}


/**
 * @desc   - details of dsa member profile (business logic included).
 * @access - public
 * @author - 362137
 * @param  - $profile_details : array of data get from webservice getMemberProfileDetails.
 * @return - returns string output
 */
function get_member_profile() {
	$args = arg();
	$user_id = array('MemberId' => $args[2]);
  drupal_add_js(array('CMHDSA' => array('pageName' => 'MemberDetails')), array("type" => "setting"));
  drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');
	$list = get_session('member_contracts');
	drupal_add_js(array('CMHDSA' => array('contracts' => $list)), array("type" => "setting"));

	if($_POST['type'] == 'contract'){
		$user_param = array('MemberId' => $_POST['member'], 'MemberShipId' => $_POST['contract']);
  	$arr_contract = get_session('contract_member_ws_data-'.$_POST['contract']);
		if (empty($arr_contract)) {
			$arr_contract = get_data_ws('getContractDetails', 'getContractDetailsResult', $user_param);
			set_session('contract_member_ws_data-'.$_POST['contract'], $arr_contract);
		}
		drupal_json_output(array('data' => array('season' => $arr_contract['ContractsDetails']['@attributes']['ContractSeason'], 'apartment' => $arr_contract['ContractsDetails']['@attributes']['ContractRoomType'], 'membership_id' => $_POST['contract'])));
		exit;
	}
	if (module_exists('cmh_dsa') && function_exists('get_data_ws')) {
		$arr_dsa_member_profile = get_session('profile_member_ws_data-'.$args[2]);
		if (empty($arr_dsa_member_profile)) {
			$arr_dsa_member_profile = get_data_ws('getMemberProfileDetails', 'getMemberProfileDetailsResult', $user_id);
			set_session('profile_member_ws_data-'.$args[2], $arr_dsa_member_profile);
		}
	}
	foreach ($arr_dsa_member_profile['MemberProfileDetails'] as $profile_details);
	set_session('tMembershipID', $profile_details['tMembershipID']);
  $out_member_details = '';
  $out_member_details .= '<table summary="Member Details" class="member_details">';
  $out_member_details .= '<tbody><tr><td class="font14bold height25">Member Name</td><td class="font13">' . $profile_details['MEMBERNAME'] . '</td>
													<td class="font14bold">Member ID</td>
                          <td class="font13">' . $profile_details['MemberID'] . '</td></tr>
                          <tr><td class="font14bold height25">Type of Membership</td><td class="font13" id="season">' . $profile_details['tseason'] . '</td><td class="font14bold">Type of Apartment</td><td class="font13" id="apartment">' . $profile_details['tapartment'] . '</td></tr>
													<tr><td class="font14bold height25">First Name</td><td class="font13">' . $profile_details['tFirstName'] . '</td><td class="font14bold">Last Name</td><td class="font13">' . $profile_details['tLastName'] . '</td></tr>
                          <tr><td class="font14bold height25">Email Id</td><td class="font13">' . $profile_details['EMAIL'] . '</td><td class="font14bold">Membership ID</td><td class="font13" id="membership_id">' . $profile_details['tMembershipID'] . '</td></tr>
                          <tr><td class="font14bold height25">Alternate Mobile No</td><td class="font13">' . $profile_details['AlternateMobileNo'] . '</td><td class="font14bold">Mobile Number</td><td class="font13">' . $profile_details['tMobile'] . '</td></tr>
                          <tr><td class="font14bold height25">Date of Birth</td><td class="font13">' . $profile_details['DateofBirth'] . '</td><td class="font14bold">Gender</td><td class="font13">' . $profile_details['tGender'] . '</td></tr>
                          <tr><td class="font14bold height25">Nationality</td><td class="font13">' . $profile_details['Nationality'] . '</td><td class="font14bold">Marital Status</td><td class="font13">' . $profile_details['tMaritalstatus'] . '</td></tr>
                          <tr><td class="font14bold height25">Type of Credit Card Owned</td><td class="font13">' . $profile_details['TypeofCreditCardOwned'] . '</td><td class="font14bold">Profession</td><td class="font13">' . $profile_details['Occupation'] . '</td></tr>
                          <tr><td class="font14bold height25">Preferred mode of contact</td><td class="font13">' . $profile_details['PreferredModeofCommunication'] . '</td><td class="font14bold">Frequent Flyer</td><td class="font13">' . $profile_details['FrequentFlyer'] . '</td></tr>
                          <tr><td class="font14bold allign-top height25">Residence Address</td><td class="font13 allign-top">';
	$out_member_details .=	$profile_details['tResDoorNo'] ? $profile_details['tResDoorNo'].', ' : '';
	$out_member_details .=  $profile_details['tResStreet'] ? $profile_details['tResStreet']. ', ' : '';
	$out_member_details .=  $profile_details['tResArea'] ? $profile_details['tResArea'].' ' : '';
  $out_member_details .=  $profile_details['tResCity'] ? $profile_details['tResCity'].', ' : '';
	$out_member_details .=  $profile_details['tResState'] ? $profile_details['tResState'].'<br>' : '';
	$out_member_details .=  $profile_details['tResCountry'] ? $profile_details['tResCountry'].' - ' : '';
	$out_member_details .=  $profile_details['tResPinCode'] ? $profile_details['tResPinCode'].'<br>' : '';
	$out_member_details .=  $profile_details['tResPhone1'] ? 'Phone1: ' . $profile_details['tResPhone1'] .', ' : '';
	$out_member_details .=  $profile_details['tResPhone2'] ? 'Phone1: ' . $profile_details['tResPhone2'] .' ' : '';
	$out_member_details .=  $profile_details['tResFax'] ? 'Fax: ' . $profile_details['tResFax'] .' ' : '';
	$out_member_details .=  '</td><td class="font14bold allign-top">Office Address</td><td class="font13 allign-top">';
	$out_member_details .=	$profile_details['tOffDoorNo'] ? $profile_details['tOffDoorNo'].', ' : '';
	$out_member_details .=  $profile_details['tOffArea'] ? $profile_details['tOffArea'].'<br>' : '';
	$out_member_details .=  $profile_details['tOffCity'] ? $profile_details['tOffCity'].', ' : '';
	$out_member_details .=  $profile_details['tOffState'] ? $profile_details['tOffState'].'<br>' : '';
	$out_member_details .=  $profile_details['tOffCountry'] ? $profile_details['tOffCountry'].' - ' : '';
	$out_member_details .=  $profile_details['tOffPincode'] ? $profile_details['tOffPincode'].'<br>' : '';
	$out_member_details .=  $profile_details['tOffPhone1'] ? 'Phone1: ' . $profile_details['tOffPhone1'] .', ' : '';
	$out_member_details .=  $profile_details['tOffPhone2'] ? 'Phone1: ' . $profile_details['tOffPhone2'] .' ' : '';
	$out_member_details .=  $profile_details['tOffFax'] ? 'Fax: ' . $profile_details['tOffFax'] .' ' : '';
	$out_member_details .= '</td></tr>';
	$out_member_details .=  '<tr><td class="font14bold allign-top height25">Permanent Address</td><td class="font13 allign-top">';
	$out_member_details .=	$profile_details['tPermanentDoorNo'] ? $profile_details['tPermanentDoorNo'].', ' : '';
	$out_member_details .=  $profile_details['tPermanentStreet'] ? $profile_details['tPermanentStreet']. ', ' : '';
	$out_member_details .=  $profile_details['tPermanetArea'] ? $profile_details['tPermanetArea'].'<br>' : '';
  $out_member_details .=  $profile_details['tPermanentCity'] ? $profile_details['tPermanentCity'].', ' : '';
	$out_member_details .=  $profile_details['tPermanentState'] ? $profile_details['tPermanentState'].'<br>' : '';
	$out_member_details .=  $profile_details['tPermanentCountry'] ? $profile_details['tPermanentCountry'].' - ' : '';
	$out_member_details .=  $profile_details['tPermanentPincode'] ? $profile_details['tPermanentPincode'].'<br>' : '';
	$out_member_details .=  $profile_details['tPermanentPhone1'] ? 'Phone: ' . $profile_details['tPermanentPhone1'] .' ' : '';
	$out_member_details .=  '</td><td></td><td></td></tr>';
  $out_member_details .= '</tbody></table>';
  return $out_member_details;
}

/**
 * @desc   - details of dsa member contract (business logic included).
 * @access - public
 * @author - 362137
 * @param  - $profile_details : array of data get from webservice getMemberProfileDetails.
 * @return - returns string output
 */
function get_member_contract() {
  $args = arg();
	$user_id = array('MemberId' => $args[2]);
  drupal_add_js(array('CMHDSA' => array('pageName' => 'MemberDetails')), array("type" => "setting"));
  drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');
	$list = get_session('member_contracts');
	drupal_add_js(array('CMHDSA' => array('contracts' => $list)), array("type" => "setting"));
	
 	if (module_exists('cmh_dsa') && function_exists('get_data_ws')) {
		$arr_dsa_member_profile = get_session('profile_member_ws_data-'.$args[2]);
		if (empty($arr_dsa_member_profile)) {
			$arr_dsa_member_profile = get_data_ws('getMemberProfileDetails', 'getMemberProfileDetailsResult', $user_id);
			set_session('profile_member_ws_data-'.$args[2], $arr_dsa_member_profile);
		}
	}
  foreach ($arr_dsa_member_profile['MemberProfileDetails'] as $profile_details);
	drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');
	
	if($_POST['type'] == 'contract'){
		$contract_id = array('ContractID' =>  $_POST['contract']);
		$arr_dsa_member_cancel_request = get_data_ws('getCancelRequestDetails', 'GetCancelRequestDetailsResult', $contract_id);
		$member_param = array('MemberId' => $user_id, 'MemberShipId' => $_POST['contract']);
		$arr_dsa_member_holiday_balance = get_data_ws('getHolidayBalance', 'getHolidayBalanceResult', $member_param);
		foreach ($arr_dsa_member_cancel_request['CancelRequestDetails'] as $key_c => $val_c);
		foreach ($arr_dsa_member_holiday_balance['HolidayBalance'] as $key_h => $val_h);
		$can_req_date = $val_c['CanCreatedOn'] ? date('d/m/Y', strtotime($val_c['CanCreatedOn'])) : "";
		drupal_json_output(array('data' => array('cancel_status' => $val_c['CancelledPending'], 'can_req_date' => $can_req_date, 'cancel_rec' => $val_c['Recession'], 'hol_bal' => $val_h['TotalEntBalance'])));
		exit;
	}
	
	$contract_id = array('ContractID' => $profile_details['tMembershipID']);
  $arr_dsa_member_cancel_request = get_data_ws('getCancelRequestDetails', 'GetCancelRequestDetailsResult', $contract_id);
  $member_param = array('MemberId' => $user_id, 'MemberShipId' => $profile_details['tMembershipID']);
  $arr_dsa_member_holiday_balance = get_data_ws('getHolidayBalance', 'getHolidayBalanceResult', $member_param);
  $out_member_contract_info = '';
  $out_member_contract_info .= '<table id="memberDetailTbl" class="member_details" summary="Member Details" width="97%" >';
  foreach ($arr_dsa_member_cancel_request['CancelRequestDetails'] as $key_c => $val_c);
  foreach ($arr_dsa_member_holiday_balance['HolidayBalance'] as $key_h => $val_h);
  $out_member_contract_info .= '<tr><td class="font14bold height25">Sale Logged in date:</td><td class="font13">';
  $out_member_contract_info .= $profile_details['SalesapprovedOn'] ? date('d/m/Y', strtotime($profile_details['SalesapprovedOn'])) : "";
  $out_member_contract_info .= '</td><td class="font14bold height25">Holiday Start Date</td><td class="font13">';
  $out_member_contract_info .= $profile_details['dtHolidayStartDate'] ? date('d/m/Y', strtotime($profile_details['dtHolidayStartDate'])) : "";
  $out_member_contract_info .= '</td></tr><tr><td class="font14bold height25">Sale Posted on date</td><td class="font13">';
  $out_member_contract_info .= $profile_details['SalesPostedDate'] ? date('d/m/Y', strtotime($profile_details['SalesPostedDate'])) : "";
  $out_member_contract_info .= '</td><td class="font14bold height25">Last holidayed Date</td><td class="font13">';
  $out_member_contract_info .= $profile_details['LastHolidayedDate'] ? date('d/m/Y', strtotime($profile_details['LastHolidayedDate'])) : "";
  $out_member_contract_info .= '</td></tr><tr><td class="font14bold height25">Contract No</td><td class="font13" id="membership_id">' . $profile_details['MEMBERSHIPID'] . '</td><td class="font14bold height25">Last Holiday
                                Destination</td><td class="font13">' . $profile_details['LastCountryHolidayedAt'] . '</td></tr>
                                <tr><td class="font14bold height25">Contract Status</td><td class="font13">' . $profile_details['Contract_x0020_Status'] . '</td><td class="font14bold height25">Holiday Balance</td><td class="font13" id="hol_bal">' . $val_h['TotalEntBalance'] . '</td></tr>
                                <tr><td class="font14bold height25">Welcome letter status</td><td class="font13">' . $profile_details['WelcomeLetterStatus'] . '</td><td class="font14bold height25">Cancellation Status </td><td class="font13" id="cancel_status">' . $val_c['CancelledPending'] . '</td></tr><tr><td class="font14bold height25">Date of Welcome letter Despatch</td><td class="font13 allign-top">';
  $out_member_contract_info .= $profile_details['DateOfDespatchOfWelcomeLetter'] ? date('d/m/Y', strtotime($profile_details['DateOfDespatchOfWelcomeLetter'])) :"";
  $out_member_contract_info .= '</td><td class="font14bold height25">Cancellation Request Date </td><td class="font13" id="can_req_date">';
  $out_member_contract_info .= $val_c['CanCreatedOn'] ? date('d/m/Y', strtotime($val_c['CanCreatedOn'])) : "";
  $out_member_contract_info .= '</td></tr><tr><td class="font14bold height25">Membership Kit Status</td><td class="font13">' . $profile_details['tMembershipKitStatus'] . '</td><td class="font14bold height25">
                                Cancellation Recession </td><td class="font13" id="cancel_rec">' . $val_c['Recession'] . '</td></tr>
                                <tr><td class="font14bold height25">Date of Membership Kit Despatched</td><td class="font13 allign-top">';
  $out_member_contract_info .= $profile_details['MembershipKitDispatchDate'] ? date('d/m/Y', strtotime($profile_details['MembershipKitDispatchDate'])) : "";
  $out_member_contract_info .= '</td><td class="font14bold height25">RCI Enrolment status</td><td class="font13">' . $profile_details['RCIEnrollmentStatus'] . '</td></tr>
                                <tr><td class="font14bold height25"></td><td class="font13"></td><td class="font14bold height25">RCI Start Date</td><td class="font13">';
  $out_member_contract_info .= $profile_details['RCIMEMBERSHIPFROM'] ? date('d/m/Y', strtotime($profile_details['RCIMEMBERSHIPFROM'])) :"";
  $out_member_contract_info .= '</td></tr>';
  $out_member_contract_info .= '</table>';
  return $out_member_contract_info;
}

/**
 * @desc   - details of dsa member usage of holiday summary (business logic included).
 * @access - public
 * @author - 362137
 * @param  - $profile_details : array of data get from webservice getMemberProfileDetails.
 * @return - returns string output
 */
function get_member_hub() {
  $args = arg();
	$user_id = array('MemberId' => $args[2]);
	drupal_add_js(array('CMHDSA' => array('pageName' => 'MemberDetails')), array("type" => "setting"));
  drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');
	$list = get_session('member_contracts');
	drupal_add_js(array('CMHDSA' => array('contracts' => $list)), array("type" => "setting"));
	
 	if (module_exists('cmh_dsa') && function_exists('get_data_ws')) {
		$arr_dsa_member_profile = get_session('profile_member_ws_data-'.$args[2]);
		if (empty($arr_dsa_member_profile)) {
			$arr_dsa_member_profile = get_data_ws('getMemberProfileDetails', 'getMemberProfileDetailsResult', $user_id);
			set_session('profile_member_ws_data-'.$args[2], $arr_dsa_member_profile);
		}
	}
  foreach ($arr_dsa_member_profile['MemberProfileDetails'] as $profile_details);
	
	if($_POST['type'] == 'contract'){
		$member_param = array('MemberId' => $args[2], 'MemberShipId' => $_POST['contract']);
		$arr_holiday_usage_summary = get_session('holiday_usage_ws_data-'.$_POST['contract']);
		if (empty($arr_holiday_usage_summary)) {
			$arr_holiday_usage_summary = get_data_ws('GetHolidayUsageSummary', 'GetHolidayUsageSummaryResult', $member_param);
			set_session('holiday_usage_ws_data-'.$_POST['contract'], $arr_holiday_usage_summary);
		}
		foreach ($arr_holiday_usage_summary['HolidayUsageSummary'] as $holiday_usage);
		drupal_json_output(array('data' => array('hol_ent' => $holiday_usage['InventoryEntitlement'], 'hol_booked' => $holiday_usage['TotalBookedBlocked']*(-1), 'hol_rci' => $holiday_usage['TotalRCI']*(-1), 'hol_cancelled' => $holiday_usage['TotalCancelled']*(-1), 'holiday_bal' => round($holiday_usage['TotBeforeLapse'], 1), 'excs_hol_lapsed' => $holiday_usage['TotalLapsing']*(-1), 'acc_bal' => round($holiday_usage['TotalEntBalance'], 1))));
		exit;
	}
	
  $member_param = array('MemberId' => $args[2], 'MemberShipId' => $profile_details['tMembershipID']);
  $arr_holiday_usage_summary = get_data_ws('GetHolidayUsageSummary', 'GetHolidayUsageSummaryResult', $member_param);
  foreach ($arr_holiday_usage_summary['HolidayUsageSummary'] as $holiday_usage);
		
  $arr_member_contracts = get_data_ws('getMemberContracts', 'getMemberContractsResult', $user_id);
  foreach ($arr_member_contracts['MemberDetails'] as $contract_details);
  $arr_holiday_entitled = get_data_ws('GetEntitledHolidays', 'GetEntitledHolidaysResult', $member_param);
  $arr_holiday_history = get_data_ws('getHolidayHistory', 'getHolidayHistoryResult', $member_param);
  $arr_holiday_lapsed = get_data_ws('GetDaysLapsed', 'GetDaysLapsedResult', $member_param);
	if(count($contract_details) == 1) {
		$contract_duration = explode('-', $contract_details['@attributes']['ProductName']);
  }
	else {
		$contract_duration = explode('-', $contract_details['ProductName']);
	}
	if (empty($holiday_usage)) {
    $husdisplaystatus = 'hide';
  }
  else{
    $husdisplaystatus = 'show';
  }
  $today = current_date;
  $currentyear=date("Y");
  $out_holiday_summary = '';
  if ($husdisplaystatus == 'hide') {
    $out_holiday_summary .= '<div class="noDataAvailable" style="display:block"><h3>Sorry, there is a temporary problem with the page you requested.
                            Please contact Member Relations Center at 18602101111* to get your Holiday Utilisation Statement</h3></div>
                            <div class="dynamicTabContent HUSpg" style="display:none"></div>';
  }
  else{
    $out_holiday_summary .= '<div class="dynamicTabContent HUSpg" style="display:block">
															 <div class="clearfix summaryTbl">
																 <div class="float-left custDetails">
																 <table class="HUStbl">
																 <tr><th scope="col" colspan="3" class="welcome-user">Membership Details </th></tr></thead>
																 <tr><td class="font14bold height25" style="width:40%">  Membership ID  </td><td class="font13" id="membership_id">' . $profile_details['tMembershipID'] . '</td></tr>
																 <tr><td class="font14bold height25">  Customer Name </td><td class="font13"><span>' . $profile_details['MEMBERNAME'] . '</span> </td></tr>
																 <tr><td class="font14bold height25">  Address  </td><td class="font13"><div class="paraHeight"><span>' . $profile_details['tResDoorNo'] . ' ' . $profile_details['tResStreet'] . ' ' . $profile_details['tResArea'] . ' ' . $profile_details['tResCity'] . ' ' . $profile_details['tResCountry'] . ' </span></div></td></tr>
																 <tr><td class="font14bold height25"> Ownership</td><td class="font13"><span>' . $contract_duration['0'] . '</span></td></tr>
																 <tr><td class="font14bold height25"> Location  </td><td class="font13"><span>' . $profile_details['SALELOCATION'] . '</span></td></tr>
																 <tr><td class="font14bold height25">Season  </td><td class="font13" id="season"> <span>' . $profile_details['tseason'] . '</span></td></tr>
																 <tr><td class="font14bold height25"> Apartment </td><td class="font13" id="apartment"><span>' . $profile_details['tapartment'] . '</span></td></tr>
																 </table>
																 </div>
																 <div class="holidaySummary float-left" style="width:50%;">
																 <table class="HUStbl" width="80%">
																 <tr><th scope="col" colspan="4" class="welcome-user">Usage Summary (in Holidays)</th></tr>
																 <tr><td class="font14bold height25"> Holidays Entitled </td><td class="noOfDays font13" id="hol_ent">' . $holiday_usage['InventoryEntitlement'] . '</td></tr>
																 <tr><td class="font14bold height25"> Holidays Booked/Blocked  </td><td class="noOfDays font13" id="hol_booked">' . $holiday_usage['TotalBookedBlocked']*(-1) . '</td></tr>
																 <tr><td class="font14bold height25"> Holidays banked with RCI  </td><td class="noOfDays font13" id="hol_rci">' . $holiday_usage['TotalRCI']*(-1) . '</td></tr>
																 <tr><td class="font14bold height25">Holidays Cancelled  </td><td class="noOfDays font13" id="hol_cancelled">' . $holiday_usage['TotalCancelled']*(-1) . '</td></tr>
																 <tr class="font13bold"><td class="font13 height25"> Balance </td><td class="total font13" id="holiday_bal">' . round($holiday_usage['TotBeforeLapse'], 1) . '</td></tr>
																 <tr class="red"><td class="height25">Maximum Balance</td><td>21.0</td></tr>
																 <tr><td class="font14bold height25">Excess Holidays Lapsed </td><td class="font13" id="excs_hol_lapsed">' . $holiday_usage['TotalLapsing']*(-1) . '</td></tr>
																 <tr class="font13bold"><td  class="total font14bold height25"><div class="paraHeight">Account Balance</div></td><td colspan="1" class="total font13" id="acc_bal">' . round($holiday_usage['TotalEntBalance'], 1) . '</td></tr>
																 </table>
																 </div>
															 </div>
                             <div class="clear"></div>
                             <div class="content-separator"> </div>
                             <div id="tabs" class="stepByStep">
																<ul>
																	<li id="tab-1" class="tab-title active"><a href="#tab-1-content">Holiday Entitled</a></li>
																	<li id="tab-2" class="tab-title"><a href="#tab-2-content">Holiday Booked/Blocked</a></li>
																	<li id="tab-3" class="tab-title"><a href="#tab-3-content">Holiday Cancelled</a></li>
																	<li id="tab-4" class="tab-title"><a href="#tab-4-content">Holiday Lapsed</a></li>
																</ul>
                               
                                
                              
                               <div id="tab-1-content" class="tab-content">
                                            <div class="thead-content">
                                                <div class="thbackcolor">
                                                    <div class="theader ent-yr"><label class="thlabel">Entitled Year</label></div>
                                                    <div class="theader season-apt"><label class="thlabel">Season Apt.</label></div>
                                                    <div class="theader annual-ent"><label class="thlabel">Annual Entitlement (Holidays)</label></div>
                                                    <div class="theader ent-purple-stu"><label class="thlabel">Entitlement in terms of ' . $profile_details['tseason'] . ' - ' . $profile_details['tapartment'] . ' (Holidays)</label></div>
                                                </div>
                                            </div>
                                            <div class="tbody-content">';
		if (!empty($arr_holiday_entitled)) {
    foreach ($arr_holiday_entitled['HUSEntitledHolidays']['0'] as $enti_holi);	
      $renewmonth=$enti_holi['tMonth'];
      $renewmonth=date('m', strtotime($renewmonth));
      foreach ($arr_holiday_entitled as $entitled_holiday_details) {
				if(count($entitled_holiday_details) == 1){
					foreach ($entitled_holiday_details as  $en_holiday);
					$out_holiday_summary .= '<div class="trow">
																		<div class="tdata ent-yr">' . $en_holiday['tYear'] . '&nbsp;' . $en_holiday['tMonth'] . '</div>
																		<div class="tdata season-apt">' . $en_holiday['ProductName'] . '</div>
																		<div class="tdata annual-ent">' . $en_holiday['ActEntitlement'] . '</div>
																		<div class="tdata ent-purple-stu">' . $en_holiday['EntitlementDays'] . '</div>
																	</div>';
				}
				else{
					for ($i = 0; $i < count($entitled_holiday_details) ; $i++) {
						$even = $i%2;
						if ($even == 0) {
							foreach ($entitled_holiday_details[$i] as  $en_holiday) {
								$out_holiday_summary .= '<div class="trow">
																					<div class="tdata ent-yr">' . $en_holiday['tYear'] . '&nbsp;' . $en_holiday['tMonth'] . '</div>
																					<div class="tdata season-apt">' . $en_holiday['ProductName'] . '</div>
																					<div class="tdata annual-ent">' . $en_holiday['ActEntitlement'] . '</div>
																					<div class="tdata ent-purple-stu">' . $en_holiday['EntitlementDays'] . '</div>
																				</div>';
							}
						}
						else{
							foreach ($entitled_holiday_details[$i] as  $en_holiday) {
								$out_holiday_summary .= '<div class="even-row trow">
																					<div class="tdata ent-yr">' . $en_holiday['tYear'] . '&nbsp;' . $en_holiday['tMonth'] . '</div>
																					<div class="tdata season-apt">' . $en_holiday['ProductName'] . '</div>
																					<div class="tdata annual-ent">' . $en_holiday['ActEntitlement'] . '</div>
																					<div class="tdata ent-purple-stu">' . $en_holiday['EntitlementDays'] . '</div>
																				</div>';
							}
						}
					}
				}
      }                        
      $out_holiday_summary .= '</div><div class="total-bottom">Total Holiday Entitled <span>'. $holiday_usage['InventoryEntitlement'] . '</span></div></div>';
    }
    else{
      $out_holiday_summary .= '<div class="trow tdata"><center>No Data Available</center></div></div><div class="total-bottom"></div></div>';
    } 																					
    $out_holiday_summary .= ' <div id="tab-2-content" class="tab-content" style="display:none;">
                                            <div class="thead-content">
                                                <div class="thbackcolor">
                                                    <div class="theader tab-voucher"><label class="thlabel">Voucher #</label></div>
                                                    <div class="theader tab-voucher"><label class="thlabel">Resort</label></div>
                                                    <div class="theader tab-voucher" style="width:80px;"><label class="thlabel">Guest Name</label></div>
                                                    <div class="theader tab-voucher" style="width:130px;"><label class="thlabel">Room Type and Corres. # of Rooms</label></div>
																										<div class="theader tab-voucher" style="width:80px;"><label class="thlabel">Reservation Type</label></div>
																										<div class="theader tab-voucher"><label class="thlabel">Check In Date</label></div>
																										<div class="theader tab-voucher"><label class="thlabel">Check Out Date</label></div>
																										<div class="theader tab-voucher"><label class="thlabel"># of Holidays</label></div>
                                                </div>
                                            </div>
                                            <div class="tbody-content">';
																						
		if (!empty($arr_holiday_history)) {
      foreach ($arr_holiday_history as $holiday_history_details) {
				if(count($holiday_history_details) == 1){
					foreach ($holiday_history_details as $history_details_value);
          if (isset($history_details_value['ResStatus']) && $history_details_value['ResStatus']=='26') {
            $holidaycancelledarray[0]=$history_details_value;
          }
          if ($history_details_value['ResStatus']=='21' || $history_details_value['ResStatus']=='23' || $history_details_value['ResStatus']=='24' || $history_details_value['ResStatus']=='22') {
            $holidaybookedarray[0]=$history_details_value;
          }
				}else{
					for ($i = 0, $count = count($holiday_history_details); $i < $count; $i++) {
						foreach ($holiday_history_details[$i] as $history_details_value);
						if (isset($history_details_value['ResStatus']) && $history_details_value['ResStatus']=='26') {
							$holidaycancelledarray[$i]=$history_details_value;
						}
						if ($history_details_value['ResStatus']=='21' || $history_details_value['ResStatus']=='23' || $history_details_value['ResStatus']=='24' || $history_details_value['ResStatus']=='22') {
							$holidaybookedarray[$i]=$history_details_value;
						}
					}
					$holidaycancelledarray = array_values($holidaycancelledarray);
					$holidaybookedarray = array_values($holidaybookedarray);
				}
        $holidaybookedarray = array_values($holidaybookedarray);
        if (!empty($holidaybookedarray)) {
          for ($i = 0, $count = count($holidaybookedarray); $i < $count; $i++) {
            $even = $i%2;
            if ($even == 0) {
              $out_holiday_summary .= '<div class="trow">
																					<div class="tdata tab-voucher">' . $holidaybookedarray[$i]['ConfirmationNo'] . '</div>
																					<div class="tdata tab-voucher">' . $holidaybookedarray[$i]['SiteName'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaybookedarray[$i]['Name'] . '</div>
																					<div class="tdata tab-voucher" style="width:130px;">' . $holidaybookedarray[$i]['ApartmentType'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaybookedarray[$i]['restype'] . '</div>
																					<div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaybookedarray[$i]['CheckIn'] ? date('d/m/Y', strtotime($holidaybookedarray[$i]['CheckIn'])) : "";$out_holiday_summary .= '</div>
																		 <div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaybookedarray[$i]['CheckOut'] ? date('d/m/Y', strtotime($holidaybookedarray[$i]['CheckOut'])) : "";$out_holiday_summary .= '</div>
																					<div class="tdata tab-voucher">' . $holidaybookedarray[$i]['TotalUtilized'] . '</div>
																				</div>';
            }
            else{
              $out_holiday_summary .= '<div class="even-row trow">
																					<div class="tdata tab-voucher">' . $holidaybookedarray[$i]['ConfirmationNo'] . '</div>
																					<div class="tdata tab-voucher">' . $holidaybookedarray[$i]['SiteName'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaybookedarray[$i]['Name'] . '</div>
																					<div class="tdata tab-voucher" style="width:130px;">' . $holidaybookedarray[$i]['ApartmentType'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaybookedarray[$i]['restype'] . '</div>
																					<div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaybookedarray[$i]['CheckIn'] ? date('d/m/Y', strtotime($holidaybookedarray[$i]['CheckIn'])) : "";$out_holiday_summary .= '</div>
																		 <div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaybookedarray[$i]['CheckOut'] ? date('d/m/Y', strtotime($holidaybookedarray[$i]['CheckOut'])) : "";$out_holiday_summary .= '</div>
																					<div class="tdata tab-voucher">' . $holidaybookedarray[$i]['TotalUtilized'] . '</div>
																				</div>';
            }
          }
				$out_holiday_summary .= '</div><div class="total-bottom">Total Holidays Booked <span>' . round($holiday_usage['TotalBookedBlocked'], 1) . '</span></div></div>';
        }                           
      }
    }
    else{
			$out_holiday_summary .= '<div class="trow tdata"><center>No Booked Holidays</center></div></div><div class="total-bottom"></div></div>';
    }																				
		
		$out_holiday_summary .= ' <div id="tab-3-content" class="tab-content" style="display:none;">
                                            <div class="thead-content">
                                                <div class="thbackcolor">
                                                    <div class="theader tab-voucher"><label class="thlabel">Voucher #</label></div>
                                                    <div class="theader tab-voucher"><label class="thlabel">Resort</label></div>
                                                    <div class="theader tab-voucher" style="width:80px;"><label class="thlabel">Guest Name</label></div>
                                                    <div class="theader tab-voucher" style="width:130px;"><label class="thlabel">Room Type and Corres. # of Rooms</label></div>
																										<div class="theader tab-voucher" style="width:80px;"><label class="thlabel">Reservation Type</label></div>
																										<div class="theader tab-voucher"><label class="thlabel">Check In Date</label></div>
																										<div class="theader tab-voucher"><label class="thlabel">Check Out Date</label></div>
																										<div class="theader tab-voucher"><label class="thlabel"># of Holidays</label></div>
                                                </div>
                                            </div>
                                            <div class="tbody-content">';		
		if (!empty($holidaycancelledarray)) {
      for ($i = 0, $count = count($holidaycancelledarray); $i < $count; $i++) {
        $even = $i%2;
        if ($even == 0) {
              $out_holiday_summary .= '<div class="trow">
																					<div class="tdata tab-voucher">' . $holidaycancelledarray[$i]['ConfirmationNo'] . '</div>
																					<div class="tdata tab-voucher">' . $holidaycancelledarray[$i]['SiteName'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaycancelledarray[$i]['Name'] . '</div>
																					<div class="tdata tab-voucher" style="width:130px;">' . $holidaycancelledarray[$i]['ApartmentType'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaycancelledarray[$i]['restype'] . '</div>
																					<div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaycancelledarray[$i]['CheckIn'] ? date('d/m/Y', strtotime($holidaycancelledarray[$i]['CheckIn'])) : "";$out_holiday_summary .= '</div>
																		 <div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaycancelledarray[$i]['CheckOut'] ? date('d/m/Y', strtotime($holidaycancelledarray[$i]['CheckOut'])) : "";$out_holiday_summary .= '</div>
																					<div class="tdata tab-voucher">' . $holidaycancelledarray[$i]['TotalUtilized'] . '</div>
																				</div>';
            }
            else{
              $out_holiday_summary .= '<div class="even-row trow">
																					<div class="tdata tab-voucher">' . $holidaycancelledarray[$i]['ConfirmationNo'] . '</div>
																					<div class="tdata tab-voucher">' . $holidaycancelledarray[$i]['SiteName'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaycancelledarray[$i]['Name'] . '</div>
																					<div class="tdata tab-voucher" style="width:130px;">' . $holidaycancelledarray[$i]['ApartmentType'] . '</div>
																					<div class="tdata tab-voucher" style="width:80px;">' . $holidaycancelledarray[$i]['restype'] . '</div>
																					<div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaycancelledarray[$i]['CheckIn'] ? date('d/m/Y', strtotime($holidaycancelledarray[$i]['CheckIn'])) : "";$out_holiday_summary .= '</div>
																		 <div class="tdata tab-voucher">';
						$out_holiday_summary .= $holidaycancelledarray[$i]['CheckOut'] ? date('d/m/Y', strtotime($holidaycancelledarray[$i]['CheckOut'])) : "";$out_holiday_summary .= '</div>
																					<div class="tdata tab-voucher">' . $holidaycancelledarray[$i]['TotalUtilized'] . '</div>
																				</div>';
            }
			}
				$out_holiday_summary .= '</div><div class="total-bottom">Total Holidays Cancelled<span>' .round($holiday_usage['TotalCancelled'], 1) . '</span></div></div>';
    }                           
    else{
			$out_holiday_summary .= '<div class="trow tdata"><center>No Cancelled Holidays</center></div></div><div class="total-bottom"></div></div>';
    }
		$out_holiday_summary .= ' <div id="tab-4-content" class="tab-content" style="display:none;">
                                            <div class="thead-content">
                                                <div class="thbackcolor">
                                                    <div class="theader tab-lapsed"><label class="thlabel">Lapsing Date</label></div>
                                                    <div class="theader tab-lapsed"><label class="thlabel">Holidays Lapsed</label></div>
                                                </div>
                                            </div>
                                            <div class="tbody-content">';	
    if (!empty($arr_holiday_lapsed)) {
			if (count($arr_holiday_lapsed['HUSLapsedDetail']) == 1) {
				foreach ($arr_holiday_lapsed ['HUSLapsedDetail'] as $holiday_lapsed_details);
				$out_holiday_summary .= '<div class="trow">
																					<div class="tdata tab-lapsed">';
						$out_holiday_summary .= $holiday_lapsed_details['LapsingDate'] ? date('d/m/Y', strtotime($holiday_lapsed_details['LapsingDate'])) : "";
						$out_holiday_summary .= '</div>
																					<div class="tdata tab-lapsed">' . $holiday_lapsed_details['LapsedDays'] . '</div>
																		</div>';
			}
			else{
				for ($i = 0, $count = count($arr_holiday_lapsed['HUSLapsedDetail']); $i < $count; $i++) {
					$even = $i%2;
					foreach ($arr_holiday_lapsed ['HUSLapsedDetail'][$i]as $holiday_lapsed_details);
					if ($even != 0) {
						$out_holiday_summary .= '<div class="trow">
																					<div class="tdata tab-lapsed">';
						$out_holiday_summary .= $holiday_lapsed_details['LapsingDate'] ? date('d/m/Y', strtotime($holiday_lapsed_details['LapsingDate'])) : "";
						$out_holiday_summary .= '</div>
																					<div class="tdata tab-lapsed">' . $holiday_lapsed_details['LapsedDays'] . '</div>
																		</div>';
					}
					else{
						$out_holiday_summary .= '<div class="even-row trow">
																					<div class="tdata tab-lapsed">';
						$out_holiday_summary .= $holiday_lapsed_details['LapsingDate'] ? date('d/m/Y', strtotime($holiday_lapsed_details['LapsingDate'])) : "";
						$out_holiday_summary .= '</div>
																					<div class="tdata tab-lapsed">' . $holiday_lapsed_details['LapsedDays'] . '</div>
																		</div>';
					}
				}
			}
			$out_holiday_summary .= '</div><div class="total-bottom">Total Holidays Lapsed<span>' . $holiday_usage['TotalLapsing']*(-1) . '</span></div></div>';
    }                           
    else{
			$out_holiday_summary .= '<div class="trow tdata"><center>No Elapsed Holidays</center></div></div><div class="total-bottom"></div></div>';
    }
    $out_holiday_summary .= '</div><div class="booking-notes"><div class="cancellation-info"></div>
                            <div class="cancel-book"><p>You can accumulate a maximum of 21 days (including your current years entitlement). If not utilised, any days in excess of 21 days, are liable to lapse. </p><p>If not utilised, future inventory is liable to lapse as per the following schedule:</p>
                            <table class="HUStblfake">
                            <tr><th scope="col">Date </th><th scope="col" class="noOfDays"># of Holidays</th></tr>
                            <tr><td> 01/' . $renewmonth . '/' . ($currentyear+2) . '  </td><td class="noOfDays"> 7 Days </td></tr>
                            <tr class="even-row"><td> 01/' . $renewmonth . '/' . ($currentyear+3) . ' </td><td class="noOfDays"> 7 Days </td></tr>
                            <tr><td> 01/' . $renewmonth . '/' . ($currentyear+4) . '  </td><td class="noOfDays"> 7 Days </td></tr>
                            </table></div>
                            </div>';
    $out_holiday_summary .= '<div class="cancellation-heading">Cancellation Of Confirmed Holidays</div>
                            <div class="cancellation-rule">
                            <p>We are sure that you will not cancel your holidays unless and until it is absolutely necessary and unavoidable. However, if you cancel your booked holiday without adequate notice, it will be difficult to find alternative members willing to go on those dates and the space cannot be utilized. </p>
                            <div class="cbTable">
                            <table class="cancellation-tbl">
															<tr>
																<th scope="col">Notice Time Of Cancellation (Regular Inventory<span class="asterik">* &nbsp;</span> &nbsp;)</th>
																<th scope="col">No Of Holidays Debited From Membership</th></tr>
															<tr>
																<td>Between 6 months to 16 days notice prior to the start date of holiday</td>
																<td>0% of holidays booked</td>                                    
															</tr>
															<tr class="even-row">
																<td>Between 15 days to 8 days prior to the start date of the holiday</td>
																<td>50% of the holidays booked</td>                                    
															</tr>
															<tr>
																<td>Less than 7 days prior to the start date of the holiday</td>
																<td>100% of the holidays booked</td>                                    
															</tr>
                            </table>                            
                            </div>
                            <p class="positonPR">Any amendments (or) recredit of holidays against Gift Voucher & Special offer (Complimentary holidays for members) bookings is not allowed. The same will be treated as cancellations. Cancellation policy is applicable only for Regular holidays (holidays using the Annual entitlement of 7 days) </p>
                            </div>';
  }
  $out_holiday_summary .= '</div>';
  return $out_holiday_summary;
}

/**
 * @desc   - details of dsa member payment history (business logic included).
 * @access - public
 * @author - 362137
 * @param  - $profile_details : array of data get from webservice getMemberProfileDetails.
 * @return - returns string output
 */
function get_member_phistory() {
  $args = arg();
	$user_id = array('MemberId' => $args[2]);
	drupal_add_js(array('CMHDSA' => array('pageName' => 'MemberDetails')), array("type" => "setting"));
  drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');
	$list = get_session('member_contracts');
	drupal_add_js(array('CMHDSA' => array('contracts' => $list)), array("type" => "setting"));
	
 	if (module_exists('cmh_dsa') && function_exists('get_data_ws')) {
		$arr_dsa_member_profile = get_session('profile_member_ws_data-'.$args[2]);
		if (empty($arr_dsa_member_profile)) {
			$arr_dsa_member_profile = get_data_ws('getMemberProfileDetails', 'getMemberProfileDetailsResult', $user_id);
			set_session('profile_member_ws_data-'.$args[2], $arr_dsa_member_profile);
		}
	}
  foreach ($arr_dsa_member_profile['MemberProfileDetails'] as $profile_details);
	
	drupal_add_js(drupal_get_path('module', 'cmh_dsa_members') . '/js/cmh_dsa_member.js');
	
  $start_date = start_date;
  $end_date = end_date;
  $member_phistory_param = array('MemberID' => $args[2], 'MembershipID' => $profile_details['tMembershipID'], 'StartDate' => $start_date, 'EndDate' => $end_date);
  $arr_dsa_member_acc_emi = get_data_ws('getAccountStatementEMI', 'getAccountStatementEMIResult', $member_phistory_param);
  foreach ($arr_dsa_member_acc_emi['AccountStatementEMI'] as $key_emi => $val_emi);
  $arr_dsa_member_acc_asf = get_data_ws('getAccountStatementASF', 'getAccountStatementASFResult', $member_phistory_param);
  $out_member_payment_history = '';
  $out_member_payment_history .= '<div id="payment-his">
																	 <div class="clearfix summaryTbl">
																		<div class="float-left paymentDetails">
																			<table summary="Member Details" class="payment_deatils" id="memberDetailTbl">';
  $out_member_payment_history .= '   		<tr><td class="font14bold height25">Total Payable (Including Interest)</td><td class="font13">' . sprintf("%.2f", $profile_details['TotalAmtPayIncludeInterest']) . '</td></tr>
																				<tr><td class="font14bold height25">Payment Due</td><td class="font13">' . sprintf("%.2f", $profile_details['TotalPaymentDue']) . '</td></tr>
																				<tr><td class="font14bold height25">Payment Paid</td><td class="font13">' . sprintf("%.2f", $profile_details['TotalAmtPaid']) . '</td></tr>
																				<tr><td class="font14bold height25">Payment Overdue</td><td class="font13">' . sprintf("%.2f", $profile_details['PaymentOverdueAmount']) . '</td></tr>
																				<tr><td class="font14bold height25">Future Principle</td><td class="font13">' . sprintf("%.2f", $profile_details['FuturePrincipalDue']) . '</td></tr>
																				<tr><td class="font14bold height25">Emi Overdue Count</td><td class="font13">' . sprintf("%.0f", $profile_details['EMIOverDueCount']) . '</td></tr>';
  $out_member_payment_history .= '  	</table>
																		</div>';
	$out_member_payment_history .= '	<div class="float-left" style="width:50%;">
																		  <table summary="Member Details" class="payment_deatils" id="memberDetailTbl">';
	$out_member_payment_history .= '			<tr><td class="font14bold height25">Emi ROC Count</td><td class="font13">' . $profile_details['EMIROCCount'] . '</td></tr>
																				<tr><td class="font14bold height25">Emi Overdue Amount </td><td>' . sprintf("%.2f", $profile_details['EMIOverdueAmount']) . '</td></tr>
																				<tr><td class="font14bold height25">ASF overdue Amount</td><td class="font13">' . sprintf("%.2f", $profile_details['AsfOverdue']) . '</td></tr>
																				<tr style="display:none;"><td class="font14bold height25">  Membership ID  </td><td class="font13" id="membership_id">' . $profile_details['tMembershipID'] . '</td></tr>	';																						
	$out_member_payment_history .= '		</table>
																		</div>
																	 </div>';
	$out_member_payment_history .= '<div class="content-separator"> </div>
																	<div id="tabs" class="stepByStep">
																		<ul>
																			<li id="tab-1" class="tab-title active tab-payment1"><a href="#tab-1-content">EMI Payment History</a></li>
																			<li id="tab-2" class="tab-title tab-payment2"><a href="#tab-2-content">ASF Payment History</a></li>
																		</ul>
																		<div id="tab-1-content" class="tab-content">
																			<div class="thead-content">
																					<div class="thbackcolor">
																							<div class="theader tab-emi"><label class="thlabel">Amount</label></div>
																							<div class="theader tab-emi"><label class="thlabel">Instrument Type</label></div>
																							<div class="theader tab-emi"><label class="thlabel">Instrument Date</label></div>
																							<div class="theader tab-emi"><label class="thlabel">Instrument Number</label></div>
																							<div class="theader tab-emi"><label class="thlabel">Status</label></div>
																					</div>
																			</div>
																			<div class="tbody-content">';
	if (count($arr_dsa_member_acc_emi['AccountStatement']) != 0) {
		if (count($arr_dsa_member_acc_emi['AccountStatement']) == 1) {
			foreach ($arr_dsa_member_acc_emi['AccountStatement'] as $val_emi);
			$out_member_payment_history .= '	<div class="trow">
																					<div class="tdata tab-emi">' . sprintf("%.2f", $val_emi['instrumentAmount']) . '</div>
																					<div class="tdata tab-emi">' . $val_emi['InstrumentType'] . '</div>
																					<div class="tdata tab-emi">';																	
			$out_member_payment_history .= $val_emi['InstrumentDate'] ? date('d-M-Y', strtotime($val_emi['InstrumentDate'])) : " ";
			$out_member_payment_history .='			</div>
																					<div class="tdata tab-emi">' . $val_emi['InstrumentNumber'] . '</div>
																					<div class="tdata tab-emi">' . $val_emi['InstrumentStaus'] . '</div>
																				</div>'; 
		}
		else{ 
			for ($i = 0, $count = count($arr_dsa_member_acc_emi['AccountStatement']); $i < $count; $i++) {
				foreach ($arr_dsa_member_acc_emi['AccountStatement'][$i] as $val_emi);
				$even = $i%2;
				if ($even == 0) {
					$out_member_payment_history .= '<div class="trow">
																						<div class="tdata tab-emi">' . sprintf("%.2f", $val_emi['instrumentAmount']) . '</div>
																						<div class="tdata tab-emi">' . $val_emi['InstrumentType'] . '</div>
																						<div class="tdata tab-emi">';																	
			$out_member_payment_history .= $val_emi['InstrumentDate'] ? date('d-M-Y', strtotime($val_emi['InstrumentDate'])) : " ";
			$out_member_payment_history .='				</div>
																						<div class="tdata tab-emi">' . $val_emi['InstrumentNumber'] . '</div>
																						<div class="tdata tab-emi">' . $val_emi['InstrumentStaus'] . '</div>
																					</div>'; 
				}
				else{
					$out_member_payment_history .= '<div class="even-row trow">
																						<div class="tdata tab-emi">' . sprintf("%.2f", $val_emi['instrumentAmount']) . '</div>
																						<div class="tdata tab-emi">' . $val_emi['InstrumentType'] . '</div>
																						<div class="tdata tab-emi">';																	
			$out_member_payment_history .= $val_emi['InstrumentDate'] ? date('d-M-Y', strtotime($val_emi['InstrumentDate'])) : " ";
			$out_member_payment_history .='				</div>
																						<div class="tdata tab-emi">' . $val_emi['InstrumentNumber'] . '</div>
																						<div class="tdata tab-emi">' . $val_emi['InstrumentStaus'] . '</div>
																					</div>'; 
				}
			}
		}
	$out_member_payment_history .= '</div><div class="total-bottom"></div></div>';
  }
  else{
    $out_member_payment_history .= '			<div class="trow tdata"><center>No Data Available</center></div>
																				</div>
																				<div class="total-bottom"></div>
																			</div>';
  }
	


	$out_member_payment_history .= '		<div id="tab-2-content" class="tab-content" style="display:none;">
																				<div class="thead-content">
																					<div class="thbackcolor">
																						<div class="theader tab-asf-no"><label class="thlabel">No</label></div>
																						<div class="theader tab-asf-invoice"><label class="thlabel">Invoice No.</label></div>
																						<div class="theader tab-asf-date"><label class="thlabel">Due Date</label></div>
																						<div class="theader" style="width: 125px"><label class="thlabel">Invoice Amount</label></div>
																						<div class="theader" style="width: 75px"><label class="thlabel">Paid Amount</label></div>
																						<div class="theader" style="width: 100px"><label class="thlabel">Balance</label></div>
																					</div>
																				</div>
																				<div class="tbody-content">';
	if (count($arr_dsa_member_acc_asf['ASFStatement']) != 0) {
		if (count($arr_dsa_member_acc_asf['ASFStatement']) == 1) {
			foreach ($arr_dsa_member_acc_asf['ASFStatement'] as $val_asf);
			$out_member_payment_history .= '		<div class="trow">
																						<div class="tdata tab-asf-no">1</div>
																						<div class="tdata tab-asf-invoice">' . $val_asf['InvoiceNumber'] . '</div>
																						<div class="tdata tab-asf-date">';
			$out_member_payment_history .= 					$val_asf['InstrumentDate'] ? date('d-M-Y', strtotime($val_asf['InstrumentDate'])) : " ";
			$out_member_payment_history .='				</div>
																						<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['ChargedAmount']) . '</div>															
																						<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['PaidAmount']) . '</div>
																						<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['BalanceAmount']) . '</div>
																					</div>'; 																		
		}
		else{ 
			for ($i = 0, $count = count($arr_dsa_member_acc_asf['ASFStatement']); $i < $count; $i++) {
				foreach ($arr_dsa_member_acc_asf['ASFStatement'][$i] as $val_asf);
				$even = $i%2;
				$j = $i + 1;
				if ($even == 0) {
					$out_member_payment_history .= ' 	<div class="trow">
																							<div class="tdata tab-asf-no">' . $j . '</div>
																							<div class="tdata tab-asf-invoice">' . $val_asf['InvoiceNumber'] . '</div>
																							<div class="tdata tab-asf-date">';
					$out_member_payment_history .= 				$val_asf['InstrumentDate'] ? date('d-M-Y', strtotime($val_asf['InstrumentDate'])) : " ";
					$out_member_payment_history .='			</div>
																							<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['ChargedAmount']) . '</div>															
																							<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['PaidAmount']) . '</div>
																							<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['BalanceAmount']) . '</div>
																						</div>';
				}
				else{
					$out_member_payment_history .= '	<div class="even-row trow">
																							<div class="tdata tab-asf-no">' . $j . '</div>
																							<div class="tdata tab-asf-invoice">' . $val_asf['InvoiceNumber'] . '</div>
																							<div class="tdata tab-asf-date">';
					$out_member_payment_history .= 				$val_asf['InstrumentDate'] ? date('d-M-Y', strtotime($val_asf['InstrumentDate'])) : " ";
					$out_member_payment_history .='			</div>
																							<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['ChargedAmount']) . '</div>														
																							<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['PaidAmount']) . '</div>
																							<div class="tdata tab-asf">' . sprintf("%.2f", $val_asf['BalanceAmount']) . '</div>
																						</div>';
				}
			}
		}
		$out_member_payment_history .= '				</div>
																					<div class="total-bottom"></div>
																				</div>';
  }
  else{
    $out_member_payment_history .= '		<div class="trow tdata"><center>No Data Available</center></div>
																			</div>
																			<div class="total-bottom"></div>
																		</div>';
  }
  
  $out_member_payment_history .= '</div></div>';
  return $out_member_payment_history;
}