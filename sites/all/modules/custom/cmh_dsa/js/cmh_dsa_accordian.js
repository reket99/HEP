/**
 * @file
 * The JS file for Accordian page.
 *
 */
 ( function(accordian){
  Drupal.behaviors.accordian = {
		attach: function (context, settings){
			accordian(document).ready(function() {
				var accordianFun = {
					initHUSTblColor:function(){
								accordian(".HUStbl tbody tr:last").addClass("last");
								accordian(".HUStbl tr:even").addClass("even"); 
					},
					accordianClickHandler:function(target, context){
						accordian(target, context).live('click',function(){
						if(accordian(this).hasClass("accordian_up")){
									accordianFun.collapsePanel(this, context);
							} else {
									accordianFun.expandPanel(this, context);
							}
						});
					},
					expandPanel:function(target, context){
							accordian(target, context).addClass("accordian_up");
							accordian(target, context).removeClass("accordian_down");
							accordian(target, context).closest(context).find(".showContent").slideDown("slow");
					},
					collapsePanel:function(target, context){
							accordian(target, context).removeClass("accordian_up");
							accordian(target, context).addClass("accordian_down");
							accordian(target, context).closest(context).find(".showContent").slideUp("slow");
					}
				
				}//End of function definition
				
				accordianFun.accordianClickHandler(".btnUpDwn", ".bookingSteps");
				accordianFun.accordianClickHandler(".btnUpDwn", ".bookingTips");
				accordianFun.collapsePanel(".btnUpDwn", "#step1");
				accordianFun.collapsePanel(".btnUpDwn", "#step2");
				accordianFun.collapsePanel(".btnUpDwn", "#step3");
				accordianFun.collapsePanel(".btnUpDwn", "#step4");
				accordianFun.accordianClickHandler();
				accordianFun.initHUSTblColor();
			});
		}
	};
}(jQuery));