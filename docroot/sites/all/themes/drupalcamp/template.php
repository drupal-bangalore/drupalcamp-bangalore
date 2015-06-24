<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * drupalcamp theme.
 */

function drupalcamp_menu_link(array $variables) {
	global $user;
	if ($variables ['element']['#title'] == 'My account' && $variables ['element']['#href'] == 'user'){
		$variables ['element']['#href'] = 'user/'.$user->uid.'/edit';
	}
	$element = $variables ['element'];
	$sub_menu = '';

	if ($element ['#below']) {
	$sub_menu = drupal_render($element ['#below']);
	}
	$output = l($element ['#title'], $element ['#href'], $element ['#localized_options']);
	return '<li' . drupal_attributes($element ['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}