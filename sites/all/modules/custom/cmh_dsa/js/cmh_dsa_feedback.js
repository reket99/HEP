/**
 * @file
 * The JS file for Feedback page.
 *
 */
( function(dsafeedback){
  Drupal.behaviors.dsafeedback = {
	attach: function (context, settings){
		
				dsafeedback(document).ready(function() {
				
					reset_form();
					dsafeedback('#txtfeedback').maxlength({max: 200, target:'maxFdbckTxtField'});
					if(dsafeedback('a[rel*=facebox]').length > 0) {
							triggerFacebox(); //Initializes the Facebox plugin for anchor tags with rel as 'facebox'
					}
					//dsafeedback('#maxFdbckTxtField').next().removeClass("maxlength-feedback maxlength-full");
					//dsafeedback('#maxFdbckTxtField').next().addClass("maxlength-feedback").html('200 characters remaining (Max 200 Characters)');
				});
				
				dsafeedback("form input, form select, form textarea").live("keypress", function (e) {
					if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) { 
						dsafeedback('#feedback-submitbtn').click();
					}
				});

				var common={
					save_feedback:function(){
					
						//get all the values.
						var drpsubject = getIdValue('drpsubject');	
						var txtfeedback = getIdValue('txtfeedback');
						//var errArr = new Array(); 
						dsafeedback('#error-mesg').hide();
						dsafeedback('#error-mesg').html('');		
						
						//Validation for Category
						if(!isDrpDownNotEmpty(drpsubject)) {	
							var err = 1;
							dsafeedback('#formsubject').addClass("errorfield");
						}
						else {
							dsafeedback('#formsubject').removeClass("errorfield");
						}
						//Validation for feedback
						if(!isNotEmpty(txtfeedback)) { 
							var err = 1;
							dsafeedback('#formfeedback').addClass("errorfield");
						}
						else { 
							
							if(isValidFreeText(txtfeedback)) {  
								dsafeedback('#formfeedback').removeClass("errorfield");
							}
							else { 
								var err = 1;
								dsafeedback('#formfeedback').addClass("errorfield");
								//errArr.push('<li>Please enter valid feedback</li>');
								dsafeedback('#error-mesg').hide();
								dsafeedback('#feedback-invalid').show(); 
								
							} 
						}
						dsafeedback('#error-mesg').show();
						if(err == 1) {	
							dsafeedback("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
							dsafeedback(".success-msg").hide();						
									
						} else {
							dsafeedback('#feedback-form').submit();
						}
						return false;
					
					},
					
					show_reset_popup:function(){
						tb_show('', '#TB_inline?height=170&width=364&inlineId=resetConfirmDialog&modal=true');
					},
					
					redirect_to_url:function(url){
						tb_remove();
						location.href = 'feedback';
					}
				}
				
				dsafeedback('#feedback-submitbtn').click(function(){
					dsafeedback('.success-msg').hide();
					dsafeedback('#error-mesg').hide();
					common.save_feedback();
				});

				dsafeedback('#btnresetform').click(function(){
					common.show_reset_popup();
				});
				dsafeedback('#yesbtn').live('click',function(){
					common.redirect_to_url();
				});
		}
  };
}(jQuery));		

	var NOT_ALLOWED = '<script, <a, <input, <base, <object, <html, <div, <form, &gt;, &lt;, &gt, &lt, <frame, <iframe, <body, <meta, <head ';
