/**
 * @file
 * The JS file for MyAccount page.
 *
 */
( function(dsa_myaccount){
  Drupal.behaviors.dsa_myaccount = {
	attach: function (context, settings){
	
		dsa_myaccount(document).ready(function() {
			reset_form();
			dsa_myaccount("#error-mesg").hide();
			dsa_myaccount("#success-mesg").hide();

			dsa_myaccount('#save-myaccount').click(function(){
			
				dsa_myaccount("#error-mesg").html("");
				dsa_myaccount("#success-mesg").html("");
				
				var emailid = getIdValue("emailaddress");
				var phone1 = getIdValue("phone1");
				var phone2 = getIdValue("phone2");
				var err = 0;	
				var emt = 0;	
				
				var myarray = ["phone1","phone2","emailaddress"];
					dsa_myaccount.each(myarray, function() {
						
						dsa_myaccount("#" + this).parent().parent().removeClass("errorfield");
						if(!isNotEmpty(getIdValue(this)))	{
						
							emt = 1;
							dsa_myaccount("#" + this).parent().parent().addClass("errorfield");
							dsa_myaccount("#error-mesg").show();
							dsa_myaccount("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
							dsa_myaccount("#accountinfo_content").removeClass("margintop40");
							dsa_myaccount("#success-mesg").hide();
						}
					});
				
					dsa_myaccount("#accountinfo_content").addClass("margintop40");
					if (isNotEmpty(emailid) && !isValidEmailId(emailid)) {
						err = 1;
						dsa_myaccount("#email-invalid").show();
						dsa_myaccount("#emailaddress").parent().parent().addClass("errorfield");
					}
					else {
						dsa_myaccount("#email-invalid").hide();
					}
					if (phone1 != "" && (!isNumeric(phone1) || !checkAllowedLength(phone1,mobileMin,mobileMax))) {
						err = 1;
						dsa_myaccount("#phone1-invalid").show();
						dsa_myaccount("#phone1").parent().parent().addClass("errorfield");
					}
					else {
						dsa_myaccount("#phone1-invalid").hide();
					}
					if (phone2!="" && (!isNumeric(phone2) || !checkAllowedLength(phone2,mobileMin,mobileMax))) {
						err = 1;
						dsa_myaccount("#phone2-invalid").show();
						dsa_myaccount("#phone2").parent().parent().addClass("errorfield");
					}
					else {
						dsa_myaccount("#phone2-invalid").hide();
					}									
					if(err != 1 && emt != 1) { 
					
						common_functions.myaccount_submit();
						return true;						
					} else if (emt == 1) { 
					
						dsa_myaccount("#error-mesg").show();
						dsa_myaccount("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
						dsa_myaccount("#accountinfo_content").removeClass("margintop40");
						return false;
					} else {
						return false;
					}
			});
					
			dsa_myaccount("form input, form select, form textarea").live("keypress", function (e) {
        if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) { 
          dsa_myaccount('#save-myaccount').click();
        }
      });
				
			var common_functions = {
				myaccount_submit:function() {
				
					dsa_myaccount.blockUI();
					dsa_myaccount.ajax({
						type: 'POST',
						url:'?q=myaccount_submit',
						data: dsa_myaccount("#cmh-dsa-myaccount-form").serialize(),
						success:function(data) {
							dsa_myaccount.unblockUI();		
							dsa_myaccount("#success-mesg").html('');
							if(data == 'success') {
								
								dsa_myaccount("#success-mesg").html('<div class="acc-success-msg"><span class="success-img"></span><span class="font13bold float-left margintop12">Account Information has been saved successfully.</span></div>');
								dsa_myaccount("#accountinfo_content").removeClass("margintop40");
								dsa_myaccount("#success-mesg").show();
								dsa_myaccount("#error-mesg").hide();
								reset_form();
								return true;
							}else if (data == 'redirect_login') {
								location.href = 'dsalogin';
							}else {
								dsa_myaccount("#error-mesg").show();
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
					location.href = 'AccountInformation';
				}
			}
			dsa_myaccount('#btnresetform').click(function(){
					common_functions.show_reset_popup();
			});
			dsa_myaccount('#yesbtn').live('click',function(){
				common_functions.redirect_to_url();
			});
		});
	}
};
}(jQuery));