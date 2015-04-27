<?php

/**
 * @file
 * Blocks
 */

function emf_subscription_list_form($form, &$form_state, $lid = NULL, $hide_subscribed = TRUE) {

  drupal_add_css(drupal_get_path('module', 'emf') . '/emf-style.css');

  $form = array();

  // fetching list object
  if ($lid) {
    $lists = array($lid);
  }
  else {
    $lists = emf_db_get_lists(TRUE);
    $lists = array_keys($lists);
  }

  // if user is logged in, only allow subscription to lists not subscribed to yet
  if (!user_is_anonymous() && $hide_subscribed) {
    global $user;

    $result = db_query("SELECT lid FROM {emf_subscription} WHERE mail = :mail", array(':mail' => $user->mail));

    $subscribed_lists = array();
    while ($row = $result->fetchObject()) {
      $subscribed_lists[] = $row->lid;
    }

    $lists = array_diff($lists, $subscribed_lists);
  }

  // check for each list if user has access and if language is ok
  $tmp = array();
  foreach ($lists as $list) {
    $show_list = FALSE;

    if (emf_list_visibile($list)) {
      $tmp[] = $list;
    }
  }
  $lists = $tmp;

  if (count($lists) == 0) {
    return;
  }

  if (user_is_anonymous() || count($lists) == 1) {
    $list = emf_db_get_list($lists[0]);

    if (!empty($list->name_action_long_clean)) {
      $form['action_long'] = array(
        '#type' => 'markup',
        '#value' => $list->name_action_long_clean,
      );
    }
  }

  if (user_is_anonymous()) {
    $form['fields']['#tree'] = TRUE;

    // mail field
    $form['fields']['mail'] = array(
      '#type' => 'textfield',
      '#title' => t('E-mail'),
      '#required' => TRUE,
    );

    // custom fields
    foreach ($lists as $list) {
      $list = emf_db_get_list($list);

      foreach ($list->field_mapping as $field) {

        // don't show field in some occasions
        if (!$field->show_anonymous) continue;
        if ($lid == NULL && !$field->common_form_show) continue;

        // set mail field weight
        if (in_array($field->key, array('mail'))) {
          $form['fields']['mail']['#weight'] = $field->weight;
        }

        // display field
        switch ($field->type) {
          case 'text':
            $form['fields'][$field->key] = array(
              '#type' => 'textfield',
              '#title' => t($field->name),
              '#weight' => $field->weight,
            );
            break;
          case 'select_one':
          case 'select_many':
          case 'dropdown':
            $form['fields'][$field->key] = array(
              '#type' => 'select',
              '#title' => t($field->name),
              '#options' => drupal_map_assoc($field->options),
              '#multiple' => $field->type == 'select_many',
              '#weight' => $field->weight,
            );
            break;
        }
      }
    }
  }

  if (!user_is_anonymous() || count($lists) > 1) {
    $options = array();
    foreach ($lists as $list) {
      $list = emf_db_get_list($list);
      $options[$list->lid] = $list->name_action_clean;
    }

    $form['lists'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Newsletters'),
      '#options' => $options,
    );
  }
  else {
    // saving the list id in a hidden field
    $form['lists'] = array(
      '#type' => 'hidden',
      '#value' => $lists[0],
    );
  }

  // submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Subscribe'),
  );

  return $form;
}

function emf_subscription_list_form_validate($form, &$form_state) {
  if (user_is_anonymous()) {
    $mail = $form_state['values']['fields']['mail'];
    if (!valid_email_address($mail)) {
      form_set_error('mail', t('Not a valid e-mail address.'));
    }
  }
}

function emf_subscription_list_form_submit($form, &$form_state) {
  $lists = array();

  if (is_array($form_state['values']['lists'])) {
    $lists = array_keys(array_filter($form_state['values']['lists']));
  }
  else {
    $lists[] = $form_state['values']['lists'];
  }

  foreach ($lists as $lid) {

    // fetch list info
    $list = emf_db_get_list($lid);

    if (user_is_anonymous()) {
      // anonymous user
      $field_values = $form_state['values']['fields'];

      $mail = $field_values['mail'];
      unset($field_values['mail']);
    }
    else {
      // registered user
      $field_values = emf_helpers_parse_field_values($list->lid);

      $mail = $field_values['mail'];

      unset($field_values['mail']);
    }

    // subscribe user
    emf_helpers_subscribe($mail, $list->lid, $field_values);

    drupal_set_message(t('You have now been subscribed to the mailing list !list', array('!list' => t($list->name_clean))));
  }
}
