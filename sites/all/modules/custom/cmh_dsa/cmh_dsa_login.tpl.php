<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Login form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['dsalogin'];
*
*/
?>
<div class="loginPgImg">
   <img alt="Welcome" src="<?php print base_path().drupal_get_path('theme', 'cmh_dsa_theme') ?>/images/welcome1.jpg" />
</div>
<div class="welcomeForm">
    <div class="form">
  <div class="label"><h3>Login - Business Partner</h3></div>
  <div class="mandetoryTxt">All Fields are mandatory</div>
  <?php 
  if ( get_session('dsa_user_data', 'dsa_login_err') == 'invalid' ) {
  ?>
  <div id="errorMsg" class="validationErrMsg"><ul>Invalid UserID/Password.</ul></div>
  <?php
    unset_session('dsa_user_data', 'dsa_login_err');
  } 
  else {
  ?>
  <div id="errorMsg" class="validationErrMsg" style="display:none"><ul></ul></div>
  <?php 
  }
  ?>
  <div class="clearfix">
    <div class="floatLeft label marginT labelwidth150px">User ID</div>
    <div id="userId" class="txtBoxMask clearfix normtxtbox floatLeft marginT">
    <?php print $variables['dsalogin']['user_id']; ?>
    </div>
    <div class="floatLeft label marginT labelwidth150px">Password</div>
    <div id="password" class="txtBoxMask clearfix normtxtbox floatLeft marginT">
    <?php print $variables['dsalogin']['password']; ?>
    </div>
    <div class="actionButton floatLeft fullWidth">
    <?php print $variables['dsalogin']['submit']; ?>
    <!-- <span class="login-text" style="">Login</span> -->
    <div class="clear"></div>
    </div>
    <div class="clear"></div>
    <div class="dsaForgotLinks">
    <ul>
      <li><a href="#forgotDSAUserID" id="forgotUId" title="Forgot User ID ?" rel="facebox" >Forgot User ID ?</a> </li>
      <li><a href="#forgotDSAPassword" id="forgotPwd" title="Forgot User Password?" rel="facebox"> Forgot User Password ?</a></li>
    </ul>
    </div>
  </div>
  <?php print $variables['dsalogin']['hidden']; ?>
    </div>
</div>
<!-- forgot user id block starts -->
<div class="popUpFormContent" id="forgotDSAUserID" style="display:none;">
  <div class="popup_heading">
    <h2>Forgot User ID</h2>
  </div>
  <div class="actionButton">
    <p class="italic">Hint : User ID might be your DSA ID; else please contact Member Relations Centre  (18602101111*) </p>
  </div>   
</div>
<!-- forgot user id block ends -->
<!-- forgot Password block starts-->
<div class="popUpFormContent" id="forgotDSAPassword" style="display:none;">
  <div class="popup_heading"><h2>Forgot Password</h2></div>
  <form name="frmforgotPassword" >
    <div class="formContent clearfix formContentFields">
      <div class="marginB">Please enter the following fields </div>
      <div class="heading floatLeft labels"><label for="fgpwduser"><span class="asterik">* </span>User ID </label></div>
      <div class="clearfix" id="forgotUser" style="padding-top:10px;">
				<!--<div class="left"></div><div class="txtField">-->
					<input id="fgDSApwduserId" name="fgDSApwduserId" type="text" maxlength="50" class="txtBox_medium"/>
				<!--</div><div class="right"></div>-->
			</div>
      <div class="heading floatLeft labels"><label for="fgpwdRegEmail"><span class="asterik">* </span>Primary Email ID </label></div>
      <div class="clearfix" id="forgotEmail" style="padding-top:10px;">
				<!--<div class="left"></div><div class="txtField">-->
					<input id="fgpwdDSARegEmailid" name="fgpwdDSARegEmailid" maxlength="50" type="text" class="txtBox_medium"/>
				<!--</div><div class="right"></div>-->
			</div>
    </div>
    <input id="roleid" name="roleid" type="hidden" value="1011"/>
    <div class="validationErrMsg" id="forgotErr" style="display:none"><ul></ul></div>
    <div class="actionButton clearfix" id="ajaxfrgtpwd">
      <div class="actionButtonBorder floatLeft"><a href="javascript:void(0);" class="clearfix submitFB fbBtn"  rel="facebox" title="Submit" id="forgotPassSubmit"><span class="left"></span><span class="mid">Submit</span><span class="right"></span></a></div>
      <div class="greyBox_small floatLeft marginleft-15"><a href="javascript:void(0);" class="clearfix cancelFB fbBtn" title="Cancel" id="forgotPassCancel"><span class="left"></span><span class="mid">Cancel</span><span class="right"></span></a></div>
    </div>
    <div class="actionButton clearfix" id="ajaxfrgtpwdloading" style="display:none"><img src="sites/all/modules/cmh_dsa/images/ajaxProcessing.gif" alt='Loading'/><span class='ajaxLoadingText'>Validating Please Wait !</span></div>
  </form>
</div>
<!-- forgot Password block ends-->
<div id="exitPasswordPopUp" style="display:none" class="exitPopup">
    <div class="popup_heading"><h2 class="floatLeft">Forgot Password</h2></div>
       <div class="exitContent">
        <p>Please verify the link in your registered email to reset your password</p>
         <div class="actionButtonBorder"><a href="#" class="clearfix resultFB" rel="facebox"><span class="left"></span><span class="mid">Ok</span><span class="right"></span></a></div>
        </div>
</div>

<script type="text/javascript">
jQuery.noConflict();
jQuery(document).ready(function() {
  if(jQuery('a[rel*=facebox]').length > 0) {
    jQuery.facebox.settings.closeImage = '<?php echo base_path().drupal_get_path("theme", "cmh_orange_theme"); ?>/images/closelabel.png';
    jQuery.facebox.settings.loadingImage = '<?php echo base_path().drupal_get_path("theme", "cmh_orange_theme"); ?>/images/loadingAnimation.gif';
    jQuery('a[rel*=facebox]').facebox();
  }
});
 
</script>