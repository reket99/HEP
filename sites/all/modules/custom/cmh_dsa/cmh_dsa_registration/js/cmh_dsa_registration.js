/**
 * @file
 * The JS file for Registration page.
 *
 */
var radDom ='domestic';
( function(dsa){
  Drupal.behaviors.dsa = {
	attach: function (context, settings){
		
			dsa(document).ready(function() {
				reset_form();
			});
			
			dsa("form input, form select").live("keypress", function (e) {
				if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) { 
					dsa('#register').click();
				}
			});
				
			var other={"other":{"0":"--Please Select--","Other":"Other"}};
			var exp = 'No';
			dsa("#edit-priorexperience").removeClass('expradio');
			
			dsa(".expradio").click(function(){ 
				exp = dsa(this).val();
				if(exp == 'Yes'){
					dsa("#expYrs").show();
				}else{
					dsa("#expYrs").hide();
				}
			});
			
					
			var address = "international";
			dsa("#rdModeOfenquiries").removeClass('domesticIntrRadioBtn');
			dsa(".domesticIntrRadioBtn").click(function(){
						
				//clearing all the values
				dsa("#txtMailAddress").val('');	
				dsa("#txtEmailId").val('');	
				dsa("#txtMobile").val('');
				
				var gCountryCode="Country Code";
				var gAreaCode="State Code";
				var gTelephone="Telephone";		
				dsa('#txtMailAddress').maxlength({max: 200, target:'checkAddressLimit'});
				initInputBox(gCountryCode, ".inputCountryCodeRes");
				initInputBox(gAreaCode, ".inputAreaCodeRes");
				initInputBox(gTelephone, ".inputTelephoneRes");
				initInputBox(gOtherState, ".inputOtherState");
				initInputBox(gOtherCity, ".inputOtherCity");		
				
				dsa("#txtCountryCodeRes").val('');
				dsa("#txtCountryCodeRes").val(gCountryCode);
				dsa("#txtAreaCodeRes").val('');
				dsa("#txtAreaCodeRes").val(gAreaCode);
				dsa("#txtTelephoneRes").val('');
				dsa("#txtTelephoneRes").val(gTelephone);
				
				dsa('#drpResAddrState').val('0');
				dsa('#drpResAddrCity').val('0');
				dsa("#drpResAddrCity").attr("disabled","disabled");
				
				dsa("#txtOtherState").val('');
				dsa("#txtOtherCity").val('');
				dsa("#otherState").hide();
				dsa("#otherCity").hide();
				address = dsa(this).val();
	
				if(address=='international'){
					dsa("#txtOtherCountry").val('');
				  dsa("#otherCountry").hide(); 
					dsa("#country").show();
					dsa('#drpResAddrCountry').val('0');
					dsa("#drpResAddrState").attr("disabled","disabled");
				}
				else
				{
				
					dsa("#country").hide();	
					Common.getShowData('country','1','state','drpResAddrState','loadState');
					dsa("#drpResAddrState").removeAttr('disabled');
					dsa("#otherCountry").hide();
					
				}
			});
			
			//For Registration Page
			var Register = {
				//Validation
				validate:function(){
					var err=0;
					dsa(".validationErrMsg").hide();
					Error.clear();
					dsa("div[id^='Err']").removeClass("errorfield");
					//dsa("#ErrMailingAddress").removeClass("errorfieldTxtArea");
					dsa("#txtMailAddress").parent().removeClass("errorfield");
					dsa("#otherCountry,#otherState,#otherCity,").removeClass("errorfield");
					dsa("#errBuisType").removeClass("errorfield");
					//Have the values in variables
					var firstName=getIdValue("txtFirstName");
					var lastName=getIdValue("txtLastName");
					var country=getIdValue("drpResAddrCountry");
					var state=getIdValue("drpResAddrState");
					var city=getIdValue("drpResAddrCity");
					var emailId=getIdValue("txtEmailId");
					var mailingAddress=getIdValue("txtMailAddress");
					var mobileNo=getIdValue("txtMobile");
					var industry=getIdValue("Industry");
					var offSpace=getIdValue("txtOffSpace");
					var txtexp=getIdValue("textErrExp");
					
					dsa("input:radio[name=rdModeOfenquiries]").click(function() {
					
						var value = dsa(this).val();
						if(value =='domestic')
								var radDom =  'domestic';
						else
								var radDom =  'international';
					});
					 
					var dobDate=getIdValue("drpFamilyDetail1dd"), dobMonth=getIdValue("drpFamilyDetail1mm"), dobYear=getIdValue("drpFamilyDetail1yy");
					//Checking all the manadorty field
					if(exp=="Yes" && radDom=="international")
						var myarray = ["txtFirstName","busType","txtMobile","Industry","txtLastName","txtEmailId","txtZipCode","textErrExp","txtCurrentBussiness","drpResAddrCountry","drpResAddrState","txtMailAddress"];
					else if(exp=="No" && radDom=="international")
						var myarray = ["txtFirstName","busType","txtMobile","Industry","txtLastName","txtEmailId","txtZipCode","txtCurrentBussiness","drpResAddrCountry","drpResAddrState","txtMailAddress"];
					else if(exp=="No" && radDom=="domestic")
						var myarray = ["txtFirstName","busType","txtMobile","Industry","txtLastName","txtEmailId","txtZipCode","txtCurrentBussiness","drpResAddrState","txtMailAddress"];
					else
						var myarray = ["txtFirstName","busType","txtMobile","Industry","txtLastName","txtEmailId","txtZipCode","textErrExp","txtCurrentBussiness","drpResAddrState","txtMailAddress"];
					
					dsa.each(myarray, function() {
						if((dsa("#"+this).is("input") && (!isNotEmpty(getIdValue(this)))) || (dsa("#"+this).is("textarea") && (!isNotEmpty(getIdValue(this)))) || (dsa("#"+this).is("select") && !isDrpDownNotEmpty(getIdValue(this))))
						{
						
							if(dsa("#"+this).is("input"))
								dsa("#"+this).parent().parent().addClass("errorfield");
							else if(dsa("#"+this).is("textarea"))
								dsa("#"+this).parent().addClass("errorfield");
							else
								dsa("#"+this).parent().addClass("errorfield");
							if(dsa(".validationErrMsg ul li").size()==0)
								Error.addError("Please enter the mandatory fields highlighted in RED","prepend");
						}
					});
					
					if(isNotEmpty(firstName) && (!checkValidName(firstName) || !checkAllowedLength(firstName,firstNameMin,firstNameMax)))
					{
						Error.addError("Please enter valid First name","append");
						dsa("#txtFirstName").parent().parent().addClass("errorfield");
					}
			
					if(offSpace!='')
					{
						if((!isNumeric(offSpace) || !checkAllowedLength(offSpace,offSpaceMin,offSpaceMax)))
						{
							Error.addError("Please enter valid Office Space","append");
							dsa("#txtOffSpace").parent().parent().addClass("errorfield");
						}
						else
							dsa("#txtOffSpace").parent().parent().removeClass("errorfield");
					}
					else
						dsa("#txtOffSpace").parent().parent().removeClass("errorfield");
					if(isNotEmpty(lastName) && (!checkValidName(lastName) || !checkAllowedLength(lastName,lastNameMin,lastNameMax)))
					{
						Error.addError("Please enter valid Last name","append");
						dsa("#txtLastName").parent().parent().addClass("errorfield");
					}
					if(industry!='')
					{
						if((!checkValidName(industry) || !checkAllowedLength(industry,industryMin,industryMax)))
						{
							Error.addError("Please enter valid Industry name","append");
							dsa("#Industry").parent().parent().addClass("errorfield");
						}
						else
							dsa("#Industry").parent().parent().removeClass("errorfield");
					}
					
					if(exp=='Yes')
					{
						var regExp='^[0-9]*[.][0-9]+dsa';
						if (isNotEmpty(txtexp) && (!isNumeric(txtexp) && !txtexp.match(regExp)) || !checkAllowedLength(txtexp,experienceMin,experienceMax) || txtexp<0 || txtexp==0)
						{
							Error.addError("Please enter valid Experience","append");
							dsa("#textErrExp").parent().parent().addClass("errorfield");
						}
					}
										
					var dob=dobDate+"-"+dobMonth+"-"+dobYear;
					if((dobDate!=0 || dobMonth!=0 || dobYear!=0) && (!isValidDate(dob) || !compareDates(dob)))
					{
						Error.addError("Please select valid Date Of Birth","append");
						dsa("#drpFamilyDetail1dd").parent().addClass("errorfield");
					}
					
					if(isNotEmpty(mailingAddress) && !checkValidAddress(mailingAddress))
					{
						Error.addError("Please enter valid Mailing Address","append");
						dsa("#txtMailAddress").parent().addClass("errorfield");
					}
					
					
					var otherState = getIdValue('txtOtherState');
					var otherCity = getIdValue('txtOtherCity');
					var otherCountry = getIdValue('txtOtherCountry');
					
					if(country=='Other'){
					if(otherCountry == 'Type in Your Country' || !isNotEmpty(otherCountry)){
						dsa("#txtOtherCountry").parent().parent().addClass("errorfield");
						Error.addError("Please enter valid Country","append");
					}
					else if(!checkValidName(otherCountry) || !checkAllowedLength(otherCountry,otherCountryMin,otherCountryMax))
					{
						Error.addError("Please enter valid Country","append");
						dsa("#txtOtherState").parent().parent().addClass("errorfield");
					}
					else
							dsa("#txtOtherCountry").parent().parent().removeClass("errorfield");
						}
					if(state=='Other'){
					if (otherState == 'Type in Your State' || !isNotEmpty(otherState)){
						dsa("#txtOtherState").parent().parent().addClass("errorfield");
						Error.addError("Please enter valid State","append");
					}
					else if(!checkValidName(otherState) || !checkAllowedLength(otherState,otherStateMin,otherStateMax))
					{
						Error.addError("Please enter valid State","append");
						dsa("#txtOtherState").parent().parent().addClass("errorfield");
					}
					else
						dsa("#txtOtherState").parent().parent().removeClass("errorfield");
					}
					
					if(city=='Other'){
					if(otherCity == 'Type in Your City' || !isNotEmpty(otherCity)){
						dsa("#txtOtherCity").parent().parent().addClass("errorfield");
						Error.addError("Please enter valid City","append");
					}
					else if(!checkValidName(otherCity) || !checkAllowedLength(otherCity,otherCityMin,otherCityMax))
					{
						Error.addError("Please enter valid City","append");
						dsa("#txtOtherCity").parent().parent().addClass("errorfield");
					}
					else
						dsa("#txtOtherCity").parent().parent().removeClass("errorfield");
					}
					
					if (isNotEmpty(emailId) && !isValidEmailId(emailId))
					{
						Error.addError("Please enter valid Email ID","append");
						dsa("#txtEmailId").parent().parent().addClass("errorfield");
					}
				
					var countryCodeRes = getIdValue('txtCountryCodeRes');	
					var areaCodeRes = getIdValue('txtAreaCodeRes');	
					var telephoneRes = getIdValue('txtTelephoneRes');
					if((countryCodeRes.toLowerCase()!="country code"  || areaCodeRes.toLowerCase()!="state code" || telephoneRes.toLowerCase()!="telephone"))
					{
						if(!isNumeric(countryCodeRes) || !checkAllowedLength(countryCodeRes,countryCodeMin,countryCodeMax))
						{
							Error.addError("Please enter valid Country Code for Telephone number","append");
							dsa("#txtCountryCodeRes").parent().parent().addClass("errorfield");
						}
						if(!isNumeric(areaCodeRes) || !checkAllowedLength(areaCodeRes,areaCodeMin,areaCodeMax))
						{
							Error.addError("Please enter valid State Code for Telephone number","append");
							dsa("#txtAreaCodeRes").parent().parent().addClass("errorfield");
						}
						if(!isNumeric(telephoneRes) || !checkAllowedLength(telephoneRes,telephonMin,telephonMax))
						{
							Error.addError("Please enter valid Telephone number","append");
							dsa("#txtTelephoneRes").parent().parent().addClass("errorfield");
						}
					}
					
					if (mobileNo!="" && (!isNumeric(mobileNo) || !checkAllowedLength(mobileNo,mobileMin,mobileMax)))
					{
						Error.addError("Please enter valid Mobile Number","append");
						dsa("#txtMobile").parent().parent().addClass("errorfield");
					}
					
					if(dsa(".validationErrMsg ul li").size()>0)
					{
						dsa(".validationErrMsg").show();
						goToByScroll("errorMsg");
					}
					else
					{
						Register.isEmailIdExists(emailId);
					}
				},
				//Check whether email id exists
				isEmailIdExists:function(email){
				
					dsa.ajax({
						url:"check_mail",
						async: false,
						cache: "false",
						dataType: "json",
						data:"format=block&status=checkEmail&email="+email, 
						success: function(data)
						{
						
							//checkSession(data);
							if(data)
							{
								Error.addError("Email Id already exists","append");
								dsa(".validationErrMsg").show();
								dsa("#txtEmailId").parent().parent().addClass("errorfield");
								goToByScroll("errorMsg");
							}
							else
							{
								document.dsa_registration_form.submit();
							}
						}
					});
				}
			};
				
			//Adding error message to the error div
			var Error={
				addError:function(error,position){
					if(position=="append")
						dsa(".validationErrMsg ul").append("<li>"+error+"</li>");
					else
						dsa(".validationErrMsg ul").prepend("<li>"+error+"</li>");
				},
				clear:function(){
					dsa(".validationErrMsg ul").html("");
				}
				
			};
			
			//Common functions
			var Common={
				
				getState:function(){
					
					dsa("#drpResAddrState").removeAttr('disabled');
					dsa("#otherCountry").hide();
					dsa("#otherState").hide();
					dsa('#drpResAddrState').val('0');
					dsa('#drpResAddrCity').val('0');
					dsa("#drpResAddrCity").attr("disabled","disabled");
					
					dsa("#otherCity").hide();
					var country=getIdValue("drpResAddrCountry");
					if(country==0) //Reseting the city drop down
					{				
						Common.displayOther('drpResAddrState','');
						dsa("#drpResAddrState").attr("disabled","disabled");
						
					}
					else if(country=="Other")
					{
						//Reseting the city drop down and showing other state inputbox.
						Common.displayOther('drpResAddrState','otherCountry');
						dsa('#drpResAddrCity').val('0');
					}
					else
					{
						//Getting and showing all related states
						Common.getShowData('country',country,'state','drpResAddrState','loadState');
					}
				},
					
				//Get the cities for the state
				getCity:function(){
					dsa("#drpResAddrCity").removeAttr('disabled');
					dsa("#otherState").hide();
					dsa("#otherCity").hide();
					var state=getIdValue("drpResAddrState");
					if(state==0) //Reseting the city drop down
					{
						Common.displayOther('drpResAddrCity','');
						dsa("#drpResAddrCity").attr("disabled","disabled");
					}
					else if(state=="Other")
					{
						//Reseting the city drop down and showing other state inputbox
						Common.displayOther('drpResAddrCity','otherState');
					}
					else
					{
						//Getting and showing all related cities
						Common.getShowData('state',state,'city','drpResAddrCity','loadState');
					}
				},
				//If other city is selected
				City:function(){
					var city=getIdValue("drpResAddrCity");
					dsa("#otherCity").hide();
					if(city=="Other")
					{
						//showing other city inputbox
						Common.displayOther('','otherCity');
					}
				},
				//Displays other input box and resets the required control
				displayOther:function(control,displayControl){
					if(control !=""){ 
						//if last control is selected then value is ""
						dsa("#"+control).html('');
						dsa.each(other.other, function(index,item) {
							dsa("#"+control).append("<option value=" + index + ">" + item + "</option>"); 
						});
					}
							
						
					if(displayControl!=""){
						dsa("#"+displayControl).show();
						if(displayControl == "otherCountry") {
							dsa('#txtOtherCountry').addClass('colorLight');
								dsa("#txtOtherCountry").attr("value","Type in Your Country");
						}
						if(displayControl == "otherState") {
							dsa('#txtOtherState').addClass('colorLight');
								dsa("#txtOtherState").attr("value","Type in Your State");
						}
						if(displayControl == "otherCity") {
							dsa('#txtOtherCity').addClass('colorLight');
								dsa("#txtOtherCity").attr("value","Type in Your City");
						}
					}
						
				},
				//Fetch required data and fill it in the required dropdown
				getShowData:function(inputType,inputId,outputType,optionControl,loadControl)
				{
					dsa("#"+loadControl).show();
					dsa.ajax({
						url:"fill_drop_down_list",
						async: false,
						cache: "false",
						dataType: "json",
						data:"&status="+outputType+"&"+inputType+"="+inputId, 
						success: function(data)
						{ 
						
							//checkSession(data);
							dsa("#"+loadControl).hide();
							
							dsa("#"+optionControl).html('');
							dsa.each(data.drplist, function(index,item) {
								dsa("#"+optionControl).append("<option value=" + index + ">" + item + "</option>"); 
							});
							dsa("#"+optionControl).removeAttr('disabled');
						}
					});
				},
				showResetPopup:function(){
						tb_show('', '#TB_inline?height=170&width=364&inlineId=resetConfirmDialog&modal=true');
				},
				redirect2Url:function(url){
					tb_remove();
					location.href = 'DsaRegister';
				},
			}
			
			var pageId = 'DsaRegister';
			if(pageId=='DsaRegister'){
			
				//Mailing Address
				dsa('#txtMailAddress').val('');
				dsa('#txtMailAddress').maxlength({max: 200, target:'checkAddressLimit'});
				
				var gCountryCode="Country Code";
				var gAreaCode="State Code";
				var gTelephone="Telephone";
				initInputBox(gCountryCode, ".inputCountryCodeRes");
				initInputBox(gAreaCode, ".inputAreaCodeRes");
				initInputBox(gTelephone, ".inputTelephoneRes");
				
				var gOtherCountry= "Type in Your Country";
				var gOtherState = "Type in Your State";
				var gOtherCity = "Type in Your City";
				initInputBox(gOtherCountry, ".inputOtherCountry");
				initInputBox(gOtherState, ".inputOtherState");
				initInputBox(gOtherCity, ".inputOtherCity");
				
				dsa("#drpResAddrCity").attr("disabled","disabled");
				
				//Register Page Calls
				dsa("#register").click(function(){
					Register.validate();
				});
				
				  dsa("#drpResAddrCountry").change(function(){		
				  dsa("#txtCountryName").val((dsa("#drpResAddrCountry option:selected").text()));
					Common.getState();
				});
				
				dsa("#drpResAddrState").change(function(){
					dsa("#txtStateName").val((dsa("#drpResAddrState option:selected").text()));
					Common.getCity();
				});
				
				dsa("#drpResAddrCity").change(function(){
					dsa("#txtCityName").val((dsa("#drpResAddrCity option:selected").text()));
					Common.City();
				});
			}
			Common.getShowData('country','1','state','drpResAddrState','loadState');
			dsa('#btnResetForm').click(function(){
					Common.showResetPopup();
			});
			dsa('#yesBtn').live('click',function(){
					Common.redirect2Url();
			});
				
	  }
  };
}(jQuery));