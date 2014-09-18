/**
 * @file
 * The JS file for DSA Member page.
 *
 */
( function(member){
  Drupal.behaviors.member = {
		attach: function (context, settings){
		   if(Drupal.settings.CMHDSA.pageId == 'DsaMember'){
				var contract = '<span>Contract: </span><select name="mul_contracts" id="mul_contracts">';
				var arr = Drupal.settings.CMHDSA.contracts;
				if(arr != null && member.isArray(arr[Drupal.settings.CMHDSA.MEMBERID])) {
					for(i = 0; i < arr[Drupal.settings.CMHDSA.MEMBERID].length; i++) {
						if(member("#membership_id").html() == arr[Drupal.settings.CMHDSA.MEMBERID][i]) {
							contract += '<option value="' + arr[Drupal.settings.CMHDSA.MEMBERID][i] + '" selected>' + arr[Drupal.settings.CMHDSA.MEMBERID][i] + '</option>';
							 contract_no = arr[Drupal.settings.CMHDSA.MEMBERID][i];
						} else {
							contract += '<option value="' + arr[Drupal.settings.CMHDSA.MEMBERID][i] + '">' + arr[Drupal.settings.CMHDSA.MEMBERID][i] + '</option>';
							 contract_no = arr[Drupal.settings.CMHDSA.MEMBERID][i];
						}
					}
					contract += '</select>';
					member(".memberdet-contract").html(contract);
				}
				else{
					member(".memberdet-contract").html('<span>Contract: </span>' + Drupal.settings.CMHDSA.MEMBERID);
				}
			}
			
			
			member(".memberdet-contract").live('change', function(){
				member.ajax({
					type: 'POST',
					url: '?q=DsaMember/MemberDetails',
					dataType: 'json',
					success: function(response){
						 member("#season").html(response.data.season);
						 member("#apartment").html(response.data.apartment);
						 member("#membership_id").html(response.data.membership_id);
						return false;
					},
					data: 'type=contract&member='+Drupal.settings.CMHDSA.MEMBERID+'&contract='+member(".memberdet-contract option:selected").text()
				});
			});
			
			member(".memberdet-contract").live('change', function(){
				member.ajax({
					type: 'POST',
					url: '?q=DsaMember/MemberInformation',
					dataType: 'json',
					success: function(response){
						member("#membership_id").html(response.data.membership_id);
						member("#cancel_status").html(response.data.cancel_status);
						member("#can_req_date").html(response.data.can_req_date);
						member("#cancel_rec").html(response.data.cancel_rec);
						member("#hol_bal").html(response.data.hol_bal);
						return false;
					},
					data: 'type=contract&member='+Drupal.settings.CMHDSA.MEMBERID+'&contract='+member(".memberdet-contract option:selected").text()
				});
			});
			
			member(".memberdet-contract").live('change', function(){
				member.ajax({
					type: 'POST',
					url: '?q=DsaMember/HUS',
					dataType: 'json',
					success: function(response){
						member("#hol_ent").html(response.data.hol_ent);
						member("#hol_booked").html(response.data.hol_booked);
						member("#hol_rci").html(response.data.hol_rci);
						member("#hol_cancelled").html(response.data.hol_cancelled);
						member("#holiday_bal").html(response.data.holiday_bal);
						member("#excs_hol_lapsed").html(response.data.excs_hol_lapsed);
						member("#acc_bal").html(response.data.acc_bal);
						return false;
					},
					data: 'type=contract&member='+Drupal.settings.CMHDSA.MEMBERID+'&contract='+member(".memberdet-contract option:selected").text()
				});
			});
			
			
			//On enter key call filter key press event
			member("form input, form select").live("keypress", function (e) {
				if ((e.which && e.which == '13') || (e.keyCode && e.keyCode == '13')) { 
					member('#filter').click();
				}
			});
				
			//To show, hide search textboxes
			member("#drpSearchMember").live('change', function(){				
				if(member("#drpSearchMember").val() == 'MemberId'){
					member('#txtSearchKeyword').val('Enter Member ID');
				} else if(member("#drpSearchMember").val() == 'MemberName') { 
					member('#txtSearchKeywordName').val('Enter Member Name');
				}				
				member('#txtSearchKeyword').focus(function(){
					member('#txtSearchKeyword').val('');
				});
				member('#txtSearchKeywordName').focus(function(){
					member('#txtSearchKeywordName').val('');                                                                       
				});
				member('#txtSearchKeyword').focusout(function(){
				  if(member('#txtSearchKeyword').val() == '')
					  member('#txtSearchKeyword').val('Enter Member ID');
				});
				member('#txtSearchKeywordName').focusout(function(){
				  if(member('#txtSearchKeywordName').val() == '')
					  member('#txtSearchKeywordName').val('Enter Member Name');
				});		
				
				member(".validationErrMsg").hide();
				member(".txtField").removeClass("errorField");
				var filter_optn = member('#drpSearchMember').val();
				member("#divFilter").show();
				if(filter_optn == '0' || filter_optn == '1') {
					member("#searchkeywordtxtbox").hide();
					member("#searchkeywordtxtboxname").hide();
					member("#searchkeywordtxtbox,#searchkeywordtxtboxname").removeClass("errorField");
					member(".member-drp").removeClass("member-drp-height");
				}
				else if(filter_optn == 'MemberId') {
 					member("#searchkeywordtxtbox").show();
					member("#searchkeywordtxtboxname").hide();
					member(".member-drp").removeClass("member-drp-height");
				}
				else if(filter_optn == 'MemberName') {
					member("#searchkeywordtxtboxname").show();
					member("#searchkeywordtxtbox").hide();
					member(".member-drp").removeClass("member-drp-height");
				}
			});

			//To change the status of contracts
			member(".contract").live('change', function(){
				var memberval = member(this).attr("id");
				var contract = member(".contract option:selected").text();
				member.ajax({
					type: 'POST',
					url: '?q=DsaSearchMember',
					dataType: 'json',
					success: function(response){
						member("#status-"+memberval).html(response.data); return false;
					},
					data: 'type=contract&page=1&member='+memberval+'&contract='+contract
				});
			});
			
			//To validate and call to search_member()
			member("#filter").live('click', function(){
				var type = member('#drpSearchMember').val();
				var page = '1';
				var searchId = member('#txtSearchKeyword').val();
				var searchName = member('#txtSearchKeywordName').val();
				if(type != '0' && (searchId == "" || searchId == 'Enter Member ID') && type == 'MemberId'){
					member(".member-drp").addClass("member-drp-height");
					member(".validationErrMsg").html('<span class="error-img"></span><span class="font13bold float-left margintop12"> Please enter search text for ID </span>');
					member(".validationErrMsg").show();
					member("#searchkeywordtxtbox").addClass("errorField");
					member("#searchkeywordtxtboxname").removeClass("errorField");
				}
				else if(type != '0' && searchId != "" && type == 'MemberId'){
					member(".validationErrMsg").html('');
					member(".validationErrMsg").hide();
					member("#searchkeywordtxtbox,#searchkeywordtxtboxname").removeClass("errorField");
					member(".member-drp").removeClass("member-drp-height");
					search_member(page, type, searchId);
				}
				if(type != '0' && searchName == "" && type == 'MemberName'){
				  member(".member-drp").addClass("member-drp-height");
					member(".validationErrMsg").html('<span class="error-img"></span><span class="font13bold float-left margintop12"> Please enter search text for name </span>');
					member(".validationErrMsg").show();
					member("#searchkeywordtxtboxname").addClass("errorField");
					member("#searchkeywordtxtbox").removeClass("errorField");
				}
				else if(type != '0' && searchName != "" && type == 'MemberName'){ 
					member(".validationErrMsg").html('');
					member(".validationErrMsg").hide();
					member("#searchkeywordtxtbox,#searchkeywordtxtboxname").removeClass("errorField");
					member(".member-drp").removeClass("member-drp-height");
					search_member(page, type, searchName);
				}
				if(type == '0'){
					member(".validationErrMsg").html('');
					member(".validationErrMsg").hide();
					member("#searchkeywordtxtbox,#searchkeywordtxtboxname").removeClass("errorField");
					member(".member-drp").removeClass("member-drp-height");
					var search = '';
					search_member(page, type, search);
				}
				
			});

			/* Start: code for pagination in search member page */
			member('.pager').live("click", function (){
				var type = member(this).attr('id');
				var id = type.split('-');
				var typeSearch = member('#drpSearchMember').val();
				var search;
				if (typeSearch == 'MemberName')
					search = member('#txtSearchKeywordName').val();
				else if (typeSearch == 'MemberId')
					search = member('#txtSearchKeyword').val();
				search_member(id[1], id[0], search);
			});
			/* End: code for pagination in search member page */
			
			member(".memberLink").click(function(){
				var member_id = member("#user_id").val();
				var reference_page = member(this).attr("id");
				member(".memberLink").removeClass('active');
				member_ajax_call(reference_page, member_id);
				return false;
			});				
			
	
			function search_member(page, type, search){
				member.ajax({
					type: 'POST',
					url: '?q=DsaSearchMember',
					dataType: 'json',
					success: function(response){
						container = member('#searchMemberContent');
						container.html(response.data);
					},
					data: 'type='+type+'&page='+page+'&search='+search
				});	
			}
			
			function member_ajax_call(page, member_id){
				member.ajax({
					type: 'POST',
					url: '?q=DsaMember',
					dataType: 'json',
					success: function(response){
						member('#'+page).addClass('active');
						container = member('#block-content');
						container.html(response.data);
						member("#contract_info").html('<div class="floatRight displayContract"><span class="bold">Contract : </span>'+container.find("#contract_id").val()+'</div>');
						return false;
					},
					data: 'ch=1&member_id='+member_id+'&page='+page
				});			
			}
			
			member("#tabs ul li").live("click", function (){
				member(".tab-title").removeClass('active');
				var tab_id = member(this).attr('id');
				var tab_val = member('a', this).attr('href');
				var div_id = tab_val.split('#');
				member(".tab-content").hide();
				member("#"+tab_id).addClass('active');
				member("#"+div_id[1]).show();
				console.log(div_id[1]);
				return false;
		  });
		}
  };
}(jQuery));