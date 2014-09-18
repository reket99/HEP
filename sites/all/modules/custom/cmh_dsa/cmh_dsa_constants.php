<?php
/**
 * @file         dsa_common_function file
 * @version      1.0.0
 * @author       CTS
 * @desc         This is a DAS Common Constants file
 * @date         29/07/2013
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 */
define('SESSION_TIMEOUT','1800');  
define('SITE_SESSION','DSA_SESSION');  
define('theme', 'cmh_orange_theme');
define('theme_path', drupal_get_path('theme', 'cmh_orange_theme'));
define('current_date', date("d-m-Y"));
define('not_allowded', '<script, <a, <input, <base, <object, <html, <div, <form, &gt;, &lt;, &gt, &lt, <frame, <iframe, <body, <meta, <head ');
define('striptime', 10);
$path = drupal_lookup_path('alias', current_path());
if (trim($path) == '') {
  $params = arg();
}
else{
  $params = arg(NULL, $path);
}

//echo "<pre>"; print_r($_SERVER);echo "</pre>";
define('pageId', $params[0]);
define('IP', $_SERVER['REMOTE_ADDR']);
define('SESSID', session_id());
define('LOGINID', '');
define('LOG_CONTEXT_VAR', 'yes');
define('USER_AGENT', $_SERVER['HTTP_USER_AGENT']);
define('url_root_for_media', 'http://localhost/drupalnew/');
//define('SITE_URL', 'http://localhost/drupalnew/');
if (!isset($_SERVER['HTTPS']) || strtolower($_SERVER['HTTPS']) == 'off' ||  $_SERVER['HTTPS'] == '') {
	define('SITE_URL', 'http://' . $_SERVER['HTTP_HOST'] . '/');
}
else {
	define('SITE_URL', 'https://' . $_SERVER['HTTP_HOST'] . '/');
}
//Base public content folder
define('base_public_content_folder', 'D:\\xampp\\htdocs\\drupalnew\\');
define('start_date', '1997-01-01');
define('end_date', date("Y-m-d", strtotime(date("Y-m-d") . " +1 day")));
define('public_media_url_path', 'sites/default/files/');
//default redirection constant
define('default_redirection_url', 'DsaSearchMember');

/* Feedback constants */
define('feedback_status', 'yes');
if (isset($_SERVER["HTTPS"]) && strtolower($_SERVER["HTTPS"]) == "on") {
  define('ishttps', $_SERVER['HTTPS']);
}
static $default_zone_array = array("EAST_ZONE", "WEST_ZONE", "SOUTH_ZONE", "NORTH_ZONE", "CENTRAL_ZONE");
static $unauth_pageid_array = array("dsalogin", "DsaRegister", "forgot_password", "user", "captcha", "checkUserSession", "fill_drop_down_list", "check_mail", "DsaThankyou", "EmailSecurity");

drupal_add_js(array('CMHDSA' => 
              array('SITETHEME' => theme, 
                    'SITE_URL' => SITE_URL,
                    'SITE_PROJECT_FOLDER' => 'drupalnew/',
                    'THEME_PATH' => theme_path,
                    'PROCESSING' => '<img src=' . SITE_URL . theme_path . '/images/ajaxProcessing.gif alt="Loading"/><span class="ajaxLoadingText">Logging in - Please Wait !</span>',
                    'LOGINPROCESSSING' => '<img src=' . SITE_URL . theme_path . '/images/ajaxProcessing.gif  alt="Loading" class="loadingLogin" /><span class="ajaxLoadingText">Logging in - Please Wait !</span>',
                    'LOADING' => '<span class="ajaxLoadingText">Loading Please Wait!</span>',
                    'WAITING' => '<img src=http:' . SITE_URL  . theme_path . '/images/ajaxProcessing.gif alt="Loading"/><span class="ajaxLoadingText">Loading Please Wait!</span>',
                    'HTTPS_URL' =>  '',
                    'CURRENT_DATE' => current_date,
                    'NOT_ALLOWED' => not_allowded,
                    'IMAGE_PATH' => SITE_URL  . theme_path . '/images/',
                    'STRIPTIME' => striptime,
                    'PAGEID' => pageId,
                    'pageId' => pageId,
                    'LOOKFOR' => isset($params[1]) ? $params[1] : '',
                    'MEMBERID' => isset($params[2]) ? $params[2] : '',
                    'wishlistStatus' => 0,
                    'dialogWishlistStatus' => 0,
                    'CONTRACT_ID' => 80352,
                    'AJAX_URL_ARR' => array('checkUserSession', "forgot_password", "fill_drop_down_list", "check_mail"),
                  ),
                ), 
              'setting');