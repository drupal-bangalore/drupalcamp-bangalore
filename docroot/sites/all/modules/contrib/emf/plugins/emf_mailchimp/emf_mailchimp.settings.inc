<?php
// $Id: emf_mailchimp.settings.inc,v 1.1 2009/10/28 18:59:01 davyvandenbremt Exp $

/**
 * @file
 * Settings functions and callbacks.
 *
 * @author Davy Van Den Bremt
 */

function emf_mailchimp_settings() {
  $form = array();

  // info
  $form['emf_mailchimp_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#description' => t('Your MailChimp API Key.'),
    '#default_value' => variable_get('emf_mailchimp_api_key', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}