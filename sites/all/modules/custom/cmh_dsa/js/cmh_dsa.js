/**
 * @file
 * The JS file for DSA page.
 *
 */
( function(dsa){
  Drupal.behaviors.dsa = {
		attach: function (context, settings){
			//alert(Drupal.settings.CMHDSA.THEME_PATH);		
			dsa(document).ready(function() {
			
				dsa('.topBgNoBorder').hide(); 
				dsa('#edit-submit').click(function(){
					var err_string = '';
					dsa('#errorMsg').hide();
					dsa("#userId,#password").removeClass("errorfield");
					  if(dsa('#edit-user-id').val() == ''){
							err_string += '<li>Please Enter User ID.</li>';
							dsa("#userId").addClass("errorfield");
					  }
					  if(dsa('#edit-password').val() == ''){
							err_string += '<li>Please Enter Password.</li>';
							dsa("#password").addClass("errorfield");
					  }
					  if (err_string.length > 0 && err_string != '') {
							dsa('#errorMsg').html(err_string);
							dsa('#errorMsg').show();
							return false;
					  }
					  else {
							err_string = '';
							dsa('#errorMsg').hide();
							return true;
					  }
					  return true;
				});
				
				dsa("form input, form select").live("keypress", function (e) {
					if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) { 
						dsa('#edit-submit').click();
					}
				});
						
				dsa('#forgotPassCancel').live('click',function(){
					dsa(document).trigger('close.facebox');
				});
				
				dsa('#forgotPassSubmit').live('click',function(){
          var fgDSApwduserId = dsa(this).parents().find('.popup').children().find('#fgDSApwduserId').val();
					var fgpwdDSARegEmailid = dsa(this).parents().find('.popup').children().find('#fgpwdDSARegEmailid').val();
					var err_string = '';
					
          dsa(this).parents().find('.popup').children().find('#fgDSApwduserId').parent().removeClass("errorfield");
					dsa(this).parents().find('.popup').children().find('#fgpwdDSARegEmailid').parent().removeClass("errorfield");
					if(returnTrimmedValue(fgDSApwduserId) =='') {
							err_string += '<li>User ID: Please enter this information</li>';
							dsa(this).parents().find('.popup').children().find('#fgDSApwduserId').parent().addClass("errorfield");
					}
					if( returnTrimmedValue(fgpwdDSARegEmailid) =='') {
							err_string += '<li>Email ID: Please enter this information</li>';
							dsa(this).parents().find('.popup').children().find('#fgpwdDSARegEmailid').parent().addClass("errorfield");							
					}
					else if(!isValidEmailId(fgpwdDSARegEmailid)) {
							err_string += '<li>Please enter a valid Email ID</li>';
							dsa(this).parents().find('.popup').children().find('#fgpwdDSARegEmailid').parent().addClass("errorfield");
					}
					
					if (err_string.length > 0 && err_string != '') {
					 
              dsa(this).parents().find('.popup').children().find('#forgotErr ul').html(err_string);
              dsa(this).parents().find('.popup').children().find('#forgotErr').show();
							
          		return false;
					  }
					  else {
							err_string = '';
              dsa(this).parents().find('.popup').children().find('#forgotErr ul').html(err_string);
              dsa(this).parents().find('.popup').children().find('#forgotErr').hide();
              
							commonFun.forgotPassSubmit(fgDSApwduserId,fgpwdDSARegEmailid,dsa(this))
							return true;
					  }
				});
				
				var commonFun={
						//Ajax for forgot password
					forgotPassSubmit:function(fgDSApwduserId,fgpwdDSARegEmailid,submit_btn) {
						dsa.ajax({
							type: 'get',
							url:'?q=forgot_password' + "/" + fgDSApwduserId + "/" + fgpwdDSARegEmailid + "//////invalid",
							success:function(data) {
								if(data == 'valid') {
									dsa(document).trigger('close.facebox');
								}
								else if(data == 'invalid') {
									dsa("#ajaxfrgtpwd","#facebox").show();
									dsa("#ajaxfrgtpwdloading","#facebox").hide();
                  
                  submit_btn.parents().find('.popup').children().find('#forgotErr ul,"#facebox').append("<li>User ID or Email ID is invalid</li>");
                  submit_btn.parents().find('.popup').children().find('#forgotErr,"#facebox').show();
								}
								else if(data == 'invalid_mail') {
									dsa("#ajaxfrgtpwd","#facebox").show();
									dsa("#ajaxfrgtpwdloading","#facebox").hide();
                  
                  submit_btn.parents().find('.popup').children().find('#forgotErr ul').append("<li>Mail not sent. Please try again.!</li>");
                  submit_btn.parents().find('.popup').children().find('#forgotErr').show();
								}								
								dsa('.popup #ajaxfrgtpwdloading').hide();
							}
						});
					}	
				}
			});
			
		}
    };
}(jQuery));				

