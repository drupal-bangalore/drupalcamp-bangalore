<?php

/**
 * Implements hook_preprocess_page().
 */
function drupalcamp_preprocess_page(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
  $logo = $variables['is_front'] ? 'banner-logo.png' : 'banner-logo-small.png';
  $variables['logo'] = file_create_url(drupal_get_path('theme', 'drupalcamp') . '/images/' . $logo);
  if (current_path() == 'node/23' && !user_access('administer conferences')) {
    unset($variables['tabs']);
  }
}
