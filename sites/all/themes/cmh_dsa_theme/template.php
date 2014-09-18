<?php
/**
 * @file         template.php
 * @version      1.0.0
 * @author       CTS
 * @desc         Override or insert variables into the page template.
 * @date         
 * @copyright    Copyright (c) 2013, Club Mahindra Holidays.  All rights reserved.
 *               Property of Club Mahindra Holidays.  This file cannot be used or altered
 *               in anyway without expressed written permission from 
 *               Club Mahindra Holidays.
 * @modified by  
 * @modified on  
 */
function cmh_dsa_theme_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
	//echo '<pre>'; print_r($variables);
  $heading = $variables['heading'];
  global $language_url;
  $output = '';
	
  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';
		
    $num_links = count($links);
    $i = 1;   
    foreach ($links as $key => $link) {
			$class = array();
			
      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      
      //display the first links in footer one region without <a> by 362137
      if (isset($attributes['id']) && !empty($attributes['id'])) {
        if ($attributes['id'] == 'footer') {
          if ($i == 1)
            unset($link['href']);
        }
      }
      $class[] = cmh_dsa_theme_classforuli($link['title']);
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
				
      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= $link['title'];
      }
      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }
  return $output;
}

/**
 * Function used to return all the sub menus data for a main menu
 * 
 * @param $menu contains the menu name
 * @param $title contains the name of the menu title
 * @return array/boolean returns list of sub menus or false if no list
 */
function cmh_dsa_theme_submenu_tree_all_data($menu = 'primary-links', $title) {
	$tree = menu_tree_all_data($menu);
	foreach ($tree as $branch) {
		if ($branch['link']['title'] == $title){
			$childtree = $branch['below'];
			break;
		}
	}
				
	if (count($childtree) > 0) {
		return $childtree;
	}
	else{
		return FALSE;
	}
}

/**
 * function for changing the class name according to title
 * 
 * @param $link contains the menu name
 * @return string returns the menu name after removing special characters
 */
function cmh_dsa_theme_classforuli($link){
    $titlelower = strtolower($link);
    $regex = '/[^A-Za-z0-9]/';
    if(preg_match($regex, $titlelower)):
		  $titlelower = preg_replace($regex, "-", $titlelower);
    endif;
    return $titlelower;
}

/**
 * Returns HTML for a form element.
 *
 * Each form element is wrapped in a DIV container having the following CSS
 * classes:
 * - form-item: Generic for all form elements.
 * - form-type-#type: The internal element #type.
 * - form-item-#name: The internal form element #name (usually derived from the
 *   $form structure and set via form_builder()).
 * - form-disabled: Only set if the form element is #disabled.
 *
 * In addition to the element itself, the DIV contains a label for the element
 * based on the optional #title_display property, and an optional #description.
 *
 * The optional #title_display property can have these values:
 * - before: The label is output before the element. This is the default.
 *   The label includes the #title and the required marker, if #required.
 * - after: The label is output after the element. For example, this is used
 *   for radio and checkbox #type elements as set in system_element_info().
 *   If the #title is empty but the field is #required, the label will
 *   contain only the required marker.
 * - invisible: Labels are critical for screen readers to enable them to
 *   properly navigate through forms but can be visually distracting. This
 *   property hides the label for everyone except screen readers.
 * - attribute: Set the title attribute on the element to create a tooltip
 *   but output no label element. This is supported only for checkboxes
 *   and radios in form_pre_render_conditional_form_element(). It is used
 *   where a visual label is not needed, such as a table of checkboxes where
 *   the row and column provide the context. The tooltip will include the
 *   title and required marker.
 *
 * If the #title property is not set, then the label and any required marker
 * will not be output, regardless of the #title_display or #required values.
 * This can be useful in cases such as the password_confirm element, which
 * creates children elements that have their own labels and required markers,
 * but the parent element should have neither. Use this carefully because a
 * field without an associated label can cause accessibility challenges.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #title_display, #description, #id, #required,
 *     #children, #type, #name.
 *
 * @ingroup themeable
 * Created By : 351462
 * Description: To remove the "form_item" class from form design
 */
function cmh_dsa_theme_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  //$attributes['class'] = array('form-item');
  $attributes['class'] = array('');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  //$output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  $output = '';

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  //$output .= "</div>\n";

  return $output;
}

/**
 * Hook function for changing the output of menu block
 * 
 * @param $variables contains the data of the menu block variables
 * @return string returns the menu block output
 */
function cmh_dsa_theme_menu_tree__menu_block($variables){
  return '<ul>' . $variables['tree'] . '</ul>';
}