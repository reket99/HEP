<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php 
//echo "<pre>";print_r($view);die;
$files = explode(', ', $fields['field_upload_file']->content);
$query = db_select('file_managed', 'f', array('fetch' => PDO::FETCH_ASSOC));
$query->leftJoin('field_data_field_upload_file', 'u', 'u.field_upload_file_fid = f.fid');
$query->fields('f', array('uri'));
$query->condition('f.fid', $files, 'IN');
$data = $query->execute()->fetchCol();
$file_count = count($data);
?>
<?php 
	if(pageId == 'NewsUpdates') {

		$path_parts = pathinfo(file_create_url($data[0]));
		$file_ext = $path_parts['extension'];
		if($file_ext == 'jpg' || $file_ext == 'jpeg') {
			$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/jpg.png';
		} 
		else if($file_ext == 'eps') {
			$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/Eps.png';
		} 
		else if($file_ext == 'pdf') {
			$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/Pdf.png';
		}
		else {
			$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/download.png';
		} 
?>
		<div class="news-wrapper bottom-border-dotted">														
			<!--<div class="section-title"><?php //print $fields['title']->content; ?></div>-->
			<div class="news-section">
				<a href="<?php print file_create_url($data[0]); ?>" target="_blank" title="">
				<span class="news-section-img">
					<img width="36px" border="" height="32px" src="<?php echo $imgicon; ?>" alt="PDF" />																		
				</span>
				<span class="news-section-content"><?php print $fields['title']->content; ?></span>
				</a>
			</div>																				
		</div>		

<?php } else {

		if ($file_count > 1 ) { ?>
			<div class="news-wrapper bottom-border-dotted">														
				<div class="section-title"><?php print $fields['title']->content; ?></div>
				<?php  
					foreach($data as $files) {
						$path_parts = pathinfo(file_create_url($files));
						$file_ext = $path_parts['extension'];
						if($file_ext == 'jpg' || $file_ext == 'jpeg') {
							$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/jpg.png';
						} 
						else if($file_ext == 'eps') {
							$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/Eps.png';
						}
						else if($file_ext == 'pdf') {
							$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/Pdf.png';
						}
				?>
										
				<div class="news-section">
					<a href="<?php print file_create_url($files); ?>" target="_blank" title="">
						<span class="news-section-img">
							<img width="36px" border="" height="32px" src="<?php echo $imgicon; ?>" alt="PDF" />																			
						</span>
						<span class="news-section-content">Download as <?php echo strtoupper($file_ext); ?></span>
					</a>
				</div>	
			<?php }	?>	
			</div>	
			<?php }
				else {		
					$path_parts = pathinfo(file_create_url($data[0]));
					$file_ext = $path_parts['extension'];
					if($file_ext == 'jpg' || $file_ext == 'jpeg') {
						$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/jpg.png';
					} 
					else if($file_ext == 'eps') {
						$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/Eps.png';
					} 
					else if($file_ext == 'pdf') {
						$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/Pdf.png';
					}
					else {
						$imgicon = base_path() . drupal_get_path('theme', 'cmh_dsa_theme') . '/images/download.png';
					}
			?>	
			<div class="news-wrapper bottom-border-dotted">														
				<div class="section-title"><?php print $fields['title']->content; ?></div>
				<div class="news-section">
					<a href="<?php print file_create_url($data[0]); ?>" target="_blank" title="">
					<span class="news-section-img">
						<img width="36px" border="" height="32px" src="<?php echo $imgicon; ?>" alt="PDF" />																		
					</span>
					<span class="news-section-content"><?php if($fields['title']->content == 'Pre-Approved Collaterals') echo 'Standees Artwork - '; ?>
					Download as <?php echo strtoupper($file_ext); ?></span>
					</a>
				</div>																				
			</div>									
			<?php }
	}		?>						
