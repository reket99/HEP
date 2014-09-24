/**
 * @file
 * The JS file for Common Functions.
 *
 */
( function(commonfns){
  Drupal.behaviors.commonfns = {
		attach: function (context, settings){
			// add active class for main menus when sub menu is selected
			commonfns('.left-nav li a.active-trail').parent().addClass('active');
			// remove <a> for look for and add white BG for the first tabs in sub menus
			commonfns('.look-for').html('Look for');
			if(Drupal.settings.CMHDSA.LOOKFOR == 'MemberDetails' || Drupal.settings.CMHDSA.LOOKFOR == 'AccountInformation' || Drupal.settings.CMHDSA.LOOKFOR == 'ExtraDegree'){
				commonfns('.look-for').addClass('bgWhite');
			}else{
				commonfns('.look-for').removeClass('bgWhite');
			}
		}
	}
}(jQuery));

jQuery(document).ready(function(){     
	jQuery('a').bind('focus blur',function(){jQuery(this).toggleClass('focusantab')});
	jQuery('input[type="radio"]').bind('focus blur',function(){jQuery(this).toggleClass('focusonradio')});
	jQuery('input[type="checkbox"]').bind('focus blur',function(){jQuery(this).toggleClass('focusonradio')});

	jQuery("body").live("click", function() {
	closeLoginPanel();
	});

	jQuery('#memberLogin').click(function(event){
		    event.stopPropagation();
	});
	jQuery('#demoLogin').click(function(event){
			event.stopPropagation();
	});

});

function reset_form(){
	var form_id = jQuery('form').attr('id');
	jQuery(':input[prepopulate!="yes"]','#' + form_id)
				.not(':button, :submit, :reset, :hidden')
				.val('')
				.removeAttr('checked')
				.removeAttr('selected');
}
	
function checkRedeemPoints(loginId, membershipId)
{
    var param =  "format=block&ContractId="+membershipId+"&memberId="+loginId;
    jQuery('.loadingImg').show();
    jQuery.ajax( {
	url : 'checkandAllowRedeem',
	data : param,
	success : function(data) {
	jQuery('.loadingImg').hide();
	//checkSession(data);
	if(data == 'false')
	{
		tb_show('','#TB_inline?height=170&width=450&inlineId=redeemErrDialog&modal=true');
		jQuery("a.dialogOk").focus();
		var errorMessage=LANG.redeem_error;
		errorMessage=errorMessage.replace(/HOUR/g,redeemHrs);
		jQuery(".dialogMessage").html(errorMessage);
	}	
	else
	{
		window.location.href = 'RedeemPoints.php'; 
	}	
	}});
		
}
function disableTab(){
	 if (jQuery(".loadingImg").is(":visible")) {
			jQuery(document).keydown(function(e) {
			    if (e.keyCode == 9) {  //tab pressed
			    	e.preventDefault(); // stops its action
			    }
			});
		  }
	}

function closeLoginPanel() {
	
	if(jQuery('.loadingLogin').length==0)
	  {
		if(jQuery("#memberLogin:visible"))
		{
			 jQuery('#memberLogin').slideUp("slow");

			 jQuery('#showMemberLoginNew').removeClass("active");	 
		}
		if(jQuery("#demoLogin:visible"))
	    {
		jQuery('#demoLogin').slideUp("slow");
	        jQuery('#showDemoLoginNew').removeClass("active");
			 
	    }
	  } 
}

function submitLoginform(form){
	jQuery("#memberLoginErr ul").html("");
	jQuery("#memberPwd").removeClass("errorField");
	jQuery("#memberUser").removeClass("errorField");
	var browserName=navigator.appName; 
    var member_id =  getIdValue('mluserId');	//document.forms[form].member_id.value;
	var password =  getIdValue('mlpassword');	//document.forms[form].password.value;
	var vercode='empty';
	var status=true;
	var err=0;
	
	if(!isNotEmpty(member_id) || member_id=='User/Email ID')
    {
		jQuery("#memberUser").addClass("errorField");
		err=1;
        status=false;
		if(document.forms[form].vercode)         //to reload the captcha block 
	    {
			document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
	    }
    }
	else
	{
		if(member_id.indexOf('@')>-1)
		{
			if(!isValidEmailId(member_id))
			{
				jQuery("#memberUser").addClass("errorField");
				jQuery("#memberLoginErr ul").append('<li>Please enter a valid Email ID</li>');
		        status=false;
				if(document.forms[form].vercode)         //to reload the captcha block 
				{
					document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
				}
			}
			else
				jQuery("#memberUser").removeClass("errorField");
		}
		else
		{
			if(!checkAllowedLength(member_id,loginMin,loginMax))
			{
				jQuery("#memberUser").addClass("errorField");
				jQuery("#memberLoginErr ul").append('<li>Please enter a valid User ID</li>');
		        status=false;
				if(document.forms[form].vercode)         //to reload the captcha block 
			    {
				 document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
			    }
			}
			else
				jQuery("#memberUser").removeClass("errorField");
		}
	}
	
	if(!isNotEmpty(password))
	{
		jQuery("#memberPwd").addClass("errorField");
		//jQuery("#memberLoginErr ul").append('<li>Password: Please enter this information</li>');
		err=1;
        status=false;
		if(document.forms[form].vercode)         //to reload the captcha block 
	    {
		 document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
	    }
		
	}
	else{
		jQuery("#memberPwd").removeClass("errorField");
	}
	
	if(captchaHideFlag == 0)
	{
		if(document.forms[form].vercode)           //don't change the condition
		{
			 vercode = jQuery("#vercode").val();
		     if(!isNotEmpty(vercode))
		     {
				jQuery("#memberCode").addClass("errorField");
		 		jQuery("#memberLoginErr ul").append('<li>Verification code: Please enter this information</li>');
		    	status=false;
				document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
				
		     }
			  else{
			 jQuery("#memberCode").removeClass("errorField");
			 }
		}
	}
	if(err==1)
	{
		jQuery("#memberLoginErr ul").append('<li>Please enter login details</li>');
	}
   if(status)
   {
		jQuery(".loadingImg").show();
		jQuery.ajax({
			url:HTTPS_URL+"Login.php",
			type: "POST",
			data:"login=Log-in&format=block&password="+password+"&member_id="+member_id+"&vercode="+vercode, 
			success: function(data){  
				//checkSession(data);
				if (data) 
				{
					window.location.href = data;					
				}
			}
		});	
   }
   else
   {
	   jQuery("#memberLoginErr").css("display","block");
   } 
}

function checkUser(userId){

return false;
}
//Facebook Login
function submitFbloginform(form){

	jQuery("#fbMemberLoginErr ul").html("");
	jQuery("#fbUserPwd").removeClass("errorField");
	jQuery("#fbUserLogin").removeClass("errorField");
	var browserName=navigator.appName; 
    var member_id =  getIdValue('fbmluserId');	//document.forms[form].member_id.value;
	var password =  getIdValue('fbmlpassword');	//document.forms[form].password.value;
	var vercode='empty';
	var status=true;
	  
   //alert(jQuery('#fbmluserId').val());
//alert(password);
	
	if(!isNotEmpty(member_id) || member_id=='User/Email ID')
    {
        //showAlertDialog(jQuery("#fbmluserId"),'<center>User Id  should  not be blank</center>');
		jQuery("#fbMemberLoginErr").css("display","block");
		jQuery("#fbUserLogin").addClass("errorField");
		jQuery("#fbMemberLoginErr").html('<ul><li>User ID: Please enter this information</li></ul>');
        status=false;
		if(document.forms[form].vercode)         //to reload the captcha block 
	    {
			document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
	    }
		return false;
     
    }
	else
	{
		if(member_id.indexOf('@')>-1)
		{
		
			if(!isValidEmailId(member_id))
			{
				
				jQuery("#fbMemberLoginErr").css("display","block");
				jQuery("#fbUserLogin").addClass("errorField");
				jQuery("#fbMemberLoginErr").html('<ul><li>Please enter a valid Email ID</li></ul>');
		        status=false;
				if(document.forms[form].vercode)         //to reload the captcha block 
				{
					document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
				}
				return false;
			}
			else
				jQuery("#fbUserLogin").removeClass("errorField");
		}
		else
		{
			if(!checkAllowedLength(member_id,loginMin,loginMax))
			{
				jQuery("#fbMemberLoginErr").css("display","block");
				jQuery("#fbUserLogin").addClass("errorField");
				jQuery("#fbMemberLoginErr").html('<ul><li>Please enter a valid User ID</li></ul>');
		        status=false;
				if(document.forms[form].vercode)         //to reload the captcha block 
			    {
				 document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
			    }
				return false;
			}
			else
				jQuery("#fbUserLogin").removeClass("errorField");
		}
	}
	
	if(!isNotEmpty(password))
	{
		//showAlertDialog(jQuery("#fbmlpassword"),'<center>password should  not be blank</center>');
		jQuery("#fbMemberLoginErr").css("display","block");
		jQuery("#fbUserPwd").addClass("errorField");
		jQuery("#fbMemberLoginErr").html('<ul><li>Password: Please enter this information</li></ul>');
        status=false;
		if(document.forms[form].vercode)         //to reload the captcha block 
	    {
		 document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
	    }
		return false;
	}
	else{
		jQuery("#fbUserPwd").removeClass("errorField");
	}
	
	if(captchaHideFlag == 0)
	{
		if(document.forms[form].vercode)           //don't change the condition
		{
				 vercode=  getIdValue("fbvercode");
			     if(!isNotEmpty(vercode))
			     {
			    	jQuery("#fbMemberLoginErr").css("display","block");
					jQuery("#fbMemberCode").addClass("errorField");
			 		jQuery("#fbMemberLoginErr").html('<ul><li>Verification code: Please enter this information</li></ul>');
			    	status=false;
					document.getElementById('captchamembercode').src='captcha.php?rand='+Math.random();
					return false;
			     }
				  else{
				 jQuery("#fbMemberCode").removeClass("errorField");
				 }
		}
	}
	
       if(status)
    	{
			jQuery(".loadingImg").css("display", "block");
			jQuery.ajax({
			url:HTTPS_URL+"Welcome.php",
			type: "POST",
			data:"login=Log-in&format=block&password="+password+"&member_id="+member_id+"&vercode="+vercode, 
			success: function(data){  
			//checkSession(data);
				if (data) 
				{
					window.location.href = data;
				}
			}
			});	
    	}
	
}




function submitDemoLoginform(form){
	jQuery("#demoLoginErr ul").html("");
	jQuery("#demoUser").removeClass("errorField");
	jQuery("#demoPwd").removeClass("errorField");
	var browserName=navigator.appName; 
    var loginid =  getIdValue('dluserId');
	var password =  getIdValue('dlpassword');
	var vercode='empty';
	var status=true;
	var err=0;
  
	if(!isNotEmpty(loginid))
    {
	  jQuery("#demoUser").addClass("errorField");
	  err=1;
      status=false;
	  	if(document.forms[form].dlvercode)         //to reload the captcha block 
	    {
		 document.getElementById('captchademocode').src='captcha.php?rand='+Math.random();
	    }
    }
	else
	{
		if(!isValidEmailId(loginid))
		{
			jQuery("#demoUser").addClass("errorField");
			jQuery("#demoLoginErr ul").append('<li>Please enter a valid User ID</li>');
	        status=false;
			if(document.forms[form].dlvercode)         //to reload the captcha block 
			{
			 document.getElementById('captchademocode').src='captcha.php?rand='+Math.random();
			}
		}
		else
			jQuery("#demoUser").removeClass("errorField");
	}
	
	if(!isNotEmpty(password))
	{
		jQuery("#demoPwd").addClass("errorField");
	    status=false;
	    err=1;
		if(document.forms[form].dlvercode)         //to reload the captcha block 
		{
		 document.getElementById('captchademocode').src='captcha.php?rand='+Math.random();
		}
	}
	else
		jQuery("#demoPwd").removeClass("errorField");
	
	
	if(captchaHideFlag == 0)
	{
		if(document.forms[form].dlvercode)           //don't change the condition
		{
			 vercode = jQuery("#dlvercode").val();
		     if(!isNotEmpty(vercode))
		     {
				jQuery("#demomemberCode").addClass("errorField");
		   	  	jQuery("#demoLoginErr ul").append('<li>Verification code: Please enter this information</li>');
				status=false;
				document.getElementById('captchademocode').src='captcha.php?rand='+Math.random();
		     } 
			 else
			 {
				 jQuery("#demomemberCode").removeClass("errorField");
			 }
		}
	}
	if(err==1)
	{
		jQuery("#demoLoginErr ul").append('<li>Please enter login details</li>');
	}
    if(status)
	{
		jQuery("#demoajaxLogin").html(LOGINPROCESSSING);
		jQuery.ajax({
			url:HTTPS_URL+"DemoLogin.php",
			type: "POST",
			data:"format=block"+"&password="+password+"&userid="+loginid+"&vercode="+vercode, 
			success: function(data){  
				//checkSession(data);
				if (data) 
				{
					window.location.href = data;   
				}
			}
		});
	}
    else
    {
    	jQuery("#demoLoginErr").css("display","block");
    }
}

jQuery(function() {
	function closeFacebox() {		
		jQuery(document).trigger('close.facebox');	
	}
	function addActiveGuideItem() {
		var context = ".guideDesc ul";
		jQuery("li", context).click(function() {
			jQuery("li", context).removeClass("activeGuideItem");
			jQuery(this).addClass("activeGuideItem");
		});
		
	}
	
	function addSelectedAttractionPlace() {
		var context = ".attractionView";
		jQuery("div.section", context).click(function() {
			jQuery("div.section", context).removeClass("selectedAttraction");
			jQuery(this).addClass("selectedAttraction");
		});
		
	}
	
	function toggleResortRoute() {
	
		jQuery(".accordian_down", ".enrouteExperience").click(function(){
		
			if(jQuery(this).hasClass("accordian_down")){
			       jQuery(this).addClass("accordian_up").removeClass("accordian_down");
			       jQuery("#connectingMaps").slideDown("slow", function(){
			       jQuery("#connectingMaps").hide();    
			       });
				   
				   
			   } else {
			       jQuery(this).addClass("accordian_down").removeClass("accordian_up");
			       jQuery("#connectingMaps").slideUp("slow", function(){
			       jQuery("#connectingMaps").show();    
			       
			       });
		       }
		});
	}
	function addContentScroller() {
		if(typeof PAGEID != "undefined" && PAGEID != "CommunitySpace")
		{
			var scrollContentObj = jQuery(".customScrollBar");
			if(scrollContentObj.length > 0) {
				scrollContentObj.jScrollPane({
					    showArrows: true,
					    verticalDragMinHeight: 82,
					    verticalDragMaxHeight: 82
					    
					    
					    });
			}
		}
	}
	

	shareThis(); //Opens the 'Share This' Layer if 'Share' button is clicked
	 function attachDropdownMask() {
	    // if(jQuery("select.drpdown").length>0){
	        // jQuery("select.drpdown").selectBox();
	    // }
	 }
	
	function showComingSoonMessage() {
		jQuery(document.body).append(jQuery("#comingSoonLayer"));
		var comingSoonLayer = jQuery("#comingSoonLayer");
		jQuery(".comingSoon").hover(function() {
			var menuUnderContr = jQuery(this);
			if(!menuUnderContr.is(":animated")) {
				var leftDistance = menuUnderContr.offset().left;
				var righttDistance = menuUnderContr.offset().left - menuUnderContr.outerWidth();
				var layerTopOffset = menuUnderContr.offset().top + menuUnderContr.outerHeight();
				layerTopOffset = layerTopOffset;
				var bubblePosUp= menuUnderContr.hasClass('down');
				var spaceForBubble= menuUnderContr.hasClass('space');
				jQuery("#comingSoonLayer").css({
					top: (layerTopOffset - (bubblePosUp ? 70 : 5)) + "px",
					left: leftDistance + "px"
				});
				
				
				if(spaceForBubble){
					jQuery("#comingSoonLayer").css({					
						left:( righttDistance + 35) + "px" 
					});
					jQuery(".up").css({									
						left: 102 + "px"					
					});
				}
				if(bubblePosUp){
					
					
					jQuery(".down","#comingSoonLayer").show();
				}
				else{
					jQuery(".up","#comingSoonLayer").show();

				}				
				
				jQuery("#comingSoonLayer").show("fast");
			}
		}, function(){
			jQuery("#comingSoonLayer").fadeOut();
			jQuery(".up,.down","#comingSoonLayer").hide();
		});
	}
	function onEnterSubmitForm(){
		jQuery("form input, form select").live("keypress", function (e) {
			if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
				var formName=jQuery(this).parents("form").attr("name");
				if(jQuery(this).parents("form").attr("name") == "frmDemoLogin"){
					jQuery(this).parents("form").find(".submitOnEnterDemo").click();
					
				}else if(jQuery(this).parents("form").attr("name") == "loginForm"){
					jQuery(this).parents("form").find(".submitOnEnterMember").click();
				}
				else if(jQuery(this).parents("form").attr("name") == "DsaLoginFrm"){
					jQuery(this).parents("form").find("#login").click();
				}
				else if(formName == "frmforgotPassword" || formName == "frmregistration"){
						jQuery("#facebox a.submitFB").click();
				}
				else if(jQuery(this).parents("form").attr("name") == "frmforgotUserId"){
					jQuery("#facebox a.feedbackSubmit").click();
				}
				return false;
			}
			else {
				return true;
			}
		});
	}
	
	jQuery(".submitOnEnterDemo").click(function(){
		submitDemoLoginform('frmDemoLogin');
	});
	
	jQuery(".submitOnEnterMember").click(function(){
		submitLoginform('loginForm');
	});
	jQuery(".submitOnFacebookMember").click(function(){
		submitFbloginform('formLgin');
	});
	function initInputTypeButtons(){
		jQuery(":input[type=button], .dialogOk, .dialogCancel").focus(function(e){
			if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
				jQuery(this).trigger("click");
			}
		});
		jQuery(":input[type=button], .dialogOk, .dialogCancel").keypress(function(e){
			if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
				jQuery(this).trigger("click");
			}
		});
	}
	jQuery(".hasSubmenu").click(function(e){
		jQuery(this).parent().find(".subMenuList").slideToggle(300);
		jQuery(this).toggleClass("active");
	});
	
	toggleResortRoute(); //toggle resorts route in enroute experience
	addContentScroller(); //adds custom scrollbar
	addActiveGuideItem(); //adds active number to guides description div
	addSelectedAttractionPlace(); // adds active number to selected attraction
	attachDropdownMask(); //Attached different mask to HTML dropdown
	showComingSoonMessage();
	onEnterSubmitForm();
	initInputTypeButtons();
});

//--------------------------------Functions in global scopes--------------------------------//
function setCustomRange(sourceTarget, destTarget, selectable){
	var dates = getDateRange(sourceTarget);
	if(dates != null && dates != "" && dates != undefined){
		selectedRange = dates;
	}
	destroyCustomDatePicker(destTarget);
	
	initiateCalendarControl(selectedRange, memberSeason, resortID, destTarget, selectable);
}
function getCustomRange(sourceTarget, destTarget, selectable){
	var dates = getDateRange(sourceTarget);
	return dates;
}
/* initiateCalendarControl: To initiate the control
 * args:
 * selectedRange:string - From and To date in format - "09/23/2011 - 09/27/2011"
 * memberSeason:string - 'blue','purple','red'
 * resortID:string
 * target:string - ID or class of element in DOM with (.) or (#) (E.g. #elemID)
 * isSelectable:boolean - true/false, by default it is true.
 **/

function initiateCalendarControl(selectedRange, memberSeason, resortID, target, isSelectable){		
	var rangeObj = getFormattedDate(selectedRange);
	if(isSelectable == 'undefined'){
		isSelectable = true;
	}
	jQuery(target).datepickCustom({
		dateFormat: "dd/mm/yyyy",
		isSelectable:isSelectable, memberSeason:memberSeason, selectedStartDate:rangeObj.startDate, selectedEndDate:rangeObj.endDate, resortID:resortID, rangeSelect: true, minDate: new Date(), maxDate: '+6m' , monthsToShow: 1
	});
}
function initiateCalendarControlrange(selectedRange, memberSeason, resortID, target, isSelectable, range){		
	var rangeObj = getFormattedDate(selectedRange);
	if(isSelectable == 'undefined'){
		isSelectable = true;
	}
	jQuery(target).datepickCustom({
		dateFormat: "dd/mm/yyyy",
		isSelectable:isSelectable, memberSeason:memberSeason, selectedStartDate:rangeObj.startDate, selectedEndDate:rangeObj.endDate, resortID:resortID, rangeSelect: true, minDate: new Date(), maxDate: '+'+range+'d' , monthsToShow: 1
	});
}
function destroyCustomDatePicker(target){
	jQuery(target).datepick('destroy');
}
function getDateRange(target){
	var dates = jQuery(target).datepick('getDate');
	var val = '';
	var selectedRange='';
	if(dates != null && dates!= ""){
		for (var i = 0; i < dates.length; i++) { 
			val += (i == 0 ? '' : '-') + jQuery.datepick.formatDate("dd/mm/yyyy",dates[i]);
			selectedRange = val;
		} 
	}
	return selectedRange;
}
function dayHeaderClick(index){
	jQuery(".wk-custom td:eq("+index+") a").trigger("click");
}


function initInputFaceBox(gStr, target){
	target.addClass("colorLight");
	if(pageId != 'DsaRegister')
		target.addClass("inputheight");
	
	target.focus(function(){
	    if(this.value == gStr){
		this.value = "";
		target.removeClass("colorLight");
	    }
	});
	target.blur(function(){
	    if(this.value == ""){
	    	target.addClass("colorLight");
		this.value = gStr;
	    }
	});
	target.click(function(){
	    if(this.value == gStr){
		this.value = "";
		target.removeClass("colorLight");
	    }
	});
}

function initInputBox(gStr, target){

	var pageId = 'DsaRegister';
	jQuery(target).addClass("colorLight");
	if(pageId != 'DsaRegister')
		jQuery(target).addClass("inputheight");
	
	jQuery(target).focus(function(){ 
		if(this.value == gStr){
			this.value = "";
			jQuery(target).removeClass("colorLight");
		}
	});
	jQuery(target).blur(function(){
		if(this.value == ""){
			jQuery(target).addClass("colorLight");
			this.value = gStr;
		}
	});
	jQuery(target).click(function(){
		if(this.value == gStr){
			this.value = "";
			jQuery(target).removeClass("colorLight");
		}
	});
}
function forceInitInput(gStr, target){
	jQuery(target).addClass("colorLight");
	jQuery(target).addClass("inputheight");
	jQuery(target).val(gStr);
}
function copyFields(element){

    var emailVal =jQuery(element).val();
     jQuery(".inputDemoUserId").val(emailVal);
	 //checks that the user already registered with the same Id.
	 emailVal = jQuery.trim(emailVal);
	 if(emailVal!='')
	 {
	 jQuery.ajax({
		url:HTTPS_URL+"Signup.php",
		type: "POST",
		data:"checkUserId="+emailVal+"&format=block", 
		success: function(data){  
		//checkSession(data);
			if(data=='Success')
			{
				jQuery('.demoFailureMes').show();
				jQuery('.demoFailureMes').html('<ul><li>You have already registered</li></ul>');
				jQuery("#enabledDemoSubmit","#facebox").css("display","none");
				jQuery("#disabledDemoSubmit","#facebox").css("display","block");
			}
			else
			{
				jQuery('.demoFailureMes').hide();
				jQuery('.demoFailureMes').html('');
				jQuery("#enabledDemoSubmit","#facebox").css("display","block");
				jQuery("#disabledDemoSubmit","#facebox").css("display","none");
			}

		}
		});
	}
	else
	{
		
		jQuery('.demoFailureMes').html('');
	}
		

}
function checkUser(emailVal)
{
	emailVal = jQuery.trim(emailVal);
	if(emailVal!='')
	{ 
	 jQuery.ajax({
		url:HTTPS_URL+"Signup.php",
		type: "POST",
		data:"checkUserId="+emailVal+"&format=block", 
		success: function(data){  
		//checkSession(data);
			if(data=='Success')
			{
				jQuery('.signfailerMsg').show();
				jQuery('.signfailerMsg').html('<ul><li>The User is already registered</li></ul>');
				jQuery("#enabledSubmit","#facebox").css("display","none");
				jQuery("#disabledSubmit","#facebox").css("display","block");
			}
			else
			{
				jQuery('.signfailerMsg').hide();
				jQuery('.signfailerMsg').html('');
				jQuery("#enabledSubmit","#facebox").css("display","block");
				jQuery("#disabledSubmit","#facebox").css("display","none");
			}

		}
		});
	}
	else
	{
		
		jQuery('.signfailerMsg').html('');
	}
}


function shareThis(target, context) {
	if(!target || target == ""){
		target = "#shareThis";
	}
	if(!context || context == ""){
		context = "";
	}
	jQuery(target).click(function(e) {		
		var topOffSet = jQuery(this).parents('.dwnLayerContainer', context).css('top');
		var leftOffSet = jQuery(this).parents('.dwnLayerContainer').position().left;
		var menuHeight = jQuery("#shareThisMenu").outerHeight();
		if(jQuery(this).hasClass("shareThisCommon")) {
			topOffSet = jQuery(this).parents('.dwnLayerContainer').position().top - menuHeight;
			leftOffSet = leftOffSet + 20;
		} else {
			topOffSet = parseInt(topOffSet.replace(/px/, '')) -  menuHeight + 8;
			leftOffSet = leftOffSet +  (jQuery(this).hasClass("shareFromPopup") ? 7: 106);	
		}
		jQuery("#shareThisMenu").css({
			top:  topOffSet + 'px',
			left:   leftOffSet + 'px'
		}).show();
		e.stopPropagation();
	});
	
	jQuery(document).click(function(e) {
		var shareThisMenu = jQuery("#shareThisMenu");
		if(shareThisMenu.is(":visible")) {	    
			shareThisMenu.fadeOut("slow");
		}
	});
}
function multiShareThis(target, menuTarget, context) {
	var shareThisMenu = jQuery(menuTarget);
	jQuery(target).click(function(e) {
		var topOffSet = jQuery(this).parents('.dwnLayerContainer', context).css('top');
		var leftOffSet = jQuery(this).parents('.dwnLayerContainer', context).css('right');
		var menuHeight = jQuery(shareThisMenu).outerHeight();
		topOffSet = parseInt(topOffSet.replace(/px/, '')) -  menuHeight + 8;
		leftOffSet = parseInt(leftOffSet.replace(/px/, '')) + 12;	
		jQuery(shareThisMenu).css({
			top:  topOffSet + 'px',
			right:   leftOffSet + 'px'
		}).fadeToggle("slow");
		e.stopPropagation();
	});
	
	jQuery(document).click(function(e) {
		if(shareThisMenu.is(":visible")) {	    
			shareThisMenu.fadeOut("slow");
		}
	});
}
/* Formats the Date Range in mm/dd/yyyy format
 * args: dt format e.g. "08/12/2011"
*/
function getFormattedDate(dtRange) {
	var startDate = dtRange.split("-")[0];
	  var endDate = dtRange.split("-")[1];
	
	function formatDateExpect(dt) {
		var strDateArr = dt.split("/");
		var d = strDateArr[0];
		var m = strDateArr[1];
		var y = strDateArr[2];
		var newdate = m+"/"+d+"/"+y;
		newdate = newdate.replace(' ','');
		return newdate;
	}
	return {
		"startDate" : formatDateExpect(startDate),
		"endDate" : formatDateExpect(endDate)
	}
}
jQuery(document).ready(function(){
	var tabIndex = 1;
	jQuery(document).ready(function(){
	    var inputBoxSet = jQuery("select");
	    if(inputBoxSet.length > -1){
		jQuery.each(inputBoxSet, function(key, val){
		    jQuery(inputBoxSet[key]).attr("tabindex", -1);
		});
	    }
	});	
});

//this is used for reset option
	function callToDialog(ajaxURL,pageID, divID, buttonID, statusParam, buttonFocused)
           {
				jQuery(buttonID).click(function() {
					jQuery.ajax({ 
						url : ajaxURL,
						async: false,
						type : "GET",
						data : "format=block&pageId="+pageID+"&status="+statusParam,
						success : function(data) {
						//checkSession(data);
								jQuery("#ajaxResult").html(data);
								tb_show('', '#TB_inline?height=170&width=364&inlineId='+divID+'&modal=true');
								//Added below line to make the Yes button as focused when popup comes.
								jQuery(buttonFocused).focus();
							}
					});
				});
			}
			
	//this function is used in the add wishlist page
	function callToWishDelete(ajaxURL,wishId, divID, buttonID, statusParam, buttonFocused)
           {
				jQuery(buttonID).click(function() {
					jQuery.ajax({ 
						url : ajaxURL,
						async: false,
						type : "GET",
						data : "format=block&wishId="+wishId+"&status="+statusParam,
						success : function(data) {
						//checkSession(data);
						jQuery(".diagPopupBox").html('');
								jQuery("#ajaxResult").html(data);
								tb_show('', '#TB_inline?height=170&width=364&inlineId='+divID+'&modal=true');
								//Added below line to make the Yes button as focused when popup comes.
								jQuery(buttonFocused).focus();
							}
					});
				});
			}
	
	// this function is used for the back to my wishList button in the wishlist page
	function callBackToWish(ajaxURL,wishId, divID, buttonID, statusParam, buttonFocused)
           {
				jQuery('#backToWish').click(function() {
					jQuery.ajax({ 
						url : ajaxURL,
						async: false,
						type : "GET",
						data : "format=block&wishId="+wishId+"&status="+statusParam,
						success : function(data) {
						//checkSession(data);
								jQuery("#ajaxResult").html(data);
								tb_show('', '#TB_inline?height=170&width=364&inlineId='+divID+'&modal=true');
								//Added below line to make the Yes button as focused when popup comes.
								jQuery(buttonFocused).focus();
							}
					});
				});
			}
	function callToWishDialog()
           {	
					jQuery.ajax({ 
						url : GajaxURL,
						async: false,
						type : "GET",
						data : "format=block&wishId="+GWishId+"&status="+GstatusParam,
						success : function(data) {
						//checkSession(data);
						//Below line is added to restrict calling the function calltoWishDialog twice
					
								jQuery("#ajaxResult").html(data);
								tb_show('', '#TB_inline?height=170&width=364&inlineId='+GdivID+'&modal=true');
								//Added below line to make the Yes button as focused when popup comes.
								jQuery(GbuttonFocused).focus();
							}
					});
			
				
				}
	
	function sendToPrinter(){		
		
			var clickedSrc ="includes/"+SITETHEME+"images/clicked_print.png";
			var printSrc = "includes/"+SITETHEME+"images/print.png";
			jQuery('.printThis').find("img").attr('src', clickedSrc);
			setTimeout(function() {				
				jQuery(".printThis").find("img").attr('src', printSrc);
			      }, 500);
			
			window.print();
			
		
	}
	
	function sendCVToPrinter(cvnumber)
	{
		var voucherNum=cvnumber;
		var form = document.createElement('form');
		form.setAttribute('action', 'PrintCV.php');
		form.setAttribute('method', 'POST');
		form.setAttribute('target', '_new');
	    var input = jQuery('<input name="cvumber" type="hidden" value="' + voucherNum + '"/>');
	    form.appendChild(input[0]);
		document.body.appendChild(form);
		form.submit();
	}
	
	if(jQuery('a[rel*=facebox]').length > 0) {
	    triggerFacebox(); //Initializes the Facebox plugin for anchor tags with rel as 'facebox'
	}
	
	//Inorder to avoid loding facebox popup multiple times
	//Remove the content befor loading
	jQuery(document).bind('beforeReveal.facebox', function() {
	  jQuery("#facebox .content").empty();
	});
	
	//on enter key, focus sent to the textarea
	jQuery(document).bind('keydown.ajaxReview,keydown.postAReview', function(e) {
	    if(e.keyCode == 13)
	    	setTimeout('jQuery("#facebox textarea").focus()',1000);
	});
	// function checkSession(data)
	// {
		
		// var redirect=false;
		
		// if(data == 'sessionTimeout' || data == '"sessionTimeout"')
		// {	
			// redirect=true;
		// }
		// if(redirect)
		// {
			// location.reload();
		// }	
			
	// }
	
	//To check the session before ajax call
	// jQuery( document ).ajaxSend(function( event, jqxhr, settings ) {
		// if ( settings.url != "checkUserSession/ajax" ) {
			 // checkSession();
		// }
	// });
	
	//To check the session after ajax call
	jQuery( document ).ajaxComplete(function( event, jqxhr, settings ) {
		var in_arr_flag = [];
		
		jQuery.each(Drupal.settings.CMHDSA.AJAX_URL_ARR, function( index, value ) {
			//console.log('value = ' + value);
			//console.log('settings.url = ' + settings.url);
			patt1=new RegExp(value);
			//str = '/' + value + '/gi';  
			//console.log('== = ' + patt1.test(settings.url));
			if ( patt1.test(settings.url)) {
				in_arr_flag[index] = '1';//found in array
			}
			else {
				in_arr_flag[index] = '0';//not found in array
			}
			
		});
		// console.log(in_arr_flag);
		// console.log('tt' + jQuery.inArray( "1", in_arr_flag));
		//alert('tt' + jQuery.inArray( "1", in_arr_flag));
		if (jQuery.inArray( "1", in_arr_flag) > -1)  {
			return false;
		}
		else {
			checkSession();
		}
	});
	
	//To check the session ajax call
	function checkSession() {
		var flag;
		jQuery.ajax({
			url:"?q=checkUserSession/ajax",
			type:"POST",
			async: false,
			success: function(data){
				if (data == 'FALSE' || data == false) {
					flag = false;	
				}
				else {
					flag = true;
				}
			}
		});
		//if false then reload the page
		if (flag == 'FALSE' || flag == false) { 
			location.reload();
			return false;	
		}
		else {
			return true;
		}
	}
	
	//Flash News ticker in Index and Member dashboard page 
	function initNewsTicker(){
	    jQuery("#ticker").newsticker();
	}
	
	
		
function Pager(tableName, itemsPerPage) {
    this.tableName = tableName;
    this.itemsPerPage = itemsPerPage;
    this.currentPage = 1;
	this.bottomCurrentPage = 1;
    this.pages = 0;
    this.inited = false;
   
    this.showRecords = function(from, to) {       
        var rows = document.getElementById(tableName).rows;
        // i starts from 1 to skip table header row
        for (var i = 1; i < rows.length-1; i++) {
            if (i < from || i > to) 
                rows[i].style.display = 'none';
            else
                rows[i].style.display = '';
        }
    }
   
    this.showPage = function(pageNumber) {
     if (! this.inited) {
      alert("not inited");
      return;
     }
		var oldPageAnchor = document.getElementById('pg'+this.currentPage);
        oldPageAnchor.className = 'pg-normaltext';  
	    var bottomOldPageAnchor = document.getElementById('bottom_pg'+this.bottomCurrentPage);
        bottomOldPageAnchor.className = 'pg-normaltext';       
        this.currentPage = this.bottomCurrentPage = pageNumber;
        
        var newPageAnchor = document.getElementById('pg'+this.currentPage);
        newPageAnchor.className = 'pg-selected';
		var prevIcon = document.getElementById('prev');
       	var nextIcon = document.getElementById('next');
		
		if(this.currentPage == this.pages) {			
			nextIcon.style.display="none";
		}else {
			nextIcon.style.display="inline";
		}
		if(this.currentPage > 1) {
			prevIcon.style.display="inline";
		}else if(this.currentPage == 1) {
			prevIcon.style.display="none";
		}
		
        var bottomNewPageAnchor = document.getElementById('bottom_pg'+this.bottomCurrentPage);
        bottomNewPageAnchor.className = 'pg-selected';
		var botomPrevIcon = document.getElementById('bottom_prev');
       	var bottomNextIcon = document.getElementById('bottom_next');
		if(this.bottomCurrentPage == this.pages) {			
			bottomNextIcon.style.display="none";
		}else {
			bottomNextIcon.style.display="inline";
		}
		if(this.bottomCurrentPage > 1) {
			botomPrevIcon.style.display="inline";
		}else if(this.bottomCurrentPage == 1) {
			botomPrevIcon.style.display="none";
		}
		
        var from = (pageNumber - 1) * itemsPerPage + 1;
        var to = from + itemsPerPage - 1;
        this.showRecords(from, to);
		
    }  

   
    this.prev = function() {
        if (this.currentPage > 1)
            this.showPage(this.currentPage - 1);			
    }
   
    this.next = function() {		
        if (this.currentPage < this.pages) {
            this.showPage(this.currentPage + 1);			
        }
    }                       
   
    this.init = function() {
        var rows = document.getElementById(tableName).rows;			
        var records = (rows.length - 2);		
        this.pages = Math.ceil(records / itemsPerPage);		
        this.inited = true;
    }

    this.showPageNav = function(pagerName, positionId) {
     if (! this.inited) {
      alert("not inited");
      return;
     }
     var element = document.getElementById(positionId);
     var pagerHtml = "";
     var pagerHtml = '<a id="prev" href="javascript:void(0);" onclick="' + pagerName + '.prev();" class="pg-normal" title="Previous" style="display:none;"> Prev <</a>  ';
        for (var page = 1; page <= this.pages; page++)
            pagerHtml += '<a href="javascript:void(0);" id="pg' + page + '" class="pg-normaltext" onclick="' + pagerName + '.showPage(' + page + ');">' + page + '</a>  ';		
	    	pagerHtml += '<a id="next"  href="javascript:void(0);" onclick="'+pagerName+'.next();" class="pg-normal" title="Next" style="display:none;"> > Next </a>';           
        element.innerHTML = pagerHtml;
    }
	
	this.showPageNavBottom = function(pagerName, positionId) {
     if (! this.inited) {
      alert("not inited");
      return;
     }
     var element = document.getElementById(positionId);
     var pagerHtml = "";
     var pagerHtml = '<a id="bottom_prev" href="javascript:void(0);" onclick="' + pagerName + '.prev();" class="pg-normal" title="Previous" style="display:none;"> Prev <</a>  ';
        for (var page = 1; page <= this.pages; page++)
            pagerHtml += '<a href="javascript:void(0);" id="bottom_pg' + page + '" class="pg-normaltext" onclick="' + pagerName + '.showPage(' + page + ');">' + page + '</a>  ';		
		
	    	pagerHtml += '<a id="bottom_next"  href="javascript:void(0);" onclick="'+pagerName+'.next();" class="pg-normal" title="Next" style="display:none;"> > Next </a>';           
        element.innerHTML = pagerHtml;
    }
}
		
function showBookMsg(siteid,prsntravelling)
{
	var errorMessage='';
	if(prsntravelling=='4753')
		{
		errorMessage='We regret to inform you that we cannot process editing  holiday reservation for employee at the moment! Kindly contact the member relations center @ 39880000*';
		}
	if(siteid=='31')
		{
		errorMessage='We regret to inform you that we cannot process editing  holiday reservation for Kuala Lumpur at the moment! Kindly contact the member relations center @ 39880000*';
		}
	
	tb_show('', '#TB_inline?height=200&width=340&inlineId=errResponseDialog&modal=true');
    jQuery(".dialogMessage").html(errorMessage);                
	return false;
	
}

function trim(stringToTrim) {
	return stringToTrim.replace(/^\s+|\s+$/g, "");
}