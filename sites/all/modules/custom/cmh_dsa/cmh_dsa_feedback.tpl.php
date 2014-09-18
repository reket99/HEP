<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Feedback Form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['news_updates_block'];
*
*/
 ?>

<div class="content-header"><div class="content-header-text">Feedback</div></div>
	<!-- content-block start -->
	<div class="content-block">
		<!-- Success and error messages div start-->
		<?php if((get_session('dsa_user_data', 'feedback_success_msg')) != '') { ?>
		<div class="success-msg">
			<span class="success-img"></span>
			<span class="font13bold float-left margintop12">
				<?php  echo get_session('dsa_user_data', 'feedback_success_msg');?>
				<?php unset_session('dsa_user_data', 'feedback_success_msg'); ?>
			</span>
		</div>
		<?php } ?>
		<div id="error-mesg" class="err-succs-msg"></div>						
		<!-- Success and error messages div end-->
		<!-- Feedback form start -->
		<div class="formfield">
			<div class="formfield-label">
				<label class="font13bold">DSA ID</label>
			</div>
			<div id="dsaid">
				<?php print $variables['news_updates_block']['dsa_id']; ?>
			</div>
		</div>
		<div class="formfield">
			<div class="formfield-label">
				<label class="font13bold">DSA Contact</label>
			</div>
			<div id="dsa_contact">
				<?php print $variables['news_updates_block']['dsa_contact']; ?>
			</div>
		</div>
		<div class="formfield">
			<div class="formfield-label">
				<label class="font13bold">Category<span class="asterik">* </span></label>
			</div>
			<div id="formsubject">
				<?php print $variables['news_updates_block']['drpsubject']; ?>
			</div>
		</div>
		<div class="formfield">
			<div class="formfield-label">
				<label class="font13bold">Subject</label>
			</div>
			<div id="subjectid">
				<?php print $variables['news_updates_block']['sub_text']; ?>
			</div>
		</div>
		<div class="formfield">
			<div class="formfield-label">
				<label class="font13bold">Feedback<span class="asterik">* </span></label>
			</div>
			<div class="form-textarea-wrapper width68" id="formfeedback">
				<?php print $variables['news_updates_block']['txtfeedback']; ?>
			</div>
			<div class="fontred12 err-msg" id="feedback-invalid" style="display:none">Please enter valid feedback.</div>
		</div>
		<!-- Feedback form end -->
	<!-- Submit Button section start -->
	<div class="button-row">
		<div class="actionbutton clearfix dialogBtns">
			<div class="action-button-border float-left">
				<a title="Submit" onclick="" class="clearfix" id="feedback-submitbtn" href="javascript:void(0)">
					<span class="left"></span>
					<span class="mid">Submit</span>
					<span class="right"></span>
				</a>
			</div>
			<div class="greybox-small marginleft-15 float-left">
				<a onclick="" href="javascript:void(0)" title="Reset" class="" id="btnresetform">
					<span class="left"></span><span class="mid">Reset</span><span class="right"></span>
				</a>
			</div>
		</div>
	</div>
	<!-- Submit Button section end -->
</div><!-- content-block end-->
	
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
<?php print $variables['news_updates_block']['hidden']; ?>    

