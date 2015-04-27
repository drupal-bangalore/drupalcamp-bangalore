<?php

/**
 * @file
 * Settings functions and callbacks.
 */

function emf_settings_advanced() {
  $form = array();

  // sync interval options
  $sync_interval_options = array();
  $minute = 60;
  $sync_interval_options = drupal_map_assoc(array(1 * $minute, 5 * $minute, 10 * $minute, 15 * $minute, 30 * $minute, 45 * $minute, 60 * $minute, 120 * $minute, 180 * $minute, 240 * $minute), 'format_interval');
  $sync_interval_options[-1] = t('Never (disable)');
  $sync_interval_options[0] = t('Every cron run');
  ksort($sync_interval_options);

  // account
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Account handling'),
    '#collapsible' => TRUE,
  );
  $form['account']['emf_account_status_sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unsubscribe when account is deleted'),
    '#description' => t('When a user\'s account is deleted on this website, unsubscribe the corresponding e-mail address from all lists.'),
    '#default_value' => variable_get('emf_account_status_sync', FALSE),
  );

  // synchronisation settings
  $form['sync'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synchronisation'),
    '#collapsible' => TRUE,
  );
  $form['sync']['emf_sync_requests_interval'] = array(
    '#type' => 'select',
    '#title' => t('Requests synchronisation interval'),
    '#description' => t('Specify the maximum time before subscriptions are pushed.'),
    '#options' => $sync_interval_options,
    '#default_value' => variable_get('emf_sync_requests_interval', 0),
  );
  $form['sync']['emf_sync_structure_interval'] = array(
    '#type' => 'select',
    '#title' => t('Struture synchronisation interval'),
    '#description' => t('Specify the maximum time before the structure (lists and fields) are synced.'),
    '#options' => $sync_interval_options,
    '#default_value' => variable_get('emf_sync_structure_interval', 0),
  );
  $form['sync']['emf_sync_subscriptions_interval'] = array(
    '#type' => 'select',
    '#title' => t('Subscriptions synchronisation interval'),
    '#description' => t('Specify the maximum time before the subscriptions are synced.'),
    '#options' => $sync_interval_options,
    '#default_value' => variable_get('emf_sync_subscriptions_interval', 0),
  );

  return system_settings_form($form);
}

function emf_settings_tools() {
  $form = array();

  // developer settings
  $form['emf_sync'] = array(
    '#type' => 'submit',
    '#value' => t('Resync subscriptions synchronisation.'),
  );

  return $form;
}

function emf_settings_tools_submit($form, &$form_state) {
  variable_set('emf_last_sync_subscriptions', 0);
  drupal_set_message(t('Subscriptions synchronisation successfully reset. Next time subscriptions are synchronised, all states will be checked.'));
}

function emf_settings_defaults() {
  // status
  $form['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default status'),
    '#collapsible' => TRUE,
  );
  $form['status']['emf_default_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate on this site'),
    '#description' => t('Default value for the status of the list. When a new list is synced, this will be the default status for this list. If a list is not activated, it\'s fields and subscriptions will not be synced with your e-mail marketing service. Subscription will not be possible and no subscription block will be available for the list.'),
    '#default_value' => variable_get('emf_default_status', TRUE),
  );

  // info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Info'),
    '#collapsible' => TRUE,
  );
  $form['info']['emf_default_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('Default value for the name of the list. When a new list is synced, this will be the default name for this list. This can differ from the name specified in your e-mail marketing service. An example of where the list name is used is in the subscription block title. You can use !name as a replacement variable.', array('!name' => '!name')),
    '#default_value' => variable_get('emf_default_name', '!name_api'),
    '#required' => TRUE,
  );
  $form['info']['emf_default_name_action'] = array(
    '#type' => 'textfield',
    '#title' => t('Action name'),
    '#description' => t('Default value for the action name of the list. When a new list is synced, this will be the default action name for this list. An example of where the list\'s action name is used is in the subscription form checkboxes. You can use !name and !name_api as replacement variables.', array('!name_api' => '!name_api', '!name' => '!name')),
    '#default_value' => variable_get('emf_default_name_action', 'Subscribe to !name'),
    '#required' => TRUE,
  );
  $form['info']['emf_default_name_action_long'] = array(
    '#type' => 'textfield',
    '#title' => t('Long action name'),
   '#description' => t('Default value for the long action name of the list. When a new list is synced, this will be the default long action name for this list. An example of where the list\'s long action name is used is in the subscription form intro text for anonymous users. You can use !name and !name_api as replacement variables.', array('!name_api' => '!name_api', '!name' => '!name')),
    '#default_value' => variable_get('emf_default_name_action_long', 'If you subscribe to !name, we will keep you up to date by sending newsletters.'),
  );

  return system_settings_form($form);
}