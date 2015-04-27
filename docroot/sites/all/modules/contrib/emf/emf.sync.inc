<?php

/**
 * @file
 * Cron synchronisation functions.
 */

/**
 * Synchronise structure, requests and subscriptions (if allowed).
 */
function emf_sync() {
  // fixme : what if a) request for subscription is done on site b) subscription is done somewhere else c) unsubscription is done somewhere else d) push of request is done

  // sync structure
  if (_emf_allow_sync('structure')) {
    emf_sync_lists();
    emf_sync_fields();
  }

  // sync requests
  if (_emf_allow_sync('requests')) {
    emf_sync_push_requests();
  }

  // sync subscriptions
  if (_emf_allow_sync('subscriptions')) {
    emf_sync_subscriptions();
  }
}

/**
 * Synchronise mailing lists.
 */
function emf_sync_lists() {
  $api_lists = emf_plugin_invoke('get_lists', array());
  $db_lists = emf_db_get_lists();

  $name = variable_get('emf_default_name', '!name_api');
  $name_action = variable_get('emf_default_name_action', 'Subscribe to !name');
  $name_action_long = variable_get('emf_default_name_action_long', 'If you subscribe to !name, we will keep you up to date by sending newsletters.');
  $status = variable_get('emf_default_status', TRUE);

  // check for new and missing lists
  if ($api_lists !== FALSE && $db_lists !== FALSE) {
    $added = array_diff_key($api_lists, $db_lists);
    $missing = array_diff_key($db_lists, $api_lists);
    $other = array_intersect_key($api_lists, $db_lists);

    foreach ($added as $list) {
      emf_db_save_list($list->lid, $list->name_api, TRUE, $name, $status, $name_action, $name_action_long, '', '');
    }

    foreach ($missing as $lid => $list) {
      emf_db_save_list($list->lid, $list->name_api, FALSE, $list->name, $list->status, $list->name_action, $list->name_action_long, $list->description, $list->language);
    }

    foreach ($other as $lid => $list) {
      if ($api_lists[$lid]->name_api != $db_lists[$lid]->name_api) {
        $list_api = $api_lists[$lid];
        $list_db = $db_lists[$lid];
        emf_db_save_list($list_db->lid, $list_api->name_api, $list_db->status_api, $list_db->name, $list_db->status, $list_db->name_action, $list_db->name_action_long, $list_db->description, $list->db->language);
      }
    }
  }

  // check lists that were lost but now found again
  foreach ($db_lists as $list) {
    if ($list->status_api == FALSE && array_key_exists($list->lid, $api_lists)) {
      emf_db_save_list($list->lid, $list->name_api, TRUE, $list->name, $list->status, $list->name_action, $list->name_action_long, $list->description, $list->language);
    }
  }
}

/**
 * Synchronise fields of all lists that are avaiable in database.
 */
function emf_sync_fields() {
  $lists = emf_db_get_lists();

  foreach ($lists as $list) {
    $mapping = array();

    $fields = emf_plugin_invoke('get_custom_fields', array($list->lid));

    // default field : mail
    if (!isset($list->field_mapping['mail'])) {
      $mapping['mail'] = new stdClass();
      if (module_exists('token')) {
        $mapping['mail']->mapping_type = 'token';
        $mapping['mail']->mapping_value = '[user:mail]';
      }
      else {
        $mapping['mail']->mapping_type = 'php';
        $mapping['mail']->mapping_value = 'return $account->mail;';
      }
      $mapping['mail']->weight = 0;
    }
    else {
      $mapping['mail'] = $list->field_mapping['mail'];
    }
    $mapping['mail']->key = 'mail';
    $mapping['mail']->name = 'Mail';
    $mapping['mail']->type = 'text';
    $mapping['mail']->show_anonymous = TRUE;
    $mapping['mail']->common_form_show = TRUE;

    if ($fields) {

      // custom fields
      foreach ($fields as $field) {
        // this way we're deleting removed fields

        if (isset($list->field_mapping[$field->key])) {
          $mapping[$field->key] = $list->field_mapping[$field->key];
        }
        else {
          $mapping[$field->key] = new stdClass();
          $mapping[$field->key]->weight = 0;
        }
        $mapping[$field->key]->key = $field->key;
        $mapping[$field->key]->name = $field->name;
        $mapping[$field->key]->type = $field->type;
        if (isset($field->options) && $field->options) {
          $mapping[$field->key]->options = $field->options;
        }
      }
    }

    emf_db_save_field_mapping($list->lid, $mapping);
  }
}

/**
 * Push all (un)subscription requests
 */
function emf_sync_push_requests() {
  // fetch and count all requests
  $requests = array_values(emf_db_get_requests());
  $count_requests = count($requests);

  // fetch lists
  $lists = emf_db_get_lists();

  // init counter
  $count = 0;

  // store maximum execution time
  $max_execution_time = ini_get('max_execution_time') == 0 ? 120 : ini_get('max_execution_time');

  // loop through all requests ...
  while ($count < $count_requests) {
    // stop 5 seconds before script time out.
    if (($max_execution_time - 5) < round(timer_read('page') / 1000)) break;

    // fetch the request
    $request = $requests[$count];

    // fetch list for request
    $list = $lists[$request->lid];

    // fetch field mapping for list of request
    $mapping = $list->field_mapping;

    // only push fields that are still availabe on the list
    $fields = array_intersect_key($request->fields, $mapping);

    // push it
    $success = FALSE;
    if ($request->type == 'subscribe') {
      $success = emf_plugin_invoke('subscribe', array($request->mail, $fields, $request->lid));
    }
    else {
      $success = emf_plugin_invoke('unsubscribe', array($request->mail, $request->lid));
    }

    // if push succeeded or failed too many times, request can be deleted
    if ($success || $request->fails > variable_get('emf_max_request_fails', 5)) {
      emf_db_delete_request($request->mail, $request->lid);
      if ($request->fails > variable_get('emf_max_request_fail', 5)) {
        watchdog('emf', t('%type request to %list cancelled for %mail after @count failed push attempts.', array(
          '%type' => $request->type,
          '%list' => $list->name_clean,
          '%mail' => $request->mail,
          '@count' => $request->fails,
        )), WATCHDOG_ERROR);
      }
    }
    else {
      $request->fails += 1;
      emf_db_save_request($request->type, $request->mail, $request->lid, $request->fields, $request->fails);
    }

    // count up
    $count++;
  }
}

/**
 * Synchronise all subscriptions
 */
function emf_sync_subscriptions() {
  $last_sync = emf_plugin_invoke('unix_to_service_time', array(variable_get('emf_last_sync_subscriptions', 0)));

  $lists = emf_db_get_lists(TRUE);
  foreach ($lists as $lid => $list) {
    // fetch requests
    $requests = emf_db_get_requests();

    // fetching subscriptions
    $subscribed = emf_plugin_invoke('get_subscribers_subscribed', array($last_sync, $lid));
    $unsubscribed = emf_plugin_invoke('get_subscribers_unsubscribed', array($last_sync, $lid));

    // check subscriptions
    if ($subscribed !== FALSE && count($subscribed) > 0) {
      foreach ($subscribed as $mail) {
        // if a request is pending for this address, ignore subscription status
        if (in_array($mail, $requests)) continue;

        // set address as subscripted to
        emf_db_save_subscription($mail, $lid);
      }
    }

    // check unsubscriptions
    if ($unsubscribed !== FALSE && count($unsubscribed) > 0) {
      foreach ($unsubscribed as $mail) {
        // if a request is pending for this address, ignore subscription status
        if (in_array($mail, $requests)) continue;

        // delete address as subscripted to
        emf_db_delete_subscription($mail, $lid);
      }
    }
  }
  variable_set('emf_last_sync_subscriptions', $_SERVER['REQUEST_TIME']);
}