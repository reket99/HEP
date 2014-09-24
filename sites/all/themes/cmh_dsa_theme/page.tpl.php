<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['user_info']: Displays the welcome message for user.
 * - $page['user_nav']: The user navigation for profile and logging out.
 * - $page['left_navigation']: Main navigation for users.
 * - $page['member_navigation']: Navigation for members information.
 * - $page['content']: The main content of the current page.
 * - $page['footer']: Items for the footer region.
 * - $page['policy'] = Items for the Site Policies.
 * - $page['copyright'] = Items for the site copyrights.
 * - $page['secure'] = Items for the VeriSign.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
	<!-- wrapper Start -->
	<div class="wrapper">
		<!-- header Start -->
		<div class="header">
				<!-- logo Start -->
				<div class="logo">
					 <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
				</div>
				<!-- logo End -->
				<!-- user-info start -->
				<div class="user-info">
						<?php if($page['user_info']):?>
            <!-- user-welcome Start -->
						<div class="user-welcome">
								<?php print render($page['user_info']);?>
                <!--<span class="welcome">Welcome</span> 
								<span class="welcome-user">Linear </span>-->
						</div>
						<!-- user-welcome End -->
            <?php endif; ?>
						<?php if($page['user_nav']):?>
						<!-- user-nav start -->
						<div class="user-nav">
							<!-- <ul>
									<li><div class="menu-link my-account">My Account </div></li>
									<li><div class="menu-link logout">Logout</div></li>
							</ul> -->
							<?php
									$menu_logout = menu_navigation_links('menu-dsa-logout');
									//print_r($menu_logout); exit;
									if ($menu_logout):
										print theme('links__system_menu_dsa_logout', array('links' => $menu_logout));
									endif;
								?>
						</div>
						<!-- user-nav End -->
					<?php endif; ?>
				</div>
				<!-- user-info End -->
		</div>
		<!--end of header-->
	  
		<!-- header-sepataor Start -->
		<div class="header-separator"></div>
		<!-- header-sepataor End -->
		<!--Start:Marquee(news_holder) -->
      <?php if($page['news_holder']): ?>
				<div class="news_ticker">
					<div class="ticker_holder"> 
						<?php print render($page['news_holder']); ?>
					</div>
				</div>
			<?php endif; ?>
		<!--End:Marquee(news_holder) -->
		<!-- page Start -->
		<div class="page">
			
			<!-- page-wrapper start -->
			<div class="page-wrapper">
					<?php if($page['left_navigation']):?>
						<!-- left-nav start -->
							<div class="left-nav">
								<?php
									$menu_navigation = menu_navigation_links('menu-dsa-navigation');
									if ($menu_navigation):
										print theme('links__system_menu_dsa_navigation', array('links' => $menu_navigation));
									endif;
								?>
							</div>  
						<!-- left-nav End -->
						<?php  endif; ?>
				<?php if($page['content']):?>
						<!-- content Start -->
						<div class="content">
							<?php if($page['member_navigation']):?>
								<div class="content-header"><?php echo $title; ?></div>
								<?php if(strtolower(pageId) == 'dsamember') : ?>
								  <div class="memberdet-contract"></div>
									<div class="memberdet-back-div"><a href="<?php echo base_path(); ?>DsaSearchMember">Back to Member's List</a></div>
								<?php endif; ?>
								<div class="content-block">
									<div class="content-container">
										<!-- Member Nav Start -->
										<div id="<?php echo strtolower(pageId); ?>-nav" class="sub-menu">
											<?php print render($page['member_navigation']);?>
										</div>
										<!--end of Member Nav-->
										<div id="block-content" class="page-content">
											<?php print render($page['content']);?>
										</div>
									</div>
								</div>
							<?php  else : ?>
						<?php print render($page['content']);?>
						<?php  endif; ?>
						</div>
						<!-- end of content -->
				<?php  endif; ?>
			</div>
		 <!-- page-wrapper End -->
			<div class="footer-separator"></div>
			<!-- footer-separator start & end -->
	</div>
 <!-- page-wrapper End -->


	<div class="footer"> 
	<!-- footer Start -->
			<div class="footer-wrapper" >    
			<!-- footer-wrapper Start -->
					<div class="footer-content clearfix float-left" >
					<!-- footer-content Start -->
						<?php
							if($page['footer']):
								$footermenu1 = menu_navigation_links('menu-clubmahindra');
								if ($footermenu1):
									print theme('links__system_menu_clubmahindra', array('links' => $footermenu1, 'attributes' => array('id' => 'footer')));
								endif;
								
								$footermenu2 = menu_navigation_links('menu-region');
								if ($footermenu2):
									print theme('links__system_menu_region', array('links' => $footermenu2, 'attributes' => array('id' => 'footer')));
								endif;
								
								$footermenu3 = menu_navigation_links('menu-holiday-type');
								if ($footermenu3):
									print theme('links__system_menu_holiday_type', array('links' => $footermenu3, 'attributes' => array('id' => 'footer')));
								endif;
								
								$footermenu4 = menu_navigation_links('menu-terrain');
								if ($footermenu4):
									print theme('links__system_menu_terrain', array('links' => $footermenu4, 'attributes' => array('id' => 'footer')));
								endif;        
							endif;
							
							if($page['policy']):
								$footermenu5 = menu_navigation_links('menu-footer-two-top');
									if ($footermenu5):
											print theme('links__system_menu_policy', array('links' => $footermenu5, 'attributes' => array('id' => 'policy')));
									endif;
							endif;
					  ?>              
					</div>
					 <!-- footer-content End -->
					 <!-- footer-copy-rights start -->
					<div class="footer-copy-rights">
						 <div class="footer-cr-right">
						 <?php
              if($page['copyright']):
                print render($page['copyright']);
              endif;
              ?>
						</div>
						 <div class="footer-cr-left">
						  <?php
              if($page['secure']):
                print render($page['secure']);
              endif;
              ?>
						 </div>
					</div>
					 <!-- footer-copy-rights end -->
			</div>   
			<!-- footer-wrapper End -->
		</div>
		<!-- footer End -->
	</div>
	<!--end of wrapper-->
