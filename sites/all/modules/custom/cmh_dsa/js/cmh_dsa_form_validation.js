/**
 * @file
 * The JS file for Form Validation.
 *
 */
//global variables
var loginMin = 1;
var loginMax = 15;
var passwordMin = 8;
var passwordMax = 25;
var postMin = 4;
var postMax = 10;
var firstNameMin = 2;
var firstNameMax = 50;
var lastNameMin = 1;
var lastNameMax = 50;
var mobileMin = 10;
var mobileMax = 15;
var otherCountryMin = 2;
var otherCountryMax = 50;
var otherStateMin = 2;
var otherStateMax = 50;
var otherCityMin = 2;
var otherCityMax = 50;
var countryCodeMin = 1;
var countryCodeMax = 4;
var areaCodeMin = 2;
var areaCodeMax = 5;
var telephonMin = 6;
var telephonMax = 10;
var faxMin = 6;
var faxMax = 15;
var configMin = 1;
var configMax = 500;
var secuQuesMin = 10;
var secuQuesMax = 100;
var subjectMin = 2;
var subjectMax = 50;
var magazineMin = 2;
var magazineMax = 50;
var webserviceTelephonMax = 15;
var jobCodesMin=2;
var jobCodesMax=10;
var jobTypesMin=5;
var jobTypesMax=100;
var industryMin=1;
var industryMax=50;
var experienceMin=1;
var experienceMax=3;
var offSpaceMin=1;
var offSpaceMax=10;

//for admin pages
var jobCodeMin = 3;
var jobCodeMax = 10;
var jobTitleMin = 5;
var jobTitleMax = 30;
var jobPosMin = 3;
var jobPosMax = 15;
var numPosMin = 1;
var numPosMax = 3;
var jobDescMin = 10;
var jobDescMax = 200;
var jobReqMin=10;
var jobReqMax=200;
var addrMin = 3;
var addrMax = 100;
var activityMin = 3;
var activityMax = 50;
var aliasMin = 3;
var aliasMax = 30;
var designationMin = 3
var designationMax = 50
var locationMin = 3
var locationMax = 50
var timingsMin = 3
var timingsMax = 15

/* Todays date start*/
function current_date_val(){
	var today = new Date();
	var dd = today.getDate();
	var mm = today.getMonth()+1;
	var yyyy = today.getFullYear();
	if(dd<10){dd='0'+dd}
	if(mm<10){mm='0'+mm}
	var CURRENT_DATE = dd+'-'+mm+'-'+yyyy;
	return CURRENT_DATE;
}
/* Todays date end*/

//function to get the value for the given Id
function getIdValue(id)
{
	var content = jQuery("#"+id).val();
	return returnTrimmedValue(content);
}
//function to get the value for the given Id with multiple params
function getFaceboxIdValue(id1,id2)
{
	var content = jQuery(id1,id2).val();
	return returnTrimmedValue(content);
}
//function to check if a given value is empty or not
function isNotEmpty(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var trimmedContentLength = trimmedContent.length;
	if(trimmedContentLength > 0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

//validate drop downs & default value should be zero
function isDrpDownNotEmpty(value)
{
	var trimmedContent = returnTrimmedValue(value);
	if(trimmedContent != 0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

//returns trimmed content
function returnTrimmedValue(value)
{
	var trimmedContent = jQuery.trim(value);
	return trimmedContent;
}

//function to check if a given value is alpha(with space) or not
function isAlphaWithSpace(value)
{
	var trimmedContent = returnTrimmedValue(value);
    var characterReg = /^[a-zA-Z ]+$/;
	if(trimmedContent.match(characterReg))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Allows only letters, numbers and spaces. All other characters will return an error. eg: postalcode
function isAlphaNumericWithSpace(value)
{
	var trimmedContent = returnTrimmedValue(value);
    var characterReg = /^\s*[a-zA-Z0-9,\s]+\s*$/;
	if(trimmedContent.match(characterReg))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Allows only letters, numbers and spaces. All other characters will return an error. eg: postalcode
function postalCode(value, country,allowedMin, allowedMax)
{
	var trimmedContent = returnTrimmedValue(value);
    var characterReg = /^\s*[a-zA-Z0-9,\s]+\s*$/;
    var numericReg = /^[0-9]+$/;
    if(country == '1')
	{
		if(value.length == 6 && trimmedContent.match(numericReg))
			return true;
		else
			return false;
	}
    else
    {
    	if(trimmedContent.match(characterReg))
    	{
			if(checkAllowedLength(value, allowedMin, allowedMax))
				return true;
			else
				return false;
		}		
	}

}

//function to check if a given email id is valid or not
function isValidEmailId(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var emailReg = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
	if(trimmedContent.match(emailReg))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//function to check if a given password id is valid or not
function isValidPassword(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var pwdReg = /^(?=.{8,25}$)(?=.*\d.*)(?=.*[a-zA-Z].*)(?=.*[\*@#_$&^!%-].*).*/;
	
	if(trimmedContent.match(pwdReg))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//function to check if a given number is numeric or not
function isNumeric(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var numericReg = /^[0-9]+$/;
	if(trimmedContent.match(numericReg))
	{
		return true;
	}
	else
	{
		return false;
	}
		
}
//function to check if a given number is numeric or special charachters.
function isNumericSpecial(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var numericReg = /^[0-9-/\n\r\g/\/'.,#!@$%&*()" ]+$/;
	if(trimmedContent.match(numericReg))
	{
		return true;
	}
	else
	{
		return false;
	}
		
}

//function to check web service telephone 
function isTelephone(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var numericReg = /^[0-9+]+$/;
	if(trimmedContent.match(numericReg))
	{
		return true;
	}
	else
	{
		return false;
	}
		
}
//function to find the length of the given input
function findLength(value)
{
	var trimmedContent = returnTrimmedValue(value);
	return trimmedContent.length;
}

//function to check the if the given values length is with in the allowed length
function checkAllowedLength(value, allowedMin, allowedMax)
{
	originalLength = findLength(value);
	if(originalLength <= allowedMax && originalLength >= allowedMin)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//function to check if value allowing &, - and space
function checkValidChar(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var nameReg = /^[a-zA-Z-& ]+$/;
	if(trimmedContent.match(nameReg))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
//function to check if valid name
function checkValidName(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var nameReg = /^[a-zA-Z-'., ]+$/;
	if(trimmedContent.match(nameReg))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
function checkValidAddress(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var addressReg = /^[a-zA-Z0-9-/\n\r\g/\/'.,#:&-()" ]+$/;
	if(trimmedContent.match(addressReg))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//Sparsh Description validation
function checkDescription(value)
{
	var trimmedContent = returnTrimmedValue(value);
	var addressReg = /^[a-zA-Z0-9-/\n\r\g/\/'.,#+:&-()" ]+$/;
	if(trimmedContent.match(addressReg))
	{
		return true;
	}
	else
	{
		return false;
	}	
}

//get unique array 
function getUniqueArray(arrayValue)
{
	arrayValue = jQuery.unique(arrayValue);
	return arrayValue;
}

//validating common feedbacks in textarea allowing all characters
function isValidFreeText(value)
{
	var value  = value.toLowerCase();
	var notAllowed = NOT_ALLOWED;
	var found = 0;
	var substr = notAllowed.split(',');
	for (var i=0, il=substr.length; i<il; i++) 
	{
		elmval = returnTrimmedValue(substr[i]).toLowerCase();
		if (value.indexOf(elmval) !=-1) {
			found++;
		}
	}
	if(found > 0)
	{
		return false;
	}
	else
	{
		return true;
	}	
}

//remove empty values in an array & return the array
function removeEmptyVal(arr)
{
	arr = jQuery.grep(arr,function(n){
	    return(n);
	});
	return arr;
}

//pass regular expression,match the passed value with it & return result
function checkRegEx(value,regex)
{
	var trimmedContent = returnTrimmedValue(value);
	if(trimmedContent.match(regex))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//validate date of birth
function isValidDate(sDate) {
  var sd = sDate.split('-');
  var y = sd[2], m  =sd[1], d = sd[0];
	if(y != '0' && m != '0' && d != '0')
{	  
  // Assume not leap year by default (note zero index for Jan)
  var daysInMonth = [31,28,31,30,31,30,31,31,30,31,30,31];

  // If evenly divisible by 4 and not evenly divisible by 100,
  // or is evenly divisible by 400, then a leap year
  if ( (!(y % 4) && y % 100) || !(y % 400)) {
    daysInMonth[1] = 29;
  }
  return d <= daysInMonth[--m];
	}else{
		return false;
	}
}
function compareDates(sDate){

	tDate = current_date_val();
	var sd = sDate.split('-');
	var y = sd[2], m  = sd[1], d = sd[0];
	var currDate = tDate.split('-');
	var y1 = currDate[2], m1  = currDate[1], d1 = currDate[0];
	var date1 = new Date(y, m-1, d);
	var date2 = new Date(y1, m1-1, d1); 
	if(date2 <= date1)
    {
        return false;
    }
	else
	{
		return true;
	}	
}
function compareTwoDates(date1,date2)
{

	var sd1 = date1.split('-');
	var sd2 = date2.split('-');
	var y1 = sd1[2], m1  = sd1[1], d1 = sd1[0];
	var y2 = sd2[2], m2  = sd2[1], d2 = sd2[0];
	var date1 = new Date(y1, m1-1, d1);
	var date2 = new Date(y2, m2-1, d2); 

	if(date2 < date1)
    {
        return false;
    }
	else
	{
		return true;
	}
}
function changeArrayOrder(errorArray)
{
	newErrorArray = new Array();
	var i=1;
  for(var j=0; j< errorArray.length;j++)
  {
	
	if(errorArray[j] == '<li>Please enter the mandatory fields highlighted in RED</li>')
	{
		newErrorArray[0] = '<li>Please enter the mandatory fields highlighted in RED</li>';
	}
	else
	{
		newErrorArray[i] = errorArray[j];
	}	
	i++;
	
	
  }
	newErrorArray = removeEmptyVal(newErrorArray);
	return newErrorArray;
}

function getLowerValue(id)
{
	var content = jQuery("#"+id).val().toLowerCase();
	return returnTrimmedValue(content);
}
function goToByScroll(id){
}