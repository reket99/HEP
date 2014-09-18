<?php
/**
* @file
*
* This is the template file for rendering the formexample DSA Registration Form.
* In this file each element of the form is rendered individually
* instead of the entire form at once, giving me the ultimate control
* over how my forms are laid out. I could also print the whole form
* at once - using the predefined layout in the module by
* printing $variables['dsa_registration'];
*
*/
 ?>
<!--Start:Content-->
<div class="dsaWelcomePage">
  <div class="dsaTopHeaderContent">
    <h1 class="dsaTopHeader"><?php print $variables['dsa_registration']['top_header']['title'];?></h1>
    <div class="dsaPointsList">
      <?php print $variables['dsa_registration']['top_header']['header_body'];?>
    </div>
  </div>
  <div class="welcomeImg">
    <div class="transbox" >
      <?php print $variables['dsa_registration']['left_panel']['title'];?>
      <div class="dsaLeftPanelContent">
        <?php print $variables['dsa_registration']['left_panel']['header_body'];?>
      </div>
      <div class="dsaLeftPanelImgContnr">
        <?php 
          $image_id = strip_tags($variables['dsa_registration']['left_panel']['image_val']);
          $imgpath = file_load($image_id)->uri;
          $img_url = file_create_url($imgpath);
        ?>
        <img src="<?php print $img_url;?>" title="DSA Register" class="fullWidth"/>
      </div>
    </div>
    <div class="welcomeForm ">
      <div class="label">
        <div class="dsaRightPanelHeaderDivBG"></div>
        <p class="dsaRightPanelHeaderDivContent">Then, go ahead and fill this form and we'll get in touch with you at the earliest.</span>
      </div>
        <div class="form">
    <form name="dsaRegisterFrm" action="DsaRegister" method="POST" class="dsaRegisterForm">
      <div id="errorMsg" class="validationErrMsg" style="display:none"><ul></ul></div>              
      <div class="bigdsavimg dsaRegisterDetailsForm">
        <div class="label"><h4>Allow us to know you better</h4></div>
        <div class="registration-section">
          <div class="section clearfix ">
            <div class="pdField">
              <div class="pdfieldName"><span class="asterik margin-left0">* </span><label>First Name</label></div>
              <div id="ErrFirstName" class="clearfix">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['First_Name']; ?>
                </div>
              </div>
            </div>
            <div class="pdField">
              <div class="pdfieldName"><span class="asterik margin-left0">* </span><label>Last Name</label></div>
              <div id="ErrLastName" class="clearfix normtxtbox">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['Last_Name']; ?>
                </div>
              </div>
            </div>
            <div class="pdField">
              <div class="pdfieldName"><label>Date Of Birth</label></div>
              <div id="ErrDOB" class="pdfieldField dob">
                <?php print $variables['dsa_registration']['drpFamilyDetail1dd']; ?>
                <?php print $variables['dsa_registration']['drpFamilyDetail1mm']; ?>
                <?php print $variables['dsa_registration']['drpFamilyDetail1yy']; ?>
              </div>
            </div>
            <div class="pdField">
              <div class="pdfieldName "><span class="asterik margin-left0">* </span><label>Business Type</label></div>
              <div id="errBuisType" class="pdfieldField smallSizeDrp">
                <?php print $variables['dsa_registration']['Business_Type']; ?>
                
              </div>                      
            </div>
            <div class="pdField">
              <div class="pdfieldName"><span class="asterik margin-left0">* </span><label>Industry</label></div>
              <div id="errIndustry" class="clearfix normtxtbox">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['Industry']; ?>
                </div>
              </div>
            </div>
            <div class="pdField">
              <div class="pdfieldName "><label>Current Monthly Turnover </label></div>
              <div class="pdfieldField smallSizeDrp">
                <?php print $variables['dsa_registration']['Current_Turnover']; ?>
                
              </div>                      
            </div>
            <div class="pdField">
              <div class="pdfieldName"><label>Office Space  (sq.ft)</label></div>
              <div id="offSpace" class="clearfix normtxtbox">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['Office_Space']; ?>
                </div>
              </div>
            </div>
            <div class="pdField">
              <div class="pdfieldName">
                <label>Prior experience of sales & marketing  (In years) </label>
              </div>
              <div class="txtRadio">
                <?php print $variables['dsa_registration']['priorExperience']; ?>
              </div>
            </div>
            <div class="clear"></div>
            <div id="expYrs" class="pdField" style="display:none;">
              <div class="pdfieldName ">
                <label>
                  <span class="asterik"> </span>
                </label>
              </div>
              <div id="ErrExp" class="clearfix normtxtbox">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['priorExperience_otherField']; ?>
                </div>
              </div>
            </div>
            <div class="clear"></div>
            <div class="pdField">
              <div class="pdfieldName">
                <label>How do you rate your knowledge of the timeshare industry?</label>
              </div>
              <div class="txtRadio clearfix" style="margin-top: 10px;">
                <?php print $variables['dsa_registration']['knowledgeRating']; ?>
              </div>
            </div>
            <div class="clear"></div>
            <div class="label"><h4>We can reach you at</h4></div>
            <div class="txtRadio clearfix label" style="padding-bottom: 10px;padding-right: 25px;" >
              <?php print $variables['dsa_registration']['rdModeOfenquiries']; ?>
            </div>                    
            <div class="pdField clearfix" id="country" style="display: none;">
              <div class="pdfieldName">
                <label><span class="asterik margin-left0"> * </span>Country</label>
              </div>
              <div id="ErrCountry" class="pdfieldField midSizeDrp floatLeft">
                <?php print $variables['dsa_registration']['Country_ID']; ?>
              </div>
              <div class="clear"></div>
              <div class="pdField" style="display:none;" id="otherCountry">                   
                <div class="pdfieldName"><label></label></div>
                <div class="clearfix normtxtbox floatLeft" style="padding-top: 5px;" >
                  <div class="txtField">
                    <?php print $variables['dsa_registration']['country_otherField']; ?>
                  </div>
                </div>
              </div>
              <input type="hidden" name="txtCountryName" id="txtCountryName" value="">
              <div id="loadState" style="display:none"><img src="<?php print base_path().drupal_get_path('theme', 'cmh_orange_theme') ?>/images/ajaxProcessing.gif" alt='Loading'/></div>
            </div>
            <div class="pdField clearfix">
              <div class="pdfieldName"><label><span class="asterik margin-left0"> * </span>State</label></div>
              <div id="ErrState" class="pdfieldField midSizeDrp floatLeft">
                <?php print $variables['dsa_registration']['State_ID']; ?>
              </div>
              <div class="clear"></div>
              <div class="pdField" style="display:none;" id="otherState">                   
                <div class="pdfieldName"><label></label></div>
                <div class="clearfix normtxtbox floatLeft" style="padding-top: 5px;" >
                  <div class="txtField">
                    <?php print $variables['dsa_registration']['state_otherField']; ?>
                  </div>
                </div>
              </div>
              <input type="hidden" name="txtStateName" id="txtStateName" value="">
              <div id="loadState" style="display:none"><img src="<?php print base_path().drupal_get_path('theme', 'cmh_orange_theme') ?>/images/ajaxProcessing.gif" alt='Loading'/></div>
            </div>
            <div class="pdField clearfix">
              <div class="pdfieldName"><label>City</label></div>                          
              <div id="ErrCity"  class="pdfieldField smallSizeDrp floatLeft">
                <?php print $variables['dsa_registration']['City_ID']; ?>
              </div>
              <div class="clear"></div>
              <div class="pdField" style="display:none;" id="otherCity">                    
                <div class="pdfieldName"><label></label></div>
                <div class="clearfix normtxtbox floatLeft" style="padding-top: 5px;" >
                  <div class="txtField">
                    <?php print $variables['dsa_registration']['city_otherField']; ?>
                  </div>
                </div>
              </div>
              <input type="hidden" name="txtCityName" id="txtCityName" value="">
            </div>
            <div class="pdField">
              <div class="pdfieldName"><span class="asterik margin-left0">* </span><label>Mailing Address</label></div>                          
              <div class="pdfieldField">
                <div id="ErrMailingAddress" class="txtAreaMask clearfix largetxtArea">
									<?php print $variables['dsa_registration']['Mailing_Address']; ?>
								</div>
              </div>
            </div>
            <div class="pdField clearfix">
              <div class="pdfieldName"><label></label></div>
              <div class="floatLeft">
                <div id="checkAddressLimit"></div>
              </div>            
            </div>
            <div class="pdField">
              <div class="pdfieldName"><span class="asterik margin-left0">* </span><label>Email Address</label></div>
              <div id="ErrEmailId" class="clearfix normtxtbox">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['Email_ID']; ?>
                </div>
              </div>
            </div>
            <div class="pdField">
              <div class="pdfieldName">
                <label>Landline Number</label>
              </div>
              <div class="clearfix">
                <div id="ErrCountryCode" class="clearfix smalltxtbox floatLeft">
                  <div class="txtField">
                    <?php print $variables['dsa_registration']['Landline_No_CountryC']; ?>
                  </div>
                </div>
                <div class="dash">-</div>
                <div id="ErrAreaCode" class="clearfix smalltxtbox floatLeft">
                  <div class="txtField">
                    <?php print $variables['dsa_registration']['Landline_No_StateC']; ?>
                  </div>
                </div>
                <div class="dash">-</div>
                <div id="ErrTelephone" class="clearfix smalltxtbox floatLeft">
                  <div class="txtField">
                    <?php print $variables['dsa_registration']['Landline_No_TelephoneC']; ?>
                  </div>
                </div>              
              </div>
            </div>
            <div class="pdField clearfix">
              <div class="pdfieldName"><span class="asterik margin-left0"> * </span><label>Mobile Number</label></div>
              <div id="ErrMobile" class="clearfix normtxtbox floatLeft">
                <div class="txtField">
                  <?php print $variables['dsa_registration']['MobileNumber']; ?>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>              
    </form>
    <div class="clearfix">
      <div class="actionButton clearfix">
        <div class="actionButtonBorder floatLeft marginLeft190">
          <a title="Submit" href="javascript:void(0)" id="register">
            <span class="left"></span><span class="mid">Submit</span><span class="right"></span>
          </a>
        </div>
        <div class="greyBox_small floatLeft marginleft15">
          <a id="btnResetForm" class="" title="Reset" href="javascript:void(0)">
            <span class="left"></span><span class="mid">Reset</span><span class="right"></span>
          </a>
        </div>
      </div>          
    </div>
    <?php print $variables['dsa_registration']['hidden']; ?>
  </div>
  </div>
</div>
</div>
<!--End:Content-->
<!-- Thick box for RESET button -->
<div id="resetConfirmDialog" class="modalMessage" style="position: relative;display: none;">
  <div class="diagPopupBox">
    <div class="popupHeading">
      <h2>Please Confirm</h2>
    </div>
    <div class="dialogMessage">Unsaved information will be lost. Are you sure you want to reset?</div>
    <div class="dialogButtons">
      <div class="actionButtonSmall dialogLeftbtn">
        <a class="clearfix dialogOk" href="javascript:void(0);" id="yesBtn" onclick="" title="Yes"> <span
          class="left"></span> <span class="mid">Yes</span> <span
          class="right"></span>
        </a>
      </div>
      <div class="greyBox_small dialogRightbtn">
        <a class="clearfix dialogCancel" href="javascript:void(0);"
          title="No" onClick="tb_remove();"> <span class="left"></span> <span
          class="mid">No</span> <span class="right"></span>
        </a>
      </div>
    </div>
  </div>
</div>