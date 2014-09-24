/**
 * @file
 * The JS file for DSA Gallery page.
 *
 */
jQuery(function() {
		function initiateCarousel() {           
		jQuery('#slides').slides({ 
			preload: true,
			preloadImage: '../images/loadingAnimation.gif',
			play: 3500,
			pause: 50,
			hoverPause: false,
			generatePagination: true,
			slideSpeed: 10,
			effect: 'slide',
			});
		}
		initiateCarousel(); 
});