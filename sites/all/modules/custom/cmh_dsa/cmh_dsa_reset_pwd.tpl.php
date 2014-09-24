<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Reset Password Form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['dsa_reset_password'];
*
*/
 ?>
<div class="content-header-forgot-pass">Reset Your Password</div>
<div class="content-block-forgot-pass">
<div class="contentWrapper clearfix">
    <div class="viewSection recoverAccess" id="myAccount">
      <div class="dashboardContent">
        <div class="accountSettingDetails leftPad clearfix minHeight">
          <input type="hidden" id="signup" name="signup" value="" />
          
          <!--<div class="success-msg">
            <span class="success-img"></span>
            <span class="font13bold float-left margintop12">
              Booking request sent successfully!
            </span>
          </div>-->
          <div id="error-mesg" class="err-succs-msg"></div>		
          
          
          <?php 
          if (get_session('dsa_user_data', 'dsa_user_id_reset_errormsg') != ''){
          ?>            
          <div class="error-msg">
            <span class="error-img"></span>
            <span class="font13bold float-left margintop12" id="err-invalid-text">
             <?php echo get_session('dsa_user_data', 'dsa_user_id_reset_errormsg'); ?>
            </span>
          </div>
          <?php
          }
          ?>
          
          <div class="formfield">
            <div class="formfield-label"><label>User ID</label></div>
            <div class="clearfix normtxtbox">
							<!--<div class="left"></div><div class="txtField">-->
							<?php print $variables['dsa_reset_password']['user_id']; ?>
							<!--</div><div class="right"></div>-->
						</div>
          </div>
          <div class="formfield">
            <div class="formfield-label"><label><font color="#CC0000">*</font>Enter New Password</label></div>
            <div class="clearfix normtxtbox" id="enterPwd">
							<!--<div class="left"></div><div class="txtField">-->
							<?php print $variables['dsa_reset_password']['new_password']; ?>
              <div class="fontred12 reset-pass-err-msg clearfix" id="newpwd-invalid" style="display:none">
              Password should be more than 8 characters with atleast 1 number (1,2,3...), atleast 1 special character (@,#,_,$,%,!,^,&,*,-) and atleast 1 letter
              </div>
							<!--</div><div class="right"></div>-->
						</div>
          </div>
          <div class="formfield">
            <div class="formfield-label"><label><font color="#CC0000">*</font>Re-enter New Password</label></div>
            <div class="clearfix normtxtbox" id="reenterPwd">
							<!--<div class="left"></div><div class="txtField">-->
							<?php print $variables['dsa_reset_password']['confirm_new_password']; ?>
               <div class="fontred12 reset-pass-err-msg clearfix" id="renewpwd-invalid" style="display:none">
              Password should be more than 8 characters with atleast 1 number (1,2,3...), atleast 1 special character (@,#,_,$,%,!,^,&,*,-) and atleast 1 letter
              </div>
							<!--</div><div class="right"></div>-->
						</div>
          </div>
          <div class="formfield captcha">
            <div class="formfield-label"><label><font color="#CC0000">*</font>Verification Code <span><br>(type characters on the image in the text box)</span> </label></div>
            <img src="?q=captcha" border="0" alt="captcha" title="captcha" id='captchacode' style="padding-right: 10px"/>
            <div class="clearfix normtxtbox" id="vercodeDiv">
              <!--<div class="left"></div>
              <div class="txtField">-->
              <?php print $variables['dsa_reset_password']['varification_code']; ?>   
              <div class="fontred12 reset-pass-err-msg clearfix" id="vercode-invalid" style="display:none">
              Incorrect verification code
              </div>
              <input type="hidden" name="tokenval" id="tokenval" tabindex="1" value="
              <?php  echo get_session('dsa_user_data', 'dsa_token_reset');?>" maxlength="10" size="20">
              <!--</div>
              <div class="right"></div>-->
            </div>
            <div class="clear"></div>
          </div>
          <!--
          <div class="formButtons clearfix bottomButtons">
            <div class="float-right"><div class="actionbutton floatLeft"><a title="Submit" href="javascript:void(0);"  id="submitBtn"> <span class="left">&nbsp;</span><span class="middle">Submit</span> <span class="right">&nbsp;</span></a></div></div>
          </div>
         -->
         <div class="actionbutton clearfix dialogBtns"  id="btnAgree">
         <?php print $variables['dsa_reset_password']['submit']; ?>
         
         </div>
        </div>
      </div>
        <?php print $variables['dsa_reset_password']['hidden']; ?>    
    </div>
</div>
</div>
