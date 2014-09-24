/**
 * @file
 * The JS file for Change Password page.
 *
 */
( function(dsachangepass){
  Drupal.behaviors.dsachangepass = {
    attach: function (context, settings){    
      dsachangepass(document).ready(function() {
        reset_form();
        dsachangepass("#change-pass-errormsg").hide();
        dsachangepass("#chgpass-success-msg").hide();
				var err = 0;	
				var emt = 0;	
				
        dsachangepass('#save-changepass').click(function(){
				
          dsachangepass("#change-pass-errormsg").html("");
					dsachangepass("#chgpass-success-msg").html("");
				
          var current_pwd = getIdValue("edit-current-password");
          var new_pwd = getIdValue("edit-new-password");
          var reenter_pwd = getIdValue("edit-confirm-new-password");
          
          var myarray = ["edit-current-password","edit-new-password","edit-confirm-new-password"];
            dsachangepass.each(myarray, function() {
               dsachangepass("#" + this).parent().parent().removeClass("errorfield");
              if(!isNotEmpty(getIdValue(this))) { 
								emt = 1;	
                dsachangepass("#" + this).parent().parent().addClass("errorfield");
								
								dsachangepass("#change-pass-errormsg").show();
								dsachangepass("#change-pass-errormsg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields highlighted in RED star.</span></div>');
								dsachangepass("#changepass_content").removeClass("margintop40");
								dsachangepass("#chgpass-success-msg").hide();	
								dsachangepass("#curr-pass-invalid").hide();			
								dsachangepass("curpass-newpass-invalid").hide();
								dsachangepass("#new-pass-invalid").hide();			              
              }
            });
						
            dsachangepass("#changepass_content").addClass("margintop40");
						
						if(isNotEmpty(current_pwd) && (!isValidPassword(current_pwd) || !checkAllowedLength(current_pwd,passwordMin,passwordMax))) {
							err = 1;
							dsachangepass("#curr-pass-invalid").show();
							dsachangepass("#edit-current-password").parent().parent().addClass("errorfield");							
						}
						else { 
							dsachangepass("#curr-pass-invalid").hide();
						}
						
						if(isNotEmpty(new_pwd) && (!isValidPassword(new_pwd) || !checkAllowedLength(new_pwd,passwordMin,passwordMax))) {
							err = 1;
							dsachangepass("#new-pass-invalid").show();
							dsachangepass("#edit-new-password").parent().parent().addClass("errorfield");
						}
						else {
							dsachangepass("#new-pass-invalid").hide();
						}
							
						if (isNotEmpty(current_pwd) && isNotEmpty(new_pwd) && isNotEmpty(reenter_pwd)) {
							emt = 0;
							if(new_pwd != reenter_pwd) {
								err = 1;
								dsachangepass("#newpass-repass-invalid").show();
								dsachangepass("#edit-new-password").parent().parent().addClass("errorfield");
								dsachangepass("#edit-confirm-new-password").parent().parent().addClass("errorfield");
							} else if(current_pwd == new_pwd) {
								err = 1;
								dsachangepass("#curpass-newpass-invalid").show();
								dsachangepass("#edit-current-password").parent().parent().addClass("errorfield");
								dsachangepass("#edit-new-password").parent().parent().addClass("errorfield");
								dsachangepass("#edit-confirm-new-password").parent().parent().addClass("errorfield");
							} else {
								err = 0;
								dsachangepass("#newpass-repass-invalid").hide();
								dsachangepass("#curpass-newpass-invalid").hide();
								
							}
						}
						//alert("err"+err);alert("emt"+ emt);
						if(err != 1 && emt != 1) { 			
							common_fun.is_valid_current_pwd(current_pwd, new_pwd);
							return true;						
						} else if (emt == 1) { 	
						
							dsachangepass("#change-pass-errormsg").show();
							dsachangepass("#change-pass-errormsg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
							dsachangepass("#changepass_content").removeClass("margintop40");
							return false;
							
						} else { 
							return false;
						}
					return false;    
        });
        
        dsachangepass("form input, form select").live("keypress", function (e) {
          if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) { 
            dsachangepass('#save-changepass').click();
          }
        });
       
        var common_fun = {
          is_valid_current_pwd:function(current_pwd, new_pwd) {
            dsachangepass.blockUI();
            dsachangepass.ajax({
              type: 'POST',
              url:'?q=validate_current_password',
              data:"status=checkPwd&current_pwd=" + current_pwd + "&new_pass=" + new_pwd ,
							async: false,
              success:function(data) {
								dsachangepass.unblockUI();
                if(data == 'Success'){
								
									dsachangepass("#chgpass-success-msg").html('<div class="acc-success-msg"><span class="success-img"></span><span class="font13bold float-left margintop12">Password successfully changed.</span></div>');
									dsachangepass("#changepass_content").removeClass("margintop40");
									dsachangepass("#chgpass-success-msg").show();
									dsachangepass("#change-pass-errormsg").hide();
									dsachangepass("#correct-curpass-invalid").hide();
								  reset_form();
                  return true;
                }else if (data == 'redirect_login') {
                  location.href = 'dsalogin';
                }else {
								  //Error.addError("Please enter correct Current Password","prepend");
									dsachangepass("#correct-curpass-invalid").show();
                  dsachangepass("#edit-current-password").parent().parent().addClass("errorfield");
                  return false;
                }
              }
            });
          },
					show_reset_popup:function(){
						tb_show('', '#TB_inline?height=170&width=364&inlineId=resetConfirmDialog&modal=true');
					},
					redirect_to_url:function(url){
						tb_remove();
						location.href = 'dsaChangePwd';
					}
        }				
				dsachangepass('#btnresetform').click(function(){
					common_fun.show_reset_popup();
				});
				dsachangepass('#yesbtn').live('click',function(){
					common_fun.redirect_to_url();
				});
			
      });
      
    }
  };
}(jQuery));  
