<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA My Account Form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['cmh_dsa_myaccount'];
*
*/
?>					
<div id="accountinfo_content" class="account-container margintop40">
	
	<!-- Success and error messages div start -->
	<div id="success-mesg" class="err-succs-msg acc-margintop20"></div>
	<div id="error-mesg" class="err-succs-msg"></div>
	<!-- Success and error messages div end-->
	
	<!-- Account Info form start -->
	<div class="account-field-row">
		<div class="accfield" id="accfieldrow-id">
			<span><label class="font13bold">DSA ID</label></span>
			<span>
				<?php print $variables['cmh_dsa_myaccount']['dsa_id']; ?>
			</span>
		</div>
		<div class="accfield" id="accfieldrow-phone">
			<span><label class="font13bold">Phone1<span class="asterik">* </span></label></span>
			<span><?php print $variables['cmh_dsa_myaccount']['phone1']; ?></span>
		</div>
		<div class="fontred12 acc-err-msg" id="phone1-invalid" style="display:none">Please enter valid Phone Number 1.</div>
	</div>
	<div class="account-field-row">
		<div class="accfield" id="accfieldrow-name">
			<span><label class="font13bold">DSA Name</label></span>
			<span><?php print $variables['cmh_dsa_myaccount']['dsa_name']; ?></span>
		</div>
		<div class="accfield" id="accfieldrow-phone">
			<span><label class="font13bold">Phone2<span class="asterik">* </span></label></span>
			<span><?php print $variables['cmh_dsa_myaccount']['phone2']; ?></span>
		</div>
		<div class="fontred12 acc-err-msg" id="phone2-invalid" style="display:none">Please enter valid Phone Number 2.</div>
	</div>
	<div class="account-field-row">
		<div class="accfield" id="accfieldrow">
			<span><label class="font13bold">Owner1</label></span>
			<span><?php print $variables['cmh_dsa_myaccount']['owner1']; ?></span>
		</div>
		<div class="accfield" id="accfieldrow-email">
			<span><label class="font13bold">Email ID<span class="asterik">* </span></label></span>
			<span><?php print $variables['cmh_dsa_myaccount']['email_address']; ?></span>
		</div>
		<div class="fontred12 acc-err-msg" id="email-invalid" style="display:none">Please enter valid Email ID.</div>
	</div>
	<div class="account-field-row">
		<div class="accfield" id="accfieldrow">
			<span><label class="font13bold">Owner2</label></span>
			<span><?php print $variables['cmh_dsa_myaccount']['owner2']; ?></span>
		</div>
	</div>
	<div class="account-field-row">
		<div class="addfield" id="accfieldrow-add">
			<span><label class="font13bold">Office Address</label></span>
			<span class="form-textarea-wrapper address-textarea">
				<?php print $variables['cmh_dsa_myaccount']['office_address']; ?>
			</span>
		</div>
	</div>
	<!-- Account Info form end -->
	<!-- Submit Button section start -->
	<div class="account-but-row">
		<div class="actionbutton clearfix dialogBtns">
			<?php print $variables['cmh_dsa_myaccount']['submit']; ?>
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
<?php print $variables['cmh_dsa_myaccount']['hidden']; ?> 