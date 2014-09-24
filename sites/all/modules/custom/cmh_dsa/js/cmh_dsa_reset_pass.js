/**
 * @file
 * The JS file for Reset Password page.
 *
 */
( function(dsaReset){
  Drupal.behaviors.dsaReset = {
		attach: function (context, settings){

			dsaReset(document).ready(function() {
        ajaxflag = true;
				reset_form();
				dsaReset('#edit-user-id').attr('disabled',true);
				//dsaReset('#submitBtn').click(function(){
				dsaReset('#cmh-dsa-reset-password-form').submit(function(){
          dsaReset("#error-mesg").hide(); 
          if (common_fun.validate_dsa_pwd() == false) { 
            return false;
          }
          else {
            return true;
          }
				});
				
				dsaReset("form input, form select").live("keypress", function (e) {
					if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) { 
						dsaReset('#cmh-dsa-reset-password-form').submit();
					}
				});
			});

			var common_fun = {
				validate_dsa_pwd:function() { 
					var pwd = dsaReset("#password").val();
					var pwd = dsaReset("#password").val();
					var confpwd = dsaReset("#confirmpassword").val();
					var userid = dsaReset("#edit-user-id").val();
					var token = trim(dsaReset("#tokenval").val()); 
					var vercode = dsaReset("#vercode").val();
					var signFlag = dsaReset("#signup").val(); 

						var flagpwd = true;
						var flagpwd_valid = true;
						
					if (pwd == '') {
						dsaReset("#enterPwd").addClass("errorfield");
            dsaReset("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
            dsaReset("#error-mesg").show();
            dsaReset(".success-msg").hide();
            
						flagpwd=false;
						common_fun.reload();
						return false;

					} else {
						 dsaReset("#enterPwd").removeClass("errorfield");
					}
					if (!isValidPassword(pwd)) {
						dsaReset("#newpwd-invalid").show();
            dsaReset("#enterPwd").addClass("errorfield");
						dsaReset("#password,#confirmpassword,#vercode").val("");	
						flagpwd_valid=false;
						common_fun.reload();
						return false;
					} else {
						 dsaReset("#enterPwd").removeClass("errorfield");
             dsaReset("#newpwd-invalid").hide();
					}
					if (confpwd == '') {
						dsaReset("#reenterPwd").addClass("errorfield");
            dsaReset("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
            dsaReset("#error-mesg").show();
            dsaReset(".success-msg").hide();
            
						flagpwd=false;
						common_fun.reload();
						return false;

					} else {
						 dsaReset("#reenterPwd").removeClass("errorfield");
					}
					
					if (!isValidPassword(confpwd)) {
						 dsaReset("#renewpwd-invalid").show();
  					 dsaReset("#reenterPwd").addClass("errorfield");
						 flagpwd_valid=false;
						 dsaReset("#password,#confirmpassword,#vercode").val("");	
						 common_fun.reload();
						 return false;
					} else {
						 dsaReset("#reenterPwd").removeClass("errorfield");
             dsaReset("#renewpwd-invalid").hide();
					}
					
					
					if (pwd != confpwd) {
						dsaReset("#password,#confirmpassword,#vercode").val("");	
						dsaReset("#enterPwd").addClass("errorfield");
						dsaReset("#reenterPwd").addClass("errorfield");
            dsaReset("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">New Password and Re-enter New Password should be same.</span></div>');
            dsaReset("#error-mesg").show();
            dsaReset(".success-msg").hide();
						flagpwd_valid=false;
						common_fun.reload();
						return false;
					} else {
						dsaReset("#enterPwd").removeClass("errorfield");
						dsaReset("#reenterPwd").removeClass("errorfield");
					}

					if (vercode == '') {
						dsaReset("#vercodeDiv").addClass("errorfield");
            dsaReset("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
            dsaReset("#error-mesg").show();
            dsaReset(".success-msg").hide();
            
						flagpwd=false;
						common_fun.reload();
						return false;
					} else {
						dsaReset("#vercodeDiv").removeClass("errorfield");
					}
					
						
					if(flagpwd && flagpwd_valid) {
						if(signFlag == ''){
							signFlag = 'invalid';
						}
						var data = userid + '///' + token + "/" + pwd + "/" + confpwd + "/" + vercode + "/" + signFlag;
						dsaReset.ajax({ 
							// add field for question & answer
							type : "POST",
							url : "?q=forgot_password/" + data,
							async:false,
							success : function(data) {
                common_fun.check_session(data);	
								if (data == 'errorcode') {
									dsaReset('#vercode-invalid').show();
                  dsaReset("#vercodeDiv").addClass("errorfield");
                  ajaxflag = false;
                  return false;
								}
								else if (data == 'link_expired') {
                  dsaReset("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Sorry ! The change password link has expired.</span></div>');
                  dsaReset("#error-mesg").show();
                  dsaReset(".success-msg").hide();
                  ajaxflag = false;
									return false;
								}
								if (data == 'success') {
									 alert("Password has been Reset successfully");
									 location.href = '?q=dsalogin';
									 // common_fun.show_alert_dialog_security_success(
											// dsaReset("#cmh-dsa-reset-password-form"),
											// "DSAforgotpasswordsuccess");
								}
							}

						});
            if(ajaxflag == false){
              return false;
            }
            else {
              return true;
            }
            
					}
          else if(flagpwd == false) {
            return false;
          }
				},
			
				//captcha reload
				reload:function (){
						var x = dsaReset('#captchacode');
						x.src = '?q=captcha.php?rand='+Math.random();
				},
				
				check_session:function (data) {
					var redirect=false;
					if(data == 'sessionTimeout' || data == '"sessionTimeout"')	{	
						redirect=true;
					}
					if(redirect) {
						location.reload();
					}	
				},
				// for SecurityQuestion/ForgotPassword page
				show_alert_dialog_security_success:function (jQSelector, errorMessage) {

					if (errorMessage == 'demosuccess') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSecurityNonmembersuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Your answer saved successfully');
					}
					if (errorMessage == 'success') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSecuritymembersuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Your answer saved successfully');
					}
					if (errorMessage == 'feedbacksuccess') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSecuritymemberFeedbackSuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Your answer saved successfully');
					}
					if (errorMessage == 'forgotpassword') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSecurityforgotsuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Your answer saved successfully');
					}
					if (errorMessage == 'forgotpasswordsuccess') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSecurityforgotsuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Your password has been changed successfully');
					}
					if (errorMessage == 'signuppasswordsuccess') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSignupforgotsuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Your password has been created successfully');
					}
					if (errorMessage == 'forgotpassworderror') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=errResponseDialogSecurityforgotsuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Error in password updation');
					}
					if (errorMessage == 'DSAforgotpasswordsuccess') {
						tb_show('','#TB_inline?height=170&width=364&inlineId=DSAForgotPasswordSuccess&modal=true');
						dsaReset("a.dialogOk").focus();
						dsaReset(".dialogMessage").html('Password has been Reset successfully');
					}

					if (jQSelector) {
						jQSelector.addClass("failedOnValidation");
					}
				}
			} 
		}
	};
}(jQuery));				