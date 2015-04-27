<?php

/**
 * @file
 * Settings functions and callbacks.
 */

function emf_campaign_monitor_settings() {
  $form = array();

  // info
  $form['emf_campaign_monitor_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#description' => t('Your Campaign Monitor API Key. See Campaign Monitor\'s <a href="http://www.campaignmonitor.com/api/required/">documentation</a> for more info.'),
    '#default_value' => variable_get('emf_campaign_monitor_api_key', ''),
    '#required' => TRUE,
  );
  $form['emf_campaign_monitor_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#description' => t('Your Campaign Monitor Client ID. See Campaign Monitor\'s <a href="http://www.campaignmonitor.com/api/required/">documentation</a> for more info.'),
    '#default_value' => variable_get('emf_campaign_monitor_client_id', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}