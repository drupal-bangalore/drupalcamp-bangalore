<?php

/**
 * @file
 * Page callbacks.
 */

function emf_page($list = NULL) {
  if (!empty($list)) {
    drupal_set_title(emf_page_title($list));
  }
  module_load_include('inc', 'emf', 'emf.form');
  // fetch form
  $form = drupal_get_form('emf_subscription_list_form', $list ? $list->lid : NULL);
  // check if form is empty
  if (isset($form['lists'])) {
    return $form;
  }
  else {
    drupal_set_message(t('You are not allowed to view this subscription form or are already subscribed to this list.'));
    drupal_access_denied();
  }
}