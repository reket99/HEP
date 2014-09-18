<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Change Password Form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['dsaChangePassword'];
*
*/
?>					
<div id="changepass_content" class="account-content margintop40">
	
	<!-- Success and error messages div start -->
	<div id="chgpass-success-msg" class="err-succs-msg acc-margintop20"></div>
	<div id="change-pass-errormsg" class="err-succs-msg"></div>
	<!-- Success and error messages div end-->
	
	<!-- Change Password form start -->
	<div class="account-field-row">
		<div class="accfield75" id="accfieldrow-curpass">
			<span><label class="font13bold">Current Password<span class="asterik asterik-pos">* </span></label></span>
			<span><?php print $variables['cmh_dsa_change_pwd']['current_password']; ?></span>
		</div>
		<div class="fontred12 chng-err-msg" id="curr-pass-invalid" style="display:none">Password should be more than 8 characters with atleast 1 number (1,2,3...), atleast 1 special character (@,#,_,$,%,!,^,&,*,-) and atleast 1 letter.</div>
		<div class="fontred12 chng-err-msg" id="curpass-newpass-invalid" style="display:none">Current Password and New Password should not be same</div>
		<div class="fontred12 chng-err-msg" id="correct-curpass-invalid" style="display:none">Please enter correct Current Password.</div>
		
	</div>
	<div class="account-field-row">
		<div class="accfield75" id="accfieldrow-pass">
			<span><label class="font13bold">New Password<span class="asterik asterik-pos">* </span></label></span>
			<span><?php print $variables['cmh_dsa_change_pwd']['new_password']; ?></span>
		</div>
		<div class="fontred12 chng-err-msg" id="new-pass-invalid" style="display:none">New Password should be more than 8 characters with atleast 1 number (1,2,3...), atleast 1 special character (@,#,_,$,%,!,^,&,*,-) and atleast 1 letter.</div>
										
	</div>
	<div class="account-field-row">
		<div class="accfield75" id="accfieldrow-repass">
			<span><label class="font13bold">Re-enter new Password<span class="asterik asterik-pos">* </span></label></span>
			<span><?php  print $variables['cmh_dsa_change_pwd']['confirm_new_password']; ?></span>
		</div>
		<div class="fontred12 chng-err-msg" id="repass-invalid" style="display:none">Password should be more than 8 characters with atleast 1 number (1,2,3...), atleast 1 special character (@,#,_,$,%,!,^,&,*,-) and atleast 1 letter.</div>
		<div class="fontred12 chng-err-msg" id="newpass-repass-invalid" style="display:none">New Password and Re-enter Password do not match.</div>
	</div>																	
	<!-- Change Password form end -->
	<!-- Submit Button section start -->
	<div class="button-row">
		<div class="actionbutton clearfix dialogBtns">
			<?php print $variables['cmh_dsa_change_pwd']['submit']; ?>
			<div class="greybox-small marginleft-15 float-left">
				<a onclick="" href="javascript:void(0)" title="Reset" class="" id="btnresetform">
					<span class="left"></span><span class="mid">Reset</span><span class="right"></span>
				</a>
			</div>
		</div>
	</div>
	<!-- Submit Button section end -->
</div>					
					
<!-- Thick box for RESET button -->
<div id="resetConfirmDialog" class="modalMessage" style="position: relative;display: none;">
  <div class="diagPopupBox">
    <div class="popupHeading">
      <h2>Please Confirm</h2>
    </div>
    <div class="dialogMessage">Unsaved information will be lost. Are you sure you want to reset?</div>
    <div class="dialogButtons">
      <div class="actionButtonSmall dialogLeftbtn">
        <a class="clearfix dialogOk" href="javascript:void(0);" id="yesbtn" onclick="" title="Yes"> <span
          class="left"></span> <span class="mid">Yes</span> <span
          class="right"></span>
        </a>
      </div>
      <div class="greyBox_small dialogRightbtn">
        <a class="clearfix dialogCancel" href="javascript:void(0);"
          title="No" onClick="tb_remove();"> <span class="left"></span> <span
          class="mid">No</span> <span class="right"></span>
        </a>
      </div>
    </div>
  </div>
</div>
<?php print $variables['cmh_dsa_change_pwd']['hidden']; ?> 	