/**
 * @file
 * The JS file for Resort Detail page.
 *
 */
/* Function call on change event of Resort Dropdown */
jQuery(document).ready(function() {
	reset_form();
});
function get_resort_details(resortid){
	if(resortid == 0 || resortid =='' ){
		alert("Please select a Resort");
		jQuery('#resortdata').html('');
		return false;
	}else{
	
		jQuery.ajax({		
			url: "resort_details",
			data: "resortid="+resortid+"&format=block",
			async: false,
			success: function(data){	
				jQuery.unblockUI();	
				jQuery('#resortdata').html(data);
			}
		});	
	}
}