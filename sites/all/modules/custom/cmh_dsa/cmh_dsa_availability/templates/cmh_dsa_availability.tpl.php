<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Availability form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['dsa_resort_availability'];
*
*/
 ?>
<script type="text/javascript">
var mydate=new Date();
jQuery('.datePickerField').datepick({
    dateFormat: "dd-mm-yyyy",
    monthsToShow: 1, showTrigger: '#search_Calender',minDate:new Date(),
    onSelect: function (){this.focus();}
});
</script>
  <form name="availabilityFrm" id="availabilityFrm" method="post" action="DsaAvailability">
  <div class="content-header"><div class="content-header-text">Resort Availability</div></div>
  <div class="content-block">
		<div class="accountSettingDetails clearfix fullWidth">
			
      <!-- Success and error messages div start-->
      <?php 	if(get_session('dsa_user_data', 'booking_req_sent') == '1') {
					unset_session('dsa_user_data', 'booking_req_sent'); ?>
      <div class="success-msg">
        <span class="success-img"></span>
        <span class="font13bold float-left margintop12">
          Booking request sent successfully!
        </span>
      </div>
      <?php } ?>
      <div id="error-mesg" class="err-succs-msg"></div>						
      <!-- Success and error messages div end-->
        
        
        
        
			<div class="formfield">
				<div class="formfield-label">
          <label class="font13bold">Location<span class="asterik">*</span></label>
        </div>          
				<div class="clearfix" id="locSection">
					<?php print $variables['dsa_resort_availability']['drpWLPlanLocation']; ?>
				</div>
			</div>    

			<div class="formfield">
				<div class="formfield-label">
          <label class="font13bold">Resort<span class="asterik">*</span></label>
        </div>          
				<div class="clearfix" id="resortSection">
					<?php print $variables['dsa_resort_availability']['drpWLPlanResort']; ?>
				</div>
			</div>      
			
			<div class="formfield">
				<div class="formfield-label">
          <label class="font13bold">Date<span class="asterik">*</span></label>
        </div>
				<div class="txtField">
					<input id="popupDatepicker" name="popupDatepicker" readonly="readonly" value="" type="text" class="datePickerField" style="width:158px"/>
					<img src="sites/all/themes/<?php echo theme;?>/images/icon_calendar.gif" id="search_Calender" border="0" alt="" title="Calendar" />
				</div>
			</div>
      
			<div class="formfield">
				<div class="formfield-label">
          <label class="font13bold">Member ID</label>
        </div> 
        <div class="clearfix" id="memberSection">
						<?php print $variables['dsa_resort_availability']['member_list']; ?>
            <div class="fontred12 resort-avail-err-msg clearfix" id="memberid-invalid" style="display:none">Please select valid member ID</div>
         </div>
			</div>
      
			<div class="formfield">
				<div class="formfield-label">
          <label class="font13bold">Membership ID</label>
        </div>          
				<div class="clearfix" id="locSection">
					<?php print $variables['dsa_resort_availability']['drpContract']; ?>
				</div>
			</div>  
		</div>
		<div class="float-right" id="actionBtns" style="display:none">
		<!--	<div class="actionButton floatLeft">
				<a title="Check Availability" id="checkAvailabilityBtn" href="javascript:void(0)"> 
					<span class="left" title="Check Availability">&nbsp;</span><span class="middle" title="Check Availability">Check Availability</span> <span class="right" title="Check Availability">&nbsp;</span>
				</a>
        <?php //print $variables['dsa_resort_availability']['submit']; ?>
        
            <div class="frmGrayButton floatLeft marginL">
            <a href="javascript:void(0);" title="Reset" class="" id="btnResetForm"> 
              <span class="left" title="Reset">&nbsp;</span><span class="middle" title="Reset">Reset</span> <span class="right" title="Reset">&nbsp;</span>
            </a>
          </div>
          <div class="greybox-small marginleft-15 float-left">
            <a onclick="" href="javascript:void(0)" title="Reset" class="" id="btnresetform">
              <span class="left"></span><span class="mid">Reset</span><span class="right"></span>
            </a>
          </div>
			</div>-->

      
      
			<div class="actionbutton clearfix dialogBtns"  id="btnAgree">
        <?php print $variables['dsa_resort_availability']['submit']; ?>
        <div class="greybox-small marginleft-15 float-left">
          <a id="btnresetform" class="" title="Reset" href="javascript:void(0)" onclick="">
            <span class="left"></span><span class="mid">Reset</span><span class="right"></span>
          </a>
        </div>
		</div>
    
    
    
    
		</div>
		<div class="fullWidth availContent" id="ajaxContent" style="display:none;">
			<h2>Availability</h2>
		</div>
  </div>  
  </form>
  
</div>

       
<script type="text/javascript">
//callToDialog("{/literal}{$stylepath}{literal}HolidayDeletePopup.php","{/literal}{$pageId}{literal}", "deleteConfirmDialog", "#btnResetForm", "reset", "a.dialogOk");
</script>


<div id="resetConfirmDialog" class="modalMessage" style="position: relative;display: none;">
  <div class="diagPopupBox">
    <div class="popupHeading">
      <h2>Please Confirm</h2>
    </div>
    <div class="dialogMessage">Unsaved information will be lost. Are you sure you want to reset?</div>
    <div class="dialogButtons">
      <div class="actionButtonSmall dialogLeftbtn">
        <a class="clearfix dialogOk" href="javascript:void(0);" id="yesBtn" onclick="" title="Yes"> <span
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
<div id="ajaxResult" style="display:none;">


<?php print $variables['dsa_resort_availability']['hidden']; ?>    