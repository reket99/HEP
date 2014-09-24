<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Resort Details Form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['resort_details'];
*
*/
 ?>
<script>
jQuery(document).ready(function(){ 
  function initiateCarousel() { 
          jQuery('#slides').slides({ 
          preload: true,
          preloadImage: 'images/loadingAnimation.gif',
          play: 3000,
          pause: 1000,
          hoverPause: true,
          generatePagination: true,
          animationStart: function(current){
            jQuery('.caption').animate({
            bottom:-35
            },100);
          },
          animationComplete: function(current){
            jQuery('.caption').animate({
            bottom:0
            },200);
          },
          slidesLoaded: function() { 
            jQuery('.caption').animate({
            bottom:0
            },200);
          },
        effect: 'slide',
      });
  }
  jQuery("#drpResort").live("change", (function(){
	  initiateCarousel();
  }));
  
});
</script>
<!--Start:Content-->
	<div class="content-header"><div class="content-header-text">Resort Details</div></div>
	<div class="content-block" id="content">
		<div class="member-drp">
			<div class="resort-label">Select Resort</div>
			<?php print $variables['resort_details']['drpResort']; ?>
			<div id="resortdata" class="resort-container"></div>
		</div>
		<?php print $variables['resort_details']['hidden']; ?>
	</div>
<!--End:Content-->
