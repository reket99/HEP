/**
 * @file
 * The JS file for Availability page.
 *
 */
( function(dsaAvail){
  Drupal.behaviors.dsaAvail = {
		attach: function (context, settings){

			dsaAvail(function() {
				reset_form();
				dsaAvail("#actionBtns").show();
				dsaAvail("#drpWLPlanLocation").change(function(){
					dsaAvail('#ajaxContent').hide();
					dsaAvail('#popupDatepicker').attr("value","");
					dsaAvail("#drpWLPlanResort").html('<option value="0">-Please Select-</option>');
				});
				
				// dsaAvail('form input').live('keydown',function(e){
					 // if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
						// dsaAvail('#autocomplete>ul>li.selected div').click();
					 // }
				// });
				dsaAvail('#autocomplete>ul>li.selected div').live('click',function(){ 
					dsaAvail('#member_list_id').val('');
					var memStr = dsaAvail(this).html();		
					dsaAvail('#member_list_id').val(memStr);
					Common.recheck_atuocomplete_val(memStr);
				});
				dsaAvail('#member_list_id').live('blur',function(){ 
					var memStr = dsaAvail(this).val();
					if(!isNotEmpty(memStr)){
						dsaAvail('#drpContract').html('<option value="0">-Please Select-</option>');
					}else{
						Common.recheck_atuocomplete_val(memStr);
					}
				});
				
				//Common functions
				var Common={
					recheck_atuocomplete_val:function(member_str){
            dsaAvail.blockUI();
						dsaAvail.ajax({
							type:'post',
							data:'member_str=' + member_str,
							url:'member_autocomplete_callback',
							async:false,
							success:function(data){
                dsaAvail.unblockUI();
								if(data == 'invalid') {
                  dsaAvail("#member_list_id").parent().addClass(" errorfield");
									dsaAvail('#memberid-invalid').show();
									dsaAvail('#member_list_id').val('');
									dsaAvail('#drpContract').html('<option value="0">-Please Select-</option>');
									dsaAvail('#ajaxContent').hide();
                  dsaAvail('#ajaxContent').html('');
								} else if(data == 'valid') {
									Common.get_contracts(member_str);
                  dsaAvail("#member_list_id").parent().removeClass(" errorfield");
									dsaAvail('#memberid-invalid').hide();
								}
							}
						});
					},
					
					get_contracts:function(member_str) {
						dsaAvail.blockUI();
            dsaAvail.ajax({
							type:'post',
							data:'member_str_contract=' + member_str,
							url:'member_autocomplete_callback',
							async:false,
							success:function(dataContract){
                dsaAvail.unblockUI();
								var options = '<option value="'+ dataContract +'">' + dataContract + '</option>';
								dsaAvail('#drpContract').html(options);
							}
						});
					},
					
					
					check_availability:function () {
						var location = dsaAvail('#drpWLPlanLocation').val();
						var resort = dsaAvail('#drpWLPlanResort').val();
						var date = dsaAvail('#popupDatepicker').val();
						var member_id = dsaAvail('#member_list_id').val();
						var contract_id = dsaAvail('#drpContract').val();
						
						if (isNotEmpty(date)){
							var dateArray = date.split('-');
							var startDate = returnTrimmedValue(dateArray['0']);
							var endDate = returnTrimmedValue(dateArray['1']);
						
							var startDateYear = startDate.substring(6, 10);
							var startDateMonth = startDate.substring(3, 5);
							var startDateDate = startDate.substring(0, 2);
							startDate = startDateYear+'-'+startDateMonth+'-'+startDateDate;

							var endDateYear = endDate.substring(6, 10);
							var endDateMonth = endDate.substring(3, 5);
							var endDateDate = endDate.substring(0, 2);
							endDate = endDateYear+'-'+endDateMonth+'-'+endDateDate;
						}
						
						dsaAvail('#error-mesg').hide();
						
						var noError=true;
						if(!isDrpDownNotEmpty(location)){
							noError=false;
							dsaAvail("#locSection").addClass(" errorfield");
						}
						else{
							dsaAvail("#locSection").removeClass(" errorfield");
						}
						
						if(!isDrpDownNotEmpty(resort)){
							noError=false;
							dsaAvail("#resortSection").addClass(" errorfield");
						}
						else{
							dsaAvail("#resortSection").removeClass(" errorfield");
						}
						
						if(!isNotEmpty(date)){
							noError=false;
							dsaAvail(".txtField").addClass(" errorfield");
						}
						else{
							dsaAvail(".txtField").removeClass(" errorfield");
						}
						
						if(isNotEmpty(member_id) && !isDrpDownNotEmpty(contract_id)){
							noError=false;
						}else if(!isNotEmpty(member_id) && !isDrpDownNotEmpty(contract_id)){
							member_id = '';
							contract_id = Drupal.settings.CMHDSA.CONTRACT_ID;
						}
						
						if(noError) {
							dsaAvail.blockUI();
							dsaAvail('#errorMsg').hide();
							dsaAvail.ajax({
								url:"BookingDisplayAvailability",
								type:"POST",
								data:"crest_id="+resort+"&member_id="+member_id+"&contract_id="+contract_id+"&checkoutdate="+endDate+"&checkindate="+startDate, 
								success: function(data){
									dsaAvail.unblockUI();		
									dsaAvail('#ajaxContent').show();
									dsaAvail('#ajaxContent').html(data);
									
									/*for the availability grid start*/
									dsaAvail('.scroll-pane-os').jScrollPane({
										showArrows: true,
										horizontalArrowPositions: 'os',
										horizontalDragMinWidth: 82,
										horizontalDragMaxWidth: 82	
									});
									var rowCount = dsaAvail('#room_type_count').val();
									var resortIDDate = dsaAvail('#crest_id').val();
									var height = 0;
									if(rowCount > 0) {
										dsaAvail.browser.chrome = /chrome/.test(navigator.userAgent.toLowerCase()); 

										if(dsaAvail.browser.chrome){
											height = 62+(19*rowCount);		
										}else{
											height = 62+(18*rowCount);		
										}
										
										dsaAvail("#dates_"+resortIDDate+" .jspContainer").css("height",height);
										dsaAvail(".jspContainer table tr td").css("height","18");		 
									}
									var previousRoomType = '';
									var presentRoomType = '';
									dsaAvail("a.spotlight").click(function(){
										presentRoomType = "#"+dsaAvail(this).attr("id");
										if(presentRoomType != previousRoomType){
											if(previousRoomType != ""){
												dsaAvail(previousRoomType).parent().removeClass("currentSelecBorder");
											}
											dsaAvail(presentRoomType).parent().addClass("currentSelecBorder");
											previousRoomType = "#"+dsaAvail(this).attr("id");
										}
									});
									
									if(dsaAvail(".availabilityTable")[0])	{
										dsaAvail('.noBookHoliday').hide();
									}else{	
										dsaAvail('.noBookHoliday').show();	
										var found = {};
										dsaAvail('div[class^=noBookHoliday]').filter(function() {
											
											var ending = this.id.replace("noBookHoliday","");
											if( found.hasOwnProperty( ending ) ) {
												return this;
											} else {
												found[ ending ] = ending;
											}
										}).remove();
									}
									/*for the availability grid end*/
									
									/*for the send mail functionality Start*/
									var member_list_id = dsaAvail('#member_list_id').val();
									var booking_req_display_flag = dsaAvail('#booking_req_display_flag').val();
									
									if(isNotEmpty(member_list_id) && booking_req_display_flag != '0'){
										dsaAvail('#booking_req').show();
										txtSendMail += 'Member   : ' + member_list_id + '\n';
										var drpContract = dsaAvail('#drpContract').val();
										var drpContractHtml = dsaAvail("#drpContract>option[value$='"+drpContract+"']" ).html();
										txtSendMail += 'Contract : ' + drpContractHtml;
									}
									else{
									  dsaAvail('#booking_req').hide();
									}
									dsaAvail('#txtSendMail').html('');
									var txtSendMail = '';
									
									var location = dsaAvail('#drpWLPlanLocation').val();
									var locationHtml = dsaAvail("#drpWLPlanLocation>option[value$='"+location+"']" ).html();
									txtSendMail += 'Location : ' + locationHtml + '\n';
									
									var resort = dsaAvail('#drpWLPlanResort').val();
									var resortHtml = dsaAvail("#drpWLPlanResort>option[value$='"+resort+"']" ).html();
									txtSendMail += 'Resort   : ' + resortHtml + '\n';
									
									var popupDatepicker = dsaAvail('#popupDatepicker').val();
									txtSendMail += 'Dates    : ' + popupDatepicker + '\n';
									
									txtSendMail += 'Room Preference  : \n';
									txtSendMail += 'No of Rooms      : \n';
									txtSendMail += 'Person Traveling : \n';
									
									
									dsaAvail('#txtSendMail').html(txtSendMail);
									
									dsaAvail('#sendMailAvailabilityBtn').live('click',function(){ 
						
										dsaAvail('.validationsuccessMsg ul').html('');
										dsaAvail('.validationsuccessMsg').hide();
										dsaAvail('#error-mesg').html('');
										dsaAvail('#error-mesg').hide();
									
										var txtAreaSendMail = getIdValue('txtSendMail');
										if(!isNotEmpty(txtAreaSendMail)) {
											//error
                      dsaAvail("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
                      dsaAvail("#error-mesg").show();
                      dsaAvail(".success-msg").hide();
                    	 dsaAvail("#txtSendMail").parent().addClass(" errorfield");
										}else{
											//no error
											dsaAvail("#txtSendMail").parent().removeClass(" errorfield");
											dsaAvail('#error-mesg').html('');
											dsaAvail('#error-mesg').hide();
											dsaAvail.blockUI();
											dsaAvail.ajax({
												url:"SendAvailabilityMail",
												type:"POST",
												data:"txtAreaSendMail=" + txtAreaSendMail + '&member_id=' + member_id + '&contract_id=' + contract_id,  
												success: function(data){
													dsaAvail.unblockUI();	
													if (data == 'valid') {
														setTimeout('location.reload()',5);
													}else if (data == 'invalid') {
										        dsaAvail("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Failed to send the booking request. Please try again!</span></div>');
                            dsaAvail("#error-mesg").show();
                            dsaAvail(".success-msg").hide();
													}
													
												}
											});			
										} 
									});
									/*for the send mail functionality End*/
								}
							});
						}else{
							dsaAvail("#error-mesg").html('<div class="error-msg"><span class="error-img"></span><span class="font13bold float-left margintop12" id="err-invalid-text">Please enter all mandatory fields.</span></div>');
              dsaAvail("#error-mesg").show();
							dsaAvail(".success-msg").hide();
              dsaAvail('#ajaxContent').hide();
              dsaAvail('#ajaxContent').html('');
              return false;
						}
					},
					
					addon_change_handler:function(){
						dsaAvail("#drpWLPlanLocation").live("change", function(){ 
							var a = dsaAvail(this).val();
							var that = dsaAvail(this);
							dsaAvail.ajax({
								type:'post',
								url: "HolidayPlanResorts",
								data:"catId="+a+"&format=block",
								cache: "false",
								dataType: "json",
								success: function(data) {
									var listItems = '';
									dsaAvail.each(data,function(i,v){
										listItems += "<option value='" + i + "'>" + v  + "</option>";
									});
									dsaAvail('#drpWLPlanResort').html(listItems);
								}
							});
						});
					},

					initiate_datepicker:function () {
						dsaAvail("#calendarTooltip").css({"background-color": "#F57101"});
						var title="Select start date";	
						var selectionCount = 0;
						dsaAvail("#wrapper").append('<div id="calendarTooltip" style="display: none;">Select start date</div>');
						dsaAvail('#popupDatepicker').datepick({
							onClose: function(dates) {		
								if(dsaAvail("#createBookingSection").length > 0) {	
								}
							},
							dateFormat: "dd/mm/yyyy",
							onSelect: function onSelectHandler(dates){
								selectionCount++;
								if(selectionCount == 1){
									dsaAvail("#calendarTooltip").css({"background-color": "#F57101"}).show();
									title = "Select end date";
								}else{
									dsaAvail("#calendarTooltip").css({"background-color": "#F57101"})
									title = "Select start date";
								}
								dsaAvail("#calendarTooltip").hide();
							},
							onClose: function(dates) { selectionCount = 0; },		      
							//rangeSelect: true, monthsToShow: 2, showTrigger: '#calImg', minDate: new Date(), maxDate: '+4M -1D'
              rangeSelect: true, monthsToShow: 2, showTrigger: '#calImg', minDate: new Date(), maxDate: '31/12/2014'
						});
						dsaAvail(".customizedCal .datepick-month td a").live("mouseover", function(e){
							flagMouseIn = true;
							if(flagMouseIn)
								dsaAvail("#calendarTooltip").html(title);
							dsaAvail("#calendarTooltip").css({"left": e.pageX+5, "top": e.pageY}).show();
						});
						dsaAvail(".customizedCal .datepick-month td a").live("mouseout", function(e){
							dsaAvail("#calendarTooltip").hide();
							flagMouseIn = false;
						});
					},
					
					bind_calender_click:function () {
					// triggers focus event for Datepicker text field
						dsaAvail("#search_Calender").click(function() {
							dsaAvail('#popupDatepicker').trigger('focus');
						});
					},
					
					add_content_scroller:function () {
						if(typeof PAGEID != "undefined" && PAGEID != "CommunitySpace")
						{
							var scrollContentObj = dsaAvail(".customScrollBar");
							if(scrollContentObj.length > 0) {
								scrollContentObj.jScrollPane({
									showArrows: true,
									verticalDragMinHeight: 82,
									verticalDragMaxHeight: 82
								});
							}
						}
					}, 
					show_reset_popup:function(){
						tb_show('', '#TB_inline?height=170&width=364&inlineId=resetConfirmDialog&modal=true');
					}, 
					redirect_to_url:function(url){
						tb_remove();
						location.href = 'DsaAvailability';
					}
				}//end of Common
					
				Common.addon_change_handler();//on change of location drop down
				Common.initiate_datepicker(); //initializes the Datepicker Control
				Common.bind_calender_click();  //Puts focus on calender field
				Common.add_content_scroller();  //Puts focus on calender field

				//dsaAvail('#checkAvailabilityBtn').click(function(){ 
				dsaAvail('#cmh-dsa-resort-availability-form').submit(function(){ 
					dsaAvail('.success-msg').hide();
					dsaAvail('#error-mesg').html('');
					dsaAvail('#error-mesg').hide();
					if (Common.check_availability())
            return true;
          else
            return false;
				});
				
				dsaAvail('#btnresetform').click(function(){
					Common.show_reset_popup();
				}); 
				dsaAvail('#yesBtn').live('click',function(){
					Common.redirect_to_url();
				});
			});
		}
	};
}(jQuery));	