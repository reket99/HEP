<?php
/**
 * @file         page.tpl.php
 * @version      1.0.0
 * @author       CTS
 * @desc         The theme system, which controls the output of Drupal.
 *                The theme system allows for nearly all output of the Drupal system to be
 *                customized by user themes.
 * @date         
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 * @modified by  
 * @modified on  
 */
?>
<!--Start:wrapper -->
<?php if(pageId == 'DsaThankyou'){ ?>
<div id="wrapper" class="dsaThankYou">
<?php }else{?>
<div id="wrapper">
<?php } ?>
<!--Start:Header -->
  <div id="header">
<!--Start:Logo -->
    <?php if ($logo): ?>
      <div class="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </div>
    <?php endif; ?>
<!--End:Logo -->
<!--Start:Welcome User -->
    <?php if($page['user_info']):?>
      <div class="welcomeDsa">  
        <?php print render($page['user_info']);?>
      </div>
    <?php  endif; ?>
<!--End:Welcome User -->
<!--Start:User Info -->
      <div class="topBgNoBorder floatRight">
        <?php if($page['logout']):?>
            <?php
              $menu_logout = menu_navigation_links('menu-dsa-logout');
              if ($menu_logout):
                print theme('links__system_menu_dsa_logout', array('links' => $menu_logout, 'attributes' => array('id' => 'logout', 'class' => array( 'clearfix'))));
              endif;
            ?>
        <?php  endif;?>
      </div>
<!--End:User Info -->
  </div>
<!--End:Header -->
<!--Start:Content -->
  <div id="content">
<!--Start:ContentWrapper,SearchMember -->
    <div class="contentWrapper searchMember">
      <div class="topBgNoBorder clearfix">
			</div>
<!--Start:DSA Navigation -->
      <?php if($page['main_navigation']):?>
        <div class="tabs searchDSATabs">
          <?php
            $menu_navigation = menu_navigation_links('menu-dsa-navigation');
              if ($menu_navigation):
                print theme('links__system_menu_dsa_navigation', array('links' => $menu_navigation, 'attributes' => array('id' => 'main_navigation', 'class' => array('resortNav', 'clearfix'))));
              endif;
          ?>
        </div>  
      <?php  endif; ?>
      <?php if($page['member_navigation']):?>
        <div class="tabs searchDSATabs dsaMemberTabs">
          <?php
            $menu_member_nav = menu_navigation_links('menu-dsa-member-navigation');            
            if ($menu_member_nav):
              print theme('links__system_menu_dsa_navigation', array('links' => $menu_member_nav, 'attributes' => array('id' => 'main_navigation', 'class' => array('resortNav', 'clearfix'))));
            endif;
          ?>
        </div>  
      <?php  endif; ?>
      <?php if($page['member_info']):
        print render($page['member_info']);
      endif; ?>
<!--End:DSA Navigation -->
<!--Start:Marquee(news_holder) -->
      <?php if($page['news_holder']): ?>
        <div class="topBgNoBorder clearfix">
          <div id="newsTickerHolder" class="clearfix fullWidth" style="">
            <div class="clearfix floatLeft tickerMid fullWidth">
              <div class="floatLeft tickerContent fullWidth">
                <?php print render($page['news_holder']); ?>
              </div>
            </div>    
          </div>
        </div>
      <?php endif; ?>
<!--End:Marquee(news_holder) -->
<!--Start:Mainpage -->
      <?php if($page['content']):?>
        <div id="mainContent">
          <?php print render($page['content']);?>
        </div>  
      <?php  endif; ?>
<!--End:Mainpage -->
    </div>
<!--End:ContentWrapper,SearchMember -->
  </div>
<!--End:Content -->
<!--Start:Footer -->
  <div id="footer">
      <div class="footerWrapper">
        <div style="width: 800px;" class="footernew clearfix floatLeft">
          <?php
          if($page['footer_column']):
            $footermenu1 = menu_navigation_links('menu-clubmahindra');
            if ($footermenu1):
              print theme('links__system_menu_clubmahindra', array('links' => $footermenu1, 'attributes' => array('id' => 'footer_column', 'class' => array('footerColumn', 'floatLeft'))));
            endif;
            
            $footermenu2 = menu_navigation_links('menu-region');
            if ($footermenu2):
              print theme('links__system_menu_region', array('links' => $footermenu2, 'attributes' => array('id' => 'footer_column', 'class' => array('footerColumn', 'floatLeft'))));
            endif;
            
            $footermenu3 = menu_navigation_links('menu-holiday-type');
            if ($footermenu3):
              print theme('links__system_menu_holiday_type', array('links' => $footermenu3, 'attributes' => array('id' => 'footer_column', 'class' => array('footerColumn', 'floatLeft'))));
            endif;
            
            $footermenu4 = menu_navigation_links('menu-terrain');
            if ($footermenu4):
              print theme('links__system_menu_terrain', array('links' => $footermenu4, 'attributes' => array('id' => 'footer_column', 'class' => array('footerColumn', 'floatLeft'))));
            endif;        
          endif;
          
          if($page['policy']):
            $footermenu5 = menu_navigation_links('menu-footer-two-top');
              if ($footermenu5):
                  print theme('links__system_menu_policy', array('links' => $footermenu5, 'attributes' => array('id' => 'policy', 'class' => array('footerColumn', 'floatLeft'))));
              endif;
          endif;
          
          if($page['social']):
            print render($page['social']);
          endif;
          ?>
        </div>
        <div  class="floatRight veriSignLogo">
            <?php
              if($page['secure']):
                print render($page['secure']);
              endif;
            ?>
        </div>
        <div class="clearfix fullWidth copyRight">
            <?php
              if($page['copyright']):
                print render($page['copyright']);
              endif;
            ?>
        </div>
      </div>
  </div>
<!--End:Footer -->
</div>  
<!--End:wrapper -->  